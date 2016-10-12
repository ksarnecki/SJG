
#include "File.h"
#include "Exception.h"
//------------- string ---------------
//----------------------------------

//------------- ExternalType ---------------
ExternalType::ExternalType(const AnsiString& _source) : source(_source) {
}
const AnsiString& ExternalType::getSource() const {
  return source;
}
AnsiString& ExternalType::getSource() {
  return source;
}
ExternalType::~ExternalType() {
}
//----------------------------------

//------------- ArrayType ---------------
ArrayType::ArrayType(const AnsiString& _type) : type(_type) {
}
const AnsiString& ArrayType::getType() const {
  return type;
}
AnsiString& ArrayType::getType() {
  return type;
}
ArrayType::~ArrayType() {
}
//----------------------------------

//------------- RecordField ---------------
RecordField::RecordField(const AnsiString& _name, const AnsiString& _type) : name(_name), type(_type) {
}
const AnsiString& RecordField::getName() const {
  return name;
}
AnsiString& RecordField::getName() {
  return name;
}
const AnsiString& RecordField::getType() const {
  return type;
}
AnsiString& RecordField::getType() {
  return type;
}
RecordField::~RecordField() {
}
//----------------------------------

//------------- RecordType ---------------
RecordType::RecordType() {
}
RecordType::~RecordType() {
}
//----------------------------------

