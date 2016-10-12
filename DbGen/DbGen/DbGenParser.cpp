//---------------------------------------------------------------------------

#include "DbGenParser.h"
#include <cstdio>
#include "DbGenLang.tab.c"
//---------------------------------------------------------------------------

DbFile dbGenProcessData(LineStream& stream) {
  return dbgen_yacc_parse(stream);
}




