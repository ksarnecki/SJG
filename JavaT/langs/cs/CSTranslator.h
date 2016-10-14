#ifndef CS_TRANSLATOR
#define CS_TRANSLATOR

#include <iostream>
#include <fstream>

#include "AnsiString.h"
#include "DynSet.h"
#include "LineStream.h"
#include "Data.h"

#include "Translator.h"

#include "support/CSMapEntry.h"
#include "support/CSHashMap.h"
#include "support/CSArray.h"
#include "support/CSPattern.h"
#include "support/CSMatcher.h"
#include "support/CSDBConn.h"
#include "support/CSSDBResult.h"
#include "support/CSString.h"
#include "support/CSInteger.h"

class CSTranslator : public Translator {
  
  /* Main => */
	virtual void translatePackages(const Packages&, Types&, Builder&);
	virtual void translateImports(const Imports&, Types&, Builder&);
	virtual void prepareClassBeg(const Modifiers&, const AnsiString&, Types&, Builder&);
	virtual void prepareClassEnd(Types&, Builder&);
  virtual void prepareMethodHeader(const MethodDeclarator&, Types&, Builder&);
	virtual void prepareClassVariableDeclaration(const VariableDeclarator&, Types&, Builder&);
  /* <= Main  */
  
  /* Statements => */
  virtual void prepareBlockStatement(const BlockStatement&, Types&, Builder&);
  virtual void prepareForStatement(const ForStatement&, Types&, Builder&);
  virtual void prepareForeachStatement(const ForeachStatement&, Types&, Builder&);
  virtual void prepareVariableDeclarator(const VariableDeclarator&, Types&, Builder&);
  virtual void prepareVariableDeclaratorStatement(const VariableDeclarator&, Types&, Builder&);
  virtual void prepareExpressionStatement(const Expression&, Types&, Builder&);
  virtual void prepareReturnStatement(const Expression&, Types&, Builder&);
  virtual void prepareWhileStatement(const WhileStatement&, Types&, Builder&);
  virtual void prepareIfStatement(const IfStatement&, Types&, Builder&);
  /* <= Statements */
  
  /* Expressions => */
  virtual void prepareVariableAssigmentExpression(const VariableAssigment&, Types&, Builder&);
  virtual void prepareCreatingExpression(const CreatingExpression&, Types&, Builder&);
  virtual void prepareIdentifierExpression(const IdentifierExpression&, Types&, Builder&);
  virtual void prepareArrayIdentifierExpression(const ArrayIdentifier&, Types&, Builder&);
  virtual void prepareMultiIdentifierExpression(const MultiIdentifier&, Types&, Builder&);
  virtual void prepareTemplateIdentifierExpression(const TemplateIdentifier&, Types&, Builder&);
  virtual void prepareFunctionCallExpression(const FunctionCallExpression&, Types&, Builder&);
  virtual void prepareTestingExpression(const TestingExpression&, Types&, Builder&);
  virtual void prepareNumericBinaryExpression(const NumericBinaryExpression&, Types&, Builder&);
  virtual void prepareNumericUnaryExpression(const NumericUnaryExpression&, Types&, Builder&);
  virtual void prepareCondOperatorExpression(const CondOperatorExpression&, Types&, Builder&);
  virtual void prepareStringExpression(const StringExpression&, Types&, Builder&);
  virtual void prepareCharExpression(const CharExpression&, Types&, Builder&);
  virtual void prepareFloatExpression(const FloatExpression&, Types&, Builder&);
  virtual void prepareArrayCreatingExpression(const ArrayCreatingExpression&, Types&, Builder&);
  virtual void prepareAwaitExpression(const AwaitExpression&, Types&, Builder&);
  /* <= Expressions */

  //Modifiers
  virtual void prepareModifier(const Modifier&, Types&, Builder&);
  virtual void prepareModifiers(const Modifiers&, Types&, Builder&);
  
  //Operators
  virtual void preapreNumericOperator(const NumericOperator&, Types&, Builder&);
  virtual void preapreTestingOperator(const TestingOperator&, Types&, Builder&);
	
};

#endif