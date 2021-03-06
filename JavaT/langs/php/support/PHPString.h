#ifndef PHP_STRING_H
#define PHP_STRING_H

#include "LexicalData.h"
#include "Translator.h"

class PHPString {
  public:
    static AnsiString name();
    
    static Expression changeMethod(const MultiIdentifier&);
};

#endif