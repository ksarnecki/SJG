//---------------------------------------------------------------------------

#ifndef JavascriptGeneratorH
#define JavascriptGeneratorH
//---------------------------------------------------------------------------

#include "AnsiString.h"
#include "DynSet.h"
#include "File.h"

extern DynSet<AnsiString> generateJavascriptFile(const AnsiString& file, const DataTypeArray& data);

#endif
