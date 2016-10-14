%define api.prefix {javat}
%{

#include <string.h>
#include <malloc.h>
#include <stdio.h>

#include "AnsiString.h"
#include "LineStream.h"
#include "LexicalData.h"

extern "C" {
  int javatparse(void);
  int javatlex(void);
  int javatwrap() {
    return 1;
  }
  extern int javatlineno;
  extern char* javattext;
}

void javaterror(const char *s) {
  printf("%s at line %d", s, javatlineno);
  if (javattext!=0)
    printf(", near token %s", javattext);
  printf("\n");
}

template <class T>
class Box {
  T v;
public:
  Box(const T& _v) : v(_v) {
  }
  virtual const T& get() const {
    return v;
  }
  virtual ~Box() {
  }
};

template <class T>
static T xbox(int v) {
  Box<T>* b = (Box<T>*) v;
  T t = b->get();
  delete b;
  return t;
}

static AnsiString xboxs(int v) {
  char* s = (char*) v;
  AnsiString ret(s);
  free(s);
  return ret;
}

void deb(AnsiString msg) {
  //fprintf(stderr, "%s\n", msg.c_str());
  //fflush(stdout);
}

JavaFile* result = 0;

%}

%token IMPORT TEXT PACKAGE PRIVATE VOID BOOL CLASS FOR WHILE PUBLIC STATIC RETURN NEW ABEG AWAIT AEND AAS ASYNC SAS BEG END PBEG PEND NEQ EQ EGR ESM INC DEC FINAL STRING TEMPL INT CHAR IF ELSE /* wszystkie nazwy tokenow majace wiecej niz jeden znak musza byc zadeklarowane */

%left AAS SAS NEQ EQ EGR ESM INC DEC '+' '-' '<' '>' ABEG AEND
%left '*' '/'
%left '?'
%left '.'

%%

JavaFile : packages imports classes { 
  deb("[JavaFile] ");
  Packages p = xbox<Packages>($1);
  Imports i = xbox<Imports>($2);
  Classes c =  xbox<Classes>($3);
  result = new JavaFile(p,i,c); 
}

packages : PACKAGE packageText ';' { 
  deb("[packages] ");
  Packages ps = Packages(); 
  ps.Insert(xbox<AnsiString>($2)); 
  $$ = new Box<Packages>(ps);
}

packageText : TEXT {
  $$ = new Box<AnsiString>(xboxs($1));
}

packageText : packageText '.' packageText {
  $$ = new Box<AnsiString>(xbox<AnsiString>($1) + "." + xbox<AnsiString>($3));
}

packages : { 
  deb("[packages] ");
  $$ = new Box<Packages>(Packages());
}

imports : imports import { 
  deb("[imports] ");
  Imports imports = xbox<Imports>($1);
  imports.Insert(xbox<AnsiString>($2));
  $$ = new Box<Imports>(imports);
}

imports : { 
  deb("[imports] ");
  $$ = new Box<Imports>(Imports());
}

import : IMPORT importText ';' { 
  deb("[import] ");
  $$ = $2;
}

importText : TEXT {
  $$ = new Box<AnsiString>(xboxs($1));
}

importText : importText '.' importText {
  $$ = new Box<AnsiString>(xbox<AnsiString>($1) + "." + xbox<AnsiString>($3));
}

classes : classes class { 
  deb("[classes] ");
  Classes classes = xbox<Classes>($1);
  classes.Insert(xbox<Class>($2));
  $$ = new Box<Classes>(classes);
}

classes : { 
  deb("[classes] ");
  $$ = new Box<Classes>(Classes());
}

className : TEXT {
  deb("[className] ");
  $$ = new Box<AnsiString>(xboxs($1));
}

modifier : PUBLIC {
  deb("[modifier : PUBLIC] ");
  $$ = new Box<Modifier>(Modifier::createPublic());
}

modifier : PRIVATE {
  deb("[modifier : PRIVATE] ");
  $$ = new Box<Modifier>(Modifier::createPrivate());
}

modifier : ASYNC {
  deb("[modifier : ASYNC] ");
  $$ = new Box<Modifier>(Modifier::createAsync());
}

modifier : STATIC {
  deb("[modifier : STATIC] ");
  $$ = new Box<Modifier>(Modifier::createStatic());
}

modifier : FINAL {
  deb("[modifier : STATIC] ");
  $$ = new Box<Modifier>(Modifier::createFinal());
}

