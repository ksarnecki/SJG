#include "CSPattern.h"

AnsiString CSPattern::name() {
  return "Pattern";
}

AnsiString CSPattern::rename() {
  return "System.Text.RegularExpressions.Regex";
}

Expression CSPattern::changeMethod(const MultiIdentifier& mi) {
  Expression obj = mi.getLex();
  Expression fun = mi.getRex();
  
  if(obj.isIdentifier() && obj.asIdentifier().getValue() == name()) {
    //metoda statyczna
    if(fun.isIdentifier()) {
      //
    } else if(fun.isFunctionCallExpression()) {
      FunctionCallExpression fce = fun.asFunctionCallExpression();
      if(fce.getName().isIdentifier()) {
        AnsiString method = fce.getName().asIdentifier().getValue();
        CallParams p = fce.getParams();
        if(method == "compile") {
          //zamiana statycznej metody na konstuktor
          CreatingExpression ce = CreatingExpression(Expression::createIdentifier(IdentifierExpression(rename())), p);
          return Expression::createCreatingExpression(ce);
        }
      }
    }      
  } else {
    if(fun.isIdentifier()) {
      //zmienne
      AnsiString method = fun.asIdentifier().getValue();
      if(method=="length") {
        return Expression::createIdentifier(IdentifierExpression("Length"));
      }
    } else if(fun.isFunctionCallExpression()) {
      //metody obiektowe
      FunctionCallExpression fce = fun.asFunctionCallExpression();
      if(fce.getName().isIdentifier()) {
        AnsiString method = fce.getName().asIdentifier().getValue();
        CallParams p = fce.getParams();
        if(method=="matcher") {
          MultiIdentifier m = MultiIdentifier(obj, Expression::createIdentifier(IdentifierExpression("Match")));
          FunctionCallExpression fce = FunctionCallExpression(Expression::createMultiIdentifier(m), p);
          return Expression::createFunctionCallExpression(fce);
        }
      }
    } 
  }
  return Expression::createEmpty();
}