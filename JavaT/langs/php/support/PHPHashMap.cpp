#include "PHPHashMap.h"
#include <cstdio>

AnsiString PHPHashMap::name() {
  return "HashMap";
}

Expression PHPHashMap::changeMethod(const MultiIdentifier& mi) {
  Expression obj = mi.getLex();
  Expression fun = mi.getRex();
  
  if(obj.isIdentifier() && obj.asIdentifier().getValue() == name()) {
    //metoda statyczna
    printf("metoda statyczna\n");
  } else {
    
    if(fun.isIdentifier()) {
      //zmienne
    } else if(fun.isFunctionCallExpression()) {
      //metody obiektowe
      FunctionCallExpression fce = fun.asFunctionCallExpression();
      if(fce.getName().isIdentifier()) {
        AnsiString method = fce.getName().asIdentifier().getValue();
        CallParams p = fce.getParams();
        if(method=="get") {
          ArrayIdentifier arr = ArrayIdentifier(obj, p[0]);
          return Expression::createArrayIdentifier(arr);
        }
        if(method=="put") {
          ArrayIdentifier arr = ArrayIdentifier(obj, p[0]);
          Expression arre = Expression::createArrayIdentifier(arr);
          Expression e = Expression::createVariableAssigment(VariableAssigment(arre, p[1]));
          return e;
        }
        if(method=="toArray") {
          return obj;
        }
        if(method=="entrySet") {
          return obj;
        }
        if(method=="Count") {
          CallParams p = CallParams();
          p.Insert(obj);
          FunctionCallExpression fce = FunctionCallExpression(Expression::createIdentifier(IdentifierExpression("count")),p);
          return Expression::createFunctionCallExpression(fce);
        }
      }
    }
  }
  return Expression::createEmpty();
}