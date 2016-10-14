#ifndef CS_SDBRESULT_H
#define CS_SDBRESULT_H

#include "LexicalData.h"

class CSSDBResult {
  public:
    static AnsiString name();
    static AnsiString rename();
    
    static Expression changeMethod(const MultiIdentifier&);
};

#endif