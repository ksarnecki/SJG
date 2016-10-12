
#include "SqlParserData.h"
#include "Exception.h"
//------------- WhenOperations ---------------
WhenOperations::WhenOperations() {
}
WhenOperations::~WhenOperations() {
}
//----------------------------------

//------------- int ---------------
//----------------------------------

//------------- string ---------------
//----------------------------------

//------------- Sqls ---------------
Sqls::Sqls() {
}
Sqls::~Sqls() {
}
//----------------------------------

//------------- SqlPtr ---------------
const int SqlPtr::_TypeValue = 0;
void SqlPtr::init(int type, void* ptr) {
  if (type==_TypeValue) {
    _type = type;
    _ptr = new Sql(*(Sql*) ptr);
  }
}
void SqlPtr::clean() {
  if (_type==_TypeValue) {
    _type = -1;
    delete (Sql*) _ptr;
    _ptr = 0;
  }
}
SqlPtr::SqlPtr() : _type(-1), _ptr(0) {
}
SqlPtr::SqlPtr(const SqlPtr& _value) {
  init(_value._type, _value._ptr);
}
SqlPtr& SqlPtr::operator=(const SqlPtr& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool SqlPtr::isValue() const {
  return _type==_TypeValue;
}
const Sql& SqlPtr::asValue() const {
  if (_type!=_TypeValue)
    throw Exception("SqlPtr::asValue");
  return *(Sql*) _ptr;
}
Sql& SqlPtr::asValue() {
  if (_type!=_TypeValue)
    throw Exception("SqlPtr::asValue");
  return *(Sql*) _ptr;
}


SqlPtr::~SqlPtr() {
  clean();
}
SqlPtr SqlPtr::createValue(const Sql& _param) {
  SqlPtr _value;
  _value._type = _TypeValue;
  _value._ptr = new Sql(_param);
  return _value;
}


//----------------------------------

//------------- BasicField ---------------
BasicField::BasicField(const AnsiString& _column, const AnsiString& _table) : column(_column), table(_table) {
}
const AnsiString& BasicField::getColumn() const {
  return column;
}
AnsiString& BasicField::getColumn() {
  return column;
}
const AnsiString& BasicField::getTable() const {
  return table;
}
AnsiString& BasicField::getTable() {
  return table;
}
BasicField::~BasicField() {
}
//----------------------------------

//------------- AgrFieldKind ---------------
const int AgrFieldKind::_TypeMin = 0;
const int AgrFieldKind::_TypeMax = 1;
const int AgrFieldKind::_TypeCount = 2;
void AgrFieldKind::init(int type, void* ptr) {
  if (type==_TypeMin) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeMax) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeCount) {
    _type = type;
    _ptr = 0;
  }
}
void AgrFieldKind::clean() {
  if (_type==_TypeMin) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("AgrFieldKind::clean()");
  } else if (_type==_TypeMax) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("AgrFieldKind::clean()");
  } else if (_type==_TypeCount) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("AgrFieldKind::clean()");
  }
}
AgrFieldKind::AgrFieldKind() : _type(-1), _ptr(0) {
}
AgrFieldKind::AgrFieldKind(const AgrFieldKind& _value) {
  init(_value._type, _value._ptr);
}
AgrFieldKind& AgrFieldKind::operator=(const AgrFieldKind& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool AgrFieldKind::isMin() const {
  return _type==_TypeMin;
}
bool AgrFieldKind::isMax() const {
  return _type==_TypeMax;
}
bool AgrFieldKind::isCount() const {
  return _type==_TypeCount;
}


AgrFieldKind::~AgrFieldKind() {
  clean();
}
AgrFieldKind AgrFieldKind::createMin() {
  AgrFieldKind _value;
  _value._type = _TypeMin;
  _value._ptr = 0;
  return _value;
}
AgrFieldKind AgrFieldKind::createMax() {
  AgrFieldKind _value;
  _value._type = _TypeMax;
  _value._ptr = 0;
  return _value;
}
AgrFieldKind AgrFieldKind::createCount() {
  AgrFieldKind _value;
  _value._type = _TypeCount;
  _value._ptr = 0;
  return _value;
}


//----------------------------------

//------------- AgrField ---------------
AgrField::AgrField(const AgrFieldKind& _agrFieldKind, const AnsiString& _args) : agrFieldKind(_agrFieldKind), args(_args) {
}
const AgrFieldKind& AgrField::getAgrFieldKind() const {
  return agrFieldKind;
}
AgrFieldKind& AgrField::getAgrFieldKind() {
  return agrFieldKind;
}
const AnsiString& AgrField::getArgs() const {
  return args;
}
AnsiString& AgrField::getArgs() {
  return args;
}
AgrField::~AgrField() {
}
//----------------------------------

//------------- FieldKind ---------------
const int FieldKind::_TypeSpecialField = 0;
const int FieldKind::_TypeBasicField = 1;
const int FieldKind::_TypeAgrField = 2;
const int FieldKind::_TypeAllField = 3;
const int FieldKind::_TypeQuery = 4;
void FieldKind::init(int type, void* ptr) {
  if (type==_TypeSpecialField) {
    _type = type;
    _ptr = new AnsiString(*(AnsiString*) ptr);
  } else if (type==_TypeBasicField) {
    _type = type;
    _ptr = new BasicField(*(BasicField*) ptr);
  } else if (type==_TypeAgrField) {
    _type = type;
    _ptr = new AgrField(*(AgrField*) ptr);
  } else if (type==_TypeAllField) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeQuery) {
    _type = type;
    _ptr = new SqlPtr(*(SqlPtr*) ptr);
  }
}
void FieldKind::clean() {
  if (_type==_TypeSpecialField) {
    _type = -1;
    delete (AnsiString*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeBasicField) {
    _type = -1;
    delete (BasicField*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeAgrField) {
    _type = -1;
    delete (AgrField*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeAllField) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("FieldKind::clean()");
  } else if (_type==_TypeQuery) {
    _type = -1;
    delete (SqlPtr*) _ptr;
    _ptr = 0;
  }
}
FieldKind::FieldKind() : _type(-1), _ptr(0) {
}
FieldKind::FieldKind(const FieldKind& _value) {
  init(_value._type, _value._ptr);
}
FieldKind& FieldKind::operator=(const FieldKind& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool FieldKind::isSpecialField() const {
  return _type==_TypeSpecialField;
}
bool FieldKind::isBasicField() const {
  return _type==_TypeBasicField;
}
bool FieldKind::isAgrField() const {
  return _type==_TypeAgrField;
}
bool FieldKind::isAllField() const {
  return _type==_TypeAllField;
}
bool FieldKind::isQuery() const {
  return _type==_TypeQuery;
}
const AnsiString& FieldKind::asSpecialField() const {
  if (_type!=_TypeSpecialField)
    throw Exception("FieldKind::asSpecialField");
  return *(AnsiString*) _ptr;
}
AnsiString& FieldKind::asSpecialField() {
  if (_type!=_TypeSpecialField)
    throw Exception("FieldKind::asSpecialField");
  return *(AnsiString*) _ptr;
}
const BasicField& FieldKind::asBasicField() const {
  if (_type!=_TypeBasicField)
    throw Exception("FieldKind::asBasicField");
  return *(BasicField*) _ptr;
}
BasicField& FieldKind::asBasicField() {
  if (_type!=_TypeBasicField)
    throw Exception("FieldKind::asBasicField");
  return *(BasicField*) _ptr;
}
const AgrField& FieldKind::asAgrField() const {
  if (_type!=_TypeAgrField)
    throw Exception("FieldKind::asAgrField");
  return *(AgrField*) _ptr;
}
AgrField& FieldKind::asAgrField() {
  if (_type!=_TypeAgrField)
    throw Exception("FieldKind::asAgrField");
  return *(AgrField*) _ptr;
}
const SqlPtr& FieldKind::asQuery() const {
  if (_type!=_TypeQuery)
    throw Exception("FieldKind::asQuery");
  return *(SqlPtr*) _ptr;
}
SqlPtr& FieldKind::asQuery() {
  if (_type!=_TypeQuery)
    throw Exception("FieldKind::asQuery");
  return *(SqlPtr*) _ptr;
}


FieldKind::~FieldKind() {
  clean();
}
FieldKind FieldKind::createSpecialField(const AnsiString& _param) {
  FieldKind _value;
  _value._type = _TypeSpecialField;
  _value._ptr = new AnsiString(_param);
  return _value;
}
FieldKind FieldKind::createBasicField(const BasicField& _param) {
  FieldKind _value;
  _value._type = _TypeBasicField;
  _value._ptr = new BasicField(_param);
  return _value;
}
FieldKind FieldKind::createAgrField(const AgrField& _param) {
  FieldKind _value;
  _value._type = _TypeAgrField;
  _value._ptr = new AgrField(_param);
  return _value;
}
FieldKind FieldKind::createAllField() {
  FieldKind _value;
  _value._type = _TypeAllField;
  _value._ptr = 0;
  return _value;
}
FieldKind FieldKind::createQuery(const SqlPtr& _param) {
  FieldKind _value;
  _value._type = _TypeQuery;
  _value._ptr = new SqlPtr(_param);
  return _value;
}


//----------------------------------

//------------- Field ---------------
Field::Field(const AnsiString& _fieldName, const FieldKind& _fieldKind) : fieldName(_fieldName), fieldKind(_fieldKind) {
}
const AnsiString& Field::getFieldName() const {
  return fieldName;
}
AnsiString& Field::getFieldName() {
  return fieldName;
}
const FieldKind& Field::getFieldKind() const {
  return fieldKind;
}
FieldKind& Field::getFieldKind() {
  return fieldKind;
}
Field::~Field() {
}
//----------------------------------

//------------- Operations ---------------
Operations::Operations() {
}
Operations::~Operations() {
}
//----------------------------------

//------------- OperationPtr ---------------
const int OperationPtr::_TypeValue = 0;
void OperationPtr::init(int type, void* ptr) {
  if (type==_TypeValue) {
    _type = type;
    _ptr = new Operation(*(Operation*) ptr);
  }
}
void OperationPtr::clean() {
  if (_type==_TypeValue) {
    _type = -1;
    delete (Operation*) _ptr;
    _ptr = 0;
  }
}
OperationPtr::OperationPtr() : _type(-1), _ptr(0) {
}
OperationPtr::OperationPtr(const OperationPtr& _value) {
  init(_value._type, _value._ptr);
}
OperationPtr& OperationPtr::operator=(const OperationPtr& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool OperationPtr::isValue() const {
  return _type==_TypeValue;
}
const Operation& OperationPtr::asValue() const {
  if (_type!=_TypeValue)
    throw Exception("OperationPtr::asValue");
  return *(Operation*) _ptr;
}
Operation& OperationPtr::asValue() {
  if (_type!=_TypeValue)
    throw Exception("OperationPtr::asValue");
  return *(Operation*) _ptr;
}


OperationPtr::~OperationPtr() {
  clean();
}
OperationPtr OperationPtr::createValue(const Operation& _param) {
  OperationPtr _value;
  _value._type = _TypeValue;
  _value._ptr = new Operation(_param);
  return _value;
}


//----------------------------------

//------------- BinaryOperator ---------------
const int BinaryOperator::_TypeLike = 0;
const int BinaryOperator::_TypeAnd = 1;
const int BinaryOperator::_TypeOr = 2;
const int BinaryOperator::_TypeIn = 3;
const int BinaryOperator::_TypeEqual = 4;
const int BinaryOperator::_TypeNoEqual = 5;
const int BinaryOperator::_TypeGreater = 6;
const int BinaryOperator::_TypeSmaller = 7;
const int BinaryOperator::_TypeGreaterOrEqual = 8;
const int BinaryOperator::_TypeSmallerOrEqual = 9;
void BinaryOperator::init(int type, void* ptr) {
  if (type==_TypeLike) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeAnd) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeOr) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeIn) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeEqual) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeNoEqual) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeGreater) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeSmaller) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeGreaterOrEqual) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeSmallerOrEqual) {
    _type = type;
    _ptr = 0;
  }
}
void BinaryOperator::clean() {
  if (_type==_TypeLike) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("BinaryOperator::clean()");
  } else if (_type==_TypeAnd) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("BinaryOperator::clean()");
  } else if (_type==_TypeOr) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("BinaryOperator::clean()");
  } else if (_type==_TypeIn) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("BinaryOperator::clean()");
  } else if (_type==_TypeEqual) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("BinaryOperator::clean()");
  } else if (_type==_TypeNoEqual) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("BinaryOperator::clean()");
  } else if (_type==_TypeGreater) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("BinaryOperator::clean()");
  } else if (_type==_TypeSmaller) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("BinaryOperator::clean()");
  } else if (_type==_TypeGreaterOrEqual) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("BinaryOperator::clean()");
  } else if (_type==_TypeSmallerOrEqual) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("BinaryOperator::clean()");
  }
}
BinaryOperator::BinaryOperator() : _type(-1), _ptr(0) {
}
BinaryOperator::BinaryOperator(const BinaryOperator& _value) {
  init(_value._type, _value._ptr);
}
BinaryOperator& BinaryOperator::operator=(const BinaryOperator& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool BinaryOperator::isLike() const {
  return _type==_TypeLike;
}
bool BinaryOperator::isAnd() const {
  return _type==_TypeAnd;
}
bool BinaryOperator::isOr() const {
  return _type==_TypeOr;
}
bool BinaryOperator::isIn() const {
  return _type==_TypeIn;
}
bool BinaryOperator::isEqual() const {
  return _type==_TypeEqual;
}
bool BinaryOperator::isNoEqual() const {
  return _type==_TypeNoEqual;
}
bool BinaryOperator::isGreater() const {
  return _type==_TypeGreater;
}
bool BinaryOperator::isSmaller() const {
  return _type==_TypeSmaller;
}
bool BinaryOperator::isGreaterOrEqual() const {
  return _type==_TypeGreaterOrEqual;
}
bool BinaryOperator::isSmallerOrEqual() const {
  return _type==_TypeSmallerOrEqual;
}


BinaryOperator::~BinaryOperator() {
  clean();
}
BinaryOperator BinaryOperator::createLike() {
  BinaryOperator _value;
  _value._type = _TypeLike;
  _value._ptr = 0;
  return _value;
}
BinaryOperator BinaryOperator::createAnd() {
  BinaryOperator _value;
  _value._type = _TypeAnd;
  _value._ptr = 0;
  return _value;
}
BinaryOperator BinaryOperator::createOr() {
  BinaryOperator _value;
  _value._type = _TypeOr;
  _value._ptr = 0;
  return _value;
}
BinaryOperator BinaryOperator::createIn() {
  BinaryOperator _value;
  _value._type = _TypeIn;
  _value._ptr = 0;
  return _value;
}
BinaryOperator BinaryOperator::createEqual() {
  BinaryOperator _value;
  _value._type = _TypeEqual;
  _value._ptr = 0;
  return _value;
}
BinaryOperator BinaryOperator::createNoEqual() {
  BinaryOperator _value;
  _value._type = _TypeNoEqual;
  _value._ptr = 0;
  return _value;
}
BinaryOperator BinaryOperator::createGreater() {
  BinaryOperator _value;
  _value._type = _TypeGreater;
  _value._ptr = 0;
  return _value;
}
BinaryOperator BinaryOperator::createSmaller() {
  BinaryOperator _value;
  _value._type = _TypeSmaller;
  _value._ptr = 0;
  return _value;
}
BinaryOperator BinaryOperator::createGreaterOrEqual() {
  BinaryOperator _value;
  _value._type = _TypeGreaterOrEqual;
  _value._ptr = 0;
  return _value;
}
BinaryOperator BinaryOperator::createSmallerOrEqual() {
  BinaryOperator _value;
  _value._type = _TypeSmallerOrEqual;
  _value._ptr = 0;
  return _value;
}


//----------------------------------

//------------- BinaryOperation ---------------
BinaryOperation::BinaryOperation(const OperationPtr& _left, const OperationPtr& _right, const BinaryOperator& _binaryOperator) : left(_left), right(_right), binaryOperator(_binaryOperator) {
}
const OperationPtr& BinaryOperation::getLeft() const {
  return left;
}
OperationPtr& BinaryOperation::getLeft() {
  return left;
}
const OperationPtr& BinaryOperation::getRight() const {
  return right;
}
OperationPtr& BinaryOperation::getRight() {
  return right;
}
const BinaryOperator& BinaryOperation::getBinaryOperator() const {
  return binaryOperator;
}
BinaryOperator& BinaryOperation::getBinaryOperator() {
  return binaryOperator;
}
BinaryOperation::~BinaryOperation() {
}
//----------------------------------

//------------- UnaryOperator ---------------
const int UnaryOperator::_TypeNegative = 0;
const int UnaryOperator::_TypePositive = 1;
const int UnaryOperator::_TypeNot = 2;
void UnaryOperator::init(int type, void* ptr) {
  if (type==_TypeNegative) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypePositive) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeNot) {
    _type = type;
    _ptr = 0;
  }
}
void UnaryOperator::clean() {
  if (_type==_TypeNegative) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("UnaryOperator::clean()");
  } else if (_type==_TypePositive) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("UnaryOperator::clean()");
  } else if (_type==_TypeNot) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("UnaryOperator::clean()");
  }
}
UnaryOperator::UnaryOperator() : _type(-1), _ptr(0) {
}
UnaryOperator::UnaryOperator(const UnaryOperator& _value) {
  init(_value._type, _value._ptr);
}
UnaryOperator& UnaryOperator::operator=(const UnaryOperator& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool UnaryOperator::isNegative() const {
  return _type==_TypeNegative;
}
bool UnaryOperator::isPositive() const {
  return _type==_TypePositive;
}
bool UnaryOperator::isNot() const {
  return _type==_TypeNot;
}


UnaryOperator::~UnaryOperator() {
  clean();
}
UnaryOperator UnaryOperator::createNegative() {
  UnaryOperator _value;
  _value._type = _TypeNegative;
  _value._ptr = 0;
  return _value;
}
UnaryOperator UnaryOperator::createPositive() {
  UnaryOperator _value;
  _value._type = _TypePositive;
  _value._ptr = 0;
  return _value;
}
UnaryOperator UnaryOperator::createNot() {
  UnaryOperator _value;
  _value._type = _TypeNot;
  _value._ptr = 0;
  return _value;
}


//----------------------------------

//------------- UnaryOperation ---------------
UnaryOperation::UnaryOperation(const OperationPtr& _right, const UnaryOperator& _unaryOperator) : right(_right), unaryOperator(_unaryOperator) {
}
const OperationPtr& UnaryOperation::getRight() const {
  return right;
}
OperationPtr& UnaryOperation::getRight() {
  return right;
}
const UnaryOperator& UnaryOperation::getUnaryOperator() const {
  return unaryOperator;
}
UnaryOperator& UnaryOperation::getUnaryOperator() {
  return unaryOperator;
}
UnaryOperation::~UnaryOperation() {
}
//----------------------------------

//------------- WhenOperation ---------------
WhenOperation::WhenOperation(const OperationPtr& _condition, const OperationPtr& _stmnt) : condition(_condition), stmnt(_stmnt) {
}
const OperationPtr& WhenOperation::getCondition() const {
  return condition;
}
OperationPtr& WhenOperation::getCondition() {
  return condition;
}
const OperationPtr& WhenOperation::getStmnt() const {
  return stmnt;
}
OperationPtr& WhenOperation::getStmnt() {
  return stmnt;
}
WhenOperation::~WhenOperation() {
}
//----------------------------------

//------------- CaseOperation ---------------
CaseOperation::CaseOperation(const WhenOperations& _cases, const OperationPtr& _elseStmnt) : cases(_cases), elseStmnt(_elseStmnt) {
}
const WhenOperations& CaseOperation::getCases() const {
  return cases;
}
WhenOperations& CaseOperation::getCases() {
  return cases;
}
const OperationPtr& CaseOperation::getElseStmnt() const {
  return elseStmnt;
}
OperationPtr& CaseOperation::getElseStmnt() {
  return elseStmnt;
}
CaseOperation::~CaseOperation() {
}
//----------------------------------

//------------- Operation ---------------
const int Operation::_TypeBinaryOperation = 0;
const int Operation::_TypeUnaryOperation = 1;
const int Operation::_TypeExistsOperation = 2;
const int Operation::_TypeCaseOperation = 3;
const int Operation::_TypeField = 4;
const int Operation::_TypeEmpty = 5;
void Operation::init(int type, void* ptr) {
  if (type==_TypeBinaryOperation) {
    _type = type;
    _ptr = new BinaryOperation(*(BinaryOperation*) ptr);
  } else if (type==_TypeUnaryOperation) {
    _type = type;
    _ptr = new UnaryOperation(*(UnaryOperation*) ptr);
  } else if (type==_TypeExistsOperation) {
    _type = type;
    _ptr = new Sql(*(Sql*) ptr);
  } else if (type==_TypeCaseOperation) {
    _type = type;
    _ptr = new CaseOperation(*(CaseOperation*) ptr);
  } else if (type==_TypeField) {
    _type = type;
    _ptr = new Field(*(Field*) ptr);
  } else if (type==_TypeEmpty) {
    _type = type;
    _ptr = 0;
  }
}
void Operation::clean() {
  if (_type==_TypeBinaryOperation) {
    _type = -1;
    delete (BinaryOperation*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeUnaryOperation) {
    _type = -1;
    delete (UnaryOperation*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeExistsOperation) {
    _type = -1;
    delete (Sql*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeCaseOperation) {
    _type = -1;
    delete (CaseOperation*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeField) {
    _type = -1;
    delete (Field*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeEmpty) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("Operation::clean()");
  }
}
Operation::Operation() : _type(-1), _ptr(0) {
}
Operation::Operation(const Operation& _value) {
  init(_value._type, _value._ptr);
}
Operation& Operation::operator=(const Operation& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool Operation::isBinaryOperation() const {
  return _type==_TypeBinaryOperation;
}
bool Operation::isUnaryOperation() const {
  return _type==_TypeUnaryOperation;
}
bool Operation::isExistsOperation() const {
  return _type==_TypeExistsOperation;
}
bool Operation::isCaseOperation() const {
  return _type==_TypeCaseOperation;
}
bool Operation::isField() const {
  return _type==_TypeField;
}
bool Operation::isEmpty() const {
  return _type==_TypeEmpty;
}
const BinaryOperation& Operation::asBinaryOperation() const {
  if (_type!=_TypeBinaryOperation)
    throw Exception("Operation::asBinaryOperation");
  return *(BinaryOperation*) _ptr;
}
BinaryOperation& Operation::asBinaryOperation() {
  if (_type!=_TypeBinaryOperation)
    throw Exception("Operation::asBinaryOperation");
  return *(BinaryOperation*) _ptr;
}
const UnaryOperation& Operation::asUnaryOperation() const {
  if (_type!=_TypeUnaryOperation)
    throw Exception("Operation::asUnaryOperation");
  return *(UnaryOperation*) _ptr;
}
UnaryOperation& Operation::asUnaryOperation() {
  if (_type!=_TypeUnaryOperation)
    throw Exception("Operation::asUnaryOperation");
  return *(UnaryOperation*) _ptr;
}
const Sql& Operation::asExistsOperation() const {
  if (_type!=_TypeExistsOperation)
    throw Exception("Operation::asExistsOperation");
  return *(Sql*) _ptr;
}
Sql& Operation::asExistsOperation() {
  if (_type!=_TypeExistsOperation)
    throw Exception("Operation::asExistsOperation");
  return *(Sql*) _ptr;
}
const CaseOperation& Operation::asCaseOperation() const {
  if (_type!=_TypeCaseOperation)
    throw Exception("Operation::asCaseOperation");
  return *(CaseOperation*) _ptr;
}
CaseOperation& Operation::asCaseOperation() {
  if (_type!=_TypeCaseOperation)
    throw Exception("Operation::asCaseOperation");
  return *(CaseOperation*) _ptr;
}
const Field& Operation::asField() const {
  if (_type!=_TypeField)
    throw Exception("Operation::asField");
  return *(Field*) _ptr;
}
Field& Operation::asField() {
  if (_type!=_TypeField)
    throw Exception("Operation::asField");
  return *(Field*) _ptr;
}


Operation::~Operation() {
  clean();
}
Operation Operation::createBinaryOperation(const BinaryOperation& _param) {
  Operation _value;
  _value._type = _TypeBinaryOperation;
  _value._ptr = new BinaryOperation(_param);
  return _value;
}
Operation Operation::createUnaryOperation(const UnaryOperation& _param) {
  Operation _value;
  _value._type = _TypeUnaryOperation;
  _value._ptr = new UnaryOperation(_param);
  return _value;
}
Operation Operation::createExistsOperation(const Sql& _param) {
  Operation _value;
  _value._type = _TypeExistsOperation;
  _value._ptr = new Sql(_param);
  return _value;
}
Operation Operation::createCaseOperation(const CaseOperation& _param) {
  Operation _value;
  _value._type = _TypeCaseOperation;
  _value._ptr = new CaseOperation(_param);
  return _value;
}
Operation Operation::createField(const Field& _param) {
  Operation _value;
  _value._type = _TypeField;
  _value._ptr = new Field(_param);
  return _value;
}
Operation Operation::createEmpty() {
  Operation _value;
  _value._type = _TypeEmpty;
  _value._ptr = 0;
  return _value;
}


//----------------------------------

//------------- TableKind ---------------
const int TableKind::_TypeBasic = 0;
const int TableKind::_TypeQuery = 1;
void TableKind::init(int type, void* ptr) {
  if (type==_TypeBasic) {
    _type = type;
    _ptr = new AnsiString(*(AnsiString*) ptr);
  } else if (type==_TypeQuery) {
    _type = type;
    _ptr = new SqlPtr(*(SqlPtr*) ptr);
  }
}
void TableKind::clean() {
  if (_type==_TypeBasic) {
    _type = -1;
    delete (AnsiString*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeQuery) {
    _type = -1;
    delete (SqlPtr*) _ptr;
    _ptr = 0;
  }
}
TableKind::TableKind() : _type(-1), _ptr(0) {
}
TableKind::TableKind(const TableKind& _value) {
  init(_value._type, _value._ptr);
}
TableKind& TableKind::operator=(const TableKind& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool TableKind::isBasic() const {
  return _type==_TypeBasic;
}
bool TableKind::isQuery() const {
  return _type==_TypeQuery;
}
const AnsiString& TableKind::asBasic() const {
  if (_type!=_TypeBasic)
    throw Exception("TableKind::asBasic");
  return *(AnsiString*) _ptr;
}
AnsiString& TableKind::asBasic() {
  if (_type!=_TypeBasic)
    throw Exception("TableKind::asBasic");
  return *(AnsiString*) _ptr;
}
const SqlPtr& TableKind::asQuery() const {
  if (_type!=_TypeQuery)
    throw Exception("TableKind::asQuery");
  return *(SqlPtr*) _ptr;
}
SqlPtr& TableKind::asQuery() {
  if (_type!=_TypeQuery)
    throw Exception("TableKind::asQuery");
  return *(SqlPtr*) _ptr;
}


TableKind::~TableKind() {
  clean();
}
TableKind TableKind::createBasic(const AnsiString& _param) {
  TableKind _value;
  _value._type = _TypeBasic;
  _value._ptr = new AnsiString(_param);
  return _value;
}
TableKind TableKind::createQuery(const SqlPtr& _param) {
  TableKind _value;
  _value._type = _TypeQuery;
  _value._ptr = new SqlPtr(_param);
  return _value;
}


//----------------------------------

//------------- Table ---------------
Table::Table(const TableKind& _kind, const AnsiString& _as) : kind(_kind), as(_as) {
}
const TableKind& Table::getKind() const {
  return kind;
}
TableKind& Table::getKind() {
  return kind;
}
const AnsiString& Table::getAs() const {
  return as;
}
AnsiString& Table::getAs() {
  return as;
}
Table::~Table() {
}
//----------------------------------

//------------- Tables ---------------
Tables::Tables() {
}
Tables::~Tables() {
}
//----------------------------------

//------------- Fields ---------------
Fields::Fields() {
}
Fields::~Fields() {
}
//----------------------------------

//------------- Orders ---------------
Orders::Orders() {
}
Orders::~Orders() {
}
//----------------------------------

//------------- Groups ---------------
Groups::Groups() {
}
Groups::~Groups() {
}
//----------------------------------

//------------- Sort ---------------
const int Sort::_TypeEmpty = 0;
const int Sort::_TypeDesc = 1;
const int Sort::_TypeAsc = 2;
void Sort::init(int type, void* ptr) {
  if (type==_TypeEmpty) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeDesc) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeAsc) {
    _type = type;
    _ptr = 0;
  }
}
void Sort::clean() {
  if (_type==_TypeEmpty) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("Sort::clean()");
  } else if (_type==_TypeDesc) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("Sort::clean()");
  } else if (_type==_TypeAsc) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("Sort::clean()");
  }
}
Sort::Sort() : _type(-1), _ptr(0) {
}
Sort::Sort(const Sort& _value) {
  init(_value._type, _value._ptr);
}
Sort& Sort::operator=(const Sort& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool Sort::isEmpty() const {
  return _type==_TypeEmpty;
}
bool Sort::isDesc() const {
  return _type==_TypeDesc;
}
bool Sort::isAsc() const {
  return _type==_TypeAsc;
}


Sort::~Sort() {
  clean();
}
Sort Sort::createEmpty() {
  Sort _value;
  _value._type = _TypeEmpty;
  _value._ptr = 0;
  return _value;
}
Sort Sort::createDesc() {
  Sort _value;
  _value._type = _TypeDesc;
  _value._ptr = 0;
  return _value;
}
Sort Sort::createAsc() {
  Sort _value;
  _value._type = _TypeAsc;
  _value._ptr = 0;
  return _value;
}


//----------------------------------

//------------- Limit ---------------
const int Limit::_TypeEmpty = 0;
const int Limit::_TypeValue = 1;
void Limit::init(int type, void* ptr) {
  if (type==_TypeEmpty) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeValue) {
    _type = type;
    _ptr = new AnsiString(*(AnsiString*) ptr);
  }
}
void Limit::clean() {
  if (_type==_TypeEmpty) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("Limit::clean()");
  } else if (_type==_TypeValue) {
    _type = -1;
    delete (AnsiString*) _ptr;
    _ptr = 0;
  }
}
Limit::Limit() : _type(-1), _ptr(0) {
}
Limit::Limit(const Limit& _value) {
  init(_value._type, _value._ptr);
}
Limit& Limit::operator=(const Limit& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool Limit::isEmpty() const {
  return _type==_TypeEmpty;
}
bool Limit::isValue() const {
  return _type==_TypeValue;
}
const AnsiString& Limit::asValue() const {
  if (_type!=_TypeValue)
    throw Exception("Limit::asValue");
  return *(AnsiString*) _ptr;
}
AnsiString& Limit::asValue() {
  if (_type!=_TypeValue)
    throw Exception("Limit::asValue");
  return *(AnsiString*) _ptr;
}


Limit::~Limit() {
  clean();
}
Limit Limit::createEmpty() {
  Limit _value;
  _value._type = _TypeEmpty;
  _value._ptr = 0;
  return _value;
}
Limit Limit::createValue(const AnsiString& _param) {
  Limit _value;
  _value._type = _TypeValue;
  _value._ptr = new AnsiString(_param);
  return _value;
}


//----------------------------------

//------------- Set ---------------
Set::Set(const Field& _field, const Field& _value) : field(_field), value(_value) {
}
const Field& Set::getField() const {
  return field;
}
Field& Set::getField() {
  return field;
}
const Field& Set::getValue() const {
  return value;
}
Field& Set::getValue() {
  return value;
}
Set::~Set() {
}
//----------------------------------

//------------- Sets ---------------
Sets::Sets() {
}
Sets::~Sets() {
}
//----------------------------------

//------------- SelectQuery ---------------
SelectQuery::SelectQuery(const Fields& _fields, const Tables& _tables, const Operation& _operation, const Orders& _orders, const Sort& _sort, const Groups& _groups, const Limit& _limit) : fields(_fields), tables(_tables), operation(_operation), orders(_orders), sort(_sort), groups(_groups), limit(_limit) {
}
const Fields& SelectQuery::getFields() const {
  return fields;
}
Fields& SelectQuery::getFields() {
  return fields;
}
const Tables& SelectQuery::getTables() const {
  return tables;
}
Tables& SelectQuery::getTables() {
  return tables;
}
const Operation& SelectQuery::getOperation() const {
  return operation;
}
Operation& SelectQuery::getOperation() {
  return operation;
}
const Orders& SelectQuery::getOrders() const {
  return orders;
}
Orders& SelectQuery::getOrders() {
  return orders;
}
const Sort& SelectQuery::getSort() const {
  return sort;
}
Sort& SelectQuery::getSort() {
  return sort;
}
const Groups& SelectQuery::getGroups() const {
  return groups;
}
Groups& SelectQuery::getGroups() {
  return groups;
}
const Limit& SelectQuery::getLimit() const {
  return limit;
}
Limit& SelectQuery::getLimit() {
  return limit;
}
SelectQuery::~SelectQuery() {
}
//----------------------------------

//------------- InsertQuery ---------------
InsertQuery::InsertQuery(const Table& _table, const Fields& _fields, const Fields& _values) : table(_table), fields(_fields), values(_values) {
}
const Table& InsertQuery::getTable() const {
  return table;
}
Table& InsertQuery::getTable() {
  return table;
}
const Fields& InsertQuery::getFields() const {
  return fields;
}
Fields& InsertQuery::getFields() {
  return fields;
}
const Fields& InsertQuery::getValues() const {
  return values;
}
Fields& InsertQuery::getValues() {
  return values;
}
InsertQuery::~InsertQuery() {
}
//----------------------------------

//------------- UpdateQuery ---------------
UpdateQuery::UpdateQuery(const Table& _table, const Sets& _sets, const Operation& _operation, const Limit& _limit) : table(_table), sets(_sets), operation(_operation), limit(_limit) {
}
const Table& UpdateQuery::getTable() const {
  return table;
}
Table& UpdateQuery::getTable() {
  return table;
}
const Sets& UpdateQuery::getSets() const {
  return sets;
}
Sets& UpdateQuery::getSets() {
  return sets;
}
const Operation& UpdateQuery::getOperation() const {
  return operation;
}
Operation& UpdateQuery::getOperation() {
  return operation;
}
const Limit& UpdateQuery::getLimit() const {
  return limit;
}
Limit& UpdateQuery::getLimit() {
  return limit;
}
UpdateQuery::~UpdateQuery() {
}
//----------------------------------

//------------- DeleteQuery ---------------
DeleteQuery::DeleteQuery(const Table& _table, const Operation& _operation, const Limit& _limit) : table(_table), operation(_operation), limit(_limit) {
}
const Table& DeleteQuery::getTable() const {
  return table;
}
Table& DeleteQuery::getTable() {
  return table;
}
const Operation& DeleteQuery::getOperation() const {
  return operation;
}
Operation& DeleteQuery::getOperation() {
  return operation;
}
const Limit& DeleteQuery::getLimit() const {
  return limit;
}
Limit& DeleteQuery::getLimit() {
  return limit;
}
DeleteQuery::~DeleteQuery() {
}
//----------------------------------

//------------- Sql ---------------
const int Sql::_TypeDeleteQuery = 0;
const int Sql::_TypeInsertQuery = 1;
const int Sql::_TypeUpdateQuery = 2;
const int Sql::_TypeSelectQuery = 3;
void Sql::init(int type, void* ptr) {
  if (type==_TypeDeleteQuery) {
    _type = type;
    _ptr = new DeleteQuery(*(DeleteQuery*) ptr);
  } else if (type==_TypeInsertQuery) {
    _type = type;
    _ptr = new InsertQuery(*(InsertQuery*) ptr);
  } else if (type==_TypeUpdateQuery) {
    _type = type;
    _ptr = new UpdateQuery(*(UpdateQuery*) ptr);
  } else if (type==_TypeSelectQuery) {
    _type = type;
    _ptr = new SelectQuery(*(SelectQuery*) ptr);
  }
}
void Sql::clean() {
  if (_type==_TypeDeleteQuery) {
    _type = -1;
    delete (DeleteQuery*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeInsertQuery) {
    _type = -1;
    delete (InsertQuery*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeUpdateQuery) {
    _type = -1;
    delete (UpdateQuery*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeSelectQuery) {
    _type = -1;
    delete (SelectQuery*) _ptr;
    _ptr = 0;
  }
}
Sql::Sql() : _type(-1), _ptr(0) {
}
Sql::Sql(const Sql& _value) {
  init(_value._type, _value._ptr);
}
Sql& Sql::operator=(const Sql& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool Sql::isDeleteQuery() const {
  return _type==_TypeDeleteQuery;
}
bool Sql::isInsertQuery() const {
  return _type==_TypeInsertQuery;
}
bool Sql::isUpdateQuery() const {
  return _type==_TypeUpdateQuery;
}
bool Sql::isSelectQuery() const {
  return _type==_TypeSelectQuery;
}
const DeleteQuery& Sql::asDeleteQuery() const {
  if (_type!=_TypeDeleteQuery)
    throw Exception("Sql::asDeleteQuery");
  return *(DeleteQuery*) _ptr;
}
DeleteQuery& Sql::asDeleteQuery() {
  if (_type!=_TypeDeleteQuery)
    throw Exception("Sql::asDeleteQuery");
  return *(DeleteQuery*) _ptr;
}
const InsertQuery& Sql::asInsertQuery() const {
  if (_type!=_TypeInsertQuery)
    throw Exception("Sql::asInsertQuery");
  return *(InsertQuery*) _ptr;
}
InsertQuery& Sql::asInsertQuery() {
  if (_type!=_TypeInsertQuery)
    throw Exception("Sql::asInsertQuery");
  return *(InsertQuery*) _ptr;
}
const UpdateQuery& Sql::asUpdateQuery() const {
  if (_type!=_TypeUpdateQuery)
    throw Exception("Sql::asUpdateQuery");
  return *(UpdateQuery*) _ptr;
}
UpdateQuery& Sql::asUpdateQuery() {
  if (_type!=_TypeUpdateQuery)
    throw Exception("Sql::asUpdateQuery");
  return *(UpdateQuery*) _ptr;
}
const SelectQuery& Sql::asSelectQuery() const {
  if (_type!=_TypeSelectQuery)
    throw Exception("Sql::asSelectQuery");
  return *(SelectQuery*) _ptr;
}
SelectQuery& Sql::asSelectQuery() {
  if (_type!=_TypeSelectQuery)
    throw Exception("Sql::asSelectQuery");
  return *(SelectQuery*) _ptr;
}


Sql::~Sql() {
  clean();
}
Sql Sql::createDeleteQuery(const DeleteQuery& _param) {
  Sql _value;
  _value._type = _TypeDeleteQuery;
  _value._ptr = new DeleteQuery(_param);
  return _value;
}
Sql Sql::createInsertQuery(const InsertQuery& _param) {
  Sql _value;
  _value._type = _TypeInsertQuery;
  _value._ptr = new InsertQuery(_param);
  return _value;
}
Sql Sql::createUpdateQuery(const UpdateQuery& _param) {
  Sql _value;
  _value._type = _TypeUpdateQuery;
  _value._ptr = new UpdateQuery(_param);
  return _value;
}
Sql Sql::createSelectQuery(const SelectQuery& _param) {
  Sql _value;
  _value._type = _TypeSelectQuery;
  _value._ptr = new SelectQuery(_param);
  return _value;
}


//----------------------------------

