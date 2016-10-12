
#include "JsonTest.h"
#include "Exception.h"
#include "StringBuffer.h"
#include "JSONUtil.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
//----------------------------------

//------------- IntArray ---------------
IntArray::IntArray() {
}
AnsiString IntArray::toJSON() const {
  StringBuffer _json;
  _json += "[";
  for (int _i=0;_i<Size();_i++) {
    if (_i!=0) _json += ",";
    _json += AnsiString((*this)[_i]);
  }
    _json += "]";
    return _json.get();
}
IntArray IntArray::fromJSON(AnsiString s) {
    IntArray arr = IntArray();
    int ix=1;
    while(ix <= s.Length() && s[ix]!='[')
      ix++;
    ix++;
    if (ix >s.Length()) 
      throw Exception("IntArray::fromJSON");
    while(ix<=s.Length()) {
      int start = ix;
      bool inString = false;
      int bracketLevel = 0;
      while(ix<=s.Length()) {
        if (s[ix] == '\\')
          ix+=2;
        else if (s[ix] == '"')
          inString = !inString;
        else if (!inString && s[ix] == '[')
          bracketLevel++;
        else if (!inString && s[ix] == '{')
          bracketLevel++;
        else if (!inString && s[ix] == ']')
          bracketLevel--;
        else if (!inString && s[ix] == '}')
          bracketLevel--;
        if (bracketLevel <= 0 && !inString && (s[ix] == ',' || ix == s.Length())) {
          if (start == ix)
            return arr;
          AnsiString tmp = s.SubString(start, ix-start);
          arr.Insert(atoi(tmp.c_str()));
          ix++;
          break;
        }
        ix++;
      }
    }
    return arr;
  }
IntArray::~IntArray() {
}
//----------------------------------

//------------- StringArray ---------------
StringArray::StringArray() {
}
AnsiString StringArray::toJSON() const {
  StringBuffer _json;
  _json += "[";
  for (int _i=0;_i<Size();_i++) {
    if (_i!=0) _json += ",";
    _json += "\"" + JSONEscape::encode((*this)[_i]) + "\"";
  }
    _json += "]";
    return _json.get();
}
StringArray StringArray::fromJSON(AnsiString s) {
    StringArray arr = StringArray();
    int ix=1;
    while(ix <= s.Length() && s[ix]!='[')
      ix++;
    ix++;
    if (ix >s.Length()) 
      throw Exception("StringArray::fromJSON");
    while(ix<=s.Length()) {
      int start = ix;
      bool inString = false;
      int bracketLevel = 0;
      while(ix<=s.Length()) {
        if (s[ix] == '\\')
          ix+=2;
        else if (s[ix] == '"')
          inString = !inString;
        else if (!inString && s[ix] == '[')
          bracketLevel++;
        else if (!inString && s[ix] == '{')
          bracketLevel++;
        else if (!inString && s[ix] == ']')
          bracketLevel--;
        else if (!inString && s[ix] == '}')
          bracketLevel--;
        if (bracketLevel <= 0 && !inString && (s[ix] == ',' || ix == s.Length())) {
          if (start == ix)
            return arr;
          AnsiString tmp = s.SubString(start, ix-start);
          arr.Insert(JSONEscape::decode(tmp.SubString(2, tmp.Length()-2)));
          ix++;
          break;
        }
        ix++;
      }
    }
    return arr;
  }
StringArray::~StringArray() {
}
//----------------------------------

