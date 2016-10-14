#include "CSString.h"

AnsiString CSString::name() {
  return "String";
}

AnsiString CSString::rename() {
  return "string";
}

Expression CSString::changeMethod(const MultiIdentifier& mi) {
  Expression obj = mi.getLex();
  Expression fun = mi.getRex();
  if(obj.isIdentifier() && obj.asIdentifier().getValue() == name()) {
    //metoda statyczna  
  } else {
    if(fun.isIdentifier()) {
      //zmienne
    } else if(fun.isFunctionCallExpression()) {
     
      FunctionCallExpression fce = fun.asFunctionCallExpression();
      if(fce.getName().isIdentifier()) {
        AnsiString method = fce.getName().asIdentifier().getValue();
        CallParams p = fce.getParams();
        if(method=="indexOf") {
          FunctionCallExpression fce = FunctionCallExpression(Expression::createIdentifier(IdentifierExpression("IndexOf")),p);
          MultiIdentifier m = MultiIdentifier(obj, Expression::createFunctionCallExpression(fce));
          return Expression::createMultiIdentifier(m);
        }
        if(method=="replaceAll") {
          CallParams p2;
          p2.Insert(obj);
          p2.Insert(p[0]);
          p2.Insert(p[1]);
          FunctionCallExpression fce = FunctionCallExpression(Expression::createIdentifier(IdentifierExpression("Replace")),p2);
          MultiIdentifier m = MultiIdentifier(Expression::createIdentifier(IdentifierExpression("System.Text.RegularExpressions.Regex")), Expression::createFunctionCallExpression(fce));
          return Expression::createMultiIdentifier(m);
        }
        if(method=="split") {
          CallParams p2;
          p2.Insert(obj);
          p2.Insert(p[0]);
          FunctionCallExpression fce = FunctionCallExpression(Expression::createIdentifier(IdentifierExpression("Split")),p2);
          MultiIdentifier m = MultiIdentifier(Expression::createIdentifier(IdentifierExpression("System.Text.RegularExpressions.Regex")), Expression::createFunctionCallExpression(fce));
          return Expression::createMultiIdentifier(m);
        }
        if(method=="length") {
          MultiIdentifier m = MultiIdentifier(obj, Expression::createIdentifier(IdentifierExpression("Length")));
          return Expression::createMultiIdentifier(m);
        }
        if(method=="substring") {
          if(p.Size()==2) {
            Expression nbe1 = Expression::createNumericBinaryExpression(NumericBinaryExpression(p[1],p[0],NumericOperator::createSub()));
            Expression nbe2 = Expression::createNumericBinaryExpression(NumericBinaryExpression(nbe1,Expression::createIdentifier(IdentifierExpression("1")),NumericOperator::createAdd()));
            p[1]=nbe2;
            FunctionCallExpression fce = FunctionCallExpression(Expression::createIdentifier(IdentifierExpression("Substring")),p);
            MultiIdentifier m = MultiIdentifier(obj, Expression::createFunctionCallExpression(fce));
            return Expression::createMultiIdentifier(m);
          } else if(p.Size()==1) {
            FunctionCallExpression fce = FunctionCallExpression(Expression::createIdentifier(IdentifierExpression("Substring")),p);
            MultiIdentifier m = MultiIdentifier(obj, Expression::createFunctionCallExpression(fce));
            return Expression::createMultiIdentifier(m);
          } else {
            FunctionCallExpression fce = FunctionCallExpression(Expression::createIdentifier(IdentifierExpression("Substring")),p);
            MultiIdentifier m = MultiIdentifier(obj, Expression::createFunctionCallExpression(fce));
            return Expression::createMultiIdentifier(m);
          }
        }
      }
    } 
  }
  return Expression::createEmpty();
}