//---------------------------------------------------------------------------

#ifndef CPPGeneratorH
#define CPPGeneratorH
//---------------------------------------------------------------------------

#include "AnsiString.h"
#include "DynSet.h"
#include "File.h"

extern DynSet<AnsiString> generateHFile(const AnsiString& file, bool, bool, bool, bool, const DataTypeArray& data);
extern DynSet<AnsiString> generateCppFile(const AnsiString& file, bool, bool, bool, bool, const DataTypeArray& data);

#endif
