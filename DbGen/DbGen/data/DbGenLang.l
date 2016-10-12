%option yylineno
%option prefix="dbgen"
%option noyywrap
%{

extern "C"
    {
        int yylex(void);
    }

#include "DbGenLang.tab.h"

%}

%%
"Exec" { return EXEC; };
\"[^\"]+\" { yylval = (int) strdup(yytext); return SPEC; }
"JOIN" { return JOIN; };
"ON" { return ON; };
"j2jApiClient" { return J2JAPICLIENT ;}
"javaApiProcessor"  { return JAVAAPISERVER ;}
"javaSync"  { return JAVASYNC ;}
"javaAsync"  { return JAVAASYNC ;}
"define method" { return METHOD_DECL; }
"apiUrl" { return APIURL; }
"query" { return QUERY;}
"update" { return UPDATE;}
"delete" { return DELETE;}
"insert" { return INSERT;}
"using" { return USING; }
"record" { return RECORD; }
"array" { return ARRAY; }
"appdata" { return APPDATA; }
"of" { return OF; }
"package" {return PACKAGE; }
"import" { return IMPORT; }
"filename" { return FILENAME; }
"To" { return TO;}
"[" { return ABEG; }
"]" { return AEND; }
"}" { return END; }
"{" { return BEG; }
"(" { return PBEG; }
")" { return PEND; }
[:|_|*|,|;|\'|%|!|=] { return *yytext; }   
[a-zA-Z_\.\/]+[a-zA-Z_\.0-9\/\*]* { yylval = (int) strdup(yytext); return TEXT; }
[0-9]+ { yylval = (int) strdup(yytext); return NUMBER; }
.|\n {};
