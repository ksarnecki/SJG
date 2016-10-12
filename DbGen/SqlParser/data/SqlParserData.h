#ifndef _SQLPARSERDATA_GEN_H_
#define _SQLPARSERDATA_GEN_H_
#include "DynSet.h"
//------------- WhenOperations ---------------
#include "DynSet.h"

class WhenOperation;

class WhenOperations : public DynSet<WhenOperation> {
public:
  WhenOperations();


  virtual ~WhenOperations();

};
//----------------------------------

//------------- int ---------------
//----------------------------------

//------------- string ---------------
#include "AnsiString.h"
//----------------------------------

//------------- Sqls ---------------
#include "DynSet.h"

class Sql;

class Sqls : public DynSet<Sql> {
public:
  Sqls();


  virtual ~Sqls();

};
//----------------------------------

//------------- SqlPtr ---------------
class SqlPtr {
  int _type;
  void* _ptr;

  static const int _TypeValue;

  virtual void init(int, void*);
  virtual void clean();
  SqlPtr();
public:
  SqlPtr(const SqlPtr&);
  virtual SqlPtr& operator=(const SqlPtr&);

  virtual bool isValue() const;

  virtual const Sql& asValue() const;
  virtual Sql& asValue();


  virtual ~SqlPtr();

  static SqlPtr createValue(const Sql&);

};
//----------------------------------

//------------- BasicField ---------------
class BasicField {
  AnsiString column;
  AnsiString table;
public:
  BasicField(const AnsiString&, const AnsiString&);
  virtual const AnsiString& getColumn() const;
  virtual const AnsiString& getTable() const;
  virtual AnsiString& getColumn();
  virtual AnsiString& getTable();


  virtual ~BasicField();

};
//----------------------------------

//------------- AgrFieldKind ---------------
class AgrFieldKind {
  int _type;
  void* _ptr;

  static const int _TypeMin;
  static const int _TypeMax;
  static const int _TypeCount;

  virtual void init(int, void*);
  virtual void clean();
  AgrFieldKind();
public:
  AgrFieldKind(const AgrFieldKind&);
  virtual AgrFieldKind& operator=(const AgrFieldKind&);

  virtual bool isMin() const;
  virtual bool isMax() const;
  virtual bool isCount() const;



  virtual ~AgrFieldKind();

  static AgrFieldKind createMin();
  static AgrFieldKind createMax();
  static AgrFieldKind createCount();

};
//----------------------------------

//------------- AgrField ---------------
class AgrField {
  AgrFieldKind agrFieldKind;
  AnsiString args;
public:
  AgrField(const AgrFieldKind&, const AnsiString&);
  virtual const AgrFieldKind& getAgrFieldKind() const;
  virtual const AnsiString& getArgs() const;
  virtual AgrFieldKind& getAgrFieldKind();
  virtual AnsiString& getArgs();


  virtual ~AgrField();

};
//----------------------------------

//------------- FieldKind ---------------
class FieldKind {
  int _type;
  void* _ptr;

  static const int _TypeSpecialField;
  static const int _TypeBasicField;
  static const int _TypeAgrField;
  static const int _TypeAllField;
  static const int _TypeQuery;

  virtual void init(int, void*);
  virtual void clean();
  FieldKind();
public:
  FieldKind(const FieldKind&);
  virtual FieldKind& operator=(const FieldKind&);

  virtual bool isSpecialField() const;
  virtual bool isBasicField() const;
  virtual bool isAgrField() const;
  virtual bool isAllField() const;
  virtual bool isQuery() const;

  virtual const AnsiString& asSpecialField() const;
  virtual AnsiString& asSpecialField();
  virtual const BasicField& asBasicField() const;
  virtual BasicField& asBasicField();
  virtual const AgrField& asAgrField() const;
  virtual AgrField& asAgrField();
  virtual const SqlPtr& asQuery() const;
  virtual SqlPtr& asQuery();


  virtual ~FieldKind();

  static FieldKind createSpecialField(const AnsiString&);
  static FieldKind createBasicField(const BasicField&);
  static FieldKind createAgrField(const AgrField&);
  static FieldKind createAllField();
  static FieldKind createQuery(const SqlPtr&);

};
//----------------------------------

//------------- Field ---------------
class Field {
  AnsiString fieldName;
  FieldKind fieldKind;
public:
  Field(const AnsiString&, const FieldKind&);
  virtual const AnsiString& getFieldName() const;
  virtual const FieldKind& getFieldKind() const;
  virtual AnsiString& getFieldName();
  virtual FieldKind& getFieldKind();


