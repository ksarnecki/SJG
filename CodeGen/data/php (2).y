%define api.prefix {codegen}
%{

#include <string.h>
#include <malloc.h>
#include <stdio.h>

#include "AnsiString.h"
#include "File.h"

extern "C" {
  int codegenparse(void);
  int codegenlex(void);
  int codegenwrap() {
    return 1;
  }
  extern int codegenlineno;
  extern char* codegentext;
}

void codegenerror(const char *s) {
  printf("%s at line %d", s, codegenlineno);
  if (codegentext!=0)
    printf(", near token %s", codegentext);
  printf("\n");
}

template <class T>
class Box {
  T v;
public:
  Box(const T& _v) : v(_v) {
  }
  virtual const T& get() const {
    return v;
  }
  virtual ~Box() {
  }
};

template <class T>
static T xbox(int v) {
  Box<T>* b = (Box<T>*) v;
  T t = b->get();
  delete b;
  return t;
}

static AnsiString xboxs(int v) {
  char* s = (char*) v;
  AnsiString ret(s);
  free(s);
  return ret;
}

DataFileKind mkFileType(const AnsiString type) {
  if (type=="cpp")
    return DataFileKind::createCpp();
  else if (type=="php")
    return DataFileKind::createPhp();
  else if (type=="java")
    return DataFileKind::createJava();
  else if (type=="javascript")
    return DataFileKind::createJavascript();
  else if (type=="cs")
    return DataFileKind::createCs();
  else
    throw Exception("Unknown file type ["+type+"]");
}

DataTypeArray mergeDataTypeArray(DataTypeArray a, DataTypeArray b) {
  DataTypeArray ret;
  for(int i=0;i<a.Size();i++)
    ret.Insert(a[i]);
  for(int i=0;i<b.Size();i++)
    ret.Insert(b[i]);
  return ret;
}

DataFileBase* codegenfresult = 0;

DataTypeArray inlineTypes;

%}

%token  TEXT INT BOOL STRING BASIC RECORD ARRAY EXTERNAL VARIANT /* wszystkie nazwy tokenow majace wiecej niz jeden znak musza byc zadeklarowane */

%%

fileBase : file kind types { codegenfresult = new DataFileBase(xbox<AnsiString>($1), mkFileType(xbox<AnsiString>($2)), mergeDataTypeArray(inlineTypes, xbox<DataTypeArray>($3)));} 

file : TEXT { $$ = new Box<AnsiString>(xboxs($1));}
kind : TEXT { $$ = new Box<AnsiString>(xboxs($1));}

types : types type  { DataTypeArray d = xbox<DataTypeArray>($1); d.Insert(xbox<DataType>($2)); $$ = new Box<DataTypeArray>(d);}
types : { $$ = new Box<DataTypeArray>(DataTypeArray());}

type : recordType 
type : basicType
type : externalType
type : variantType
type : arrayType


basicType : basicTypeName BASIC { AnsiString name = xbox<AnsiString>($1); $$ = new Box<DataType>(DataType(name,DataTypeKind::createBasic(name)));}

basicTypeName : INT { $$ = new Box<AnsiString>("int");}
basicTypeName : BOOL { $$ = new Box<AnsiString>("bool");}
basicTypeName : STRING { $$ = new Box<AnsiString>("string");}

externalType : TEXT EXTERNAL TEXT { $$ = new Box<DataType> (DataType(xboxs($1), DataTypeKind::createExternal(ExternalType(xboxs($3)))));}

