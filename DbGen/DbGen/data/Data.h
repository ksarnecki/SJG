#ifndef _DATA_GEN_H_
#define _DATA_GEN_H_
#include "DynSet.h"
//------------- Joins ---------------
#include "DynSet.h"

class Join;

class Joins : public DynSet<Join> {
public:
  Joins();


  virtual ~Joins();

};
//----------------------------------

//------------- int ---------------
//----------------------------------

//------------- string ---------------
#include "AnsiString.h"
//----------------------------------

//------------- StringArray ---------------
#include "DynSet.h"


class StringArray : public DynSet<AnsiString> {
public:
  StringArray();


  virtual ~StringArray();

};
//----------------------------------

//------------- RecordElem ---------------
class RecordElem {
  AnsiString name;
  AnsiString type;
public:
  RecordElem(const AnsiString&, const AnsiString&);
  virtual const AnsiString& getName() const;
  virtual const AnsiString& getType() const;
  virtual AnsiString& getName();
  virtual AnsiString& getType();


  virtual ~RecordElem();

};
//----------------------------------

//------------- RecordElems ---------------
#include "DynSet.h"


class RecordElems : public DynSet<RecordElem> {
public:
  RecordElems();


  virtual ~RecordElems();

};
//----------------------------------

//------------- Record ---------------
class Record {
  AnsiString name;
  RecordElems elems;
public:
  Record(const AnsiString&, const RecordElems&);
  virtual const AnsiString& getName() const;
  virtual const RecordElems& getElems() const;
  virtual AnsiString& getName();
  virtual RecordElems& getElems();


  virtual ~Record();

};
//----------------------------------

//------------- SelectParamType ---------------
class SelectParamType {
  int _type;
  void* _ptr;

  static const int _TypePlain;
  static const int _TypeArray;

  virtual void init(int, void*);
  virtual void clean();
  SelectParamType();
public:
  SelectParamType(const SelectParamType&);
  virtual SelectParamType& operator=(const SelectParamType&);

  virtual bool isPlain() const;
  virtual bool isArray() const;

  virtual const AnsiString& asPlain() const;
  virtual AnsiString& asPlain();
  virtual const AnsiString& asArray() const;
  virtual AnsiString& asArray();


  virtual ~SelectParamType();

  static SelectParamType createPlain(const AnsiString&);
  static SelectParamType createArray(const AnsiString&);

};
//----------------------------------

//------------- SelectParam ---------------
class SelectParam {
  AnsiString name;
  SelectParamType type;
public:
  SelectParam(const AnsiString&, const SelectParamType&);
  virtual const AnsiString& getName() const;
  virtual const SelectParamType& getType() const;
  virtual AnsiString& getName();
  virtual SelectParamType& getType();


  virtual ~SelectParam();

};
//----------------------------------

//------------- SelectParams ---------------
#include "DynSet.h"


class SelectParams : public DynSet<SelectParam> {
public:
  SelectParams();


  virtual ~SelectParams();

};
//----------------------------------

//------------- Join ---------------
class Join {
  AnsiString fieldName;
  AnsiString methodName;
  StringArray params;
  AnsiString parentName;
  AnsiString childName;
public:
  Join(const AnsiString&, const AnsiString&, const StringArray&, const AnsiString&, const AnsiString&);
  virtual const AnsiString& getFieldName() const;
  virtual const AnsiString& getMethodName() const;
  virtual const StringArray& getParams() const;
  virtual const AnsiString& getParentName() const;
  virtual const AnsiString& getChildName() const;
  virtual AnsiString& getFieldName();
  virtual AnsiString& getMethodName();
  virtual StringArray& getParams();
  virtual AnsiString& getParentName();
  virtual AnsiString& getChildName();


  virtual ~Join();

};
//----------------------------------

//------------- Select ---------------
class Select {
  AnsiString type;
  AnsiString name;
  SelectParams params;
  AnsiString query;
  Joins joins;
public:
  Select(const AnsiString&, const AnsiString&, const SelectParams&, const AnsiString&, const Joins&);
  virtual const AnsiString& getType() const;
  virtual const AnsiString& getName() const;
  virtual const SelectParams& getParams() const;
  virtual const AnsiString& getQuery() const;
  virtual const Joins& getJoins() const;
  virtual AnsiString& getType();
  virtual AnsiString& getName();
  virtual SelectParams& getParams();
  virtual AnsiString& getQuery();
  virtual Joins& getJoins();


  virtual ~Select();

};
//----------------------------------

//------------- Insert ---------------
class Insert {
  AnsiString name;
  SelectParams params;
  AnsiString query;
public:
  Insert(const AnsiString&, const SelectParams&, const AnsiString&);
  virtual const AnsiString& getName() const;
  virtual const SelectParams& getParams() const;
  virtual const AnsiString& getQuery() const;
  virtual AnsiString& getName();
  virtual SelectParams& getParams();
  virtual AnsiString& getQuery();


  virtual ~Insert();

};
//----------------------------------