modifiers : modifiers modifier{
  deb("[modifiers : modifiers modifier] ");
  Modifiers modifiers = xbox<Modifiers>($1);
  modifiers.Insert(xbox<Modifier>($2));
  $$ = new Box<Modifiers>(modifiers); 
}

modifiers : {
  deb("[modifiers :] ");
  $$ = new Box<Modifiers>(Modifiers());
}

class : modifiers CLASS className BEG classElems END {
  deb("[class] ");
  $$ = new Box<Class>(Class(xbox<Modifiers>($1), xbox<AnsiString>($3), xbox<ClassElems>($5)));
}

classElems : classElems classElem { 
  deb("[classElems : classElems] ");
  ClassElems elems = xbox<ClassElems>($1);
  elems.Insert(xbox<ClassElem>($2));
  $$ = new Box<ClassElems>(elems);
}

classElems : { 
  deb("[classElems : ] ");
  $$ = new Box<ClassElems>(ClassElems());
}

creatingExpression : NEW expression PBEG callParams PEND {
  deb("[creatingExpression : NEW expression PBEG callParams PEND]");
  CreatingExpression c = CreatingExpression(xbox<Expression>($2), xbox<CallParams>($4));
  $$ = new Box<Expression>(Expression::createCreatingExpression(c));
}

creatingExpression : NEW expression PBEG PEND {
  deb("[creatingExpression : NEW expression PBEG  PEND]");
  CreatingExpression c = CreatingExpression(xbox<Expression>($2), CallParams());
  $$ = new Box<Expression>(Expression::createCreatingExpression(c));
}

creatingExpression : NEW typeName PBEG PEND {
  deb("[creatingExpression : NEW expression PBEG  PEND]");
  CreatingExpression c = CreatingExpression(xbox<Expression>($2), CallParams());
  $$ = new Box<Expression>(Expression::createCreatingExpression(c));
}

creatingExpression : NEW expression ABEG expression AEND {
  deb("creatingExpression : NEW expression ABEG expression AEND");
  ArrayCreatingExpression c = ArrayCreatingExpression(xbox<Expression>($2), xbox<Expression>($4));
  $$ = new Box<Expression>(Expression::createArrayCreatingExpression(c));
}

variableDeclarator : typeName expression {
  deb("[variableDeclarator] ");
  $$ = new Box<VariableDeclarator>(VariableDeclarator(Modifiers(), xbox<Expression>($1), xbox<Expression>($2), VariableInitializer::createDefault()));
}

variableDeclarator : modifiers typeName expression {
  deb("[variableDeclarator] ");
  $$ = new Box<VariableDeclarator>(VariableDeclarator(xbox<Modifiers>($1), xbox<Expression>($2), xbox<Expression>($3), VariableInitializer::createDefault()));
}

variableDeclarator : typeName expression '=' expression {
  deb("[variableDeclarator] ");
  Expression e = xbox<Expression>($4);
  $$ = new Box<VariableDeclarator>(VariableDeclarator(Modifiers(), xbox<Expression>($1), xbox<Expression>($2), VariableInitializer::createValue(e)));
}

variableDeclarator : modifiers typeName expression '=' expression {
  deb("[variableDeclarator] ");
  Expression e = xbox<Expression>($5);
  $$ = new Box<VariableDeclarator>(VariableDeclarator(xbox<Modifiers>($1), xbox<Expression>($2), xbox<Expression>($3), VariableInitializer::createValue(e)));
}

methodName : TEXT {
  AnsiString a = xboxs($1);
  deb("[methodName] " + a);
  $$ = new Box<AnsiString>(a);
}

params : params ',' variableDeclarator {
  deb("[params : params ',' variableDeclarator] ");
  Params params = xbox<Params>($1);
  params.Insert(xbox<VariableDeclarator>($3));
  $$ = new Box<Params>(params); 
}

params : variableDeclarator {
  deb("[params : variableDeclarator] ");
  Params params = Params();
  params.Insert(xbox<VariableDeclarator>($1));
  $$ = new Box<Params>(params); 
}

params : {
  deb("[params :] ");
  $$ = new Box<Params>(Params());
}

expression : TEXT {
  AnsiString v = xboxs($1);
  $$ = new Box<Expression>(Expression::createIdentifier(IdentifierExpression(v)));
  deb("[expression : TEXT]" + v + " " + AnsiString($$));
}

