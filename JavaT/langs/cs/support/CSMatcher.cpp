#include "CSMatcher.h"

AnsiString CSMatcher::name() {
  return "Matcher";
}

AnsiString CSMatcher::rename() {
  return "System.Text.RegularExpressions.Match";
}

Expression CSMatcher::changeMethod(const MultiIdentifier& mi) {
  Expression obj = mi.getLex();
  Expression fun = mi.getRex();
  
  if(obj.isIdentifier() && obj.asIdentifier().getValue() == name()) {
    //metoda statyczna   
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
        if(method=="find") {
          MultiIdentifier m = MultiIdentifier(obj, Expression::createIdentifier(IdentifierExpression("Success")));
          return Expression::createMultiIdentifier(m);
        }
        if(method=="group") {
          if(p.Size()>0) {
            MultiIdentifier m = MultiIdentifier(obj, Expression::createIdentifier(IdentifierExpression("Groups")));
            ArrayIdentifier arr = ArrayIdentifier(Expression::createMultiIdentifier(m), p[0]);
            MultiIdentifier m2 = MultiIdentifier(Expression::createArrayIdentifier(arr),Expression::createIdentifier(IdentifierExpression("Value")));
            return Expression::createMultiIdentifier(m2);
          }
        }
      }
    } 
  }
  return Expression::createEmpty();
}