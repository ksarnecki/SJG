%define api.prefix {dbgen}
%{

#include <string.h>
#include <malloc.h>
#include <stdio.h>

#include "data/Data.h"
#include "DbGen.h"

extern "C" {
  int yyparse(void);
  int yylex(void);
  int yywrap() {
    return 1;
  }
  extern int dbgenlineno;
  extern char* dbgentext;
}

void yyerror(const char *s) {
  printf("%s at line %d", s, dbgenlineno);
  if (dbgentext!=0)
    printf(", near token %s", dbgentext);
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

DbFile* fresult = 0;

%}

%token	RECORD ARRAY OF MINUS PLUS NUMBER INT APPDATA STRING METHOD_DECL SPEC BEGIN BEG END ABEG AEND PBEG PEND FILENAME COLON J2JAPICLIENT APIURL UPDATE JAVAAPISERVER  JAVASYNC JAVAASYNC PACKAGE DELETE INSERT IMPORT EXEC TEXT QUERY TO USING JOIN ON  /* wszystkie nazwy tokenow majace wiecej niz jeden znak musza byc zadeklarowane */

%%

dbfile : outputfiles inputfile { fresult = new DbFile(xbox<OutputFiles>($1), xbox<InputFile>($2));}

outputfiles : outputfiles outputfile { OutputFiles s = xbox<OutputFiles>($1); s.Insert(xbox<OutputFile>($2)); $$ = new Box<OutputFiles>(s);}
outputfiles : outputfile { OutputFiles s = OutputFiles(); s.Insert(xbox<OutputFile>($1)); $$ = new Box<OutputFiles>(s);}
outputfile : outputfilekind BEG filename package imports END { $$ = new Box<OutputFile>(OutputFile(xbox<OutputFileKind>($1),xboxs($3),xboxs($4), xbox<StringArray>($5)));  }
outputfile : J2JAPICLIENT BEG filename package imports apiurl END { $$ = new Box<OutputFile>(OutputFile(OutputFileKind::createJ2jApiClient(xbox<AnsiString>($6)),xboxs($3),xboxs($4), xbox<StringArray>($5)));  }
outputfilekind : JAVAAPISERVER { $$ = new Box<OutputFileKind>(OutputFileKind::createJavaApiProcessor()); }
outputfilekind : JAVASYNC { $$ = new Box<OutputFileKind>(OutputFileKind::createJavaSync()); }
outputfilekind : JAVAASYNC { $$ = new Box<OutputFileKind>(OutputFileKind::createJavaAsync()); }

apiurl: APIURL TEXT ';' { $$ = new Box<AnsiString>(xboxs($2)); }

inputfile: appdata elems { $$ = new Box<InputFile>(InputFile(xboxs($1), xbox<Elems>($2))); } 

package: PACKAGE TEXT ';' { $$ = $2; }
filename: FILENAME TEXT ';' { $$ = $2; }
appdata: APPDATA TEXT ';' { $$ = $2; }
imports: imports import { StringArray arr = xbox<StringArray>($1); arr.Insert(xbox<AnsiString>($2)); $$ = new Box<StringArray>(arr); }
imports: { $$ = new Box<StringArray>(StringArray());}
import: IMPORT TEXT ';' { $$ = new Box<AnsiString>("import " + xboxs($2) + ";");} 

elems: elems elem { Elems m = xbox<Elems>($1); m.Insert(xbox<Elem>($2)); $$ = new Box<Elems>(m); }
elems: elem { Elems m; m.Insert(xbox<Elem>($1)); $$ = new Box<Elems>(m); }

elem: QUERY TEXT TEXT PBEG select_params PEND spec joins ';' { Elem e = Elem::createSelect( Select( xboxs($2), xboxs($3), xbox<SelectParams>($5), xbox<AnsiString>($7), xbox<Joins>($8) ) ); $$ = new Box<Elem>( e ); }
elem: INSERT TEXT PBEG select_params PEND non_empty_spec ';' { Elem e = Elem::createInsert( Insert(xboxs($2), xbox<SelectParams>($4), xbox<AnsiString>($6))); $$ = new Box<Elem>( e ); }
elem: UPDATE TEXT PBEG select_params PEND non_empty_spec ';' { Elem e = Elem::createUpdate( Update(xboxs($2), xbox<SelectParams>($4), xbox<AnsiString>($6))); $$ = new Box<Elem>( e ); }
elem: DELETE TEXT PBEG select_params PEND non_empty_spec ';' { Elem e = Elem::createDelete( Delete(xboxs($2), xbox<SelectParams>($4), xbox<AnsiString>($6))); $$ = new Box<Elem>( e ); }

spec : non_empty_spec { $$ = $1; }
spec : { $$ = new Box<AnsiString>(""); }

non_empty_spec : SPEC { $$ = new Box<AnsiString>(xboxs($1)); }

joins: joins join { Joins js = xbox<Joins> ($1); js.Insert(xbox<Join>($2)); $$ = new Box<Joins>(js);}
joins: { $$ = new Box<Joins>(Joins());}
join: JOIN TEXT '=' TEXT PBEG args PEND ON TEXT '=' TEXT { Join j = Join(xboxs($2),xboxs($4),xbox<StringArray>($6),xboxs($9),xboxs($11)); $$ = new Box<Join>( j ); }
join: JOIN TEXT '=' TEXT PBEG args PEND { Join j = Join(xboxs($2),xboxs($4),xbox<StringArray>($6),"",""); $$ = new Box<Join>( j ); }
join: JOIN TEXT '=' TEXT PBEG PEND { Join j = Join(xboxs($2),xboxs($4), StringArray(),"",""); $$ = new Box<Join>( j ); }

args : args ',' TEXT { StringArray arr = xbox<StringArray>($1); arr.Insert(xboxs($3)); $$ = new Box<StringArray>(arr);}
args : TEXT { StringArray arr; arr.Insert(xboxs($1)); $$ = new Box<StringArray>(arr);}
args : { $$ = new Box<StringArray>(StringArray()); }

select_params: select_param { SelectParams m; m.Insert(xbox<SelectParam>($1)); $$ = new Box<SelectParams>(m); }
select_params: select_params ',' select_param { SelectParams m = xbox<SelectParams>($1); m.Insert(xbox<SelectParam>($3)); $$ = new Box<SelectParams>(m); }
select_params: { $$ = new Box<SelectParams>(SelectParams());}

select_param: TEXT ':' TEXT { $$ = new Box<SelectParam>(SelectParam(xboxs($1), SelectParamType::createPlain(xboxs($3)) )); }
select_param: TEXT ':' TEXT ABEG AEND { $$ = new Box<SelectParam>(SelectParam(xboxs($1), SelectParamType::createArray(xboxs($3)) )); }

%%

int yylex(void);
void yyerror(const char *);

#include <stdio.h>
#include "lex.dbgen.c"

DbFile dbgen_yacc_parse(LineStream& stream) {
  AnsiString input = "";
  stream.next();
  while(!stream.isEof()) {
    AnsiString line = stream.getLine() + "\r\n";
    input += line;
    stream.next();
  }
  dbgen_scan_string(input.c_str());
  dbgenparse(); 
  if(fresult!=0) {
    DbFile data = *fresult;
    return data;
  } else 
    throw Exception("Parser error...");
}