expression : expression '.' expression {
  Expression lob = xbox<Expression>($1);
  Expression rob = xbox<Expression>($3);
  $$ = new Box<Expression>(Expression::createMultiIdentifier(MultiIdentifier(lob, rob)));
  deb("[expression '.' expression ] " + AnsiString($$));
}

expression : PBEG expression PEND expression {
  //Dodać obsługę rzutowania.
  $$ = $4;
}

expression : variableDeclarator {
  VariableDeclarator var = xbox<VariableDeclarator>($1);
  $$ = new Box<Expression>(Expression::createVariableDeclarator(var));
}

expression : expression '=' expression {
  Expression obj = xbox<Expression>($1);
  Expression exp = xbox<Expression>($3);
  VariableAssigment vas = VariableAssigment(obj, exp);
  $$ = new Box<Expression>(Expression::createVariableAssigment(vas));
  deb("[TEXT '=' expression]" + AnsiString($$));
}

expression : expression ABEG expression AEND {
  Expression array = xbox<Expression>($1);
  Expression index = xbox<Expression>($3);
  ArrayIdentifier ai = ArrayIdentifier(array, index);
  $$ = new Box<Expression>(Expression::createArrayIdentifier(ai));
  deb("expression : expression ABEG expression AEND" + AnsiString($$));
}

expression : expression ABEG  AEND {
  Expression array = xbox<Expression>($1);
  Expression index = Expression::createEmpty();
  ArrayIdentifier ai = ArrayIdentifier(array, index);
  $$ = new Box<Expression>(Expression::createArrayIdentifier(ai));
  deb("expression : expression ABEG  AEND" + AnsiString($$));
}

callParams : callParams ',' expression {
  CallParams cp = xbox<CallParams>($1);
  cp.Insert(xbox<Expression>($3));
  $$ = new Box<CallParams>(cp);
}

callParams : expression {
  CallParams cp;
  cp.Insert(xbox<Expression>($1));
  $$ = new Box<CallParams>(cp);
}

expression : expression PBEG callParams PEND {
  Expression obj = xbox<Expression>($1);
  CallParams params = xbox<CallParams>($3);
  FunctionCallExpression f = FunctionCallExpression(obj, params);
  $$ = new Box<Expression>(Expression::createFunctionCallExpression(f));
  deb("[expression : expression PBEG callParams PEND]" + AnsiString($$));
}

expression : expression PBEG PEND {
  Expression obj = xbox<Expression>($1);
  FunctionCallExpression f = FunctionCallExpression(obj, CallParams());
  $$ = new Box<Expression>(Expression::createFunctionCallExpression(f));
  deb("[expression : expression PBEG PEND]" + AnsiString($$));
}

expression : PBEG expression PEND {
  $$ = $2;
  deb("[expression : PBEG expression PEND ]" + AnsiString($$));
}

expression : expression testingOperator expression {
  Expression lop = xbox<Expression>($1);
  TestingOperator op = xbox<TestingOperator>($2);
  Expression rop = xbox<Expression>($3);
  TestingExpression t = TestingExpression(lop,rop,op);
  $$ = new Box<Expression>(Expression::createTestingExpression(t));
  deb("[[ expression testing expression]]" + AnsiString($$));
}

expression : expression '?' expression ':' expression {
  deb("[expression '?' expression ':' expression]");
  Expression cond = xbox<Expression>($1);
  Expression trueExpr = xbox<Expression>($3);
  Expression falseExpr = xbox<Expression>($5);
  CondOperatorExpression coe = CondOperatorExpression(cond,trueExpr,falseExpr);
  $$ = new Box<Expression>(Expression::createCondOperatorExpression(coe));
}

expression : AWAIT expression {
  Expression exp = xbox<Expression>($2);
  $$ = new Box<Expression>(Expression::createAwaitExpression(AwaitExpression(exp)));
}

expression : STRING {
  AnsiString s = xboxs($1);
  s = s.SubString(2, s.Length()-2);
  $$ = new Box<Expression>(Expression::createStringExpression(StringExpression(s)));
}

expression : CHAR {
  $$ = new Box<Expression>(Expression::createCharExpression(CharExpression(xboxs($1))));
}

expression : INT {
  $$ = new Box<Expression>(Expression::createFloatExpression(FloatExpression(xboxs($1))));
}