recordType : TEXT '=' RECORD  '{' recordFields '}' { $$ = new Box<DataType>(DataType(xboxs($1), DataTypeKind::createRecord(xbox<RecordType>($5))));}
recordType : TEXT '=' RECORD  '{' '}' { $$ = new Box<DataType>(DataType(xboxs($1), DataTypeKind::createRecord(RecordType())));}
recordFields : recordFields ',' recordField {RecordType r = xbox<RecordType>($1); r.Insert(xbox<RecordField>($3)); $$ = new Box<RecordType> (r);}
recordFields : recordField { RecordType r = RecordType(); r.Insert(xbox<RecordField>($1)); $$ = new Box<RecordType> (r); }
recordField : TEXT ':' type  {  DataType inlineType = xbox<DataType>($3); inlineTypes.Insert(inlineType); $$ = new Box<RecordField>(RecordField(xboxs($1), inlineType.getName())); }
recordField : TEXT ':' basicTypeName { AnsiString name = xbox<AnsiString>($3); $$ = new Box<RecordField>(RecordField(xboxs($1), name));}
recordField : TEXT ':' TEXT     { $$ = new Box<RecordField>(RecordField(xboxs($1), xboxs($3)));}

arrayType : TEXT '=' ARRAY type  {  DataType inlineType = xbox<DataType>($4); inlineTypes.Insert(inlineType);  $$ = new Box<DataType>(DataType(xboxs($1), DataTypeKind::createArray(ArrayType(inlineType.getName())))); }
arrayType : TEXT '=' ARRAY TEXT { $$ = new Box<DataType>(DataType(xboxs($1), DataTypeKind::createArray(ArrayType(xboxs($4)))));}
arrayType : TEXT '=' ARRAY basicTypeName {  $$ = new Box<DataType>(DataType(xboxs($1), DataTypeKind::createArray(ArrayType(xbox<AnsiString>($4)))));}

variantType : TEXT '=' VARIANT '{' variantFields '}' {  $$ = new Box<DataType>(DataType(xboxs($1), DataTypeKind::createVariant(xbox<VariantType>($5))));}
variantFields : variantFields ',' variantField { VariantType v = xbox<VariantType>($1); v.Insert(xbox<VariantField>($3)); $$ = new Box<VariantType> (v);}
variantFields : variantFields '|' variantField { VariantType v = xbox<VariantType>($1); v.Insert(xbox<VariantField>($3)); $$ = new Box<VariantType> (v);}
variantFields : variantField { VariantType v = VariantType(); v.Insert(xbox<VariantField>($1)); $$ = new Box<VariantType> (v);}
variantField : fieldName ':' type  {  DataType inlineType = xbox<DataType>($3); inlineTypes.Insert(inlineType); $$ = new Box<VariantField>(VariantField(xboxs($1),  VariantFieldKind::createType(inlineType.getName()))); }
variantField : fieldName ':' basicTypeName { AnsiString name = xbox<AnsiString>($3); $$ = new Box<VariantField>(VariantField(xboxs($1), VariantFieldKind::createType(name)));}
variantField : fieldName ':' TEXT     {$$ = new Box<VariantField>(VariantField(xboxs($1), VariantFieldKind::createType(xboxs($3))));}
variantField : fieldName { $$ = new Box<VariantField>(VariantField(xboxs($1), VariantFieldKind::createEmpty()));}

fieldName : TEXT { $$ = $1; }
fieldName : BASIC { $$ = (int) strdup("basic"); }
fieldName : RECORD { $$ = (int) strdup("record"); }
fieldName : EXTERNAL { $$ = (int) strdup("external"); }
fieldName : VARIANT { $$ = (int) strdup("variant"); }
fieldName : INT { $$ = (int) strdup("int"); }
fieldName : STRING { $$ = (int) strdup("string"); }
fieldName : BOOL { $$ = (int) strdup("bool"); }


%%

int codegenlex(void);
void codegenerror(const char *);

#include "lex.codegen.c"

#include "CPPGenerator.h"
#include "PHPGenerator.h"
#include "JavaGenerator.h"
#include "JavascriptGenerator.h"
#include "CSGenerator.h"

#include <iostream>
#include <fstream>

extern DataFileBase codegen_yacc_parse(LineStream& stream) {
  AnsiString input = "";
  stream.next();
  while(!stream.isEof()) {
    AnsiString line = stream.getLine() + "\r\n";
    input += line;
    stream.next();
  }
  codegen_scan_string(input.c_str());
  codegenparse(); 
  if(codegenfresult!=0) {
    DataFileBase data = *codegenfresult;
    return data;
  } else 
    throw Exception("Parser error...");
}