//------------- Delete ---------------
class Delete {
  AnsiString name;
  SelectParams params;
  AnsiString query;
public:
  Delete(const AnsiString&, const SelectParams&, const AnsiString&);
  virtual const AnsiString& getName() const;
  virtual const SelectParams& getParams() const;
  virtual const AnsiString& getQuery() const;
  virtual AnsiString& getName();
  virtual SelectParams& getParams();
  virtual AnsiString& getQuery();


  virtual ~Delete();

};
//----------------------------------

//------------- Update ---------------
class Update {
  AnsiString name;
  SelectParams params;
  AnsiString query;
public:
  Update(const AnsiString&, const SelectParams&, const AnsiString&);
  virtual const AnsiString& getName() const;
  virtual const SelectParams& getParams() const;
  virtual const AnsiString& getQuery() const;
  virtual AnsiString& getName();
  virtual SelectParams& getParams();
  virtual AnsiString& getQuery();


  virtual ~Update();

};
//----------------------------------

//------------- Array ---------------
class Array {
  AnsiString name;
  AnsiString type;
public:
  Array(const AnsiString&, const AnsiString&);
  virtual const AnsiString& getName() const;
  virtual const AnsiString& getType() const;
  virtual AnsiString& getName();
  virtual AnsiString& getType();


  virtual ~Array();

};
//----------------------------------

//------------- Elem ---------------
class Elem {
  int _type;
  void* _ptr;

  static const int _TypeInsert;
  static const int _TypeUpdate;
  static const int _TypeSelect;
  static const int _TypeDelete;

  virtual void init(int, void*);
  virtual void clean();
  Elem();
public:
  Elem(const Elem&);
  virtual Elem& operator=(const Elem&);

  virtual bool isInsert() const;
  virtual bool isUpdate() const;
  virtual bool isSelect() const;
  virtual bool isDelete() const;

  virtual const Insert& asInsert() const;
  virtual Insert& asInsert();
  virtual const Update& asUpdate() const;
  virtual Update& asUpdate();
  virtual const Select& asSelect() const;
  virtual Select& asSelect();
  virtual const Delete& asDelete() const;
  virtual Delete& asDelete();


  virtual ~Elem();

  static Elem createInsert(const Insert&);
  static Elem createUpdate(const Update&);
  static Elem createSelect(const Select&);
  static Elem createDelete(const Delete&);

};
//----------------------------------

//------------- Elems ---------------
#include "DynSet.h"


class Elems : public DynSet<Elem> {
public:
  Elems();


  virtual ~Elems();

};
//----------------------------------

//------------- InputFile ---------------
class InputFile {
  AnsiString appData;
  Elems elems;
public:
  InputFile(const AnsiString&, const Elems&);
  virtual const AnsiString& getAppData() const;
  virtual const Elems& getElems() const;
  virtual AnsiString& getAppData();
  virtual Elems& getElems();


  virtual ~InputFile();

};
//----------------------------------

//------------- OutputFileKind ---------------
class OutputFileKind {
  int _type;
  void* _ptr;

  static const int _TypeJavaSync;
  static const int _TypeJavaAsync;
  static const int _TypeJ2jApiClient;
  static const int _TypeJavaApiProcessor;

  virtual void init(int, void*);
  virtual void clean();
  OutputFileKind();
public:
  OutputFileKind(const OutputFileKind&);
  virtual OutputFileKind& operator=(const OutputFileKind&);

  virtual bool isJavaSync() const;
  virtual bool isJavaAsync() const;
  virtual bool isJ2jApiClient() const;
  virtual bool isJavaApiProcessor() const;

  virtual const AnsiString& asJ2jApiClient() const;
  virtual AnsiString& asJ2jApiClient();


  virtual ~OutputFileKind();

  static OutputFileKind createJavaSync();
  static OutputFileKind createJavaAsync();
  static OutputFileKind createJ2jApiClient(const AnsiString&);
  static OutputFileKind createJavaApiProcessor();

};
//----------------------------------

//------------- OutputFile ---------------
class OutputFile {
  OutputFileKind kind;
  AnsiString name;
  AnsiString package;
  StringArray imports;
public:
  OutputFile(const OutputFileKind&, const AnsiString&, const AnsiString&, const StringArray&);
  virtual const OutputFileKind& getKind() const;
  virtual const AnsiString& getName() const;
  virtual const AnsiString& getPackage() const;
  virtual const StringArray& getImports() const;
  virtual OutputFileKind& getKind();
  virtual AnsiString& getName();
  virtual AnsiString& getPackage();
  virtual StringArray& getImports();


  virtual ~OutputFile();

};
//----------------------------------

//------------- OutputFiles ---------------
#include "DynSet.h"


class OutputFiles : public DynSet<OutputFile> {
public:
  OutputFiles();


  virtual ~OutputFiles();

};
//----------------------------------

//------------- DbFile ---------------
class DbFile {
  OutputFiles outputFiles;
  InputFile inputFile;
public:
  DbFile(const OutputFiles&, const InputFile&);
  virtual const OutputFiles& getOutputFiles() const;
  virtual const InputFile& getInputFile() const;
  virtual OutputFiles& getOutputFiles();
  virtual InputFile& getInputFile();


  virtual ~DbFile();

};
//----------------------------------

#endif
