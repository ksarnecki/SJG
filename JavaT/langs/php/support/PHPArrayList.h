#ifndef PHP_ARRAYLIST_H
#define PHP_ARRAYLIST_H

#include "LexicalData.h"

class PHPArrayList {
  public:
    static AnsiString name();
    
    static Expression changeMethod(const MultiIdentifier&);
};

#endif