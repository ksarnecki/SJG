//---------------------------------------------------------------------------

#ifndef CSGeneratorH
#define CSGeneratorH
//---------------------------------------------------------------------------

#include "AnsiString.h"
#include "DynSet.h"
#include "File.h"

extern DynSet<AnsiString> generateCSFile(const AnsiString& file, bool bin, const DataTypeArray& data);

#endif
