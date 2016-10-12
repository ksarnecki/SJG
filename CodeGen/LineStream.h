//---------------------------------------------------------------------------

#ifndef LineStreamH
#define LineStreamH
//---------------------------------------------------------------------------

#include "AnsiString.h"
#include "DynSet.h"

class LineStream {
  int ix;
  DynSet<AnsiString> lines;
public:
  LineStream(const DynSet<AnsiString>&);
  virtual bool isEof() const;
  virtual AnsiString getLine() const;
  virtual void next();
  virtual ~LineStream();
};

#endif