  virtual ~Field();

};
//----------------------------------

//------------- Operations ---------------
#include "DynSet.h"

class Operation;

class Operations : public DynSet<Operation> {
public:
  Operations();


  virtual ~Operations();

};
//----------------------------------

//------------- OperationPtr ---------------
class OperationPtr {
  int _type;
  void* _ptr;

  static const int _TypeValue;

  virtual void init(int, void*);
  virtual void clean();
  OperationPtr();
public:
  OperationPtr(const OperationPtr&);
  virtual OperationPtr& operator=(const OperationPtr&);

  virtual bool isValue() const;

  virtual const Operation& asValue() const;
  virtual Operation& asValue();


  virtual ~OperationPtr();

  static OperationPtr createValue(const Operation&);

};
//----------------------------------

//------------- BinaryOperator ---------------
class BinaryOperator {
  int _type;
  void* _ptr;

  static const int _TypeLike;
  static const int _TypeAnd;
  static const int _TypeOr;
  static const int _TypeIn;
  static const int _TypeEqual;
  static const int _TypeNoEqual;
  static const int _TypeGreater;
  static const int _TypeSmaller;
  static const int _TypeGreaterOrEqual;
  static const int _TypeSmallerOrEqual;

  virtual void init(int, void*);
  virtual void clean();
  BinaryOperator();
public:
  BinaryOperator(const BinaryOperator&);
  virtual BinaryOperator& operator=(const BinaryOperator&);

  virtual bool isLike() const;
  virtual bool isAnd() const;
  virtual bool isOr() const;
  virtual bool isIn() const;
  virtual bool isEqual() const;
  virtual bool isNoEqual() const;
  virtual bool isGreater() const;
  virtual bool isSmaller() const;
  virtual bool isGreaterOrEqual() const;
  virtual bool isSmallerOrEqual() const;



  virtual ~BinaryOperator();

  static BinaryOperator createLike();
  static BinaryOperator createAnd();
  static BinaryOperator createOr();
  static BinaryOperator createIn();
  static BinaryOperator createEqual();
  static BinaryOperator createNoEqual();
  static BinaryOperator createGreater();
  static BinaryOperator createSmaller();
  static BinaryOperator createGreaterOrEqual();
  static BinaryOperator createSmallerOrEqual();

};
//----------------------------------

//------------- BinaryOperation ---------------
class BinaryOperation {
  OperationPtr left;
  OperationPtr right;
  BinaryOperator binaryOperator;
public:
  BinaryOperation(const OperationPtr&, const OperationPtr&, const BinaryOperator&);
  virtual const OperationPtr& getLeft() const;
  virtual const OperationPtr& getRight() const;
  virtual const BinaryOperator& getBinaryOperator() const;
  virtual OperationPtr& getLeft();
  virtual OperationPtr& getRight();
  virtual BinaryOperator& getBinaryOperator();


  virtual ~BinaryOperation();

};
//----------------------------------

//------------- UnaryOperator ---------------
class UnaryOperator {
  int _type;
  void* _ptr;

  static const int _TypeNegative;
  static const int _TypePositive;
  static const int _TypeNot;

  virtual void init(int, void*);
  virtual void clean();
  UnaryOperator();
public:
  UnaryOperator(const UnaryOperator&);
  virtual UnaryOperator& operator=(const UnaryOperator&);

  virtual bool isNegative() const;
  virtual bool isPositive() const;
  virtual bool isNot() const;



  virtual ~UnaryOperator();

  static UnaryOperator createNegative();
  static UnaryOperator createPositive();
  static UnaryOperator createNot();

};
//----------------------------------

//------------- UnaryOperation ---------------
class UnaryOperation {
  OperationPtr right;
  UnaryOperator unaryOperator;
public:
  UnaryOperation(const OperationPtr&, const UnaryOperator&);
  virtual const OperationPtr& getRight() const;
  virtual const UnaryOperator& getUnaryOperator() const;
  virtual OperationPtr& getRight();
  virtual UnaryOperator& getUnaryOperator();


  virtual ~UnaryOperation();

};
//----------------------------------

//------------- WhenOperation ---------------
class WhenOperation {
  OperationPtr condition;
  OperationPtr stmnt;
public:
  WhenOperation(const OperationPtr&, const OperationPtr&);
  virtual const OperationPtr& getCondition() const;
  virtual const OperationPtr& getStmnt() const;
  virtual OperationPtr& getCondition();
  virtual OperationPtr& getStmnt();


  virtual ~WhenOperation();

};
//----------------------------------

