#ifndef PHP_HASHMAP_H
#define PHP_HASHMAP_H

#include "LexicalData.h"

class PHPHashMap {
  public:
    static AnsiString name();
    
    static Expression changeMethod(const MultiIdentifier&);
};

#endif