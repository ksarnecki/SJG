#ifndef CS_ARRAY_H
#define CS_ARRAY_H

#include "LexicalData.h"

class CSArray {
  public:
    static AnsiString name();
    static AnsiString rename();
    
    static Expression changeMethod(const MultiIdentifier&);
};

#endif