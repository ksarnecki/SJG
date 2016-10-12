//---------------------------------------------------------------------------

#ifndef PHPGeneratorH
#define PHPGeneratorH
//---------------------------------------------------------------------------

#include "File.h"
#include "DynSet.h"
#include "AnsiString.h"

extern DynSet<AnsiString> generatePHPFile(const AnsiString& file, const DataTypeArray& data);

#endif
