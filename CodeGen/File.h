#ifndef _FILE_GEN_H_
#define _FILE_GEN_H_
#include "DynSet.h"
//------------- string ---------------
#include "AnsiString.h"
//----------------------------------

//------------- ExternalType ---------------
class ExternalType {
  AnsiString source;
public:
  ExternalType(const AnsiString&);
  virtual const AnsiString& getSource() const;
  virtual AnsiString& getSource();


  virtual ~ExternalType();

};
//----------------------------------

//------------- ArrayType ---------------
class ArrayType {
  AnsiString type;
public:
  ArrayType(const AnsiString&);
  virtual const AnsiString& getType() const;
  virtual AnsiString& getType();


  virtual ~ArrayType();

};
//----------------------------------

//------------- RecordField ---------------
class RecordField {
  AnsiString name;
  AnsiString type;
public:
  RecordField(const AnsiString&, const AnsiString&);
  virtual const AnsiString& getName() const;
  virtual const AnsiString& getType() const;
  virtual AnsiString& getName();
  virtual AnsiString& getType();


  virtual ~RecordField();

};
//----------------------------------

//------------- RecordType ---------------
#include "DynSet.h"


class RecordType : public DynSet<RecordField> {
public:
  RecordType();


  virtual ~RecordType();

};
//----------------------------------

//------------- VariantFieldKind ---------------
class VariantFieldKind {
  int _type;
  void* _ptr;

  static const int _TypeEmpty;
  static const int _TypeType;

  virtual void init(int, void*);
  virtual void clean();
  VariantFieldKind();
public:
  VariantFieldKind(const VariantFieldKind&);
  virtual VariantFieldKind& operator=(const VariantFieldKind&);

  virtual bool isEmpty() const;
  virtual bool isType() const;

  virtual const AnsiString& asType() const;
  virtual AnsiString& asType();


  virtual ~VariantFieldKind();

  static VariantFieldKind createEmpty();
  static VariantFieldKind createType(const AnsiString&);

};
//----------------------------------

//------------- VariantField ---------------
class VariantField {
  AnsiString name;
  VariantFieldKind kind;
public:
  VariantField(const AnsiString&, const VariantFieldKind&);
  virtual const AnsiString& getName() const;
  virtual const VariantFieldKind& getKind() const;
  virtual AnsiString& getName();
  virtual VariantFieldKind& getKind();


  virtual ~VariantField();

};
//----------------------------------

//------------- VariantType ---------------
#include "DynSet.h"


class VariantType : public DynSet<VariantField> {
public:
  VariantType();


  virtual ~VariantType();

};
//----------------------------------

//------------- DataTypeKind ---------------
class DataTypeKind {
  int _type;
  void* _ptr;

  static const int _TypeBasic;
  static const int _TypeExternal;
  static const int _TypeArray;
  static const int _TypeRecord;
  static const int _TypeVariant;

  virtual void init(int, void*);
  virtual void clean();
  DataTypeKind();
public:
  DataTypeKind(const DataTypeKind&);
  virtual DataTypeKind& operator=(const DataTypeKind&);

  virtual bool isBasic() const;
  virtual bool isExternal() const;
  virtual bool isArray() const;
  virtual bool isRecord() const;
  virtual bool isVariant() const;

  virtual const AnsiString& asBasic() const;
  virtual AnsiString& asBasic();
  virtual const ExternalType& asExternal() const;
  virtual ExternalType& asExternal();
  virtual const ArrayType& asArray() const;
  virtual ArrayType& asArray();
  virtual const RecordType& asRecord() const;
  virtual RecordType& asRecord();
  virtual const VariantType& asVariant() const;
  virtual VariantType& asVariant();


  virtual ~DataTypeKind();

  static DataTypeKind createBasic(const AnsiString&);
  static DataTypeKind createExternal(const ExternalType&);
  static DataTypeKind createArray(const ArrayType&);
  static DataTypeKind createRecord(const RecordType&);
  static DataTypeKind createVariant(const VariantType&);

};
//----------------------------------

//------------- DataType ---------------
class DataType {
  AnsiString name;
  DataTypeKind kind;
public:
  DataType(const AnsiString&, const DataTypeKind&);
  virtual const AnsiString& getName() const;
  virtual const DataTypeKind& getKind() const;
  virtual AnsiString& getName();
  virtual DataTypeKind& getKind();


  virtual ~DataType();

};
//----------------------------------

//------------- DataTypeArray ---------------
#include "DynSet.h"


class DataTypeArray : public DynSet<DataType> {
public:
  DataTypeArray();


  virtual ~DataTypeArray();

};
//----------------------------------

//------------- DataFileKind ---------------
class DataFileKind {
  int _type;
  void* _ptr;

  static const int _TypeCpp;
  static const int _TypePhp;
  static const int _TypeJava;
  static const int _TypeCs;
  static const int _TypeJavascript;

  virtual void init(int, void*);
  virtual void clean();
  DataFileKind();
public:
  DataFileKind(const DataFileKind&);
  virtual DataFileKind& operator=(const DataFileKind&);

  virtual bool isCpp() const;
  virtual bool isPhp() const;
  virtual bool isJava() const;
  virtual bool isCs() const;
  virtual bool isJavascript() const;



  virtual ~DataFileKind();

  static DataFileKind createCpp();
  static DataFileKind createPhp();
  static DataFileKind createJava();
  static DataFileKind createCs();
  static DataFileKind createJavascript();

};
//----------------------------------

//------------- DataFileBase ---------------
class DataFileBase {
  AnsiString file;
  DataFileKind kind;
  DataTypeArray types;
public:
  DataFileBase(const AnsiString&, const DataFileKind&, const DataTypeArray&);
  virtual const AnsiString& getFile() const;
  virtual const DataFileKind& getKind() const;
  virtual const DataTypeArray& getTypes() const;
  virtual AnsiString& getFile();
  virtual DataFileKind& getKind();
  virtual DataTypeArray& getTypes();


  virtual ~DataFileBase();

};
//----------------------------------

//------------- GenerateFile ---------------
class GenerateFile {
  AnsiString name;
  AnsiString content;
public:
  GenerateFile(const AnsiString&, const AnsiString&);
  virtual const AnsiString& getName() const;
  virtual const AnsiString& getContent() const;
  virtual AnsiString& getName();
  virtual AnsiString& getContent();


  virtual ~GenerateFile();

};
//----------------------------------

//------------- GenerateFiles ---------------
#include "DynSet.h"


class GenerateFiles : public DynSet<GenerateFile> {
public:
  GenerateFiles();


  virtual ~GenerateFiles();

};
//----------------------------------

#endif