//------------- CaseOperation ---------------
class CaseOperation {
  WhenOperations cases;
  OperationPtr elseStmnt;
public:
  CaseOperation(const WhenOperations&, const OperationPtr&);
  virtual const WhenOperations& getCases() const;
  virtual const OperationPtr& getElseStmnt() const;
  virtual WhenOperations& getCases();
  virtual OperationPtr& getElseStmnt();


  virtual ~CaseOperation();

};
//----------------------------------

//------------- Operation ---------------
class Operation {
  int _type;
  void* _ptr;

  static const int _TypeBinaryOperation;
  static const int _TypeUnaryOperation;
  static const int _TypeExistsOperation;
  static const int _TypeCaseOperation;
  static const int _TypeField;
  static const int _TypeEmpty;

  virtual void init(int, void*);
  virtual void clean();
  Operation();
public:
  Operation(const Operation&);
  virtual Operation& operator=(const Operation&);

  virtual bool isBinaryOperation() const;
  virtual bool isUnaryOperation() const;
  virtual bool isExistsOperation() const;
  virtual bool isCaseOperation() const;
  virtual bool isField() const;
  virtual bool isEmpty() const;

  virtual const BinaryOperation& asBinaryOperation() const;
  virtual BinaryOperation& asBinaryOperation();
  virtual const UnaryOperation& asUnaryOperation() const;
  virtual UnaryOperation& asUnaryOperation();
  virtual const Sql& asExistsOperation() const;
  virtual Sql& asExistsOperation();
  virtual const CaseOperation& asCaseOperation() const;
  virtual CaseOperation& asCaseOperation();
  virtual const Field& asField() const;
  virtual Field& asField();


  virtual ~Operation();

  static Operation createBinaryOperation(const BinaryOperation&);
  static Operation createUnaryOperation(const UnaryOperation&);
  static Operation createExistsOperation(const Sql&);
  static Operation createCaseOperation(const CaseOperation&);
  static Operation createField(const Field&);
  static Operation createEmpty();

};
//----------------------------------

//------------- TableKind ---------------
class TableKind {
  int _type;
  void* _ptr;

  static const int _TypeBasic;
  static const int _TypeQuery;

  virtual void init(int, void*);
  virtual void clean();
  TableKind();
public:
  TableKind(const TableKind&);
  virtual TableKind& operator=(const TableKind&);

  virtual bool isBasic() const;
  virtual bool isQuery() const;

  virtual const AnsiString& asBasic() const;
  virtual AnsiString& asBasic();
  virtual const SqlPtr& asQuery() const;
  virtual SqlPtr& asQuery();


  virtual ~TableKind();

  static TableKind createBasic(const AnsiString&);
  static TableKind createQuery(const SqlPtr&);

};
//----------------------------------

//------------- Table ---------------
class Table {
  TableKind kind;
  AnsiString as;
public:
  Table(const TableKind&, const AnsiString&);
  virtual const TableKind& getKind() const;
  virtual const AnsiString& getAs() const;
  virtual TableKind& getKind();
  virtual AnsiString& getAs();


  virtual ~Table();

};
//----------------------------------

//------------- Tables ---------------
#include "DynSet.h"


class Tables : public DynSet<Table> {
public:
  Tables();


  virtual ~Tables();

};
//----------------------------------

//------------- Fields ---------------
#include "DynSet.h"


class Fields : public DynSet<Field> {
public:
  Fields();


  virtual ~Fields();

};
//----------------------------------

//------------- Orders ---------------
#include "DynSet.h"


class Orders : public DynSet<Field> {
public:
  Orders();


  virtual ~Orders();

};
//----------------------------------

//------------- Groups ---------------
#include "DynSet.h"


class Groups : public DynSet<Field> {
public:
  Groups();


  virtual ~Groups();

};
//----------------------------------

//------------- Sort ---------------
class Sort {
  int _type;
  void* _ptr;

  static const int _TypeEmpty;
  static const int _TypeDesc;
  static const int _TypeAsc;

  virtual void init(int, void*);
  virtual void clean();
  Sort();
public:
  Sort(const Sort&);
  virtual Sort& operator=(const Sort&);

  virtual bool isEmpty() const;
  virtual bool isDesc() const;
  virtual bool isAsc() const;



  virtual ~Sort();

  static Sort createEmpty();
  static Sort createDesc();
  static Sort createAsc();

};
//----------------------------------

//------------- Limit ---------------
class Limit {
  int _type;
  void* _ptr;

  static const int _TypeEmpty;
  static const int _TypeValue;

  virtual void init(int, void*);
  virtual void clean();
  Limit();
public:
  Limit(const Limit&);
  virtual Limit& operator=(const Limit&);

