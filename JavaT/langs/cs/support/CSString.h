#ifndef CS_STRING_H
#define CS_STRING_H

#include "LexicalData.h"
#include "Translator.h"
#include <cstdio>

class CSString {
  public:
    static AnsiString name();
    static AnsiString rename();
    
    static Expression changeMethod(const MultiIdentifier&);
};

#endif