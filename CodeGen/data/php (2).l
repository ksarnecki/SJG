%option yylineno
%option prefix="codegen"
%{

extern "C"
    {
        int yylex(void);
    }

#include "php.tab.h"

%}

%%
[;] { return *yytext; } 
[,] { return *yytext; } 
[:] { return *yytext; } 
[[] { return *yytext; } 
[]] { return *yytext; } 
[=] { return *yytext; } 
[{] { return *yytext; } 
[}] { return *yytext; } 
[|] { return *yytext; } 
"array of" { yylval = (int) strdup("int"); return ARRAY; }
"int" { yylval = (int) strdup("int"); return INT; }
"string" { yylval = (int) strdup("string"); return STRING; }
"bool" { yylval = (int) strdup("bool"); return BOOL; }
"basic" { return BASIC; }
"external" { return EXTERNAL; }
"record" { return RECORD; }
"variant" { return VARIANT; }
\/\/.+\n { }
[a-zA-Z$0-9\(\)\.\*\/?\-_"]+ { yylval = (int) strdup(yytext); return TEXT; }
.|\n {};
