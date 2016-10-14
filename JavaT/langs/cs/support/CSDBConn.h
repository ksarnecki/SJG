#ifndef CS_DBCONN_H
#define CS_DBCONN_H

#include "LexicalData.h"

class CSDBConn {
  public:
    static AnsiString name();
    static AnsiString rename();
    
    static Expression changeMethod(const MultiIdentifier&);
};

#endif