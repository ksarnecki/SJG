#ifndef _APPDATA_GEN_H_
#define _APPDATA_GEN_H_
#include "DynSet.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
#include "AnsiString.h"
//----------------------------------

//------------- Event ---------------
class Event {
  int id;
  AnsiString type;
  int session;
public:
  Event(const int&, const AnsiString&, const int&);
  virtual const int& getId() const;
  virtual const AnsiString& getType() const;
  virtual const int& getSession() const;
  virtual int& getId();
  virtual AnsiString& getType();
  virtual int& getSession();


  virtual ~Event();

};
//----------------------------------

#endif
