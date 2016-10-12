//---------------------------------------------------------------------------

#include "OldParser.h"
#include "CPPGenerator.h"
#include "PHPGenerator.h"
#include "JavaGenerator.h"
#include "JavascriptGenerator.h"
#include "CSGenerator.h"

#include <iostream>
#include <fstream>

//---------------------------------------------------------------------------

DynSet<AnsiString> readData() {
  char buf[1024];
  DynSet<AnsiString> ret;
  while (std::cin.getline(buf, 1024))
    ret.Insert(AnsiString(buf).Trim());
  return ret;
}

void saveToFile(const AnsiString& file, const AnsiString content) {
  printf("%s", file.c_str());
  std::fstream f(file.c_str(), std::ios::out | std::ios::trunc);
  if (!f.is_open())
    throw Exception("Cant open file " + file);
  f << content.c_str() << std::endl;
}

static void saveToFile(const GenerateFiles& res) {
  for (int i=0;i<res.Size();i++)
    saveToFile(res[i].getName(), res[i].getContent());
}

static AnsiString kindToString(DataFileKind kind) {
  if (kind.isCpp())
    return "cpp";
  if (kind.isJava())
    return "java";
  if (kind.isJavascript())
    return "javascript";
  if (kind.isCs())
    return "cs";
  if (kind.isPhp()) 
    return "php";
}

static AnsiString recordToString(DataType type) {
  AnsiString ret = "";
  AnsiString name = type.getName();
  RecordType recordType = type.getKind().asRecord();
  ret += name + " = record {\n";
  for (int i = 0; i < recordType.Size(); i++) {
    ret += "  " + recordType[i].getName() + " : " + recordType[i].getType();
    if(i < recordType.Size()-1)
      ret += ",";
    ret += "\n";
  }
  ret += "}\n\n";
  return ret;
}

static AnsiString variantToString(DataType type) {
  AnsiString ret = "";
  AnsiString name = type.getName();
  VariantType variantType = type.getKind().asVariant();
  ret += name + " = variant {\n";
  for (int i = 0; i < variantType.Size(); i++) {
    ret += "  " + variantType[i].getName();
    if(!variantType[i].getKind().isEmpty())
      ret += " : " + variantType[i].getKind().asType();
    if (i < variantType.Size() - 1)
      ret += ",";
    ret += "\n";
  }
  ret += "}\n\n";
  return ret;
}

static AnsiString basicToString(DataType type) {
  AnsiString ret = "";
  AnsiString name = type.getName();
  ret += type.getKind().asBasic() + "\nbasic\n\n";
  return ret; 
}

static AnsiString arrayToString(DataType type) {
  AnsiString ret = "";
  AnsiString name = type.getName();
  ArrayType arrayType = type.getKind().asArray();
  ret += name + " = array of " + arrayType.getType() + "\n\n";
  return ret;
}

static AnsiString externalToString(DataType type) {
  AnsiString ret = "";
  AnsiString name = type.getName();
  ExternalType externalType = type.getKind().asExternal();
  ret += name + "\nexternal\n" + externalType.getSource() + "\n\n";
  return ret;
}

static AnsiString typeToString(DataType type) {
  if (type.getKind().isRecord())
    return recordToString(type);
  if (type.getKind().isVariant())
    return variantToString(type);
  if (type.getKind().isBasic())
    return basicToString(type);
  if (type.getKind().isArray())
    return arrayToString(type);
  if (type.getKind().isExternal())
    return externalToString(type);
}


static AnsiString convert(DataFileBase data) {
  AnsiString ret = "";
  ret += data.getFile() + "\n\n";
  ret += kindToString(data.getKind()) + +"\n\n";
  for (int i = 0; i < data.getTypes().Size(); i++) {
    ret += typeToString(data.getTypes()[i]);
  }
  return ret;
}

int main() {
  DynSet<AnsiString> lines = readData();
  LineStream stream(lines);
  try {
    DataFileBase data = processData(stream);
    saveToFile("DataNew.dd", convert(data));
   
  } catch (const Exception& exc) {
    std::cout << "B³¹d: " << exc.Message.c_str() << std::endl;
    return 1;
  }
  return 0;
}
//---------------------------------------------------------------------------
 
