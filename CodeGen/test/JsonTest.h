#ifndef _JSONTEST_GEN_H_
#define _JSONTEST_GEN_H_
#include "DynSet.h"
#include <stdio.h>
#include <stdlib.h>
//------------- int ---------------
//----------------------------------

//------------- string ---------------
#include "AnsiString.h"
//----------------------------------

//------------- IntArray ---------------
#include "DynSet.h"


class IntArray : public DynSet<int> {
public:
  IntArray();

  virtual AnsiString toJSON() const;
  static IntArray fromJSON(AnsiString);

  virtual ~IntArray();

};
//----------------------------------

//------------- StringArray ---------------
#include "DynSet.h"


class StringArray : public DynSet<AnsiString> {
public:
  StringArray();

  virtual AnsiString toJSON() const;
  static StringArray fromJSON(AnsiString);

  virtual ~StringArray();

};
//----------------------------------

//------------- Wariant ---------------
class Wariant {
  int _type;
  void* _ptr;

  static const int _TypeInty;
  static const int _TypeStry;

  virtual void init(int, void*);
  virtual void clean();
  Wariant();
public:
  Wariant(const Wariant&);
  virtual Wariant& operator=(const Wariant&);

  virtual bool isInty() const;
  virtual bool isStry() const;

  virtual const IntArray& asInty() const;
  virtual IntArray& asInty();
  virtual const StringArray& asStry() const;
  virtual StringArray& asStry();

  virtual AnsiString toJSON() const;
  static Wariant fromJSON(AnsiString);

  virtual ~Wariant();

  static Wariant createInty(const IntArray&);
  static Wariant createStry(const StringArray&);

};
//----------------------------------

//------------- Rekord ---------------
class Rekord {
  Wariant pierwszy;
  int drugi;
  AnsiString trzeci;
  IntArray czwarty;
public:
  Rekord(const Wariant&, const int&, const AnsiString&, const IntArray&);
  virtual const Wariant& getPierwszy() const;
  virtual const int& getDrugi() const;
  virtual const AnsiString& getTrzeci() const;
  virtual const IntArray& getCzwarty() const;
  virtual Wariant& getPierwszy();
  virtual int& getDrugi();
  virtual AnsiString& getTrzeci();
  virtual IntArray& getCzwarty();

  virtual AnsiString toJSON() const;
  static Rekord fromJSON(AnsiString);

  virtual ~Rekord();

};
//----------------------------------

//------------- Rekordy ---------------
#include "DynSet.h"


class Rekordy : public DynSet<Rekord> {
public:
  Rekordy();

  virtual AnsiString toJSON() const;
  static Rekordy fromJSON(AnsiString);

  virtual ~Rekordy();

};
//----------------------------------

#endif
