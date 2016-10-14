#ifndef PHP_ARRAY_H
#define PHP_ARRAY_H

#include "LexicalData.h"

class PHPArray {
  public:
    static AnsiString name();
    
    static Expression changeMethod(const MultiIdentifier&);
};

#endif