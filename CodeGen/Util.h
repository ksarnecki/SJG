//---------------------------------------------------------------------------

#ifndef UtilH
#define UtilH
//---------------------------------------------------------------------------

#include "AnsiString.h"
#include "File.h"

extern AnsiString cap1st(const AnsiString&);
extern int findTypeByName(const DataTypeArray&, const AnsiString&);
extern DataType getTypeByName(const DataTypeArray&, const AnsiString&);

#endif
