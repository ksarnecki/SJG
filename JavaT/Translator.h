#ifndef TRANSLATOR
#define TRANSLATOR

#include <iostream>
#include <fstream>

#include "AnsiString.h"
#include "DynSet.h"
#include "LineStream.h"
#include "LexicalData.h"
#include "SyntaxData.h"
#include "Builder.h"
#include "Exception.h"

class Translator {
  public:
    
    //Utils
    static TypeInfo getTypeInfo(const VariableDeclarator& v, Types&);
    static int findTypePos(const AnsiString&, const Types&);
	  static RealType getType(const Expression&, const Types&);
    
    //Operators
    virtual void preapreTestingOperator(const TestingOperator&, Types&, Builder&) = 0;
    virtual void preapreNumericOperator(const NumericOperator&, Types&, Builder&) = 0;
  
    //Modifiers
    virtual void prepareModifier(const Modifier&, Types&, Builder&) = 0;
    virtual void prepareModifiers(const Modifiers&, Types&, Builder&) = 0;
    
    //Expressions
    virtual void prepareExpression(const Expression&, Types&, Builder&);
    virtual void prepareVariableAssigmentExpression(const VariableAssigment&, Types&, Builder&) = 0;
    virtual void prepareCreatingExpression(const CreatingExpression&, Types&, Builder&) = 0;
    virtual void prepareIdentifierExpression(const IdentifierExpression&, Types&, Builder&) = 0;
    virtual void prepareArrayIdentifierExpression(const ArrayIdentifier&, Types&, Builder&) = 0;
    virtual void prepareMultiIdentifierExpression(const MultiIdentifier&, Types&, Builder&) = 0;
    virtual void prepareTemplateIdentifierExpression(const TemplateIdentifier&, Types&, Builder&) = 0;
    virtual void prepareFunctionCallExpression(const FunctionCallExpression&, Types&, Builder&) = 0;
    virtual void prepareTestingExpression(const TestingExpression&, Types&, Builder&) = 0;
    virtual void prepareNumericBinaryExpression(const NumericBinaryExpression&, Types&, Builder&) = 0;
    virtual void prepareNumericUnaryExpression(const NumericUnaryExpression&, Types&, Builder&) = 0;
    virtual void prepareCondOperatorExpression(const CondOperatorExpression&, Types&, Builder&) = 0;
    virtual void prepareStringExpression(const StringExpression&, Types&, Builder&) = 0;
    virtual void prepareCharExpression(const CharExpression&, Types&, Builder&) = 0;
    virtual void prepareFloatExpression(const FloatExpression&, Types&, Builder&) = 0;
    virtual void prepareArrayCreatingExpression(const ArrayCreatingExpression&, Types&, Builder&) = 0;
    virtual void prepareAwaitExpression(const AwaitExpression&, Types&, Builder&) = 0;
    
    //Statements
    virtual void prepareStatement(const Statement&, Types&, Builder&);
    virtual void prepareBlockStatement(const BlockStatement&, Types&, Builder&) = 0;
    virtual void prepareForStatement(const ForStatement&, Types&, Builder&) = 0;
    virtual void prepareForeachStatement(const ForeachStatement&, Types&, Builder&) = 0;
    virtual void prepareVariableDeclarator(const VariableDeclarator&, Types&, Builder&) = 0;
    virtual void prepareVariableDeclaratorStatement(const VariableDeclarator&, Types&, Builder&) = 0;
    virtual void prepareExpressionStatement(const Expression&, Types&, Builder&) = 0;
    virtual void prepareReturnStatement(const Expression&, Types&, Builder&) = 0;
    virtual void prepareWhileStatement(const WhileStatement&, Types&, Builder&) = 0;
    virtual void prepareIfStatement(const IfStatement&, Types&, Builder&) = 0;
    
    //Main
    virtual void translateClass(const Class&, Types&, Builder&);
    virtual void translateImports(const Imports&, Types&, Builder&) = 0;
    virtual void translatePackages(const Packages&, Types&, Builder&) = 0;
    virtual void prepareClassBeg(const Modifiers&, const AnsiString&, Types&, Builder&) = 0;
    virtual void prepareClassEnd(Types&, Builder&) = 0;
    virtual void prepareClassVariableDeclaration(const VariableDeclarator&, Types&, Builder&) = 0;
    virtual void prepareMethod(const MethodDeclarator&, Types&, Builder&);
    virtual void prepareMethodHeader(const MethodDeclarator&, Types&, Builder&)= 0;
    virtual void translate(const JavaFile&);
};

#endif