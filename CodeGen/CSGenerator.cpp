//---------------------------------------------------------------------------

#include "CSGenerator.h"
#include "Util.h"

//---------------------------------------------------------------------------

static AnsiString conv(const DynSet<AnsiString>& lines) {
  AnsiString ret;
  for (int i=0;i<lines.Size();i++)
    ret += lines[i] + "\n";
  return ret;
}

static AnsiString getBasicTypeName(const AnsiString& type) {
  if (type=="string")
    return "String";
  else if (type=="int")
    return "int";
  else if (type=="bool")
    return "bool";
  else
    throw Exception("Nieznany typ prosty " + type);
}
static AnsiString getRealTypeName(const DataTypeArray& data, const AnsiString& type) {
  int ix = findTypeByName(data, type);
  if (ix==-1)
    throw Exception("Nieznany typ " + type);
  if (!data[ix].getKind().isBasic())
    return type;
  else
    return getBasicTypeName(type);
}
static AnsiString mkBasicToStream(const AnsiString& type, const AnsiString& access) {
  if (type=="string")
    return "_s.writeUTF("+access+");";
  else if (type=="int")
    return "_s.writeInt("+access+");";
  else if (type=="bool")
    return "_s.write(" + access + ");";
  else
    throw Exception("Nieznany typ prosty " + type);
}
static AnsiString mkToStream(const DataTypeArray& data, const AnsiString& type, const AnsiString& access) {
  int ix = findTypeByName(data, type);
  if (ix==-1)
    throw Exception("Nieznany typ " + type);
  if (!data[ix].getKind().isBasic())
    return access + ".toStream(_s);";
  else
    return mkBasicToStream(type, access);
}
static AnsiString mkBasicFromBinary(const AnsiString& type) {
  if (type=="string")
    return "_r.ReadString()";
  else if (type=="int")
    return "_r.ReadInt32()";
  else if (type=="bool")
    return "_r.ReadBoolean()";
  else
    throw Exception("Nieznany typ prosty " + type);
}
static AnsiString mkFromBinary(const DataTypeArray& data, const AnsiString& type) {
  int ix = findTypeByName(data, type);
  if (ix==-1)
    throw Exception("Nieznany typ " + type);
  if (!data[ix].getKind().isBasic())
    return type + ".fromBinary(_r)";
  else
    return mkBasicFromBinary(type);
}
static AnsiString mkToBinary(const DataTypeArray& data, const AnsiString& type, const AnsiString& access) {
  int ix = findTypeByName(data, type);
  if (ix==-1)
    throw Exception("Nieznany typ " + type);
  if (!data[ix].getKind().isBasic())
    return access + ".toBinary(_w);";
  else
    return "_w.Write("+access+");";
}
static AnsiString getConstrParam(const DataTypeArray& data, const RecordField& field, bool names) {
  return " " + getRealTypeName(data, field.getType()) + "" + ((names) ? " _" + field.getName() : AnsiString());
}
static AnsiString getConstrParams(const DataTypeArray& data, const RecordType& record, bool names) {
  AnsiString ret;
  if (record.Size()==0)
    return ret;
  ret = getConstrParam(data, record[0], names);
  for (int i=1;i<record.Size();i++)
    ret += ", " + getConstrParam(data, record[i], names);
  return ret;
}
static DynSet<AnsiString> mkImports(const DataTypeArray& data, const DynSet<AnsiString>& types) {
  DynSet<AnsiString> ret;
  for (int i=0;i<types.Size();i++) {
    int ix = findTypeByName(data, types[i]);
    if (ix==-1)
      throw Exception("Nieznany typ " + types[i]);
    if (data[ix].getKind().isExternal())
      ret.Insert("import "+data[ix].getKind().asExternal().getSource()+";");
  }
  return ret;
}
static AnsiString getConstrParamInit(const RecordField& field) {
  return "    this." + field.getName() + " = _"+field.getName()+";";
}
static DynSet<AnsiString> getConstrParamsInit(const RecordType& record) {
  DynSet<AnsiString> ret;
  for (int i=0;i<record.Size();i++)
    ret.Insert(getConstrParamInit(record[i]));
  return ret;
}
DynSet<AnsiString> generateCSRecordCode(const DataTypeArray& data, bool bin, const AnsiString& type, const RecordType& record) {
  DynSet<AnsiString> ret;
  
  ret.Insert("public class "+type+" {");
  for (int i=0;i<record.Size();i++)
    ret.Insert("  private "+getRealTypeName(data, record[i].getType())+" "+record[i].getName()+";");
  ret.Insert("  public "+type+"("+getConstrParams(data, record, true)+") {");
  ret += getConstrParamsInit(record);
  ret.Insert("  }");
  for (int i=0;i<record.Size();i++) {
    ret.Insert("  public "+getRealTypeName(data, record[i].getType())+" get"+cap1st(record[i].getName())+"() {");
    ret.Insert("    return "+record[i].getName()+";");
    ret.Insert("  }");
    ret.Insert("  public void set"+cap1st(record[i].getName())+"("+getRealTypeName(data, record[i].getType())+" _v) {");
    ret.Insert("    "+record[i].getName()+" = _v;");
    ret.Insert("  }");
  }
  if (bin) {
    ret.Insert("  public void toBinary(BinaryWriter _w) {");
    for (int i=0;i<record.Size();i++)
      ret.Insert("    " + mkToBinary(data, record[i].getType(), record[i].getName()));
    ret.Insert("  }");
    ret.Insert("  static public "+type+" fromBinary(BinaryReader _r) {");
    for (int i=0;i<record.Size();i++)
      ret.Insert("      "+getRealTypeName(data, record[i].getType())+" _t_"+record[i].getName()+" = " + mkFromBinary(data, record[i].getType()) + ";");
    ret.Insert("    return new "+type+"(");
    for (int i=0;i<record.Size();i++)
      ret.Insert("        "+AnsiString((i!=0) ? "," : "")+"_t_" + record[i].getName());
    ret.Insert("      );");
    ret.Insert("  }");
  }
  ret.Insert("}");
  return ret;
}
DynSet<AnsiString> generateCSArrayCode(const DataTypeArray& data, bool bin, const AnsiString& type, const ArrayType& array) {
  DynSet<AnsiString> ret;
  
  const DataTypeKind& kind = data[findTypeByName(data, array.getType())].getKind();
  ret.Insert("public class " + type + " {");
  ret.Insert("  private List<"+getRealTypeName(data, array.getType())+"> _table = new List<"+getRealTypeName(data, array.getType())+">();");
  ret.Insert("  public "+type+"() {}");
  ret.Insert("  public int Size() {");
  ret.Insert("    return _table.Count;");
  ret.Insert("  }");
  ret.Insert("  public void Insert("+getRealTypeName(data, array.getType())+" _v) {");
  ret.Insert("    _table.Add(_v);");
  ret.Insert("  }");
  ret.Insert("  public "+getRealTypeName(data, array.getType())+" this[int _ix] {");
  ret.Insert("    get {");
  ret.Insert("      return _table[_ix];");
  ret.Insert("    }");
  ret.Insert("    set {");
  ret.Insert("      _table[_ix] = value;");
  ret.Insert("    }");
  ret.Insert("  }");
  ret.Insert("  public "+getRealTypeName(data, array.getType())+" Get(int _ix) {");
  ret.Insert("    return _table[_ix];");
  ret.Insert("  }");
  ret.Insert("  public void Delete(int _ix) {");
  ret.Insert("    _table.RemoveAt(_ix);");
  ret.Insert("  }");
  if (bin) {
    ret.Insert("  public void toBinary(BinaryWriter _w) {");
    ret.Insert("    _w.Write(_table.Count);");
    ret.Insert("    for (int _ix=0;_ix<_table.Count;_ix++)");
    ret.Insert("      " + mkToBinary(data, array.getType(), "_table[_ix]"));
    ret.Insert("  }");
    ret.Insert("  static public "+type+" fromBinary(BinaryReader _r) {");
    ret.Insert("    "+type+" _tmp = new "+type+"();");
    ret.Insert("    int _count = _r.ReadInt32();");
    ret.Insert("    for (int _ix=0;_ix<_count;_ix++)");
    ret.Insert("      _tmp.Insert("+mkFromBinary(data, array.getType())+");");
    ret.Insert("    return _tmp;");
    ret.Insert("  }");
  }
  ret.Insert("}");
  
  return ret;
}
DynSet<AnsiString> generateCSVariantCode(const DataTypeArray& data, bool bin, const AnsiString& type, const VariantType& variant) {
  DynSet<AnsiString> ret;
  
  ret.Insert("public class "+type+" {");
  ret.Insert("  private int _type;");
  bool needObj = false;
  bool needInt = false;
  for (int i=0;i<variant.Size();i++)
    if (variant[i].getKind().isEmpty())
      ;
    else if (variant[i].getKind().isType()) {
      const DataTypeKind& kind = data[findTypeByName(data, variant[i].getKind().asType())].getKind();
      if (kind.isBasic() && kind.asBasic()=="int")
        needInt = true;
      else
        needObj = true;
    } else
      throw Exception("VariantFieldKind");
  
  if (needInt)
    ret.Insert("  private int _ptrInt;");
  if (needObj)
    ret.Insert("  private Object _ptrObj;");
  ret.Insert("");
  for (int i=0;i<variant.Size();i++)
    ret.Insert("  private const int _Type"+cap1st(variant[i].getName())+" = "+i+";");
  ret.Insert("");
  ret.Insert("  private "+type+"() {}");
  for (int i=0;i<variant.Size();i++) {
    ret.Insert("  public bool is"+cap1st(variant[i].getName())+"() {");
    ret.Insert("    return _type==_Type"+cap1st(variant[i].getName())+";");
    ret.Insert("  }");
  }
  ret.Insert("");
  for (int i=0;i<variant.Size();i++) {
    VariantField field = variant[i];
    VariantFieldKind kind = field.getKind();
    if (kind.isEmpty())
      ;
    else if (kind.isType()) {
      ret.Insert("  public "+getRealTypeName(data, kind.asType())+" as"+cap1st(variant[i].getName())+"() {");
      ret.Insert("    if (_type!=_Type"+cap1st(field.getName())+")");
      ret.Insert("      throw new Exception(\""+type+"::as"+cap1st(field.getName())+"\");");
      const DataTypeKind& typeKind = data[findTypeByName(data, kind.asType())].getKind();
      if (typeKind.isBasic() && typeKind.asBasic()=="int")
        ret.Insert("    return _ptrInt;");
      else
        ret.Insert("    return ("+getRealTypeName(data, kind.asType())+") _ptrObj;");
      ret.Insert("  }");
    } else
      throw Exception("");
  }
  ret.Insert("");
  for (int i=0;i<variant.Size();i++) {
    VariantField field = variant[i];
    VariantFieldKind kind = field.getKind();
    if (kind.isEmpty()) {
      ret.Insert("  static public "+type+" create"+cap1st(variant[i].getName())+"() {");
      ret.Insert("    "+type+" _value = new "+type+"();");
      ret.Insert("    _value._type = _Type"+cap1st(variant[i].getName())+";");
      ret.Insert("    return _value;");
      ret.Insert("  }");
    } else if (kind.isType()) {
      ret.Insert("  static public "+type+" create"+cap1st(variant[i].getName())+"("+getRealTypeName(data, kind.asType())+" _v) {");
      ret.Insert("    "+type+" _value = new "+type+"();");
      ret.Insert("    _value._type = _Type"+cap1st(variant[i].getName())+";");
      const DataTypeKind& typeKind = data[findTypeByName(data, kind.asType())].getKind();
      if (typeKind.isBasic() && typeKind.asBasic()=="int")
        ret.Insert("    _value._ptrInt = _v;");
      else
        ret.Insert("    _value._ptrObj = _v;");
      ret.Insert("    return _value;");
      ret.Insert("  }");
    } else
      throw Exception("");
  }
  if (bin) {
    ret.Insert("  public void toBinary(BinaryWriter _w) {");
    ret.Insert("    _w.Write(_type);");
    ret.Insert("    if (0==1)");
    ret.Insert("      ;");
    for (int i=0;i<variant.Size();i++) {
      VariantField field = variant[i];
      VariantFieldKind kind = field.getKind();
      ret.Insert("    else if (is"+cap1st(field.getName())+"())");
      if (kind.isEmpty())
        ret.Insert("      ;");
      else if (kind.isType())
        ret.Insert("      " + mkToBinary(data, kind.asType(), "as"+cap1st(field.getName())+"()"));
      else
        throw Exception("VariantFieldKind");
    }
    ret.Insert("    else");
    ret.Insert("      throw new Exception(\""+type+".toBinary(\"+_type+\")\");");
    ret.Insert("  }");
    ret.Insert("  static public "+type+" fromBinary(BinaryReader _r) {");
    ret.Insert("    int _type = _r.ReadInt32();");
    ret.Insert("    if (0==1)");
    ret.Insert("      ;");
    for (int i=0;i<variant.Size();i++) {
      VariantField field = variant[i];
      VariantFieldKind kind = field.getKind();
      ret.Insert("    else if (_type==_Type"+cap1st(field.getName())+")");
      if (kind.isEmpty())
        ret.Insert("      return "+type+".create"+cap1st(field.getName())+"();");
      else if (kind.isType())
        ret.Insert("      return "+type+".create"+cap1st(field.getName())+"(" + mkFromBinary(data, kind.asType()) + ");");
      else
        throw Exception("VariantFieldKind");
    }
    ret.Insert("    else");
    ret.Insert("      throw new Exception(\""+type+".fromBinary(\"+_type+\")\");");
    ret.Insert("  }");
  }
  ret.Insert("}");
  return ret;
}
DynSet<AnsiString> generateCSFile(const AnsiString&, bool bin, const DataTypeArray& data) {
  DynSet<AnsiString> lines;
  
  lines.Insert("using System;");
  lines.Insert("using System.Collections.Generic;");
  lines.Insert("using System.Text;");
  if (bin)
    lines.Insert("using System.IO;");
  
  for (int i=0;i<data.Size();i++) {
    DataType type = data[i];
    DataTypeKind kind = type.getKind();
    if (kind.isBasic())
      ;
    else if (kind.isExternal())
      throw Exception("Not implemented");
    else if (kind.isRecord())
      lines += generateCSRecordCode(data, bin, data[i].getName(), data[i].getKind().asRecord());
    else if (kind.isArray())
      lines += generateCSArrayCode(data, bin, data[i].getName(), data[i].getKind().asArray());
    else if (kind.isVariant())
      lines += generateCSVariantCode(data, bin, data[i].getName(), data[i].getKind().asVariant());
    else
      throw Exception("DataTypeKind");
  }
  return lines;
}

