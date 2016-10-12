%define api.prefix {sql}
%{

#include <string.h>
#include <malloc.h>
#include <stdio.h>

#include "SqlParser.h"
#include "data/SqlParserData.h"

extern "C" {
  int yyparse(void);
  int yylex(void);
  extern int sqllineno;
  extern char* sqltext;
}

void yyerror(const char *s) {
  AnsiString ret = AnsiString(s) + " at line " + AnsiString(sqllineno);
  if (sqltext!=0)
    ret += ", near token " + AnsiString(sqltext);
  throw Exception(ret);
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

int sqlResult = 0;

%}


%token	SELECT FROM BEG END ABEG AEND PBEG PEND TEXT STRING NUMBER WHERE ORDER LIMIT DESC ASC AS LIKE AND OR SPEC CASE WHEN THEN IN ELSE MAX MIN COUNT GROUP EXISTS VALUES INTO INSERT UPDATE DELETE SET NOT EGR ESM NEQ

/* kolejnoœæ operatorów sql */
%left OR AND //najni¿szy priorytet

%left '=' LIKE IN '>' '<' EGR ESM NEQ //najwy¿szy priorytet

%%

/* sql = rodzaje zapytañ */
sql : selectQuery { sqlResult = new Box<Sql>(Sql::createSelectQuery(xbox<SelectQuery>($1))); }
sql : insertQuery { sqlResult = new Box<Sql>(Sql::createInsertQuery(xbox<InsertQuery>($1))); }
sql : updateQuery { sqlResult = new Box<Sql>(Sql::createUpdateQuery(xbox<UpdateQuery>($1))); }
sql : deleteQuery { sqlResult = new Box<Sql>(Sql::createDeleteQuery(xbox<DeleteQuery>($1))); } 

/* selectQuery = sk³adnia select */
selectQuery : SELECT fields FROM tables condition orders sort groups limit { $$ = new Box<SelectQuery>(SelectQuery(xbox<Fields>($2), xbox<Tables>($4), xbox<Operation>($5), xbox<Orders>($6), xbox<Sort>($7), xbox<Groups>($8), xbox<Limit>($9))); }

/* selectQuery = sk³adnia insert */
insertQuery : INSERT INTO table PBEG fields PEND VALUES PBEG fields PEND { $$ = new Box<InsertQuery>(InsertQuery(xbox<Table>($3), xbox<Fields>($5), xbox<Fields>($9)));}
insertQuery : INSERT INTO table VALUES PBEG fields PEND { $$ = new Box<InsertQuery>(InsertQuery(xbox<Table>($3), Fields(), xbox<Fields>($7)));}

/* updateQuery = sk³adnia update */
updateQuery : UPDATE table sets condition limit { $$ = new Box<UpdateQuery>(UpdateQuery(xbox<Table>($2), xbox<Sets>($3),  xbox<Operation>($4), xbox<Limit>($5)));}

sets : sets ',' set { Sets ss = xbox<Sets>($1); ss.Insert(xbox<Set>($3)); $$ = new Box<Sets>(ss); }
sets :  SET set { Sets ss = Sets(); ss.Insert(xbox<Set>($2)); $$ = new Box<Sets>(ss); }

set : field '=' field { $$ = new Box<Set>(Set(xbox<Field>($1), xbox<Field>($3))); }

/* deleteQuery = sk³adnia update */
deleteQuery : DELETE FROM table condition limit { $$ = new Box<DeleteQuery>(DeleteQuery(xbox<Table>($2),  xbox<Operation>($3), xbox<Limit>($4)));}

/* --start fields = pola */
fields : fields ',' field {Fields fs = xbox<Fields>($1); fs.Insert(xbox<Field>($3)); $$ = new Box<Fields>(fs); }
fields : field { Fields fs = Fields(); fs.Insert(xbox<Field>($1)); $$ = new Box<Fields>(fs); }
/* --end fields */

/* field = pole/kolumna/napis/liczba/zapytanie */

/* zapytanie */
field : PBEG sql PEND AS TEXT   {Field f = Field(xboxs($5), FieldKind::createQuery(SqlPtr::createValue(xbox<Sql>($2)))); $$ = new Box<Field>(f); }
/* kolumna tabeli nazwana*/
field : TEXT '.' TEXT AS TEXT {Field f = Field(xboxs($4), FieldKind::createBasicField(BasicField(xboxs($1), xboxs($3)))); $$ = new Box<Field>(f); }
/* kolumna tabeli */
field : TEXT '.' TEXT { AnsiString str1 = xboxs($1); AnsiString str2 = xboxs($3); Field f = Field(str1 + "." + str2, FieldKind::createBasicField(BasicField(str1, str2))); $$ = new Box<Field>(f); }
/* liczba/napis/kolumna z domyœlnej tabeli */
field : charaters  AS TEXT {Field f = Field(xboxs($3), FieldKind::createBasicField(BasicField(xboxs($1), ""))); $$ = new Box<Field>(f); }
/* liczba/napis/kolumna z domyœlnej tabeli */
field : charaters { AnsiString str1 = xboxs($1); Field f = Field(str1, FieldKind::createBasicField(BasicField(str1, ""))); $$ = new Box<Field>(f); }
/* specjalny token DbGena %[...] */
field : SPEC { AnsiString str1 = xboxs($1); Field f = Field(str1, FieldKind::createSpecialField(str1)); $$ = new Box<Field>(f); }
/* funkcje agreguj¹ce */
field : agrFun PBEG fields PEND { Field f = Field("todo", FieldKind::createAgrField(AgrField(xbox<AgrFieldKind>($1), "todo AgrField"))); $$ = new Box<Field>(f); }
field : agrFun PBEG '*' PEND { Field f = Field("todo", FieldKind::createAgrField(AgrField(xbox<AgrFieldKind>($1), "todo AgrField"))); $$ = new Box<Field>(f); }
field : '*' {
  AnsiString str1 = "*"; 
  Field f = Field(str1, FieldKind::createAllField()); 
  $$ = new Box<Field>(f);
  }

agrFun : MAX { $$ = new Box<AgrFieldKind>(AgrFieldKind::createMax()); }
agrFun : MIN { $$ = new Box<AgrFieldKind>(AgrFieldKind::createMin()); }
agrFun : COUNT { $$ = new Box<AgrFieldKind>(AgrFieldKind::createCount()); }

charaters : TEXT
charaters : NUMBER
charaters : STRING

/* tables = tabele zapytania */
tables : tables ',' table { Tables ts = xbox<Tables>($1); ts.Insert(xbox<Table>($3)); $$ = new Box<Tables>(ts); }
tables : table { Tables ts = Tables();  ts.Insert(xbox<Table>($1)); $$ = new Box<Tables>(ts); }

table : PBEG sql PEND AS TEXT  { 
  Sql sql = xbox<Sql> ($2);
  AnsiString as = xboxs($5);
  Table t = Table(TableKind::createQuery(SqlPtr::createValue(sql)), as); 
  $$ = new Box<Table>(t);
}

table : TEXT AS TEXT { Table t = Table(TableKind::createBasic(xboxs($1)), xboxs($3)); $$ = new Box<Table>(t); }
table : TEXT TEXT { Table t = Table(TableKind::createBasic(xboxs($1)), xboxs($2)); $$ = new Box<Table>(t); }
table : TEXT { Table t = Table(TableKind::createBasic(xboxs($1)), ""); $$ = new Box<Table>(t); }


condition : { 
  $$ = new Box<Operation>(Operation::createEmpty());
}

condition : WHERE operation { 
  $$ = $2;
}

operation : field { 
  Field f = xbox<Field> ($1);
  Operation o = Operation::createField(f);
  $$ = new Box<Operation>(o); 
}

operation : PBEG operation PEND { 
  $$ = $2;
}

operation : operation binaryOperator operation {
  Operation left = xbox<Operation>($1); 
  Operation right = xbox<Operation>($3); 
  BinaryOperator bop = xbox<BinaryOperator>($2);
  BinaryOperation u = BinaryOperation(OperationPtr::createValue(left), OperationPtr::createValue(right), bop);
  $$ = new Box<Operation>(Operation::createBinaryOperation(u)); 
}

binaryOperator : OR {
  $$ = new Box<BinaryOperator>(BinaryOperator::createOr());
}

binaryOperator : AND {
  $$ = new Box<BinaryOperator>(BinaryOperator::createAnd());
}

binaryOperator : LIKE {
  $$ = new Box<BinaryOperator>(BinaryOperator::createLike());
}

binaryOperator : '=' {
  $$ = new Box<BinaryOperator>(BinaryOperator::createEqual());
}

binaryOperator : IN {
  $$ = new Box<BinaryOperator>(BinaryOperator::createIn());
}

binaryOperator : '>' {
  $$ = new Box<BinaryOperator>(BinaryOperator::createGreater());
}

binaryOperator : '<' {
  $$ = new Box<BinaryOperator>(BinaryOperator::createSmaller());
}

binaryOperator : EGR  {
  $$ = new Box<BinaryOperator>(BinaryOperator::createGreaterOrEqual());
}

binaryOperator : ESM {
  $$ = new Box<BinaryOperator>(BinaryOperator::createSmallerOrEqual());
}

binaryOperator : NEQ {
  $$ = new Box<BinaryOperator>(BinaryOperator::createNoEqual());
}

operation : unaryOperator operation {
  Operation o = xbox<Operation>($2);
  UnaryOperator uop = xbox<UnaryOperator> ($1);
  UnaryOperation u = UnaryOperation(OperationPtr::createValue(o), uop);
  $$ = new Box<Operation>(Operation::createUnaryOperation(u)); 
}

unaryOperator : NOT {
  $$ = new Box<UnaryOperator> (UnaryOperator::createNot());
}

operation : EXISTS PBEG sql PEND {
  Sql sql = xbox<Sql>($3);
  $$ = new Box<Operation>(Operation::createExistsOperation(sql));
}

operation : CASE whenConditions ELSE operation END  {
  WhenOperations cases = xbox<WhenOperations>($2);
  Operation elseStmnt = xbox<Operation>($4);
  $$ = new Box<Operation>(Operation::createCaseOperation(CaseOperation(cases, OperationPtr::createValue(elseStmnt))));
}

whenConditions : whenConditions whenCondition {
  WhenOperation wo = xbox<WhenOperation>($2);
  WhenOperations os = xbox<WhenOperations>($1);
  os.Insert(wo); 
  $$ = new Box<WhenOperations>(os); 
}

whenConditions : whenCondition {
  WhenOperation wo = xbox<WhenOperation>($1);
  WhenOperations os = WhenOperations();  
  os.Insert(wo); 
  $$ = new Box<WhenOperations>(os); 
}

whenConditions : { 
  WhenOperations os = WhenOperations();
  $$ = new Box<WhenOperations>(os);
}

whenCondition : WHEN operation THEN operation {
  Operation condition = xbox<Operation>($2); 
  Operation stmnt = xbox<Operation>($4);
  $$ = new Box<WhenOperation>(WhenOperation(OperationPtr::createValue(condition), OperationPtr::createValue(stmnt))); 
}

orders : orders ',' field { 
  Orders os = xbox<Orders>($1); 
  os.Insert(xbox<Field>($3)); 
  $$ = new Box<Orders>(os);
}

orders : ORDER field { 
  Orders os = Orders();
  os.Insert(xbox<Field>($2));
  $$ = new Box<Orders>(os); 
}

orders : { 
  Orders os = Orders();
  $$ = new Box<Orders>(os);
}

/* TODO JOINS

joins : joins ',' join { 
  Orders os = xbox<Orders>($1); 
  os.Insert(xbox<Field>($3)); 
  $$ = new Box<Orders>(os);
}

joins : join { 
  Joins os = Joins();
  os.Insert(xbox<Field>($2));
  $$ = new Box<Orders>(os); 
}

join : LEFT JOIN table ON operation { 
  Joins os = Joins();
  $$ = new Box<Joins>(os);
}

*/

sort : DESC { 
  $$ = new Box<Sort>(Sort::createDesc());
}

sort : ASC { 
  $$ = new Box<Sort>(Sort::createAsc());
}

sort : { 
  $$ = new Box<Sort>(Sort::createEmpty());
}

limit : LIMIT NUMBER {
 $$ = new Box<Limit>(Limit::createValue(xboxs($2)));
}

limit : LIMIT TEXT { 
  $$ = new Box<Limit>(Limit::createValue(xboxs($2)));
}

limit : { 
  $$ = new Box<Limit>(Limit::createEmpty());
}

groups : groups ',' field { 
  Groups gs = xbox<Groups>($1); 
  gs.Insert(xbox<Field>($3)); 
  $$ = new Box<Groups>(gs); 
}

groups : GROUP field { 
  Groups gs = Groups();  gs.Insert(xbox<Field>($2)); $$ = new Box<Groups>(gs);
}

groups : { 
  Groups gs = Groups(); $$ = new Box<Groups>(gs); 
}

%%

int yylex(void);
void yyerror(const char *);

#include <stdio.h>
#include "lex.sql.c"

Sql sql_yacc_parse(LineStream& stream) {
  AnsiString input = "";
  stream.next();
  while(!stream.isEof()) {
    AnsiString line = stream.getLine() + "\r\n";
    input += line;
    stream.next();
  }
  sql_scan_string(input.c_str());
  sqlparse(); 
  if(sqlResult!=0) {
    Sql data = xbox<Sql>(sqlResult);
    return data;
  } else 
    throw Exception("Parser error...");
}