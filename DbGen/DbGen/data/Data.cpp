
#include "Data.h"
#include "Exception.h"
//------------- Joins ---------------
Joins::Joins() {
}
Joins::~Joins() {
}
//----------------------------------

//------------- int ---------------
//----------------------------------

//------------- string ---------------
//----------------------------------

//------------- StringArray ---------------
StringArray::StringArray() {
}
StringArray::~StringArray() {
}
//----------------------------------

//------------- RecordElem ---------------
RecordElem::RecordElem(const AnsiString& _name, const AnsiString& _type) : name(_name), type(_type) {
}
const AnsiString& RecordElem::getName() const {
  return name;
}
AnsiString& RecordElem::getName() {
  return name;
}
const AnsiString& RecordElem::getType() const {
  return type;
}
AnsiString& RecordElem::getType() {
  return type;
}
RecordElem::~RecordElem() {
}
//----------------------------------

//------------- RecordElems ---------------
RecordElems::RecordElems() {
}
RecordElems::~RecordElems() {
}
//----------------------------------

//------------- Record ---------------
Record::Record(const AnsiString& _name, const RecordElems& _elems) : name(_name), elems(_elems) {
}
const AnsiString& Record::getName() const {
  return name;
}
AnsiString& Record::getName() {
  return name;
}
const RecordElems& Record::getElems() const {
  return elems;
}
RecordElems& Record::getElems() {
  return elems;
}
Record::~Record() {
}
//----------------------------------