//------------- VariantFieldKind ---------------
const int VariantFieldKind::_TypeEmpty = 0;
const int VariantFieldKind::_TypeType = 1;
void VariantFieldKind::init(int type, void* ptr) {
  if (type==_TypeEmpty) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeType) {
    _type = type;
    _ptr = new AnsiString(*(AnsiString*) ptr);
  }
}
void VariantFieldKind::clean() {
  if (_type==_TypeEmpty) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("VariantFieldKind::clean()");
  } else if (_type==_TypeType) {
    _type = -1;
    delete (AnsiString*) _ptr;
    _ptr = 0;
  }
}
VariantFieldKind::VariantFieldKind() : _type(-1), _ptr(0) {
}
VariantFieldKind::VariantFieldKind(const VariantFieldKind& _value) {
  init(_value._type, _value._ptr);
}
VariantFieldKind& VariantFieldKind::operator=(const VariantFieldKind& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool VariantFieldKind::isEmpty() const {
  return _type==_TypeEmpty;
}
bool VariantFieldKind::isType() const {
  return _type==_TypeType;
}
const AnsiString& VariantFieldKind::asType() const {
  if (_type!=_TypeType)
    throw Exception("VariantFieldKind::asType");
  return *(AnsiString*) _ptr;
}
AnsiString& VariantFieldKind::asType() {
  if (_type!=_TypeType)
    throw Exception("VariantFieldKind::asType");
  return *(AnsiString*) _ptr;
}


VariantFieldKind::~VariantFieldKind() {
  clean();
}
VariantFieldKind VariantFieldKind::createEmpty() {
  VariantFieldKind _value;
  _value._type = _TypeEmpty;
  _value._ptr = 0;
  return _value;
}
VariantFieldKind VariantFieldKind::createType(const AnsiString& _param) {
  VariantFieldKind _value;
  _value._type = _TypeType;
  _value._ptr = new AnsiString(_param);
  return _value;
}


//----------------------------------

//------------- VariantField ---------------
VariantField::VariantField(const AnsiString& _name, const VariantFieldKind& _kind) : name(_name), kind(_kind) {
}
const AnsiString& VariantField::getName() const {
  return name;
}
AnsiString& VariantField::getName() {
  return name;
}
const VariantFieldKind& VariantField::getKind() const {
  return kind;
}
VariantFieldKind& VariantField::getKind() {
  return kind;
}
VariantField::~VariantField() {
}
//----------------------------------

//------------- VariantType ---------------
VariantType::VariantType() {
}
VariantType::~VariantType() {
}
//----------------------------------

//------------- DataTypeKind ---------------
const int DataTypeKind::_TypeBasic = 0;
const int DataTypeKind::_TypeExternal = 1;
const int DataTypeKind::_TypeArray = 2;
const int DataTypeKind::_TypeRecord = 3;
const int DataTypeKind::_TypeVariant = 4;
void DataTypeKind::init(int type, void* ptr) {
  if (type==_TypeBasic) {
    _type = type;
    _ptr = new AnsiString(*(AnsiString*) ptr);
  } else if (type==_TypeExternal) {
    _type = type;
    _ptr = new ExternalType(*(ExternalType*) ptr);
  } else if (type==_TypeArray) {
    _type = type;
    _ptr = new ArrayType(*(ArrayType*) ptr);
  } else if (type==_TypeRecord) {
    _type = type;
    _ptr = new RecordType(*(RecordType*) ptr);
  } else if (type==_TypeVariant) {
    _type = type;
    _ptr = new VariantType(*(VariantType*) ptr);
  }
}
void DataTypeKind::clean() {
  if (_type==_TypeBasic) {
    _type = -1;
    delete (AnsiString*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeExternal) {
    _type = -1;
    delete (ExternalType*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeArray) {
    _type = -1;
    delete (ArrayType*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeRecord) {
    _type = -1;
    delete (RecordType*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeVariant) {
    _type = -1;
    delete (VariantType*) _ptr;
    _ptr = 0;
  }
}
DataTypeKind::DataTypeKind() : _type(-1), _ptr(0) {
}
DataTypeKind::DataTypeKind(const DataTypeKind& _value) {
  init(_value._type, _value._ptr);
}
DataTypeKind& DataTypeKind::operator=(const DataTypeKind& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool DataTypeKind::isBasic() const {
  return _type==_TypeBasic;
}
bool DataTypeKind::isExternal() const {
  return _type==_TypeExternal;
}
bool DataTypeKind::isArray() const {
  return _type==_TypeArray;
}
bool DataTypeKind::isRecord() const {
  return _type==_TypeRecord;
}
bool DataTypeKind::isVariant() const {
  return _type==_TypeVariant;
}
const AnsiString& DataTypeKind::asBasic() const {
  if (_type!=_TypeBasic)
    throw Exception("DataTypeKind::asBasic");
  return *(AnsiString*) _ptr;
}
AnsiString& DataTypeKind::asBasic() {
  if (_type!=_TypeBasic)
    throw Exception("DataTypeKind::asBasic");
  return *(AnsiString*) _ptr;
}
const ExternalType& DataTypeKind::asExternal() const {
  if (_type!=_TypeExternal)
    throw Exception("DataTypeKind::asExternal");
  return *(ExternalType*) _ptr;
}
ExternalType& DataTypeKind::asExternal() {
  if (_type!=_TypeExternal)
    throw Exception("DataTypeKind::asExternal");
  return *(ExternalType*) _ptr;
}
const ArrayType& DataTypeKind::asArray() const {
  if (_type!=_TypeArray)
    throw Exception("DataTypeKind::asArray");
  return *(ArrayType*) _ptr;
}
ArrayType& DataTypeKind::asArray() {
  if (_type!=_TypeArray)
    throw Exception("DataTypeKind::asArray");
  return *(ArrayType*) _ptr;
}
const RecordType& DataTypeKind::asRecord() const {
  if (_type!=_TypeRecord)
    throw Exception("DataTypeKind::asRecord");
  return *(RecordType*) _ptr;
}
RecordType& DataTypeKind::asRecord() {
  if (_type!=_TypeRecord)
    throw Exception("DataTypeKind::asRecord");
  return *(RecordType*) _ptr;
}
const VariantType& DataTypeKind::asVariant() const {
  if (_type!=_TypeVariant)
    throw Exception("DataTypeKind::asVariant");
  return *(VariantType*) _ptr;
}
VariantType& DataTypeKind::asVariant() {
  if (_type!=_TypeVariant)
    throw Exception("DataTypeKind::asVariant");
  return *(VariantType*) _ptr;
}


DataTypeKind::~DataTypeKind() {
  clean();
}
DataTypeKind DataTypeKind::createBasic(const AnsiString& _param) {
  DataTypeKind _value;
  _value._type = _TypeBasic;
  _value._ptr = new AnsiString(_param);
  return _value;
}
DataTypeKind DataTypeKind::createExternal(const ExternalType& _param) {
  DataTypeKind _value;
  _value._type = _TypeExternal;
  _value._ptr = new ExternalType(_param);
  return _value;
}
DataTypeKind DataTypeKind::createArray(const ArrayType& _param) {
  DataTypeKind _value;
  _value._type = _TypeArray;
  _value._ptr = new ArrayType(_param);
  return _value;
}
DataTypeKind DataTypeKind::createRecord(const RecordType& _param) {
  DataTypeKind _value;
  _value._type = _TypeRecord;
  _value._ptr = new RecordType(_param);
  return _value;
}
DataTypeKind DataTypeKind::createVariant(const VariantType& _param) {
  DataTypeKind _value;
  _value._type = _TypeVariant;
  _value._ptr = new VariantType(_param);
  return _value;
}


//----------------------------------

//------------- DataType ---------------
DataType::DataType(const AnsiString& _name, const DataTypeKind& _kind) : name(_name), kind(_kind) {
}
const AnsiString& DataType::getName() const {
  return name;
}
AnsiString& DataType::getName() {
  return name;
}
const DataTypeKind& DataType::getKind() const {
  return kind;
}
DataTypeKind& DataType::getKind() {
  return kind;
}
DataType::~DataType() {
}
//----------------------------------

//------------- DataTypeArray ---------------
DataTypeArray::DataTypeArray() {
}
DataTypeArray::~DataTypeArray() {
}
//----------------------------------

//------------- DataFileKind ---------------
const int DataFileKind::_TypeCpp = 0;
const int DataFileKind::_TypePhp = 1;
const int DataFileKind::_TypeJava = 2;
const int DataFileKind::_TypeCs = 3;
const int DataFileKind::_TypeJavascript = 4;
void DataFileKind::init(int type, void* ptr) {
  if (type==_TypeCpp) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypePhp) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeJava) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeCs) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeJavascript) {
    _type = type;
    _ptr = 0;
  }
}
void DataFileKind::clean() {
  if (_type==_TypeCpp) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("DataFileKind::clean()");
  } else if (_type==_TypePhp) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("DataFileKind::clean()");
  } else if (_type==_TypeJava) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("DataFileKind::clean()");
  } else if (_type==_TypeCs) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("DataFileKind::clean()");
  } else if (_type==_TypeJavascript) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("DataFileKind::clean()");
  }
}
DataFileKind::DataFileKind() : _type(-1), _ptr(0) {
}
DataFileKind::DataFileKind(const DataFileKind& _value) {
  init(_value._type, _value._ptr);
}
DataFileKind& DataFileKind::operator=(const DataFileKind& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool DataFileKind::isCpp() const {
  return _type==_TypeCpp;
}
bool DataFileKind::isPhp() const {
  return _type==_TypePhp;
}
bool DataFileKind::isJava() const {
  return _type==_TypeJava;
}
bool DataFileKind::isCs() const {
  return _type==_TypeCs;
}
bool DataFileKind::isJavascript() const {
  return _type==_TypeJavascript;
}


DataFileKind::~DataFileKind() {
  clean();
}
DataFileKind DataFileKind::createCpp() {
  DataFileKind _value;
  _value._type = _TypeCpp;
  _value._ptr = 0;
  return _value;
}
DataFileKind DataFileKind::createPhp() {
  DataFileKind _value;
  _value._type = _TypePhp;
  _value._ptr = 0;
  return _value;
}
DataFileKind DataFileKind::createJava() {
  DataFileKind _value;
  _value._type = _TypeJava;
  _value._ptr = 0;
  return _value;
}
DataFileKind DataFileKind::createCs() {
  DataFileKind _value;
  _value._type = _TypeCs;
  _value._ptr = 0;
  return _value;
}
DataFileKind DataFileKind::createJavascript() {
  DataFileKind _value;
  _value._type = _TypeJavascript;
  _value._ptr = 0;
  return _value;
}


//----------------------------------

//------------- DataFileBase ---------------
DataFileBase::DataFileBase(const AnsiString& _file, const DataFileKind& _kind, const DataTypeArray& _types) : file(_file), kind(_kind), types(_types) {
}
const AnsiString& DataFileBase::getFile() const {
  return file;
}
AnsiString& DataFileBase::getFile() {
  return file;
}
const DataFileKind& DataFileBase::getKind() const {
  return kind;
}
DataFileKind& DataFileBase::getKind() {
  return kind;
}
const DataTypeArray& DataFileBase::getTypes() const {
  return types;
}
DataTypeArray& DataFileBase::getTypes() {
  return types;
}
DataFileBase::~DataFileBase() {
}
//----------------------------------

//------------- GenerateFile ---------------
GenerateFile::GenerateFile(const AnsiString& _name, const AnsiString& _content) : name(_name), content(_content) {
}
const AnsiString& GenerateFile::getName() const {
  return name;
}
AnsiString& GenerateFile::getName() {
  return name;
}
const AnsiString& GenerateFile::getContent() const {
  return content;
}
AnsiString& GenerateFile::getContent() {
  return content;
}
GenerateFile::~GenerateFile() {
}
//----------------------------------

//------------- GenerateFiles ---------------
GenerateFiles::GenerateFiles() {
}
GenerateFiles::~GenerateFiles() {
}
//----------------------------------

