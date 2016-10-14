#ifndef BUILDER_H
#define BUILDER_H

#include <cstdio>
#include "AnsiString.h"
#include "LexicalData.h"

class Builder {
  private:
    DynSet<AnsiString> lines;
    
  public:
    AnsiString expressionToString(const Expression&);
    
    AnsiString act();
    void append(const AnsiString&);
    void appendLine(const AnsiString&);
    void next();
    
    void print();
};

#endif