#include "PHPString.h"

AnsiString PHPString::name() {
  return "String";
}

Expression PHPString::changeMethod(const MultiIdentifier& mi) {
  Expression obj = mi.getLex();
  Expression fun = mi.getRex();
  if(obj.isIdentifier() && obj.asIdentifier().getValue() == name()) {
    //metoda statyczna  
  } else {
    if(fun.isIdentifier()) {
      //zmienne
    } else if(fun.isFunctionCallExpression()) {
      //metody
      FunctionCallExpression fce = fun.asFunctionCallExpression();
      if(fce.getName().isIdentifier()) {
        AnsiString method = fce.getName().asIdentifier().getValue();
        CallParams p = fce.getParams();
        if(method=="charAt" && p.Size()>0) {
          ArrayIdentifier ai = ArrayIdentifier(obj, p[0]);
          return Expression::createArrayIdentifier(ai); 
        }
        if(method=="length") {
          CallParams p;
          p.Insert(obj);
          Expression e1 = Expression::createIdentifier(IdentifierExpression("strlen"));
          FunctionCallExpression fce = FunctionCallExpression(e1, p);
          return Expression::createFunctionCallExpression(fce);
        }
        if(method=="equals") {
          TestingExpression te = TestingExpression(obj, p[0], TestingOperator::createEq());
          return Expression::createTestingExpression(te);
        }
        if(method=="substring") {
          if(p.Size()==2) {
            CallParams pc;
            pc.Insert(obj);
            pc.Insert(p[0]);
            Expression nbe1 = Expression::createNumericBinaryExpression(NumericBinaryExpression(p[1],p[0],NumericOperator::createSub()));
            Expression nbe2 = Expression::createNumericBinaryExpression(NumericBinaryExpression(nbe1,Expression::createIdentifier(IdentifierExpression("0")),NumericOperator::createAdd()));
            pc.Insert(nbe2);
            FunctionCallExpression fce = FunctionCallExpression(Expression::createIdentifier(IdentifierExpression("substr")),pc);
            return Expression::createFunctionCallExpression(fce);
          }
        }
      }
    } 
  }
  return Expression::createEmpty();
}