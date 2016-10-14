%option yylineno
%option prefix="javat"
%{

extern "C"
    {
        int yylex(void);
    }

#include "php.tab.h"

%}

%%
\"(\\.|[^"])*\" { yylval = (int) strdup(yytext); return STRING; }
\'[^\']+\' { yylval = (int) strdup(yytext); return CHAR; }
\<[a-zA-Z0-9\_\ \,]+\> { yylval = (int) strdup(yytext); return TEMPL; }
[0-9]+ { yylval = (int) strdup(yytext); return INT;}
"[" { return ABEG; }
"]" { return AEND; }
"}" { return END; }
"{" { return BEG; }
"(" { return PBEG; }
")" { return PEND; }
[;] { return *yytext; }
[,] { return *yytext; } 
[=] { return *yytext; } 
[<] { return *yytext; }
[>] { return *yytext; }
[\.] { return *yytext; }
[+] { return *yytext; }
[-] { return *yytext; }
[*] { return *yytext; }
[/] { return *yytext; }
[?] { return *yytext; }
[:] { return *yytext; }
["\""] { return *yytext; }
"==" { return EQ; }
">=" { return EGR; }
"<=" { return ESM; }
"!=" { return NEQ; }
"++" { return INC; }
"+=" { return AAS; }
"-=" { return SAS; }
"--" { return DEC; }
"while" { return WHILE; }
"for" { return FOR; }
"if" { return IF; }
"else" { return ELSE; }
"public" { return PUBLIC; }
"new" { return NEW; }
"async" { return ASYNC; }
"await" { return AWAIT; }
"return" { return RETURN; }
"import" { return IMPORT; }
"class" { return CLASS; }
"private" { return PRIVATE; }
"static" { return STATIC; }
"final" { return FINAL; }
"package" { return PACKAGE; }
\/\/.+\n { }
[a-zA-Z0-9\_]+ { yylval = (int) strdup(yytext); return TEXT; }
.|\n {};

