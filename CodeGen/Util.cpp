//---------------------------------------------------------------------------

#include "Util.h"

//---------------------------------------------------------------------------

AnsiString cap1st(const AnsiString& str) {
  if (str[1]<'a' || str[1]>'z')
    throw Exception("B³êdna nazwa " + str);
  return AnsiString((char) (str[1] - 'a' + 'A')) + str.SubString(2, str.Length() - 1);
}

int findTypeByName(const DataTypeArray& data, const AnsiString& type) {
  for (int i=0;i<data.Size();i++)
    if (data[i].getName()==type)
      return i;
  return -1;
}

DataType getTypeByName(const DataTypeArray& data, const AnsiString& type) {
  int ix = findTypeByName(data, type);
  if (ix==-1)
    throw Exception("Nieznany typ " + type);
  return data[ix];
}

#pragma package(smart_init)
