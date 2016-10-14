#include "CSInteger.h"

AnsiString CSInteger::name() {
  return "Integer";
}

AnsiString CSInteger::rename() {
  return "int";
}

Expression CSInteger::changeMethod(const MultiIdentifier& mi) {
  return Expression::createEmpty();
}