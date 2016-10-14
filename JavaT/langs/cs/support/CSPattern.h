#ifndef CS_PATTERN_H
#define CS_PATTERN_H

#include "LexicalData.h"
#include <cstdio>

class CSPattern {
  public:
    static AnsiString name();
    static AnsiString rename();
    
    static Expression changeMethod(const MultiIdentifier&);
};

#endif