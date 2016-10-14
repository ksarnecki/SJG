#ifndef CS_INTEGER_H
#define CS_INTEGER_H

#include "LexicalData.h"

class CSInteger {
  public:
    static AnsiString name();
    static AnsiString rename();
    
    static Expression changeMethod(const MultiIdentifier&);
};

#endif