testingOperator : '<' {
  $$ = new Box<TestingOperator>(TestingOperator::createSm());
}

testingOperator : ESM {
  $$ = new Box<TestingOperator>(TestingOperator::createEsm());
}

testingOperator : '>' {
  $$ = new Box<TestingOperator>(TestingOperator::createGr());
}

testingOperator : EGR {
  $$ = new Box<TestingOperator>(TestingOperator::createEgr());
}

testingOperator : EQ {
  $$ = new Box<TestingOperator>(TestingOperator::createEq());
}

testingOperator : NEQ {
  $$ = new Box<TestingOperator>(TestingOperator::createNeq());
}

numericOperator : '+' {
  $$ = new Box<NumericOperator>(NumericOperator::createAdd()); 
}

numericOperator : '-' {
  $$ = new Box<NumericOperator>(NumericOperator::createSub()); 
}

numericOperator : '*' {
  $$ = new Box<NumericOperator>(NumericOperator::createMul()); 
}

numericOperator : '/' {
  $$ = new Box<NumericOperator>(NumericOperator::createDiv()); 
}

numericOperator : INC {
  $$ = new Box<NumericOperator>(NumericOperator::createInc()); 
}

numericOperator : DEC {
  $$ = new Box<NumericOperator>(NumericOperator::createDec()); 
}

numericOperator : SAS {
  $$ = new Box<NumericOperator>(NumericOperator::createSas()); 
}

numericOperator : AAS {
  $$ = new Box<NumericOperator>(NumericOperator::createAas()); 
}

expression : expression numericOperator expression {
  deb("[expression numericOperator expression]");
  Expression lex = xbox<Expression>($1);
  NumericOperator op = xbox<NumericOperator>($2);
  Expression rex = xbox<Expression>($3);
  NumericBinaryExpression e = NumericBinaryExpression(lex,rex,op);
  $$ = new Box<Expression>(Expression::createNumericBinaryExpression(e));
}

expression : expression numericOperator {
  deb("[numericOperator expression]");
  Expression ex = xbox<Expression>($1);
  NumericOperator op = xbox<NumericOperator>($2);
  NumericUnaryExpression e = NumericUnaryExpression(ex, op, NumericUnaryExpressionKind::createSufix());
  $$ = new Box<Expression>(Expression::createNumericUnaryExpression(e));
}

expression : creatingExpression {
  $$ = $1;
}

statement : variableDeclarator ';' {
  deb("[statement : variableDeclarator] ");
  VariableDeclarator v = xbox<VariableDeclarator>($1);
  $$ = new Box<Statement>(Statement::createVariableDeclaration(v));
}

statement : expression ';' {
  $$ = new Box<Statement>(Statement::createExpressionStatement(xbox<Expression>($1)));
}

blockStatement : BEG statement END {
  $$ = new Box<Statement>(Statement::createBlockStatement(BlockStatement(xbox<Statement>($2))));
}

blockStatement : BEG  END {
  $$ = new Box<Statement>(Statement::createBlockStatement(BlockStatement(Statement::createEmpty())));
}

statement : RETURN expression ';' {
  $$ = new Box<Statement>(Statement::createReturnStatement(xbox<Expression>($2)));
}

statement : blockStatement {
  $$ = $1;
}

statement : statement statement {
  deb("[statement : statement statement]" + AnsiString($1) + " " + AnsiString($2));
  Statement s1 = xbox<Statement>($1);
  Statement s2 = xbox<Statement>($2);
  MergeStatement ms = MergeStatement(s1,s2);
  Statement s = Statement::createMergeStatement(ms);
  $$ = new Box<Statement>(s);
  deb("[statement : statement statement]" + AnsiString($$));
}

statement : IF PBEG expression PEND statement ifElse {
  Expression cond = xbox<Expression>($3);
  Statement stmnt = xbox<Statement>($5);
  IfElse ifElse = xbox<IfElse>($6);
  IfStatement ifs = IfStatement(cond, stmnt, ifElse);
  $$ = new Box<Statement>(Statement::createIfStatement(ifs));
  deb("[statement : IF PBEG expression PEND statement ifElse]" + AnsiString($$));
}

ifElse : ELSE statement{
  $$ = new Box<IfElse>(IfElse::createValue(xbox<Statement>($2)));
}

