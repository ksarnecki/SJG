#ifndef _SYNTAXDATA_GEN_H_
#define _SYNTAXDATA_GEN_H_
#include "DynSet.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
#include "AnsiString.h"
//----------------------------------

//------------- HashMapFake ---------------
#include "DynSet.h"

class HashMap;

class HashMapFake : public DynSet<HashMap> {
public:
  HashMapFake();


  virtual ~HashMapFake();

};
//----------------------------------

//------------- MapEntryFake ---------------
#include "DynSet.h"

class MapEntry;

class MapEntryFake : public DynSet<MapEntry> {
public:
  MapEntryFake();


  virtual ~MapEntryFake();

};
//----------------------------------

//------------- RealType ---------------
class RealType {
  int _type;
  void* _ptr;

  static const int _TypeJavaLangInteger;
  static const int _TypeJavaLangString;
  static const int _TypeJavaLangArray;
  static const int _TypeJavaUtilRegexPattern;
  static const int _TypeJavaUtilRegexMatcher;
  static const int _TypeJavaUtilHashMap;
  static const int _TypeJavaUtilMapEntry;
  static const int _TypeLkDBConn;
  static const int _TypeLkSDBResult;
  static const int _TypeUnknown;

  virtual void init(int, void*);
  virtual void clean();
  RealType();
public:
  RealType(const RealType&);
  virtual RealType& operator=(const RealType&);

  virtual bool isJavaLangInteger() const;
  virtual bool isJavaLangString() const;
  virtual bool isJavaLangArray() const;
  virtual bool isJavaUtilRegexPattern() const;
  virtual bool isJavaUtilRegexMatcher() const;
  virtual bool isJavaUtilHashMap() const;
  virtual bool isJavaUtilMapEntry() const;
  virtual bool isLkDBConn() const;
  virtual bool isLkSDBResult() const;
  virtual bool isUnknown() const;

  virtual const RealType& asJavaLangArray() const;
  virtual RealType& asJavaLangArray();
  virtual const HashMap& asJavaUtilHashMap() const;
  virtual HashMap& asJavaUtilHashMap();
  virtual const MapEntry& asJavaUtilMapEntry() const;
  virtual MapEntry& asJavaUtilMapEntry();


  virtual ~RealType();

  static RealType createJavaLangInteger();
  static RealType createJavaLangString();
  static RealType createJavaLangArray(const RealType&);
  static RealType createJavaUtilRegexPattern();
  static RealType createJavaUtilRegexMatcher();
  static RealType createJavaUtilHashMap(const HashMap&);
  static RealType createJavaUtilMapEntry(const MapEntry&);
  static RealType createLkDBConn();
  static RealType createLkSDBResult();
  static RealType createUnknown();

};
//----------------------------------

//------------- HashMap ---------------
class HashMap {
  RealType key;
  RealType value;
public:
  HashMap(const RealType&, const RealType&);
  virtual const RealType& getKey() const;
  virtual const RealType& getValue() const;
  virtual RealType& getKey();
  virtual RealType& getValue();


  virtual ~HashMap();

};
//----------------------------------

//------------- MapEntry ---------------
class MapEntry {
  RealType key;
  RealType value;
public:
  MapEntry(const RealType&, const RealType&);
  virtual const RealType& getKey() const;
  virtual const RealType& getValue() const;
  virtual RealType& getKey();
  virtual RealType& getValue();


  virtual ~MapEntry();

};
//----------------------------------

//------------- TypeInfo ---------------
class TypeInfo {
  AnsiString name;
  RealType realType;
public:
  TypeInfo(const AnsiString&, const RealType&);
  virtual const AnsiString& getName() const;
  virtual const RealType& getRealType() const;
  virtual AnsiString& getName();
  virtual RealType& getRealType();


  virtual ~TypeInfo();

};
//----------------------------------

//------------- Types ---------------
#include "DynSet.h"


class Types : public DynSet<TypeInfo> {
public:
  Types();


  virtual ~Types();

};
//----------------------------------

#endif
