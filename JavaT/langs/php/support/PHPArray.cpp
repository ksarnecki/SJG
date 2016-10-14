#include "PHPArray.h"

AnsiString PHPArray::name() {
  return "int[]";
}

Expression PHPArray::changeMethod(const MultiIdentifier& mi) {
  Expression obj = mi.getLex();
  Expression fun = mi.getRex();
  
  if(obj.isIdentifier() && obj.asIdentifier().getValue() == name()) {
    //metody statyczna
  } else {
    if(fun.isIdentifier()) {
      //zmienne
      AnsiString method = fun.asIdentifier().getValue();
      if(method=="length") {
        CallParams p = CallParams();
        p.Insert(obj);
        FunctionCallExpression fce = FunctionCallExpression(Expression::createIdentifier(IdentifierExpression("count")),p);
        return Expression::createFunctionCallExpression(fce);
      }
    } else if(fun.isFunctionCallExpression()) {
      //metody obiektowe
      FunctionCallExpression fce = fun.asFunctionCallExpression();
      if(fce.getName().isIdentifier()) {
        AnsiString method = fce.getName().asIdentifier().getValue();
        CallParams p = fce.getParams();
         if(method=="Size") {
          FunctionCallExpression fce = FunctionCallExpression(Expression::createIdentifier(IdentifierExpression("Count")),p);
          MultiIdentifier m = MultiIdentifier(obj, Expression::createFunctionCallExpression(fce));
          return Expression::createMultiIdentifier(m);
        }
      }
    } 
  }
  return Expression::createEmpty();
}