ifElse : {
  $$ = new Box<IfElse>(IfElse::createEmpty());
}

statement : FOR PBEG expression ';' expression ';' expression PEND statement {
  Expression init = xbox<Expression>($3);
  Expression cond = xbox<Expression>($5);
  Expression after = xbox<Expression>($7);
  Statement body = xbox<Statement>($9);
  ForStatement f = ForStatement(ForInit::createExpr(init), cond, after, body);
  $$ = new Box<Statement>(Statement::createForStatement(f));
}

statement : FOR PBEG variableDeclarator ':' expression PEND statement {
  VariableDeclarator iterator = xbox<VariableDeclarator>($3);
  Expression object = xbox<Expression>($5);
  Statement body = xbox<Statement>($7);
  ForeachStatement f = ForeachStatement(iterator, object, body);
  $$ = new Box<Statement>(Statement::createForeachStatement(f));
}

statement : FOR PBEG variableDeclarator ';' expression ';' expression PEND statement {
  VariableDeclarator init = xbox<VariableDeclarator>($3);
  Expression cond = xbox<Expression>($5);
  Expression after = xbox<Expression>($7);
  Statement body = xbox<Statement>($9);
  ForStatement f = ForStatement(ForInit::createDecl(init), cond, after, body);
  $$ = new Box<Statement>(Statement::createForStatement(f));
}

statement : WHILE PBEG expression PEND statement {
  Expression cond = xbox<Expression>($3);
  Statement body = xbox<Statement>($5);
  WhileStatement w = WhileStatement(cond, body);
  $$ = new Box<Statement>(Statement::createWhileStatement(w));
}

typeName : expression {
  deb("[typeName : expression]" + AnsiString($1));
  $$ = $1;
}

typeName : typeName TEMPL  {
  deb("[typeName : expression '<' typeNames '>']");
  Expression type = xbox<Expression>($1);
  Expressions es;
  AnsiString s = xboxs($2);
  int start = 2;
  for(int i=3;i<=s.Length();i++) {
    if(s[i]==',' || i==s.Length()) {
      AnsiString type = s.SubString(start, i-start).Trim();
      es.Insert(Expression::createIdentifier(type));
      start=i+1;
    }
  }
  TemplateIdentifier t = TemplateIdentifier(type, es);
  $$ = new Box<Expression>(Expression::createTemplateIdentifier(t));
}

methodDeclarator : modifiers typeName methodName PBEG params PEND blockStatement  {
  deb("[methodDeclarator] ");
  Modifiers ms = xbox<Modifiers>($1);
  Expression tn = xbox<Expression>($2);
  AnsiString mn = xbox<AnsiString>($3);
  Params p = xbox<Params>($5);
  Statement s = xbox<Statement>($7);
  MethodDeclarator m = MethodDeclarator(ms, tn, mn, p, s);
  $$ = new Box<MethodDeclarator>(m);
}

methodDeclarator : modifiers methodName PBEG params PEND blockStatement  {
  deb("[methodDeclarator] ");
  Modifiers ms = xbox<Modifiers>($1);
  Expression tn = Expression::createEmpty();
  AnsiString mn = xbox<AnsiString>($2);
  Params p = xbox<Params>($4);
  Statement s = xbox<Statement>($6);
  MethodDeclarator m = MethodDeclarator(ms, tn, mn, p, s);
  $$ = new Box<MethodDeclarator>(m);
}


classElem : variableDeclarator ';' {
  deb("[classElem : variableDeclarator] ");
  $$ = new Box<ClassElem>(ClassElem::createVariableDeclarator(xbox<VariableDeclarator>($1)));
}


classElem : methodDeclarator {
  deb("[classElem : methodDeclarator] ");
  $$ = new Box<ClassElem>(ClassElem::createMethodDeclarator(xbox<MethodDeclarator>($1)));
}



%%

int javatlex(void);
void javaterror(const char *);

#include "lex.javat.c"

#include <iostream>
#include <fstream>

extern JavaFile javat_yacc_parse(LineStream& stream) {
  AnsiString input = "";
  stream.next();
  while(!stream.isEof()) {
    AnsiString line = stream.getLine() + "\r\n";
    input += line;
    stream.next();
  }
  javat_scan_string(input.c_str());
  javatparse(); 
  if(result!=0) {
    JavaFile data = *result;
    return data;
  } else 
    throw Exception("Parser error...");
}