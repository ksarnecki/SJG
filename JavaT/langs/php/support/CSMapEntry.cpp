#include "CSMapEntry.h"
#include <cstdio>

AnsiString CSMapEntry::name() {
  return "MapEntry";
}

AnsiString CSMapEntry::rename() {
  return "System.Collections.Generic.KeyValuePair";
}

Expression CSMapEntry::changeMethod(const MultiIdentifier& mi) {
  Expression obj = mi.getLex();
  Expression fun = mi.getRex();
  
  if(obj.isIdentifier() && obj.asIdentifier().getValue() == name()) {
    //metoda statyczna
  } else {
    if(fun.isIdentifier()) {
      //zmienne
    } else if(fun.isFunctionCallExpression()) {
      //metody obiektowe
      FunctionCallExpression fce = fun.asFunctionCallExpression();
      if(fce.getName().isIdentifier()) {
        AnsiString method = fce.getName().asIdentifier().getValue();
        CallParams p = fce.getParams();
        if(method=="getKey") {
          FunctionCallExpression fce = FunctionCallExpression(Expression::createIdentifier(IdentifierExpression("Key")),p);
          MultiIdentifier m = MultiIdentifier(obj, Expression::createFunctionCallExpression(fce));
          return Expression::createMultiIdentifier(m);
        }
        if(method=="getValue") {
          FunctionCallExpression fce = FunctionCallExpression(Expression::createIdentifier(IdentifierExpression("Value")),p);
          MultiIdentifier m = MultiIdentifier(obj, Expression::createFunctionCallExpression(fce));
          return obj;
        }
      }
    }
  }
  return Expression::createEmpty();
}