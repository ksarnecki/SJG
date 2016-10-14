
#include "SyntaxData.h"
#include "Exception.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
//----------------------------------

//------------- HashMapFake ---------------
HashMapFake::HashMapFake() {
}
HashMapFake::~HashMapFake() {
}
//----------------------------------

//------------- MapEntryFake ---------------
MapEntryFake::MapEntryFake() {
}
MapEntryFake::~MapEntryFake() {
}
//----------------------------------

//------------- RealType ---------------
const int RealType::_TypeJavaLangInteger = 0;
const int RealType::_TypeJavaLangString = 1;
const int RealType::_TypeJavaLangArray = 2;
const int RealType::_TypeJavaUtilRegexPattern = 3;
const int RealType::_TypeJavaUtilRegexMatcher = 4;
const int RealType::_TypeJavaUtilHashMap = 5;
const int RealType::_TypeJavaUtilMapEntry = 6;
const int RealType::_TypeLkDBConn = 7;
const int RealType::_TypeLkSDBResult = 8;
const int RealType::_TypeUnknown = 9;
void RealType::init(int type, void* ptr) {
  if (type==_TypeJavaLangInteger) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeJavaLangString) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeJavaLangArray) {
    _type = type;
    _ptr = new RealType(*(RealType*) ptr);
  } else if (type==_TypeJavaUtilRegexPattern) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeJavaUtilRegexMatcher) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeJavaUtilHashMap) {
    _type = type;
    _ptr = new HashMap(*(HashMap*) ptr);
  } else if (type==_TypeJavaUtilMapEntry) {
    _type = type;
    _ptr = new MapEntry(*(MapEntry*) ptr);
  } else if (type==_TypeLkDBConn) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeLkSDBResult) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeUnknown) {
    _type = type;
    _ptr = 0;
  }
}
void RealType::clean() {
  if (_type==_TypeJavaLangInteger) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("RealType::clean()");
  } else if (_type==_TypeJavaLangString) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("RealType::clean()");
  } else if (_type==_TypeJavaLangArray) {
    _type = -1;
    delete (RealType*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeJavaUtilRegexPattern) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("RealType::clean()");
  } else if (_type==_TypeJavaUtilRegexMatcher) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("RealType::clean()");
  } else if (_type==_TypeJavaUtilHashMap) {
    _type = -1;
    delete (HashMap*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeJavaUtilMapEntry) {
    _type = -1;
    delete (MapEntry*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeLkDBConn) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("RealType::clean()");
  } else if (_type==_TypeLkSDBResult) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("RealType::clean()");
  } else if (_type==_TypeUnknown) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("RealType::clean()");
  }
}
RealType::RealType() : _type(-1), _ptr(0) {
}
RealType::RealType(const RealType& _value) {
  init(_value._type, _value._ptr);
}
RealType& RealType::operator=(const RealType& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool RealType::isJavaLangInteger() const {
  return _type==_TypeJavaLangInteger;
}
bool RealType::isJavaLangString() const {
  return _type==_TypeJavaLangString;
}
bool RealType::isJavaLangArray() const {
  return _type==_TypeJavaLangArray;
}
bool RealType::isJavaUtilRegexPattern() const {
  return _type==_TypeJavaUtilRegexPattern;
}
bool RealType::isJavaUtilRegexMatcher() const {
  return _type==_TypeJavaUtilRegexMatcher;
}
bool RealType::isJavaUtilHashMap() const {
  return _type==_TypeJavaUtilHashMap;
}
bool RealType::isJavaUtilMapEntry() const {
  return _type==_TypeJavaUtilMapEntry;
}
bool RealType::isLkDBConn() const {
  return _type==_TypeLkDBConn;
}
bool RealType::isLkSDBResult() const {
  return _type==_TypeLkSDBResult;
}
bool RealType::isUnknown() const {
  return _type==_TypeUnknown;
}
const RealType& RealType::asJavaLangArray() const {
  if (_type!=_TypeJavaLangArray)
    throw Exception("RealType::asJavaLangArray");
  return *(RealType*) _ptr;
}
RealType& RealType::asJavaLangArray() {
  if (_type!=_TypeJavaLangArray)
    throw Exception("RealType::asJavaLangArray");
  return *(RealType*) _ptr;
}
const HashMap& RealType::asJavaUtilHashMap() const {
  if (_type!=_TypeJavaUtilHashMap)
    throw Exception("RealType::asJavaUtilHashMap");
  return *(HashMap*) _ptr;
}
HashMap& RealType::asJavaUtilHashMap() {
  if (_type!=_TypeJavaUtilHashMap)
    throw Exception("RealType::asJavaUtilHashMap");
  return *(HashMap*) _ptr;
}
const MapEntry& RealType::asJavaUtilMapEntry() const {
  if (_type!=_TypeJavaUtilMapEntry)
    throw Exception("RealType::asJavaUtilMapEntry");
  return *(MapEntry*) _ptr;
}
MapEntry& RealType::asJavaUtilMapEntry() {
  if (_type!=_TypeJavaUtilMapEntry)
    throw Exception("RealType::asJavaUtilMapEntry");
  return *(MapEntry*) _ptr;
}


RealType::~RealType() {
  clean();
}
RealType RealType::createJavaLangInteger() {
  RealType _value;
  _value._type = _TypeJavaLangInteger;
  _value._ptr = 0;
  return _value;
}
RealType RealType::createJavaLangString() {
  RealType _value;
  _value._type = _TypeJavaLangString;
  _value._ptr = 0;
  return _value;
}
RealType RealType::createJavaLangArray(const RealType& _param) {
  RealType _value;
  _value._type = _TypeJavaLangArray;
  _value._ptr = new RealType(_param);
  return _value;
}
RealType RealType::createJavaUtilRegexPattern() {
  RealType _value;
  _value._type = _TypeJavaUtilRegexPattern;
  _value._ptr = 0;
  return _value;
}
RealType RealType::createJavaUtilRegexMatcher() {
  RealType _value;
  _value._type = _TypeJavaUtilRegexMatcher;
  _value._ptr = 0;
  return _value;
}
RealType RealType::createJavaUtilHashMap(const HashMap& _param) {
  RealType _value;
  _value._type = _TypeJavaUtilHashMap;
  _value._ptr = new HashMap(_param);
  return _value;
}
RealType RealType::createJavaUtilMapEntry(const MapEntry& _param) {
  RealType _value;
  _value._type = _TypeJavaUtilMapEntry;
  _value._ptr = new MapEntry(_param);
  return _value;
}
RealType RealType::createLkDBConn() {
  RealType _value;
  _value._type = _TypeLkDBConn;
  _value._ptr = 0;
  return _value;
}
RealType RealType::createLkSDBResult() {
  RealType _value;
  _value._type = _TypeLkSDBResult;
  _value._ptr = 0;
  return _value;
}
RealType RealType::createUnknown() {
  RealType _value;
  _value._type = _TypeUnknown;
  _value._ptr = 0;
  return _value;
}


//----------------------------------

//------------- HashMap ---------------
HashMap::HashMap(const RealType& _key, const RealType& _value) : key(_key), value(_value) {
}
const RealType& HashMap::getKey() const {
  return key;
}
RealType& HashMap::getKey() {
  return key;
}
const RealType& HashMap::getValue() const {
  return value;
}
RealType& HashMap::getValue() {
  return value;
}
HashMap::~HashMap() {
}
//----------------------------------

//------------- MapEntry ---------------
MapEntry::MapEntry(const RealType& _key, const RealType& _value) : key(_key), value(_value) {
}
const RealType& MapEntry::getKey() const {
  return key;
}
RealType& MapEntry::getKey() {
  return key;
}
const RealType& MapEntry::getValue() const {
  return value;
}
RealType& MapEntry::getValue() {
  return value;
}
MapEntry::~MapEntry() {
}
//----------------------------------

//------------- TypeInfo ---------------
TypeInfo::TypeInfo(const AnsiString& _name, const RealType& _realType) : name(_name), realType(_realType) {
}
const AnsiString& TypeInfo::getName() const {
  return name;
}
AnsiString& TypeInfo::getName() {
  return name;
}
const RealType& TypeInfo::getRealType() const {
  return realType;
}
RealType& TypeInfo::getRealType() {
  return realType;
}
TypeInfo::~TypeInfo() {
}
//----------------------------------

//------------- Types ---------------
Types::Types() {
}
Types::~Types() {
}
//----------------------------------

