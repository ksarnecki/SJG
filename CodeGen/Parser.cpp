//---------------------------------------------------------------------------

#include "Parser.h"
#include <cstdio>
#include "php.tab.c"
//---------------------------------------------------------------------------

DataFileBase processData(LineStream& stream) {
  return codegen_yacc_parse(stream);
}




