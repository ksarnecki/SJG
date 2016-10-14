#ifndef CS_MAPENTRY_H
#define CS_MAPENTRY_H

#include "LexicalData.h"

class CSMapEntry {
  public:
    static AnsiString name();
    static AnsiString rename();
    
    static Expression changeMethod(const MultiIdentifier&);
};

#endif