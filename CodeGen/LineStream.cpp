//---------------------------------------------------------------------------

#include "LineStream.h"

//---------------------------------------------------------------------------

LineStream::LineStream(const DynSet<AnsiString>& _lines) : ix(-1), lines(_lines) {
}
bool LineStream::isEof() const {
  return ix>=lines.Size();
}
AnsiString LineStream::getLine() const {
  return lines[ix];
}
void LineStream::next() {
  ix++;
  while (ix<lines.Size() && lines[ix].Length()==0)
    ix++;
}
LineStream::~LineStream() {
}

#pragma package(smart_init)
