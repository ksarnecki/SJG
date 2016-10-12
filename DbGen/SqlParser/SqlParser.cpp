//---------------------------------------------------------------------------

#include "SqlParser.h"
#include <cstdio>
#include "SqlLang.tab.c"
//---------------------------------------------------------------------------

Sql sqlProcessData(LineStream& stream) {
  return sql_yacc_parse(stream);
}