//------------- Wariant ---------------
const int Wariant::_TypeInty = 0;
const int Wariant::_TypeStry = 1;
void Wariant::init(int type, void* ptr) {
  if (type==_TypeInty) {
    _type = type;
    _ptr = new IntArray(*(IntArray*) ptr);
  } else if (type==_TypeStry) {
    _type = type;
    _ptr = new StringArray(*(StringArray*) ptr);
  }
}
void Wariant::clean() {
  if (_type==_TypeInty) {
    _type = -1;
    delete (IntArray*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeStry) {
    _type = -1;
    delete (StringArray*) _ptr;
    _ptr = 0;
  }
}
Wariant::Wariant() : _type(-1), _ptr(0) {
}
Wariant::Wariant(const Wariant& _value) {
  init(_value._type, _value._ptr);
}
Wariant& Wariant::operator=(const Wariant& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool Wariant::isInty() const {
  return _type==_TypeInty;
}
bool Wariant::isStry() const {
  return _type==_TypeStry;
}
const IntArray& Wariant::asInty() const {
  if (_type!=_TypeInty)
    throw Exception("Wariant::asInty");
  return *(IntArray*) _ptr;
}
IntArray& Wariant::asInty() {
  if (_type!=_TypeInty)
    throw Exception("Wariant::asInty");
  return *(IntArray*) _ptr;
}
const StringArray& Wariant::asStry() const {
  if (_type!=_TypeStry)
    throw Exception("Wariant::asStry");
  return *(StringArray*) _ptr;
}
StringArray& Wariant::asStry() {
  if (_type!=_TypeStry)
    throw Exception("Wariant::asStry");
  return *(StringArray*) _ptr;
}

AnsiString Wariant::toJSON() const {
  StringBuffer _json;
   _json += "{\"type\":" + AnsiString(_type) + ",\"value\":";
    if (_type==0)
    _json += ((IntArray*) _ptr)->toJSON();
    else if (_type==1)
    _json += ((StringArray*) _ptr)->toJSON();
    else
      throw Exception("Wariant::toJSON(" + AnsiString(_type) + ")");
    _json += "}";
    return _json.get();
}
Wariant Wariant::fromJSON(AnsiString s) {
    int ix = 1;
    while(ix <= s.Length() && s[ix] != ':')
      ix++;
    if (ix >s.Length()) 
      throw Exception("Wariant::fromJSON");
     if (s.Length() > ix+1+1 && s.SubString(ix+1, 1)==("0")) {
      s = s.SubString(ix+10+1, s.Length()-ix-10-1);
      return Wariant::createInty(IntArray::fromJSON(s));
    } else if (s.Length() > ix+1+1 && s.SubString(ix+1, 1)==("1")) {
      s = s.SubString(ix+10+1, s.Length()-ix-10-1);
      return Wariant::createStry(StringArray::fromJSON(s));
    }
    AnsiString variantName = "";
    ix = 1;
    while(ix <= s.Length() && s.[ix] != ':')
      ix++;
    if (ix >s.Length()) 
      throw Exception("Wariant::fromJSON");
    variantName = s.SubString(3, ix-4);
     if (variantName==("inty")) {
      s = s.SubString(ix+1, s.Length()-ix-1);
      return Wariant::createInty(IntArray::fromJSON(s));
    } else if (variantName==("stry")) {
      s = s.SubString(ix+1, s.Length()-ix-1);
      return Wariant::createStry(StringArray::fromJSON(s));
    } else 
    throw Exception("Wariant::fromJSON");
  }

Wariant::~Wariant() {
  clean();
}
Wariant Wariant::createInty(const IntArray& _param) {
  Wariant _value;
  _value._type = _TypeInty;
  _value._ptr = new IntArray(_param);
  return _value;
}
Wariant Wariant::createStry(const StringArray& _param) {
  Wariant _value;
  _value._type = _TypeStry;
  _value._ptr = new StringArray(_param);
  return _value;
}


//----------------------------------

//------------- Rekord ---------------
Rekord::Rekord(const Wariant& _pierwszy, const int& _drugi, const AnsiString& _trzeci, const IntArray& _czwarty) : pierwszy(_pierwszy), drugi(_drugi), trzeci(_trzeci), czwarty(_czwarty) {
}
const Wariant& Rekord::getPierwszy() const {
  return pierwszy;
}
Wariant& Rekord::getPierwszy() {
  return pierwszy;
}
const int& Rekord::getDrugi() const {
  return drugi;
}
int& Rekord::getDrugi() {
  return drugi;
}
const AnsiString& Rekord::getTrzeci() const {
  return trzeci;
}
AnsiString& Rekord::getTrzeci() {
  return trzeci;
}
const IntArray& Rekord::getCzwarty() const {
  return czwarty;
}
IntArray& Rekord::getCzwarty() {
  return czwarty;
}
AnsiString Rekord::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"pierwszy\":";
    _json += pierwszy.toJSON();
    _json += ",";
    _json += "\"drugi\":";
    _json += AnsiString(drugi);
    _json += ",";
    _json += "\"trzeci\":";
    _json += "\"" + JSONEscape::encode(trzeci) + "\"";
    _json += ",";
    _json += "\"czwarty\":";
    _json += czwarty.toJSON();
  _json += "}";
  return _json.get();
}
Rekord Rekord::fromJSON(AnsiString s) {
    AnsiString arr[4];
    int ix=1;
    for(int i=0;i<4;i++) {
      while(ix <= s.Length() &&  s[ix] != ':')
        ix++;
      if (ix >s.Length()) 
        throw Exception("Rekord::fromJSON");
      int start = ix;
      bool inString = false;
      int bracketLevel = 0;
      while(ix<=s.Length()) {
        if (s[ix] == '\\')
          ix+=2;
        else if (s[ix] == '"')
          inString = !inString;
        else if (!inString && s[ix] == '[')
          bracketLevel++;
        else if (!inString && s[ix] == '{')
          bracketLevel++;
        else if (!inString && s[ix] == ']')
          bracketLevel--;
        else if (!inString && s[ix] == '}')
          bracketLevel--;
        if (bracketLevel <= 0 && !inString && (s[ix] == ',' || ix == s.Length())) {
          if (i < 4) {
            arr[i] = s.SubString(start+1, ix-start-1);
          }
          ix++;
          break;
        }
        ix++;
      }
    }
    return Rekord(Wariant::fromJSON(arr[0]), atoi(arr[1].c_str()), JSONEscape::decode(arr[2].SubString(2, arr[2].Length()-2)), IntArray::fromJSON(arr[3]));
  }
Rekord::~Rekord() {
}
//----------------------------------

//------------- Rekordy ---------------
Rekordy::Rekordy() {
}
AnsiString Rekordy::toJSON() const {
  StringBuffer _json;
  _json += "[";
  for (int _i=0;_i<Size();_i++) {
    if (_i!=0) _json += ",";
    _json += (*this)[_i].toJSON();
  }
    _json += "]";
    return _json.get();
}
Rekordy Rekordy::fromJSON(AnsiString s) {
    Rekordy arr = Rekordy();
    int ix=1;
    while(ix <= s.Length() && s[ix]!='[')
      ix++;
    ix++;
    if (ix >s.Length()) 
      throw Exception("Rekordy::fromJSON");
    while(ix<=s.Length()) {
      int start = ix;
      bool inString = false;
      int bracketLevel = 0;
      while(ix<=s.Length()) {
        if (s[ix] == '\\')
          ix+=2;
        else if (s[ix] == '"')
          inString = !inString;
        else if (!inString && s[ix] == '[')
          bracketLevel++;
        else if (!inString && s[ix] == '{')
          bracketLevel++;
        else if (!inString && s[ix] == ']')
          bracketLevel--;
        else if (!inString && s[ix] == '}')
          bracketLevel--;
        if (bracketLevel <= 0 && !inString && (s[ix] == ',' || ix == s.Length())) {
          if (start == ix)
            return arr;
          AnsiString tmp = s.SubString(start, ix-start);
          arr.Insert(Rekord::fromJSON(tmp));
          ix++;
          break;
        }
        ix++;
      }
    }
    return arr;
  }
Rekordy::~Rekordy() {
}
//----------------------------------

