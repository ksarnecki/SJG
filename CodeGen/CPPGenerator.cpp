//---------------------------------------------------------------------------

#include "CPPGenerator.h"
#include "Util.h"

//---------------------------------------------------------------------------

static AnsiString capAll(const AnsiString& str) {
  return str.UpperCase();
}
static AnsiString toUpper(const AnsiString& str) {
  AnsiString ret = str;
  if (ret.Length()>1) {
    ret[1] = capAll(ret)[1];
  }
  return ret;
}
AnsiString getBasicTypeInclude(const AnsiString& type) {
  if (type=="string")
    return "AnsiString.h";
  else if (type=="int")
    return "";
  else if (type == "bool")
    return "";
  else
    throw Exception("Nieznany typ prosty " + type);
}
AnsiString getBasicTypeName(const AnsiString& type) {
  if (type=="string")
    return "AnsiString";
  else if (type=="int")
    return "int";
  else if (type=="bool")
    return "bool";
  else
    throw Exception("Nieznany typ prosty " + type);
}
AnsiString getRealTypeName(const DataTypeArray& data, const AnsiString& type) {
  int ix = findTypeByName(data, type);
  if (ix==-1)
    throw Exception("Nieznany typ " + type);
  if (!data[ix].getKind().isBasic())
    return type;
  else
    return getBasicTypeName(type);
}
bool needForwardTableDef(const DataTypeArray& data, const AnsiString& table, const AnsiString& type) {
  int ixArr = findTypeByName(data, table);
  int ixType = findTypeByName(data, type);
  if (ixArr>ixType)
    return false;
  return !data[ixType].getKind().isBasic();
}
AnsiString getConstrParam(const DataTypeArray& data, const RecordField& field, bool names) {
  return "const " + getRealTypeName(data, field.getType()) + "&" + ((names) ? " _" + field.getName() : AnsiString());
}
AnsiString getConstrParams(const DataTypeArray& data, const RecordType& record, bool names) {
  AnsiString ret;
  if (record.Size()==0)
    return ret;
  ret = getConstrParam(data, record[0], names);
  for (int i=1;i<record.Size();i++)
    ret += ", " + getConstrParam(data, record[i], names);
  return ret;
}
DynSet<AnsiString> generateHFile(const AnsiString& file, bool xml, bool simple, bool bin, bool json, const DataTypeArray& data) {
  DynSet<AnsiString> ret;
  ret.Insert("#ifndef _"+capAll(file)+"_GEN_H_");
  ret.Insert("#define _"+capAll(file)+"_GEN_H_");
  ret.Insert("#include \"DynSet.h\"");
  if (simple)
    ret.Insert("#include \"SimpleData.h\"");
  if (bin) {
    ret.Insert("#include \"BinaryWriter.h\"");
    ret.Insert("#include \"BinaryReader.h\"");
  }
  if (json) {
    ret.Insert("#include <stdio.h>");
    ret.Insert("#include <stdlib.h>");
  }
  for (int i=0;i<data.Size();i++) {
    DataType type = data[i];
    DataTypeKind kind = type.getKind();
    ret.Insert("//------------- "+type.getName()+" ---------------");
    if (kind.isBasic()) {
      AnsiString incl = getBasicTypeInclude(type.getName());
      if (incl.Length()>0)
        ret.Insert("#include \""+incl+"\"");
    } else if (kind.isExternal())
      ret.Insert("#include \""+ kind.asExternal().getSource() +"\"");
    else if (kind.isRecord()) {
      RecordType record = kind.asRecord();
      ret.Insert("class "+type.getName()+" {");
      for (int i=0;i<record.Size();i++)
        ret.Insert("  "+getRealTypeName(data, record[i].getType())+" "+record[i].getName()+";");
      ret.Insert("public:");
      ret.Insert("  "+type.getName()+"("+getConstrParams(data, record, false)+");");
      for (int i=0;i<record.Size();i++)
        ret.Insert("  virtual const "+getRealTypeName(data, record[i].getType())+"& get"+cap1st(record[i].getName())+"() const;");
      for (int i=0;i<record.Size();i++)
        ret.Insert("  virtual "+getRealTypeName(data, record[i].getType())+"& get"+cap1st(record[i].getName())+"();");
      ret.Insert("");
      if (simple)
        ret.Insert("  virtual SimpleData toSimpleData() const;");
      if (bin)
        ret.Insert("  virtual void toBinary(BinaryWriter&) const;");
      if (xml)
        ret.Insert("  virtual AnsiString toXML() const;");
      if (json) {
        ret.Insert("  virtual AnsiString toJSON() const;");
        ret.Insert("  static "+type.getName()+" fromJSON(AnsiString);");
      }
      ret.Insert("");
      ret.Insert("  virtual ~"+type.getName()+"();");
      ret.Insert("");
      if (simple)
        ret.Insert("  static "+type.getName()+" fromSimpleData(const SimpleData&);");
      if (bin)
        ret.Insert("  static "+type.getName()+" fromBinary(BinaryReader&);");
      ret.Insert("};");
    } else if (kind.isArray()) {
      AnsiString realType = getRealTypeName(data, kind.asArray().getType());
      ret.Insert("#include \"DynSet.h\"");
      ret.Insert("");
      if (needForwardTableDef(data, type.getName(), kind.asArray().getType()))
        ret.Insert("class "+realType+";");
      ret.Insert("");
      ret.Insert("class " + type.getName() + " : public DynSet<" + realType + "> {");
      ret.Insert("public:");
      ret.Insert("  "+type.getName()+"();");
      ret.Insert("");
      if (simple)
        ret.Insert("  virtual SimpleData toSimpleData() const;");
      if (bin)
        ret.Insert("  virtual void toBinary(BinaryWriter&) const;");
      if (xml)
        ret.Insert("  virtual AnsiString toXML() const;");
      if (json) {
        ret.Insert("  virtual AnsiString toJSON() const;");
        ret.Insert("  static "+type.getName()+" fromJSON(AnsiString);");
      }
      ret.Insert("");
      ret.Insert("  virtual ~"+type.getName()+"();");
      ret.Insert("");
      if (simple)
        ret.Insert("  static "+type.getName()+" fromSimpleData(const SimpleData&);");
      if (bin)
        ret.Insert("  static "+type.getName()+" fromBinary(BinaryReader&);");
      ret.Insert("};");
    } else if (kind.isVariant()) {
      VariantType variant = kind.asVariant();
      ret.Insert("class "+type.getName()+" {");
      ret.Insert("  int _type;");
      ret.Insert("  void* _ptr;");
      ret.Insert("");
      for (int i=0;i<variant.Size();i++)
        ret.Insert("  static const int _Type"+cap1st(variant[i].getName())+";");
      ret.Insert("");
      ret.Insert("  virtual void init(int, void*);");
      ret.Insert("  virtual void clean();");
      ret.Insert("  "+type.getName()+"();");
      ret.Insert("public:");
      ret.Insert("  "+type.getName()+"(const "+type.getName()+"&);");
      ret.Insert("  virtual "+type.getName()+"& operator=(const "+type.getName()+"&);");
      ret.Insert("");
      for (int i=0;i<variant.Size();i++)
        ret.Insert("  virtual bool is"+cap1st(variant[i].getName())+"() const;");
      ret.Insert("");
      for (int i=0;i<variant.Size();i++) {
        VariantField field = variant[i];
        VariantFieldKind kind = field.getKind();
        if (kind.isEmpty())
          ;
        else if (kind.isType()) {
          ret.Insert("  virtual const "+getRealTypeName(data, kind.asType())+"& as"+cap1st(variant[i].getName())+"() const;");
          ret.Insert("  virtual "+getRealTypeName(data, kind.asType())+"& as"+cap1st(variant[i].getName())+"();");
        } else
          throw Exception("");
      }
      ret.Insert("");
      if (simple)
        ret.Insert("  virtual SimpleData toSimpleData() const;");
      if (bin)
        ret.Insert("  virtual void toBinary(BinaryWriter&) const;");
      if (xml)
        ret.Insert("  virtual AnsiString toXML() const;");
      if (json) {
        ret.Insert("  virtual AnsiString toJSON() const;");
        ret.Insert("  static "+type.getName()+" fromJSON(AnsiString);");
      }
      ret.Insert("");
      ret.Insert("  virtual ~"+type.getName()+"();");
      ret.Insert("");
      for (int i=0;i<variant.Size();i++) {
        VariantField field = variant[i];
        VariantFieldKind kind = field.getKind();
        if (kind.isEmpty())
          ret.Insert("  static "+type.getName()+" create"+cap1st(variant[i].getName())+"();");
        else if (kind.isType())
          ret.Insert("  static "+type.getName()+" create"+cap1st(variant[i].getName())+"(const "+getRealTypeName(data, kind.asType())+"&);");
        else
          throw Exception("");
      }
      ret.Insert("");
      if (simple)
        ret.Insert("  static "+type.getName()+" fromSimpleData(const SimpleData&);");
      if (bin)
        ret.Insert("  static "+type.getName()+" fromBinary(BinaryReader&);");
      ret.Insert("};");
    } else
      throw Exception("");
    ret.Insert("//----------------------------------");
    ret.Insert("");
  }
  ret.Insert("#endif");
  return ret;
}
AnsiString getConstrParamInit(const RecordField& field) {
  return field.getName() + "(_"+field.getName()+")";
}
AnsiString getConstrParamsInit(const RecordType& record) {
  AnsiString ret = getConstrParamInit(record[0]);
  for (int i=1;i<record.Size();i++)
    ret += ", " + getConstrParamInit(record[i]);
  return ret;
}
static AnsiString mkToJSONBasic(const AnsiString& access, const AnsiString& type) {
  if (type=="int")
    return "AnsiString("+access+")";
  if (type == "bool")
    return "AnsiString((int)" + access + ")";
  else if (type=="string")
    return "\"\\\"\" + JSONEscape::encode("+access+") + \"\\\"\"";
  else
    throw Exception("Bad basic type ["+type+"].");
}
static AnsiString mkFromJSON(const DataTypeArray& data, const AnsiString& type, const AnsiString& access) {
  int ix = findTypeByName(data, type);
  if (ix == -1)
    throw Exception("Nieznany typ "+type);
  if (!data[ix].getKind().isBasic())
    return type+"::fromJSON("+access+")";
  else {
    AnsiString basic = data[ix].getKind().asBasic();
    if (basic=="int" || basic=="bool")
      return "atoi("+access+".c_str())";
    else if (basic == "string") {
      return "("+access+".Length()-2<0 ? throw Exception(\"String::FromJSON\") : JSONEscape::decode("+access+".SubString(2, "+access+".Length()-2)))";
    }
    else
      throw Exception("Nieznany typ prosty "+type);
  }
}
DynSet<AnsiString> generateCppRecordCode(const DataTypeArray& data, bool xml, bool simple, bool bin, bool json, const AnsiString& type, const RecordType& record) {
  DynSet<AnsiString> ret;
  ret.Insert(type+"::"+type+"("+getConstrParams(data, record, true)+") : "+getConstrParamsInit(record)+" {");
  ret.Insert("}");
  for (int i=0;i<record.Size();i++) {
    ret.Insert("const " + getRealTypeName(data, record[i].getType())+"& "+type+"::get"+cap1st(record[i].getName())+"() const {");
    ret.Insert("  return "+record[i].getName()+";");
    ret.Insert("}");
    ret.Insert("" + getRealTypeName(data, record[i].getType())+"& "+type+"::get"+cap1st(record[i].getName())+"() {");
    ret.Insert("  return "+record[i].getName()+";");
    ret.Insert("}");
  }
  if (bin) {
    ret.Insert("void "+type+"::toBinary(BinaryWriter& writer) const {");
    for (int i=0;i<record.Size();i++) {
      DataType type = getTypeByName(data, record[i].getType());
      DataTypeKind kind = type.getKind();
      if (kind.isBasic())
        ret.Insert("  writer << "+record[i].getName()+";");
      else
        ret.Insert("  "+record[i].getName()+".toBinary(writer);");
    }
    ret.Insert("}");
  }
  if (simple) {
    ret.Insert("SimpleData "+type+"::toSimpleData() const {");
    ret.Insert("  SimpleRecord _record;");
    for (int i=0;i<record.Size();i++) {
      DataType type = getTypeByName(data, record[i].getType());
      DataTypeKind kind = type.getKind();
      if (kind.isBasic()) {
        AnsiString name = type.getName();
        if (name=="int")
          ret.Insert("  _record.add(\""+record[i].getName()+"\", SimpleData::createInt("+record[i].getName()+"));");
        else if (name=="bool")
          ret.Insert("  _record.add(\"" + record[i].getName() + "\", SimpleData::createInt(" + record[i].getName() + "));");
        else if (name=="string")
          ret.Insert("  _record.add(\""+record[i].getName()+"\", SimpleData::createString("+record[i].getName()+"));");
        else
          throw Exception("");
      } else
        ret.Insert("  _record.add(\""+record[i].getName()+"\", "+record[i].getName()+".toSimpleData());");
    }
    ret.Insert("  return SimpleData::createRecord(_record);");
    ret.Insert("}");
  }
  if (xml) {
    ret.Insert("AnsiString "+type+"::toXML() const {");
    ret.Insert("  StringBuffer _xml;");
    ret.Insert("  _xml += \"<"+type+">\";");
    for (int i=0;i<record.Size();i++)
      if (getTypeByName(data, record[i].getType()).getKind().isBasic())
        ret.Insert("    _xml += \"<"+record[i].getName()+"><![CDATA[\" + AnsiString("+record[i].getName() + ")+\"]]></"+record[i].getName()+">\";");
      else
        ret.Insert("    _xml += \"<"+record[i].getName()+">\" + "+record[i].getName()+".toXML() + \"</"+record[i].getName()+">\";");
    ret.Insert("  _xml += \"</"+type+">\";");
    ret.Insert("  return _xml.get();");
    ret.Insert("}");
  }
  if (json) {
    ret.Insert("AnsiString "+type+"::toJSON() const {");
    ret.Insert("  StringBuffer _json;");
    ret.Insert("  _json += \"{\";");
    for (int i=0;i<record.Size();i++) {
      if (i!=0)
        ret.Insert("    _json += \",\";");
      ret.Insert("    _json += \"\\\""+record[i].getName()+"\\\":\";");
      if (getTypeByName(data, record[i].getType()).getKind().isBasic())
        ret.Insert("    _json += "+mkToJSONBasic(record[i].getName(), record[i].getType())+";");
      else
        ret.Insert("    _json += "+record[i].getName()+".toJSON();");
    }
    ret.Insert("  _json += \"}\";");
    ret.Insert("  return _json.get();");
    ret.Insert("}");
    ret.Insert(type+" "+type+"::fromJSON(AnsiString s) {");
    ret.Insert("  AnsiString arr["+AnsiString(record.Size())+"];");
    ret.Insert("  int ix=1;");
    ret.Insert("  for (int i=0;i<"+AnsiString(record.Size())+";i++) {");
    ret.Insert("    while (ix<=s.Length() && s[ix]!=':')");
    ret.Insert("      ix++;");
    ret.Insert("    if (ix>s.Length()) ");
    ret.Insert("      throw Exception(\""+type+"::fromJSON\");");
    ret.Insert("    int start = ix;");
    ret.Insert("    bool inString = false;");
    ret.Insert("    int bracketLevel = 0;");
    ret.Insert("    while (ix<=s.Length()) {");
    ret.Insert("      if (s[ix]=='\\\\')");
    ret.Insert("        ix+=2;");
    ret.Insert("      else if (s[ix]=='\"')");
    ret.Insert("        inString = !inString;");
    ret.Insert("      else if (!inString && s[ix]=='[')");
    ret.Insert("        bracketLevel++;");
    ret.Insert("      else if (!inString && s[ix]=='{')");
    ret.Insert("        bracketLevel++;");
    ret.Insert("      else if (!inString && s[ix]==']')");
    ret.Insert("        bracketLevel--;");
    ret.Insert("      else if (!inString && s[ix]=='}')");
    ret.Insert("        bracketLevel--;");
    ret.Insert("      if (bracketLevel<=0 && !inString && ((ix<=s.Length() && s[ix]==',') || ix==s.Length())) {");
    ret.Insert("        if (i<"+AnsiString(record.Size())+") {");
    ret.Insert("          if (ix-start-1<=0)");
    ret.Insert("            throw Exception(\""+type+"::fromJSON\");");
    ret.Insert("          arr[i] = s.SubString(start+1, ix-start-1);");
    ret.Insert("        }");
    ret.Insert("        ix++;");
    ret.Insert("        break;");
    ret.Insert("      }");
    ret.Insert("      ix++;");
    ret.Insert("    }");
    ret.Insert("  }");
    AnsiString str;
    for (int i=0;i<record.Size();i++)
      str+=AnsiString(i > 0 ? ", " : "")+mkFromJSON(data, record[i].getType(), "arr["+AnsiString(i)+"]");
    ret.Insert("  return "+type+"("+str+");");
    ret.Insert("}");
  }
  ret.Insert(type+"::~"+type+"() {");
  ret.Insert("}");
  
  if (bin) {
    ret.Insert(type+" "+type+"::fromBinary(BinaryReader& reader) {");
    for (int i=0;i<record.Size();i++) {
      DataType type = getTypeByName(data, record[i].getType());
      DataTypeKind kind = type.getKind();
      if (kind.isBasic()) {
        AnsiString name = type.getName();
        if (name=="int") {
          ret.Insert("  int _"+record[i].getName()+";");
          ret.Insert("  reader >> _"+record[i].getName()+";");
        } else if (name=="bool") {
          ret.Insert("  int _" + record[i].getName() + ";");
          ret.Insert("  reader >> _" + record[i].getName() + ";");
        } else if (name=="string") {
          ret.Insert("  AnsiString _"+record[i].getName()+";");
          ret.Insert("  reader >> _"+record[i].getName()+";");
        } else
          throw Exception("");
      } else
        ret.Insert("  "+type.getName()+" _"+record[i].getName()+" = "+type.getName()+"::fromBinary(reader);");
    }
    AnsiString txt = "  return "+type+"(";
    for (int i=0;i<record.Size();i++) {
      if (i!=0)
        txt += ", ";
      txt += "_" + record[i].getName();
    }
    ret.Insert(txt+");");
    ret.Insert("}");
  }
  if (simple) {
    ret.Insert(type+" "+type+"::fromSimpleData(const SimpleData& _data) {");
    ret.Insert("  const SimpleRecord& _record = _data.asRecord();");
    AnsiString txt = "  return "+type+"(";
    for (int i=0;i<record.Size();i++) {
      if (i!=0)
        txt += ", ";
      DataType type = getTypeByName(data, record[i].getType());
      DataTypeKind kind = type.getKind();
      if (kind.isBasic()) {
        AnsiString name = type.getName();
        if (name=="int")
          txt += "_record[\""+record[i].getName()+"\"].asInt()";
        else if (name=="bool")
          txt += "_record[\"" + record[i].getName() + "\"].asInt()";
        else if (name=="string")
          txt += "_record[\""+record[i].getName()+"\"].asString()";
        else
          throw Exception("");
      } else
        txt += type.getName()+"::fromSimpleData(_record[\""+record[i].getName()+"\"])";
    }
    ret.Insert(txt+");");
    ret.Insert("}");
  }
  return ret;
}
DynSet<AnsiString> generateCppArrayCode(const DataTypeArray& data, bool xml, bool simple, bool bin, bool json, const AnsiString& type, const ArrayType& array) {
  DynSet<AnsiString> ret;
  ret.Insert(type+"::"+type+"() {");
  ret.Insert("}");
  DataType aType = getTypeByName(data, array.getType());
  DataTypeKind kind = aType.getKind();
  if (bin) {
    ret.Insert("void "+type+"::toBinary(BinaryWriter& writer) const {");
    ret.Insert("  writer << Size();");
    ret.Insert("  for (int _i=0;_i<Size();_i++)");
    if (kind.isBasic())
      ret.Insert("    writer << (*this)[_i];");
    else
      ret.Insert("    (*this)[_i].toBinary(writer);");  
    ret.Insert("}");
  }
  if (simple) {
    ret.Insert("SimpleData "+type+"::toSimpleData() const {");
    ret.Insert("  SimpleArray _array;");
    ret.Insert("  for (int _i=0;_i<Size();_i++)");
    if (kind.isBasic()) {
      AnsiString name = aType.getName();
      if (name=="int")
        ret.Insert("    _array.Insert(SimpleData::createInt((*this)[_i]));");
      else if (name=="bool")
        ret.Insert("    _array.Insert(SimpleData::createInt((*this)[_i]));");
      else if (name=="string")
        ret.Insert("    _array.Insert(SimpleData::createString((*this)[_i]));");
      else
        throw Exception("");
    } else
      ret.Insert("    _array.Insert((*this)[_i].toSimpleData());");
    ret.Insert("  return SimpleData::createArray(_array);");
    ret.Insert("}");
  }
  if (xml) {
    ret.Insert("AnsiString "+type+"::toXML() const {");
    ret.Insert("  StringBuffer _xml;");
    ret.Insert("  _xml += \"<"+type+">\";");
    ret.Insert("  for (int _i=0;_i<Size();_i++)");
    if (kind.isBasic())
      ret.Insert("    _xml += \"<"+array.getType()+"><![CDATA[\" + AnsiString((*this)[_i]) + \"]]></"+array.getType()+">\";");
    else
      ret.Insert("    _xml += (*this)[_i].toXML();");
    ret.Insert("    _xml += \"</"+type+">\";");
    ret.Insert("    return _xml.get();");
    ret.Insert("}");
  }
  if (json) {
    ret.Insert("AnsiString "+type+"::toJSON() const {");
    ret.Insert("  StringBuffer _json;");
    ret.Insert("  _json += \"[\";");
    ret.Insert("  for (int _i=0;_i<Size();_i++) {");
    ret.Insert("    if (_i!=0) _json += \",\";");
    if (kind.isBasic())
      ret.Insert("    _json += "+mkToJSONBasic("(*this)[_i]", array.getType())+";");
    else
      ret.Insert("    _json += (*this)[_i].toJSON();");
    ret.Insert("  }");
    ret.Insert("    _json += \"]\";");
    ret.Insert("    return _json.get();");
    ret.Insert("}");
    ret.Insert(type+" "+type+"::fromJSON(AnsiString s) {");
    ret.Insert("  "+type+" arr = "+type+"();");
    ret.Insert("  int ix=1;");
    ret.Insert("  while(ix <= s.Length() && s[ix]!='[')");
    ret.Insert("    ix++;");
    ret.Insert("  ix++;");
    ret.Insert("  if (ix>s.Length()) ");
    ret.Insert("    throw Exception(\""+type+"::fromJSON\");");
    ret.Insert("  while (ix<=s.Length()) {");
    ret.Insert("    int start = ix;");
    ret.Insert("    bool inString = false;");
    ret.Insert("    int bracketLevel = 0;");
    ret.Insert("    while (ix<=s.Length()) {");
    ret.Insert("      if (s[ix]=='\\\\')");
    ret.Insert("        ix+=2;");
    ret.Insert("      else if (s[ix]=='\"')");
    ret.Insert("        inString = !inString;");
    ret.Insert("      else if (!inString && s[ix]=='[')");
    ret.Insert("        bracketLevel++;");
    ret.Insert("      else if (!inString && s[ix]=='{')");
    ret.Insert("        bracketLevel++;");
    ret.Insert("      else if (!inString && s[ix]==']')");
    ret.Insert("        bracketLevel--;");
    ret.Insert("      else if (!inString && s[ix]=='}')");
    ret.Insert("        bracketLevel--;");
    ret.Insert("      if (bracketLevel<=0 && !inString && (s[ix]==',' || ix==s.Length())) {");
    ret.Insert("        if (start==ix)");
    ret.Insert("          return arr;");
    ret.Insert("        if (ix-start<=0)");
    ret.Insert("          throw Exception(\""+type+"::fromJSON\");");
    ret.Insert("        AnsiString tmp = s.SubString(start, ix-start);");
    ret.Insert("        arr.Insert("+mkFromJSON(data, array.getType(), "tmp")+");");
    ret.Insert("        ix++;");
    ret.Insert("        break;");
    ret.Insert("      }");
    ret.Insert("      ix++;");
    ret.Insert("    }");
    ret.Insert("  }");
    ret.Insert("  return arr;");
    ret.Insert("}");
  }
  ret.Insert(type+"::~"+type+"() {");
  ret.Insert("}");
  if (bin) {
    ret.Insert(type+" "+type+"::fromBinary(BinaryReader& reader) {");
    ret.Insert("  "+type+" _value;");
    ret.Insert("  int _no;");
    ret.Insert("  reader >> _no;");
    ret.Insert("  for (int _i=0;_i<_no;_i++) {");
    if (kind.isBasic()) {
      AnsiString name = aType.getName();
      if (name=="int") {
        ret.Insert("    int _v;");
        ret.Insert("    reader >> _v;");
        ret.Insert("    _value.Insert(_v);");
      } else if (name=="bool") {
        ret.Insert("    int _v;");
        ret.Insert("    reader >> _v;");
        ret.Insert("    _value.Insert(_v);");
      } else if (name=="string") {
        ret.Insert("    AnsiString _v;");
        ret.Insert("    reader >> _v;");
        ret.Insert("    _value.Insert(_v);");
      } else
        throw Exception("");
    } else
      ret.Insert("    _value.Insert("+aType.getName()+"::fromBinary(reader));");  
    ret.Insert("  }");
    ret.Insert("  return _value;");
    ret.Insert("}");
  }
  if (simple) {
    ret.Insert(type+" "+type+"::fromSimpleData(const SimpleData& _data) {");
    ret.Insert("  const SimpleArray& _array = _data.asArray();");
    ret.Insert("  "+type+" _value;");
    ret.Insert("  for (int _i=0;_i<_array.Size();_i++)");
    if (kind.isBasic()) {
      AnsiString name = aType.getName();
      if (name=="int")
        ret.Insert("    _value.Insert(_array[_i].asInt());");
      else if (name=="bool")
        ret.Insert("    _value.Insert(_array[_i].asInt());");
      else if (name=="string")
        ret.Insert("    _value.Insert(_array[_i].asString());");
      else
        throw Exception("");
    } else
      ret.Insert("    _value.Insert("+aType.getName()+"::fromSimpleData(_array[_i]));");
    ret.Insert("  return _value;");
    ret.Insert("}");
  }
  return ret;
}
DynSet<AnsiString> generateCppVariantCode(const DataTypeArray& data, bool xml, bool simple, bool bin, bool json, const AnsiString& type, const VariantType& variant) {
  DynSet<AnsiString> ret;
  
  for (int i=0;i<variant.Size();i++)
    ret.Insert("const int "+type+"::_Type"+cap1st(variant[i].getName())+" = " + i + ";");
  
  ret.Insert("void "+type+"::init(int type, void* ptr) {");
  for (int i=0;i<variant.Size();i++) {
    VariantField field = variant[i];
    VariantFieldKind kind = field.getKind();
    ret.Insert(AnsiString((i>0) ? "  } else " : "  ") + "if (type==_Type"+cap1st(field.getName())+") {");
    if (kind.isEmpty()) {
      ret.Insert("    _type = type;");
      ret.Insert("    _ptr = 0;");
    } else if (kind.isType()) {
      ret.Insert("    _type = type;");
      ret.Insert("    _ptr = new "+getRealTypeName(data, kind.asType())+"(*("+getRealTypeName(data, kind.asType())+"*) ptr);");
    } else
      throw Exception("");
    if (i==variant.Size()-1)
      ret.Insert("  }");
  }
  ret.Insert("}");
  ret.Insert("void "+type+"::clean() {");
  for (int i=0;i<variant.Size();i++) {
    VariantField field = variant[i];
    VariantFieldKind kind = field.getKind();
    ret.Insert(AnsiString((i>0) ? "  } else " : "  ") + "if (_type==_Type"+cap1st(field.getName())+") {");
    if (kind.isEmpty()) {
      ret.Insert("    _type = -1;");
      ret.Insert("    if (_ptr!=0)");
      ret.Insert("      throw Exception(\""+type+"::clean()\");");
    } else if (kind.isType()) {
      ret.Insert("    _type = -1;");
      ret.Insert("    delete ("+getRealTypeName(data, kind.asType())+"*) _ptr;");
      ret.Insert("    _ptr = 0;");
    } else
      throw Exception("");
    if (i==variant.Size()-1)
      ret.Insert("  }");
  }
  ret.Insert("}");
  ret.Insert(type+"::"+type+"() : _type(-1), _ptr(0) {");
  ret.Insert("}");
  
  ret.Insert(type+"::"+type+"(const "+type+"& _value) {");
  ret.Insert("  init(_value._type, _value._ptr);");
  ret.Insert("}");
  ret.Insert(type+"& "+type+"::operator=(const "+type+"& _value) {");
  ret.Insert("  clean();");
  ret.Insert("  init(_value._type, _value._ptr);");
  ret.Insert("  return *this;");
  ret.Insert("}");
  
  for (int i=0;i<variant.Size();i++) {
    ret.Insert("bool "+type+"::is"+cap1st(variant[i].getName())+"() const {");
    ret.Insert("  return _type==_Type"+cap1st(variant[i].getName())+";");
    ret.Insert("}");
  }
  
  for (int i=0;i<variant.Size();i++) {
    VariantField field = variant[i];
    VariantFieldKind kind = field.getKind();
    if (kind.isEmpty())
      ;
    else if (kind.isType()) {
      ret.Insert("const " + getRealTypeName(data, kind.asType())+"& "+type+"::as"+cap1st(field.getName())+"() const {");
      ret.Insert("  if (_type!=_Type"+cap1st(field.getName())+")");
      ret.Insert("    throw Exception(\""+type+"::as"+cap1st(field.getName())+"\");");
      ret.Insert("  return *("+getRealTypeName(data, kind.asType())+"*) _ptr;");
      ret.Insert("}");
      ret.Insert("" + getRealTypeName(data, kind.asType())+"& "+type+"::as"+cap1st(field.getName())+"() {");
      ret.Insert("  if (_type!=_Type"+cap1st(field.getName())+")");
      ret.Insert("    throw Exception(\""+type+"::as"+cap1st(field.getName())+"\");");
      ret.Insert("  return *("+getRealTypeName(data, kind.asType())+"*) _ptr;");
      ret.Insert("}");
    } else
      throw Exception("");
  }
  
  ret.Insert("");
  if (bin) {
    ret.Insert("void "+type+"::toBinary(BinaryWriter& writer) const {");
    ret.Insert("  writer << _type;");
    for (int i=0;i<variant.Size();i++) {
      VariantField field = variant[i];
      VariantFieldKind kind = field.getKind();
      ret.Insert(AnsiString((i>0) ? "  else " : "  ") + "if (_type==_Type"+cap1st(field.getName())+")");
      if (kind.isEmpty())
        ret.Insert("    ;");
      else if (kind.isType()) {
        DataType aType = getTypeByName(data, kind.asType());
        DataTypeKind kind = aType.getKind();
        if (kind.isBasic()) {
          AnsiString name = aType.getName();
          if (name=="int")
            ret.Insert("    writer << (*(int*) _ptr);");
          else if (name=="bool")
            ret.Insert("    writer << (*(bool*) _ptr);");
          else if (name=="string")
            ret.Insert("    writer << (*(AnsiString*) _ptr);");
          else
            throw Exception("");
        } else
          ret.Insert("    (("+aType.getName()+"*) _ptr)->toBinary(writer);");
      } else
        throw Exception("");
    }
    ret.Insert("  else");
    ret.Insert("    throw Exception(\""+type+"::toBinary\");");
    ret.Insert("}");
  }
  if (simple) {
    ret.Insert("SimpleData "+type+"::toSimpleData() const {");
    for (int i=0;i<variant.Size();i++) {
      VariantField field = variant[i];
      VariantFieldKind kind = field.getKind();
      ret.Insert(AnsiString((i>0) ? "  else " : "") + "if (_type==_Type"+cap1st(field.getName())+")");
      if (kind.isEmpty())
        ret.Insert("    return SimpleData::createVariant(SimpleVariant(\""+variant[i].getName()+"\", SimpleData::createInt(-1)));");
      else if (kind.isType()) {
        DataType aType = getTypeByName(data, kind.asType());
        DataTypeKind kind = aType.getKind();
        if (kind.isBasic()) {
          AnsiString name = aType.getName();
          if (name=="int")
            ret.Insert("    return SimpleData::createVariant(SimpleVariant(\""+variant[i].getName()+"\", SimpleData::createInt(*(int*) _ptr)));");
          else if (name=="bool")
            ret.Insert("    return SimpleData::createVariant(SimpleVariant(\"" + variant[i].getName() + "\", SimpleData::createInt(*(bool*) _ptr)));");
          else if (name=="string")
            ret.Insert("    return SimpleData::createVariant(SimpleVariant(\""+variant[i].getName()+"\", SimpleData::createString(*(AnsiString*) _ptr)));");
          else
            throw Exception("");
        } else
          ret.Insert("    return SimpleData::createVariant(SimpleVariant(\""+variant[i].getName()+"\", (("+aType.getName()+"*) _ptr)->toSimpleData()));");
      } else
        throw Exception("");
    }
    ret.Insert("  else");
    ret.Insert("    throw Exception(\""+type+"::toSimpleData\");");
    ret.Insert("}");
  }
  if (xml) {
    ret.Insert("AnsiString "+type+"::toXML() const {");
    ret.Insert("  StringBuffer _xml;");
    ret.Insert("   _xml += \"<"+type+">\";");
    for (int i=0;i<variant.Size();i++) {
      ret.Insert("    "+((i>0) ? AnsiString("else ") : AnsiString(""))+"if (_type=="+AnsiString(i)+")");
      if (variant[i].getKind().isEmpty()) {
        ret.Insert("      _xml += \"<"+variant[i].getName()+"/>\";");
      } else if (variant[i].getKind().isType()) {
        DataType aType = getTypeByName(data, variant[i].getKind().asType());
        if (aType.getKind().isBasic())
          ret.Insert("    _xml += \"<"+variant[i].getName()+"><![CDATA[\" + AnsiString(*(("+getBasicTypeName(aType.getName())+"*) _ptr)) + \"]]></"+variant[i].getName()+">\";");
        else
          ret.Insert("    _xml += \"<"+variant[i].getName()+">\" + (("+aType.getName()+"*) _ptr)->toXML() + \"</"+variant[i].getName()+">\";");
      } else
        throw Exception("toXML");
    }
    ret.Insert("    else");
    ret.Insert("      throw Exception(\""+type+"::toXML(\" + AnsiString(_type) + \")\");");
    ret.Insert("    _xml += \"</"+type+">\";");
    ret.Insert("    return _xml.get();");
    ret.Insert("}");
  }
  if (json) {
    ret.Insert("AnsiString "+type+"::toJSON() const {");
    ret.Insert("  StringBuffer _json;");
    ret.Insert("   _json += \"{\\\"type\\\":\" + AnsiString(_type) + \",\\\"value\\\":\";");
    for (int i=0;i<variant.Size();i++) {
      ret.Insert("    "+((i>0) ? AnsiString("else ") : AnsiString(""))+"if (_type=="+AnsiString(i)+")");
      if (variant[i].getKind().isEmpty()) {
        ret.Insert("      _json += \"0\";");
      } else if (variant[i].getKind().isType()) {
        DataType aType = getTypeByName(data, variant[i].getKind().asType());
        if (aType.getKind().isBasic())
          ret.Insert("    _json += "+mkToJSONBasic("*(("+getBasicTypeName(aType.getName())+"*) _ptr)", variant[i].getKind().asType())+";"); //\"<"+variant[i].getName()+"><![CDATA[\" + AnsiString(*(("+getBasicTypeName(aType.getName())+"*) _ptr)) + \"]]></"+variant[i].getName()+">\";");
        else
          ret.Insert("    _json += (("+aType.getName()+"*) _ptr)->toJSON();");
      } else
        throw Exception("toJSON");
    }
    ret.Insert("    else");
    ret.Insert("      throw Exception(\""+type+"::toJSON(\" + AnsiString(_type) + \")\");");
    ret.Insert("    _json += \"}\";");
    ret.Insert("    return _json.get();");
    ret.Insert("}");
    ret.Insert(type+" "+type+"::fromJSON(AnsiString s) {");
    ret.Insert("  int ix = 1;");
    ret.Insert("  while (ix<=s.Length() && s[ix]!=':')");
    ret.Insert("    ix++;");
    ret.Insert("  if (ix>s.Length()) ");
    ret.Insert("    throw Exception(\""+type+"::fromJSON\");");
    for (int i=0;i<variant.Size();i++) {
      VariantField field = variant[i];
      VariantFieldKind kind = field.getKind();
      AnsiString length = AnsiString(AnsiString(i).Length());
      ret.Insert("  "+AnsiString(i > 0 ? "} else " : "")+"if (s.Length()>ix+1+"+length+" && s.SubString(ix+1, "+length+")==(\""+AnsiString(i)+"\")) {");
      if (kind.isEmpty()) {
        ret.Insert("    return "+type+"::create"+toUpper(variant[i].getName())+"();");
      } else {
        ret.Insert("    if (s.Length()-ix-10-"+length+"<=0)");
        ret.Insert("      throw Exception(\""+type+"::fromJSON\");");
        ret.Insert("    s = s.SubString(ix+10+"+length+", s.Length()-ix-10-"+length+");");
        ret.Insert("    return "+type+"::create"+toUpper(variant[i].getName())+"("+mkFromJSON(data, kind.asType(), "s")+");");
      }
    }
    ret.Insert("  }");
    ret.Insert("  AnsiString variantName = \"\";");
    ret.Insert("  ix = 1;");
    ret.Insert("  while (ix<=s.Length() && s[ix]!=':')");
    ret.Insert("    ix++;");
    ret.Insert("  if (ix>s.Length() || ix<=4) ");
    ret.Insert("    throw Exception(\""+type+"::fromJSON\");");;
    ret.Insert("  variantName = s.SubString(3, ix-4);");
    for (int i=0;i<variant.Size();i++) {
      VariantField field = variant[i];
      VariantFieldKind kind = field.getKind();
      ret.Insert("  "+AnsiString(i > 0 ? "} else " : "")+"if (variantName==(\""+variant[i].getName()+"\")) {");
      if (kind.isEmpty()) {
        ret.Insert("    return "+type+"::create"+toUpper(variant[i].getName())+"();");
      } else {
        ret.Insert("    if (s.Length()-ix-1<=0)");
        ret.Insert("      throw Exception(\""+type+"::fromJSON\");");
        ret.Insert("    s = s.SubString(ix+1, s.Length()-ix-1);");
        ret.Insert("    return "+type+"::create"+toUpper(variant[i].getName())+"("+mkFromJSON(data, kind.asType(), "s")+");");
      }
    }
    ret.Insert("  } else ");
    ret.Insert("    throw Exception(\""+type+"::fromJSON\");");
    ret.Insert("}");
  }
  ret.Insert("");
  ret.Insert(type+"::~"+type+"() {");
  ret.Insert("  clean();");
  ret.Insert("}");
  
  for (int i=0;i<variant.Size();i++) {
    VariantField field = variant[i];
    VariantFieldKind kind = field.getKind();
    if (kind.isEmpty()) {
      ret.Insert(type+" "+type+"::create"+cap1st(variant[i].getName())+"() {");
      ret.Insert("  "+type+" _value;");
      ret.Insert("  _value._type = _Type"+cap1st(variant[i].getName())+";");
      ret.Insert("  _value._ptr = 0;");
      ret.Insert("  return _value;");
      ret.Insert("}");
    } else if (kind.isType()) {
      ret.Insert(type+" "+type+"::create"+cap1st(variant[i].getName())+"(const "+getRealTypeName(data, kind.asType())+"& _param) {");
      ret.Insert("  "+type+" _value;");
      ret.Insert("  _value._type = _Type"+cap1st(variant[i].getName())+";");
      ret.Insert("  _value._ptr = new "+getRealTypeName(data, kind.asType())+"(_param);");
      ret.Insert("  return _value;");
      ret.Insert("}");
    } else
      throw Exception("");
  }
  
  ret.Insert("");
  if (bin) {
    ret.Insert(type+" "+type+"::fromBinary(BinaryReader& reader) {");
    ret.Insert("  int _type;");
    ret.Insert("  reader >> _type;");
    for (int i=0;i<variant.Size();i++) {
      VariantField field = variant[i];
      VariantFieldKind kind = field.getKind();
      ret.Insert(AnsiString((i>0) ? "  } else " : "  ") + "if (_type==_Type"+cap1st(field.getName())+") {");
      if (kind.isEmpty())
        ret.Insert("    return "+type+"::create"+cap1st(variant[i].getName())+"();");
      else if (kind.isType()) {
        DataType aType = getTypeByName(data, kind.asType());
        DataTypeKind kind = aType.getKind();
        if (kind.isBasic()) {
          AnsiString name = aType.getName();
          if (name=="int") {
            ret.Insert("    int v;");
            ret.Insert("    reader >> v;");
            ret.Insert("    return "+type+"::create"+cap1st(variant[i].getName())+"(v);");
          } else if (name=="bool") {
            ret.Insert("    int v;");
            ret.Insert("    reader >> v;");
            ret.Insert("    return " + type + "::create" + cap1st(variant[i].getName()) + "(v);");
          } else if (name=="string") {
            ret.Insert("    AnsiString v;");
            ret.Insert("    reader >> v;");
            ret.Insert("    return "+type+"::create"+cap1st(variant[i].getName())+"(v);");
          } else
            throw Exception("");
        } else
          ret.Insert("    return "+type+"::create"+cap1st(variant[i].getName())+"("+aType.getName()+"::fromBinary(reader));");
      } else
        throw Exception("");
    }
    ret.Insert("  } else");
    ret.Insert("    throw Exception(\""+type+"::fromBinary\");");
    ret.Insert("}");
  }
  if (simple) {
    ret.Insert(type+" "+type+"::fromSimpleData(const SimpleData& _data) {");
    ret.Insert("  const SimpleVariant& _variant = _data.asVariant();");
    for (int i=0;i<variant.Size();i++) {
      VariantField field = variant[i];
      VariantFieldKind kind = field.getKind();
      ret.Insert(AnsiString((i>0) ? "  else " : "") + "if (_variant.is(\""+variant[i].getName()+"\"))");
      if (kind.isEmpty())
        ret.Insert("    return "+type+"::create"+cap1st(variant[i].getName())+"();");
      else if (kind.isType()) {
        DataType aType = getTypeByName(data, kind.asType());
        DataTypeKind kind = aType.getKind();
        if (kind.isBasic()) {
          AnsiString name = aType.getName();
          if (name=="int")
            ret.Insert("    return "+type+"::create"+cap1st(variant[i].getName())+"(_variant.as(\""+variant[i].getName()+"\").asInt());");
          else if (name=="bool")
            ret.Insert("    return " + type + "::create" + cap1st(variant[i].getName()) + "(_variant.as(\"" + variant[i].getName() + "\").asInt());");
          else if (name=="string")
            ret.Insert("    return "+type+"::create"+cap1st(variant[i].getName())+"(_variant.as(\""+variant[i].getName()+"\").asString());");
          else
            throw Exception("");
        } else
          ret.Insert("    return "+type+"::create"+cap1st(variant[i].getName())+"("+aType.getName()+"::fromSimpleData(_variant.as(\""+variant[i].getName()+"\")));");
      } else
        throw Exception("");
    }
    ret.Insert("  else");
    ret.Insert("    throw Exception(\""+type+"::fromSimpleData\");");
    ret.Insert("}");
  }
  ret.Insert("");
  
  return ret;
}
DynSet<AnsiString> generateCppFile(const AnsiString& file, bool xml, bool simple, bool bin, bool json, const DataTypeArray& data) {
  DynSet<AnsiString> ret;
  ret.Insert("");
  ret.Insert("#include \""+file+".h\"");
  ret.Insert("#include \"Exception.h\"");
  if (json || xml)
    ret.Insert("#include \"StringBuffer.h\"");
  if (json)
    ret.Insert("#include \"JSONUtil.h\"");
  for (int i=0;i<data.Size();i++) {
    DataType type = data[i];
    DataTypeKind kind = type.getKind();
    ret.Insert("//------------- "+type.getName()+" ---------------");
    if (kind.isBasic())
      ;
    else if (kind.isExternal())
      ;
    else if (kind.isRecord())
      ret += generateCppRecordCode(data, xml, simple, bin, json, data[i].getName(), data[i].getKind().asRecord());
    else if (kind.isArray())
      ret += generateCppArrayCode(data, xml, simple, bin, json, data[i].getName(), data[i].getKind().asArray());
    else if (kind.isVariant())
      ret += generateCppVariantCode(data, xml, simple, bin, json, data[i].getName(), data[i].getKind().asVariant());
    else
      throw Exception("");
    ret.Insert("//----------------------------------");
    ret.Insert("");
  }
  return ret;
}

#pragma package(smart_init)
