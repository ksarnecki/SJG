%option yylineno
%option prefix="sql"
%option noyywrap
%{

extern "C"
    {
        int yylex(void);
    }

#include "SqlLang.tab.h"

%}

%%
"NOT" { return NOT; };
"SET" { return SET; };
"UPDATE" { return UPDATE; };
"DELETE" { return DELETE; };
"INSERT" { return INSERT; };
"VALUES" { return VALUES; };
"INTO" { return INTO; };
"GROUP BY" { return GROUP; };
"COUNT" { return COUNT; };
"MAX" { return MAX; };
"MIN" { return MIN; };
"EXISTS" { return EXISTS; };
"END" { return END; };
"ELSE" { return ELSE; };
"CASE" { return CASE; };
"WHEN" { return WHEN; };
"THEN" { return THEN; };
">=" { return EGR; };
"<=" { return ESM; };
"!=" { return NEQ; };
"IN" { return IN; };
"AND" { return AND; };
"OR" { return OR; };
"LIKE" { return LIKE; };
"LIMIT" { return LIMIT; };
"DESC" { return DESC; };
"ASC" { return ASC; };
"AS" { return AS; };
"ORDER BY" { return ORDER; };
"SELECT" { return SELECT; };
"FROM" { return FROM; };
"WHERE" { return WHERE; };
"[" { return ABEG; }
"]" { return AEND; }
"(" { return PBEG; }
")" { return PEND; }
%\[[^\[]+\] { yylval = (int) strdup(yytext); return SPEC; }
[:|_|*|,|;|\'|%|!|=|\.|>|<|>=|<=|!=] { return *yytext; }   
\"[^\"]*\" { yylval = (int) strdup(yytext); return STRING; }
\'[^\']*\' { yylval = (int) strdup(yytext); return STRING; }
[a-zA-Z_]+[a-zA-Z_0-9\/_]* { yylval = (int) strdup(yytext); return TEXT; }
[0-9]+ { yylval = (int) strdup(yytext); return NUMBER; }
.|\n {};
