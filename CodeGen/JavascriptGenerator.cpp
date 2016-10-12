//---------------------------------------------------------------------------

#include "JavascriptGenerator.h"
#include "Util.h"

//---------------------------------------------------------------------------

static AnsiString getParams(const RecordType& record) {
  AnsiString txt;
  for (int i=0;i<record.Size();i++)
    txt += AnsiString((i>0) ? ", " : "") + "p_" + record[i].getName();
   return txt; 
} 

static DynSet<AnsiString> generateJavascriptRecordCode(const AnsiString& type, const RecordType& record) {
  DynSet<AnsiString> ret;
  ret.Insert("function "+type+"("+getParams(record)+") {");
  for (int i=0;i<record.Size();i++)
    ret.Insert("  this._"+record[i].getName()+" = p_"+record[i].getName()+";");
  for (int i=0;i<record.Size();i++) {
    ret.Insert("  this.get"+cap1st(record[i].getName())+" = function() {");
    ret.Insert("    return this._"+record[i].getName()+";");
    ret.Insert("  };");
    ret.Insert("  this.set"+cap1st(record[i].getName())+" = function(v) {");
    ret.Insert("    this._"+record[i].getName()+" = v;");
    ret.Insert("  };");
  }
  ret.Insert("};");
  return ret;  
}

static DynSet<AnsiString> generateJavascriptVariantCode(const AnsiString& type, const VariantType& variant) {
  DynSet<AnsiString> ret;
  
  ret.Insert("function "+type+"(_internal_type, _internal_obj) {");
  ret.Insert("  this._type = _internal_type;");
  ret.Insert("  this._obj = _internal_obj;");
  for (int i=0;i<variant.Size();i++) {
    ret.Insert("  this.is"+cap1st(variant[i].getName())+" = function() {");
    ret.Insert("    return this._type=="+AnsiString(i+1)+";");
    ret.Insert("  };");
  }
  ret.Insert("");
  for (int i=0;i<variant.Size();i++) {
    VariantField field = variant[i];
    VariantFieldKind kind = field.getKind();
    if (kind.isEmpty())
      ;
    else if (kind.isType()) {
      ret.Insert("  this.as"+cap1st(variant[i].getName())+" = function() {");
      ret.Insert("    if (this._type!="+AnsiString(i+1)+")");
      ret.Insert("      throw \""+type+"::as"+cap1st(field.getName())+"\";");
      ret.Insert("    return this._obj;");
      ret.Insert("  };");
    } else
      throw Exception("");
  }
  ret.Insert("};");
  ret.Insert("");
  for (int i=0;i<variant.Size();i++) {
    VariantField field = variant[i];
    VariantFieldKind kind = field.getKind();
    if (kind.isEmpty()) {
      ret.Insert("  "+type+".create"+cap1st(variant[i].getName())+" = function() {");
      ret.Insert("    return new "+type+"("+AnsiString(i+1)+", null);");
      ret.Insert("  };");
    } else if (kind.isType()) {
      ret.Insert("  "+type+".create"+cap1st(variant[i].getName())+" = function(_v) {");
      ret.Insert("    return new "+type+"("+AnsiString(i+1)+", _v);");
      ret.Insert("  };");
    } else
      throw Exception("");
  }
  return ret;
}

static DynSet<AnsiString> generateJavascriptArrayCode(const AnsiString& type, const ArrayType& array) {
  DynSet<AnsiString> ret;
  
  ret.Insert("function " + type + "() {");
  ret.Insert("  this._arr = new Array();");
  ret.Insert("  this.size = function() {");
  ret.Insert("    return this._arr.length;");
  ret.Insert("  };");
  ret.Insert("  this.insert = function(_v) {");
  ret.Insert("    this._arr.push(_v);");
  ret.Insert("  };");
  ret.Insert("  this.get = function(_ix) {");
  ret.Insert("    return this._arr[_ix];");
  ret.Insert("  };");
  ret.Insert("  this.delete = function(_ix) {");
  ret.Insert("    this._arr[_ix] = this._arr[this._arr.length-1];");
  ret.Insert("    this._arr.pop();");
  ret.Insert("  };");
  ret.Insert("};");
  
  return ret;
}
DynSet<AnsiString> generateJavascriptFile(const AnsiString& file, const DataTypeArray& data) {
  DynSet<AnsiString> lines;
  for (int i=0;i<data.Size();i++) {
    DataType type = data[i];
    DataTypeKind kind = type.getKind();
    if (kind.isBasic())
      ;
    else if (kind.isExternal())
      ;
    else if (kind.isRecord())
      lines += generateJavascriptRecordCode(data[i].getName(), data[i].getKind().asRecord());
    else if (kind.isArray())
      lines += generateJavascriptArrayCode(data[i].getName(), data[i].getKind().asArray());
    else if (kind.isVariant())
      lines += generateJavascriptVariantCode(data[i].getName(), data[i].getKind().asVariant());
    else
      throw Exception("");
  }
  return lines;
}

#pragma package(smart_init)
