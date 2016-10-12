
#include "AppData.h"
#include "Exception.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
//----------------------------------

//------------- Event ---------------
Event::Event(const int& _id, const AnsiString& _type, const int& _session) : id(_id), type(_type), session(_session) {
}
const int& Event::getId() const {
  return id;
}
int& Event::getId() {
  return id;
}
const AnsiString& Event::getType() const {
  return type;
}
AnsiString& Event::getType() {
  return type;
}
const int& Event::getSession() const {
  return session;
}
int& Event::getSession() {
  return session;
}
Event::~Event() {
}
//----------------------------------