  virtual bool isEmpty() const;
  virtual bool isValue() const;

  virtual const AnsiString& asValue() const;
  virtual AnsiString& asValue();


  virtual ~Limit();

  static Limit createEmpty();
  static Limit createValue(const AnsiString&);

};
//----------------------------------

//------------- Set ---------------
class Set {
  Field field;
  Field value;
public:
  Set(const Field&, const Field&);
  virtual const Field& getField() const;
  virtual const Field& getValue() const;
  virtual Field& getField();
  virtual Field& getValue();


  virtual ~Set();

};
//----------------------------------

//------------- Sets ---------------
#include "DynSet.h"


class Sets : public DynSet<Set> {
public:
  Sets();


  virtual ~Sets();

};
//----------------------------------

//------------- SelectQuery ---------------
class SelectQuery {
  Fields fields;
  Tables tables;
  Operation operation;
  Orders orders;
  Sort sort;
  Groups groups;
  Limit limit;
public:
  SelectQuery(const Fields&, const Tables&, const Operation&, const Orders&, const Sort&, const Groups&, const Limit&);
  virtual const Fields& getFields() const;
  virtual const Tables& getTables() const;
  virtual const Operation& getOperation() const;
  virtual const Orders& getOrders() const;
  virtual const Sort& getSort() const;
  virtual const Groups& getGroups() const;
  virtual const Limit& getLimit() const;
  virtual Fields& getFields();
  virtual Tables& getTables();
  virtual Operation& getOperation();
  virtual Orders& getOrders();
  virtual Sort& getSort();
  virtual Groups& getGroups();
  virtual Limit& getLimit();


  virtual ~SelectQuery();

};
//----------------------------------

//------------- InsertQuery ---------------
class InsertQuery {
  Table table;
  Fields fields;
  Fields values;
public:
  InsertQuery(const Table&, const Fields&, const Fields&);
  virtual const Table& getTable() const;
  virtual const Fields& getFields() const;
  virtual const Fields& getValues() const;
  virtual Table& getTable();
  virtual Fields& getFields();
  virtual Fields& getValues();


  virtual ~InsertQuery();

};
//----------------------------------

//------------- UpdateQuery ---------------
class UpdateQuery {
  Table table;
  Sets sets;
  Operation operation;
  Limit limit;
public:
  UpdateQuery(const Table&, const Sets&, const Operation&, const Limit&);
  virtual const Table& getTable() const;
  virtual const Sets& getSets() const;
  virtual const Operation& getOperation() const;
  virtual const Limit& getLimit() const;
  virtual Table& getTable();
  virtual Sets& getSets();
  virtual Operation& getOperation();
  virtual Limit& getLimit();


  virtual ~UpdateQuery();

};
//----------------------------------

//------------- DeleteQuery ---------------
class DeleteQuery {
  Table table;
  Operation operation;
  Limit limit;
public:
  DeleteQuery(const Table&, const Operation&, const Limit&);
  virtual const Table& getTable() const;
  virtual const Operation& getOperation() const;
  virtual const Limit& getLimit() const;
  virtual Table& getTable();
  virtual Operation& getOperation();
  virtual Limit& getLimit();


  virtual ~DeleteQuery();

};
//----------------------------------

//------------- Sql ---------------
class Sql {
  int _type;
  void* _ptr;

  static const int _TypeDeleteQuery;
  static const int _TypeInsertQuery;
  static const int _TypeUpdateQuery;
  static const int _TypeSelectQuery;

  virtual void init(int, void*);
  virtual void clean();
  Sql();
public:
  Sql(const Sql&);
  virtual Sql& operator=(const Sql&);

  virtual bool isDeleteQuery() const;
  virtual bool isInsertQuery() const;
  virtual bool isUpdateQuery() const;
  virtual bool isSelectQuery() const;

  virtual const DeleteQuery& asDeleteQuery() const;
  virtual DeleteQuery& asDeleteQuery();
  virtual const InsertQuery& asInsertQuery() const;
  virtual InsertQuery& asInsertQuery();
  virtual const UpdateQuery& asUpdateQuery() const;
  virtual UpdateQuery& asUpdateQuery();
  virtual const SelectQuery& asSelectQuery() const;
  virtual SelectQuery& asSelectQuery();


  virtual ~Sql();

  static Sql createDeleteQuery(const DeleteQuery&);
  static Sql createInsertQuery(const InsertQuery&);
  static Sql createUpdateQuery(const UpdateQuery&);
  static Sql createSelectQuery(const SelectQuery&);

};
//----------------------------------

#endif
