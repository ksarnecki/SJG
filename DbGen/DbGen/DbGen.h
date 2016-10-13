#ifndef INTERNALGEN_H
#define INTERNALGEN_H

#include "../CodeGen/Parser.h"
#include "../CodeGen/Util.h"
#include "../CodeGen/JavaGenerator.h"

#include "../SqlParser/SqlParser.h"

#include "data/Data.h"
#include "DbGenParser.h"

void generateJava(const DbFile&, const DataTypeArray&);
AnsiString parseSql(AnsiString);
AnsiString clearString(AnsiString);
AnsiString parseSql(AnsiString);
#endif