#ifndef INTERNALGEN_H
#define INTERNALGEN_H

#include "../CodeGen4/Parser.h"
#include "../CodeGen4/Util.h"
#include "../CodeGen4/JavaGenerator.h"

#include "../SqlParser/SqlParser.h"

#include "data/Data.h"
#include "DbGenParser.h"

void generateJava(const DbFile&, const DataTypeArray&);
AnsiString parseSql(AnsiString);
AnsiString clearString(AnsiString);
AnsiString parseSql(AnsiString);
#endif