//------------- SelectParamType ---------------
const int SelectParamType::_TypePlain = 0;
const int SelectParamType::_TypeArray = 1;
void SelectParamType::init(int type, void* ptr) {
  if (type==_TypePlain) {
    _type = type;
    _ptr = new AnsiString(*(AnsiString*) ptr);
  } else if (type==_TypeArray) {
    _type = type;
    _ptr = new AnsiString(*(AnsiString*) ptr);
  }
}
void SelectParamType::clean() {
  if (_type==_TypePlain) {
    _type = -1;
    delete (AnsiString*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeArray) {
    _type = -1;
    delete (AnsiString*) _ptr;
    _ptr = 0;
  }
}
SelectParamType::SelectParamType() : _type(-1), _ptr(0) {
}
SelectParamType::SelectParamType(const SelectParamType& _value) {
  init(_value._type, _value._ptr);
}
SelectParamType& SelectParamType::operator=(const SelectParamType& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool SelectParamType::isPlain() const {
  return _type==_TypePlain;
}
bool SelectParamType::isArray() const {
  return _type==_TypeArray;
}
const AnsiString& SelectParamType::asPlain() const {
  if (_type!=_TypePlain)
    throw Exception("SelectParamType::asPlain");
  return *(AnsiString*) _ptr;
}
AnsiString& SelectParamType::asPlain() {
  if (_type!=_TypePlain)
    throw Exception("SelectParamType::asPlain");
  return *(AnsiString*) _ptr;
}
const AnsiString& SelectParamType::asArray() const {
  if (_type!=_TypeArray)
    throw Exception("SelectParamType::asArray");
  return *(AnsiString*) _ptr;
}
AnsiString& SelectParamType::asArray() {
  if (_type!=_TypeArray)
    throw Exception("SelectParamType::asArray");
  return *(AnsiString*) _ptr;
}


SelectParamType::~SelectParamType() {
  clean();
}
SelectParamType SelectParamType::createPlain(const AnsiString& _param) {
  SelectParamType _value;
  _value._type = _TypePlain;
  _value._ptr = new AnsiString(_param);
  return _value;
}
SelectParamType SelectParamType::createArray(const AnsiString& _param) {
  SelectParamType _value;
  _value._type = _TypeArray;
  _value._ptr = new AnsiString(_param);
  return _value;
}


//----------------------------------

//------------- SelectParam ---------------
SelectParam::SelectParam(const AnsiString& _name, const SelectParamType& _type) : name(_name), type(_type) {
}
const AnsiString& SelectParam::getName() const {
  return name;
}
AnsiString& SelectParam::getName() {
  return name;
}
const SelectParamType& SelectParam::getType() const {
  return type;
}
SelectParamType& SelectParam::getType() {
  return type;
}
SelectParam::~SelectParam() {
}
//----------------------------------

//------------- SelectParams ---------------
SelectParams::SelectParams() {
}
SelectParams::~SelectParams() {
}
//----------------------------------

//------------- Join ---------------
Join::Join(const AnsiString& _fieldName, const AnsiString& _methodName, const StringArray& _params, const AnsiString& _parentName, const AnsiString& _childName) : fieldName(_fieldName), methodName(_methodName), params(_params), parentName(_parentName), childName(_childName) {
}
const AnsiString& Join::getFieldName() const {
  return fieldName;
}
AnsiString& Join::getFieldName() {
  return fieldName;
}
const AnsiString& Join::getMethodName() const {
  return methodName;
}
AnsiString& Join::getMethodName() {
  return methodName;
}
const StringArray& Join::getParams() const {
  return params;
}
StringArray& Join::getParams() {
  return params;
}
const AnsiString& Join::getParentName() const {
  return parentName;
}
AnsiString& Join::getParentName() {
  return parentName;
}
const AnsiString& Join::getChildName() const {
  return childName;
}
AnsiString& Join::getChildName() {
  return childName;
}
Join::~Join() {
}
//----------------------------------

//------------- Select ---------------
Select::Select(const AnsiString& _type, const AnsiString& _name, const SelectParams& _params, const AnsiString& _query, const Joins& _joins) : type(_type), name(_name), params(_params), query(_query), joins(_joins) {
}
const AnsiString& Select::getType() const {
  return type;
}
AnsiString& Select::getType() {
  return type;
}
const AnsiString& Select::getName() const {
  return name;
}
AnsiString& Select::getName() {
  return name;
}
const SelectParams& Select::getParams() const {
  return params;
}
SelectParams& Select::getParams() {
  return params;
}
const AnsiString& Select::getQuery() const {
  return query;
}
AnsiString& Select::getQuery() {
  return query;
}
const Joins& Select::getJoins() const {
  return joins;
}
Joins& Select::getJoins() {
  return joins;
}
Select::~Select() {
}
//----------------------------------

//------------- Insert ---------------
Insert::Insert(const AnsiString& _name, const SelectParams& _params, const AnsiString& _query) : name(_name), params(_params), query(_query) {
}
const AnsiString& Insert::getName() const {
  return name;
}
AnsiString& Insert::getName() {
  return name;
}
const SelectParams& Insert::getParams() const {
  return params;
}
SelectParams& Insert::getParams() {
  return params;
}
const AnsiString& Insert::getQuery() const {
  return query;
}
AnsiString& Insert::getQuery() {
  return query;
}
Insert::~Insert() {
}
//----------------------------------

//------------- Delete ---------------
Delete::Delete(const AnsiString& _name, const SelectParams& _params, const AnsiString& _query) : name(_name), params(_params), query(_query) {
}
const AnsiString& Delete::getName() const {
  return name;
}
AnsiString& Delete::getName() {
  return name;
}
const SelectParams& Delete::getParams() const {
  return params;
}
SelectParams& Delete::getParams() {
  return params;
}
const AnsiString& Delete::getQuery() const {
  return query;
}
AnsiString& Delete::getQuery() {
  return query;
}
Delete::~Delete() {
}
//----------------------------------

//------------- Update ---------------
Update::Update(const AnsiString& _name, const SelectParams& _params, const AnsiString& _query) : name(_name), params(_params), query(_query) {
}
const AnsiString& Update::getName() const {
  return name;
}
AnsiString& Update::getName() {
  return name;
}
const SelectParams& Update::getParams() const {
  return params;
}
SelectParams& Update::getParams() {
  return params;
}
const AnsiString& Update::getQuery() const {
  return query;
}
AnsiString& Update::getQuery() {
  return query;
}
Update::~Update() {
}
//----------------------------------

//------------- Array ---------------
Array::Array(const AnsiString& _name, const AnsiString& _type) : name(_name), type(_type) {
}
const AnsiString& Array::getName() const {
  return name;
}
AnsiString& Array::getName() {
  return name;
}
const AnsiString& Array::getType() const {
  return type;
}
AnsiString& Array::getType() {
  return type;
}
Array::~Array() {
}
//----------------------------------

//------------- Elem ---------------
const int Elem::_TypeInsert = 0;
const int Elem::_TypeUpdate = 1;
const int Elem::_TypeSelect = 2;
const int Elem::_TypeDelete = 3;
void Elem::init(int type, void* ptr) {
  if (type==_TypeInsert) {
    _type = type;
    _ptr = new Insert(*(Insert*) ptr);
  } else if (type==_TypeUpdate) {
    _type = type;
    _ptr = new Update(*(Update*) ptr);
  } else if (type==_TypeSelect) {
    _type = type;
    _ptr = new Select(*(Select*) ptr);
  } else if (type==_TypeDelete) {
    _type = type;
    _ptr = new Delete(*(Delete*) ptr);
  }
}
void Elem::clean() {
  if (_type==_TypeInsert) {
    _type = -1;
    delete (Insert*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeUpdate) {
    _type = -1;
    delete (Update*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeSelect) {
    _type = -1;
    delete (Select*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeDelete) {
    _type = -1;
    delete (Delete*) _ptr;
    _ptr = 0;
  }
}
Elem::Elem() : _type(-1), _ptr(0) {
}
Elem::Elem(const Elem& _value) {
  init(_value._type, _value._ptr);
}
Elem& Elem::operator=(const Elem& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool Elem::isInsert() const {
  return _type==_TypeInsert;
}
bool Elem::isUpdate() const {
  return _type==_TypeUpdate;
}
bool Elem::isSelect() const {
  return _type==_TypeSelect;
}
bool Elem::isDelete() const {
  return _type==_TypeDelete;
}
const Insert& Elem::asInsert() const {
  if (_type!=_TypeInsert)
    throw Exception("Elem::asInsert");
  return *(Insert*) _ptr;
}
Insert& Elem::asInsert() {
  if (_type!=_TypeInsert)
    throw Exception("Elem::asInsert");
  return *(Insert*) _ptr;
}
const Update& Elem::asUpdate() const {
  if (_type!=_TypeUpdate)
    throw Exception("Elem::asUpdate");
  return *(Update*) _ptr;
}
Update& Elem::asUpdate() {
  if (_type!=_TypeUpdate)
    throw Exception("Elem::asUpdate");
  return *(Update*) _ptr;
}
const Select& Elem::asSelect() const {
  if (_type!=_TypeSelect)
    throw Exception("Elem::asSelect");
  return *(Select*) _ptr;
}
Select& Elem::asSelect() {
  if (_type!=_TypeSelect)
    throw Exception("Elem::asSelect");
  return *(Select*) _ptr;
}
const Delete& Elem::asDelete() const {
  if (_type!=_TypeDelete)
    throw Exception("Elem::asDelete");
  return *(Delete*) _ptr;
}
Delete& Elem::asDelete() {
  if (_type!=_TypeDelete)
    throw Exception("Elem::asDelete");
  return *(Delete*) _ptr;
}


Elem::~Elem() {
  clean();
}
Elem Elem::createInsert(const Insert& _param) {
  Elem _value;
  _value._type = _TypeInsert;
  _value._ptr = new Insert(_param);
  return _value;
}
Elem Elem::createUpdate(const Update& _param) {
  Elem _value;
  _value._type = _TypeUpdate;
  _value._ptr = new Update(_param);
  return _value;
}
Elem Elem::createSelect(const Select& _param) {
  Elem _value;
  _value._type = _TypeSelect;
  _value._ptr = new Select(_param);
  return _value;
}
Elem Elem::createDelete(const Delete& _param) {
  Elem _value;
  _value._type = _TypeDelete;
  _value._ptr = new Delete(_param);
  return _value;
}


//----------------------------------

//------------- Elems ---------------
Elems::Elems() {
}
Elems::~Elems() {
}
//----------------------------------

//------------- InputFile ---------------
InputFile::InputFile(const AnsiString& _appData, const Elems& _elems) : appData(_appData), elems(_elems) {
}
const AnsiString& InputFile::getAppData() const {
  return appData;
}
AnsiString& InputFile::getAppData() {
  return appData;
}
const Elems& InputFile::getElems() const {
  return elems;
}
Elems& InputFile::getElems() {
  return elems;
}
InputFile::~InputFile() {
}
//----------------------------------

//------------- OutputFileKind ---------------
const int OutputFileKind::_TypeJavaSync = 0;
const int OutputFileKind::_TypeJavaAsync = 1;
const int OutputFileKind::_TypeJ2jApiClient = 2;
const int OutputFileKind::_TypeJavaApiProcessor = 3;
void OutputFileKind::init(int type, void* ptr) {
  if (type==_TypeJavaSync) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeJavaAsync) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeJ2jApiClient) {
    _type = type;
    _ptr = new AnsiString(*(AnsiString*) ptr);
  } else if (type==_TypeJavaApiProcessor) {
    _type = type;
    _ptr = 0;
  }
}
void OutputFileKind::clean() {
  if (_type==_TypeJavaSync) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("OutputFileKind::clean()");
  } else if (_type==_TypeJavaAsync) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("OutputFileKind::clean()");
  } else if (_type==_TypeJ2jApiClient) {
    _type = -1;
    delete (AnsiString*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeJavaApiProcessor) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("OutputFileKind::clean()");
  }
}
OutputFileKind::OutputFileKind() : _type(-1), _ptr(0) {
}
OutputFileKind::OutputFileKind(const OutputFileKind& _value) {
  init(_value._type, _value._ptr);
}
OutputFileKind& OutputFileKind::operator=(const OutputFileKind& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool OutputFileKind::isJavaSync() const {
  return _type==_TypeJavaSync;
}
bool OutputFileKind::isJavaAsync() const {
  return _type==_TypeJavaAsync;
}
bool OutputFileKind::isJ2jApiClient() const {
  return _type==_TypeJ2jApiClient;
}
bool OutputFileKind::isJavaApiProcessor() const {
  return _type==_TypeJavaApiProcessor;
}
const AnsiString& OutputFileKind::asJ2jApiClient() const {
  if (_type!=_TypeJ2jApiClient)
    throw Exception("OutputFileKind::asJ2jApiClient");
  return *(AnsiString*) _ptr;
}
AnsiString& OutputFileKind::asJ2jApiClient() {
  if (_type!=_TypeJ2jApiClient)
    throw Exception("OutputFileKind::asJ2jApiClient");
  return *(AnsiString*) _ptr;
}


OutputFileKind::~OutputFileKind() {
  clean();
}
OutputFileKind OutputFileKind::createJavaSync() {
  OutputFileKind _value;
  _value._type = _TypeJavaSync;
  _value._ptr = 0;
  return _value;
}
OutputFileKind OutputFileKind::createJavaAsync() {
  OutputFileKind _value;
  _value._type = _TypeJavaAsync;
  _value._ptr = 0;
  return _value;
}
OutputFileKind OutputFileKind::createJ2jApiClient(const AnsiString& _param) {
  OutputFileKind _value;
  _value._type = _TypeJ2jApiClient;
  _value._ptr = new AnsiString(_param);
  return _value;
}
OutputFileKind OutputFileKind::createJavaApiProcessor() {
  OutputFileKind _value;
  _value._type = _TypeJavaApiProcessor;
  _value._ptr = 0;
  return _value;
}


//----------------------------------

//------------- OutputFile ---------------
OutputFile::OutputFile(const OutputFileKind& _kind, const AnsiString& _name, const AnsiString& _package, const StringArray& _imports) : kind(_kind), name(_name), package(_package), imports(_imports) {
}
const OutputFileKind& OutputFile::getKind() const {
  return kind;
}
OutputFileKind& OutputFile::getKind() {
  return kind;
}
const AnsiString& OutputFile::getName() const {
  return name;
}
AnsiString& OutputFile::getName() {
  return name;
}
const AnsiString& OutputFile::getPackage() const {
  return package;
}
AnsiString& OutputFile::getPackage() {
  return package;
}
const StringArray& OutputFile::getImports() const {
  return imports;
}
StringArray& OutputFile::getImports() {
  return imports;
}
OutputFile::~OutputFile() {
}
//----------------------------------

//------------- OutputFiles ---------------
OutputFiles::OutputFiles() {
}
OutputFiles::~OutputFiles() {
}
//----------------------------------

//------------- DbFile ---------------
DbFile::DbFile(const OutputFiles& _outputFiles, const InputFile& _inputFile) : outputFiles(_outputFiles), inputFile(_inputFile) {
}
const OutputFiles& DbFile::getOutputFiles() const {
  return outputFiles;
}
OutputFiles& DbFile::getOutputFiles() {
  return outputFiles;
}
const InputFile& DbFile::getInputFile() const {
  return inputFile;
}
InputFile& DbFile::getInputFile() {
  return inputFile;
}
DbFile::~DbFile() {
}
//----------------------------------

