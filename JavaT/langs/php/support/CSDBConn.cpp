#include "CSDBConn.h"

AnsiString CSDBConn::name() {
  return "DBConn";
}

AnsiString CSDBConn::rename() {
  return "DBConn";
}

Expression CSDBConn::changeMethod(const MultiIdentifier& mi) {
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
        if(method=="escape") {
          FunctionCallExpression fce = FunctionCallExpression(Expression::createIdentifier(IdentifierExpression("Escape")),p);
          MultiIdentifier m = MultiIdentifier(obj, Expression::createFunctionCallExpression(fce));
          return Expression::createMultiIdentifier(m);
        }
        if(method=="query") {
          FunctionCallExpression fce = FunctionCallExpression(Expression::createIdentifier(IdentifierExpression("Query")),p);
          MultiIdentifier m = MultiIdentifier(obj, Expression::createFunctionCallExpression(fce));
          return Expression::createMultiIdentifier(m);
        }
        if(method=="execute") {
          FunctionCallExpression fce = FunctionCallExpression(Expression::createIdentifier(IdentifierExpression("Execute")),p);
          MultiIdentifier m = MultiIdentifier(obj, Expression::createFunctionCallExpression(fce));
          return Expression::createMultiIdentifier(m);
        }
      }
    } 
  }
  return Expression::createEmpty();
}