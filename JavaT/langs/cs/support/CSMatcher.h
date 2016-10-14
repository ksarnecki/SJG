#ifndef CS_MATCHER_H
#define CS_MATCHER_H

#include "LexicalData.h"

class CSMatcher {
  public:
    static AnsiString name();
    static AnsiString rename();
    
    static Expression changeMethod(const MultiIdentifier&);
};

#endif