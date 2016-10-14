#ifndef CS_HASHMAP_H
#define CS_HASHMAP_H

#include "LexicalData.h"

class CSHashMap {
  public:
    static AnsiString name();
    static AnsiString rename();
    
    static Expression changeMethod(const MultiIdentifier&);
};

#endif