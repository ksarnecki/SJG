//---------------------------------------------------------------------------

#include "JavaGenerator.h"
#include "Util.h"
#include <cstdio>

//---------------------------------------------------------------------------

static AnsiString conv(const DynSet<AnsiString>& lines) {
  AnsiString ret;
  for (int i=0;i<lines.Size();i++)
    ret+=lines[i]+"\n";
  return ret;
}
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
static AnsiString getBasicTypeName(const AnsiString& type) {
  if (type=="string")
    return "String";
  else if (type=="int")
    return "int";
  else if (type=="bool")
    return "boolean";
  else
    throw Exception("Nieznany typ prosty "+type);
}
static inline bool isBasic(const AnsiString& type) {
  return (type == "string") || (type == "int") || (type == "bool");
}
static AnsiString getRealTypeName(const DataTypeArray& data, const AnsiString& type) {
  int ix = findTypeByName(data, type);
  if (ix==-1)
    throw Exception("Nieznany typ "+type);
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
    return "_s.writeBoolean("+access+");";
  else
    throw Exception("Nieznany typ prosty "+type);
}
static AnsiString mkToStream(const DataTypeArray& data, const AnsiString& type, const AnsiString& access) {
  int ix = findTypeByName(data, type);
  if (ix==-1)
    throw Exception("Nieznany typ "+type);
  if (!data[ix].getKind().isBasic())
    return access+".toStream(_s);";
  else
    return mkBasicToStream(type, access);
}
static AnsiString mkBasicFromStream(const AnsiString& type) {
  if (type=="string")
    return "_s.readUTF()";
  else if (type=="int")
    return "_s.readInt()";
  else if (type=="bool")
    return "_s.readBoolean()";
  else
    throw Exception("Nieznany typ prosty "+type);
}
static AnsiString mkFromStream(const DataTypeArray& data, const AnsiString& type) {
  int ix = findTypeByName(data, type);
  if (ix==-1)
    throw Exception("Nieznany typ "+type);
  if (!data[ix].getKind().isBasic())
    return type+".fromStream(_s)";
  else
    return mkBasicFromStream(type);
}
static AnsiString getConstrParam(const DataTypeArray& data, const RecordField& field, bool names) {
  return " "+getRealTypeName(data, field.getType())+""+((names) ? " _"+field.getName() : AnsiString());
}
static AnsiString getConstrParams(const DataTypeArray& data, const RecordType& record, bool names) {
  AnsiString ret;
  if (record.Size()==0)
    return ret;
  ret = getConstrParam(data, record[0], names);
  for (int i=1;i<record.Size();i++)
    ret+=", "+getConstrParam(data, record[i], names);
  return ret;
}
static DynSet<AnsiString> mkImports(const DataTypeArray& data, const DynSet<AnsiString>& types) {
  DynSet<AnsiString> ret;
  for (int i=0;i<types.Size();i++) {
    int ix = findTypeByName(data, types[i]);
    if (ix==-1)
      throw Exception("Nieznany typ "+types[i]);
    if (data[ix].getKind().isExternal())
      ret.Insert("import "+data[ix].getKind().asExternal().getSource()+";");
  }
  return ret;
}
static AnsiString getConstrParamInit(const RecordField& field) {
  return "    this."+field.getName()+" = _"+field.getName()+";";
}
static DynSet<AnsiString> getConstrParamsInit(const RecordType& record) {
  DynSet<AnsiString> ret;
  for (int i=0;i<record.Size();i++)
    ret.Insert(getConstrParamInit(record[i]));
  return ret;
}
static AnsiString mkToJSON(const DataTypeArray& data, const AnsiString& type, const AnsiString& access) {
  int ix = findTypeByName(data, type);
  if (ix==-1)
    throw Exception("Nieznany typ "+type);
  if (!data[ix].getKind().isBasic())
    return access+".toJSON()";
  else {
    AnsiString basic = data[ix].getKind().asBasic();
    if (basic=="int")
      return access;
    else if (basic=="bool")
      return "(" + access + "? 1 : 0)";
    else if (basic=="string")
      return "\"\\\"\" + JSONUtil.escape("+access+") + \"\\\"\"";
    else
      throw Exception("Nieznany typ prosty "+type);
  }
}
static AnsiString mkFromJSON(bool j2j, const DataTypeArray& data, const AnsiString& type, const AnsiString& access) {
  int ix = findTypeByName(data, type);
  if (ix == -1)
    throw Exception("Nieznany typ 6"+type);
  if (!data[ix].getKind().isBasic())
    return type+".fromJSON("+access+")";
  else {
    AnsiString basic = data[ix].getKind().asBasic();
    if (basic=="int")
      if (j2j)
        return "IntUtil.toInt("+access+")";
      else
        return "Integer.parseInt("+access+")";
    else if (basic=="bool")
      if (j2j)
        return "(IntUtil.toInt("+access+") == 1)";
      else
        return "(Integer.parseInt("+access+") == 1)";
    else if (basic == "string")
      if (j2j)
        return "JSONUtil.unescape("+access+".substring(1, "+access+".length-1))";
      else
        return "JSONUtil.unescape("+access+".substring(1, "+access+".length()-1))";
    else
      throw Exception("Nieznany typ prosty "+type);
  }
}
static AnsiString mkToArray(const DataTypeArray& data, const AnsiString& type, const AnsiString& oaccess, const AnsiString& ixaccess, const AnsiString& access) {
  int ix = findTypeByName(data, type);
  if (ix==-1)
    throw Exception("Nieznany typ "+type);
  if (!data[ix].getKind().isBasic())
    return "JArray.putObject("+oaccess+", "+ixaccess+", "+access+".toArray());";
  else {
    AnsiString basic = data[ix].getKind().asBasic();
    if (basic=="int")
      return "JArray.putInt("+oaccess+", "+ixaccess+", "+access+");";
    else if (basic=="string")
      return "JArray.putString("+oaccess+", "+ixaccess+", "+access+");";
    else if (basic=="bool")
      return "JArray.putBoolean("+oaccess+", "+ixaccess+", "+access+");";
    else
      throw Exception("Nieznany typ prosty "+type);
  }
}
static AnsiString mkFromArray(const DataTypeArray& data, const AnsiString& type, const AnsiString& oaccess, const AnsiString& ixaccess) {
  int ix = findTypeByName(data, type);
  if (ix==-1)
    throw Exception("Nieznany typ "+type);
  if (!data[ix].getKind().isBasic())
    return type+".fromArray(JArray.getObject("+oaccess+", "+ixaccess+"))";
  else {
    AnsiString basic = data[ix].getKind().asBasic();
    if (basic=="int")
      return "JArray.getInt("+oaccess+", "+ixaccess+")";
    else if (basic=="string")
      return "JArray.getString("+oaccess+", "+ixaccess+")";
    else if (basic=="bool")
      return "JArray.getBoolean("+oaccess+", "+ixaccess+")";
    else
      throw Exception("Nieznany typ prosty "+type);
  }
}
AnsiString generateJavaRecordCode(const AnsiString& package, bool onefile, bool stream, bool json, bool xml, bool isarr, bool strictNull, bool ftl, bool j2j, bool serializable, bool iterable, const DataTypeArray& data, const AnsiString& type, const RecordType& record) {
  DynSet<AnsiString> ret;
  if (!onefile) {
    ret.Insert("package "+package+";");
    DynSet<AnsiString> imports;
    for (int i=0;i<record.Size();i++)
      imports.Insert(record[i].getType());
    ret+=mkImports(data, imports);
    if (j2j)
      ret.Insert("import mednt.lib.IntUtil;");
    if (stream) {
      ret.Insert("import java.io.DataInputStream;");
      ret.Insert("import java.io.DataOutputStream;");
      ret.Insert("import java.io.IOException;");
    }
    if (isarr)
      ret.Insert("import mednt.mhtml.JArray;");
    if (ftl)
      ret.Insert("import java.util.HashMap;");
    if (iterable)
      ret.Insert("import java.util.Iterator;");
  }
  ret.Insert(AnsiString(onefile ? "final" : "public")+" class "+type+" "+(serializable ? " implements java.io.Serializable " : "")+"{");
  for (int i=0;i<record.Size();i++)
    ret.Insert("  private "+getRealTypeName(data, record[i].getType())+" "+record[i].getName()+";");
  ret.Insert("  public "+type+"("+getConstrParams(data, record, true)+") {");
  if (strictNull) {
    for (int i=0;i<record.Size();i++) {
      if (record[i].getType()!="int") {
        ret.Insert("    if (_"+record[i].getName()+"==null)");
        ret.Insert("      throw new NullPointerException(\"Parametr is null\");");
      }  
    }
  }
  ret+=getConstrParamsInit(record);
  ret.Insert("  }");
  for (int i=0;i<record.Size();i++) {
    ret.Insert("  public "+getRealTypeName(data, record[i].getType())+" get"+cap1st(record[i].getName())+"() {");
    ret.Insert("    return this."+record[i].getName()+";");
    ret.Insert("  }");
    ret.Insert("  public void set"+cap1st(record[i].getName())+"("+getRealTypeName(data, record[i].getType())+" _v) {");
    if (strictNull && getRealTypeName(data, record[i].getType())!="int") {
      ret.Insert("    if (_v==null)");
      ret.Insert("      throw new NullPointerException(\"Parametr is null\");");
    }
    ret.Insert("    this."+record[i].getName()+" = _v;");
    ret.Insert("  }");
  }
  if (stream) {
    ret.Insert("  public void toStream(DataOutputStream _s) throws IOException {");
    if (strictNull) {
      ret.Insert("    if (_s==null)");
      ret.Insert("      throw new NullPointerException(\"Parametr is null\");");
    }
    for (int i=0;i<record.Size();i++)
      ret.Insert("    "+mkToStream(data, record[i].getType(), "this."+record[i].getName()));
    ret.Insert("  }");
    ret.Insert("  static public "+type+" fromStream(DataInputStream _s) throws IOException {");
    if (strictNull) {
      ret.Insert("    if (_s==null)");
      ret.Insert("      throw new NullPointerException(\"Parametr is null\");");
    }
    for (int i=0;i<record.Size();i++)
      ret.Insert("    "+getRealTypeName(data, record[i].getType())+" _f_"+i+" = "+mkFromStream(data, record[i].getType())+";");
    ret.Insert("    return new "+type+"(");
    ret.Insert("      _f_0");
    for (int i=1;i<record.Size();i++)
      ret.Insert("      , _f_"+AnsiString(i));
    ret.Insert("    );");
    ret.Insert("  }");
  }
  if (json) {
    ret.Insert("  public String toJSON() {");
    ret.Insert("    String _s = \"{\";");
    for (int i=0;i<record.Size();i++)
      if (i<record.Size()-1)
        ret.Insert("    _s+=\"\\\""+record[i].getName()+"\\\":\"+"+mkToJSON(data, record[i].getType(), "this."+record[i].getName())+"+\",\";");
      else
        ret.Insert("    _s+=\"\\\""+record[i].getName()+"\\\":\"+"+mkToJSON(data, record[i].getType(), "this."+record[i].getName())+"+\"}\";");
    ret.Insert("    return _s;");
    ret.Insert("  }");
    ret.Insert("  public static "+type+" fromJSON(String s) {");
    ret.Insert("    Object[] arr = new Object["+AnsiString(record.Size())+"];");
    ret.Insert("    int ix=0;");
    ret.Insert("    for(int i=0;i<"+AnsiString(record.Size())+";i++) {");
    AnsiString lengthTag = "s.length()";
    if (j2j)
      lengthTag = "s.length";
    ret.Insert("      while(ix < "+lengthTag+" &&  s.charAt(ix) != ':')");
    ret.Insert("        ix++;");
    ret.Insert("      ix+=1;");
    ret.Insert("      if (ix >="+lengthTag+") ");
    ret.Insert("        throw new RuntimeException(\""+type+"::fromJSON\");");
    ret.Insert("      int start = ix;");
    ret.Insert("      boolean inString = false;");
    ret.Insert("      int bracketLevel = 0;");
    ret.Insert("      while(ix<"+lengthTag+") {");
    ret.Insert("        if (s.charAt(ix) == '\\\\')");
    ret.Insert("          ix+=2;");
    ret.Insert("        else if (s.charAt(ix) == '\"')");
    ret.Insert("          inString = !inString;");
    ret.Insert("        else if (!inString && s.charAt(ix) == '[')");
    ret.Insert("          bracketLevel++;");
    ret.Insert("        else if (!inString && s.charAt(ix) == '{')");
    ret.Insert("          bracketLevel++;");
    ret.Insert("        else if (!inString && s.charAt(ix) == ']')");
    ret.Insert("          bracketLevel--;");
    ret.Insert("        else if (!inString && s.charAt(ix) == '}')");
    ret.Insert("          bracketLevel--;");
    ret.Insert("        if (bracketLevel <= 0 && !inString && (s.charAt(ix) == ',' || ix == "+lengthTag+"-1)) {");
    for (int i=0;i< record.Size();i++) {
      ret.Insert("          if (i == "+AnsiString(i)+") {");
      ret.Insert("            String tmp = s.substring(start, ix);");
      ret.Insert("            arr[i] = "+mkFromJSON(j2j,data, record[i].getType(), "tmp")+";");
      ret.Insert("          }");
    }
    ret.Insert("          ix++;");
    ret.Insert("          break;");
    ret.Insert("        }");
    ret.Insert("        ix++;");
    ret.Insert("      }");
    ret.Insert("    }");
    AnsiString str;
    for (int i=0;i<record.Size();i++)
      str+=AnsiString(i > 0 ? ", " : "")+"("+getRealTypeName(data, record[i].getType())+")"+"arr["+AnsiString(i)+"]";
    ret.Insert("    return new "+type+"("+str+");");
    ret.Insert("  }");
  }
  if (xml) {
    ret.Insert("  public String toXML() {");
    ret.Insert("    String _xml = \"<"+type+">\";");
    for (int i=0;i<record.Size();i++)
      if (getTypeByName(data, record[i].getType()).getKind().isBasic())
    if (getTypeByName(data, record[i].getType()).getKind().asBasic()=="bool")
      ret.Insert("    _xml+=\"<"+record[i].getName()+"><\"+(this."+record[i].getName()+")+\"/></"+record[i].getName()+">\";");
      else
      ret.Insert("    _xml+=\"<"+record[i].getName()+"><![CDATA[\"+(this."+record[i].getName()+")+\"]]></"+record[i].getName()+">\";");
      else
        ret.Insert("    _xml+=\"<"+record[i].getName()+">\"+this."+record[i].getName()+".toXML()+\"</"+record[i].getName()+">\";");
    ret.Insert("  _xml+=\"</"+type+">\";");
    ret.Insert("  return _xml;");
    ret.Insert("  }");
  }
  if (ftl) {
    ret.Insert("  public Object toFTL() {");
    ret.Insert("    HashMap<String, Object> _ftl = new HashMap<String, Object>();");
    for (int i=0;i<record.Size();i++)
      if (getTypeByName(data, record[i].getType()).getKind().isBasic())
        ret.Insert("    _ftl.put(\""+record[i].getName()+"\", this."+record[i].getName()+");");
      else
        ret.Insert("    _ftl.put(\""+record[i].getName()+"\", this."+record[i].getName()+".toFTL());");
    ret.Insert("    return _ftl;");
    ret.Insert("  }");  
  }
  if (isarr) {
    ret.Insert("  public JArray toArray() {");
    ret.Insert("    JArray jObj = JArray.create();");
    for (int i=0;i<record.Size();i++)
      ret.Insert("    "+mkToArray(data, record[i].getType(), "jObj", i, "this."+record[i].getName()));
    ret.Insert("    return jObj;");
    ret.Insert("  }");
    ret.Insert("  static public "+type+" fromArray(JArray _s) {");
    if (strictNull) {
      ret.Insert("    if (_s==null)");
      ret.Insert("      throw new NullPointerException(\"Parametr is null\");");
    }
    ret.Insert("    if (_s==null)");
    ret.Insert("      return null;");
    for (int i=0;i<record.Size();i++)
      ret.Insert("    "+getRealTypeName(data, record[i].getType())+" _f_"+i+" = "+mkFromArray(data, record[i].getType(), "_s", i)+";");
    ret.Insert("    return new "+type+"(");
    ret.Insert("      _f_0");
    for (int i=1;i<record.Size();i++)
      ret.Insert("      , _f_"+AnsiString(i));
    ret.Insert("    );");
    ret.Insert("  }");
  }
  ret.Insert("};");
  return conv(ret);
}
AnsiString generateJavaArrayCode(const AnsiString& package, bool onefile, bool stream, bool json, bool xml, bool isarr, bool strictNull, bool ftl, bool j2j, bool serializable, bool iterable, const DataTypeArray& data, const AnsiString& type, const ArrayType& array) {
  DynSet<AnsiString> ret;
  
  if (!onefile) {
    ret.Insert("package "+package+";");
    DynSet<AnsiString> imports;
    imports.Insert(array.getType());
    ret+=mkImports(data, imports);
    ret.Insert("import java.util.ArrayList;");
    if (j2j)
      ret.Insert("import mednt.lib.IntUtil;");
    if (stream) {
      ret.Insert("import java.io.DataInputStream;");
      ret.Insert("import java.io.DataOutputStream;");
      ret.Insert("import java.io.IOException;");
    }
    if (isarr)
      ret.Insert("import mednt.mhtml.JArray;");
    if (ftl)
      ret.Insert("import java.util.HashMap;");
    if (iterable)
      ret.Insert("import java.util.Iterator;");
  }
  
  int ix = findTypeByName(data, type);
  if (ix==-1)
    throw Exception("Nieznany typ "+type);
  DataType aType = getTypeByName(data, array.getType());
  DataTypeKind kind = aType.getKind();
  if (kind.isBasic() && kind.asBasic()=="int") {
    ret.Insert(AnsiString(onefile ? "final" : "public")+" class "+type+" implements Iterable<Integer>"+(serializable ? "  , java.io.Serializable, " : "")+"  {");
    ret.Insert("  private ArrayList _table;");
    ret.Insert("  public "+type+"() {");
    ret.Insert("    this._table = new ArrayList();");
    ret.Insert("  }");
    ret.Insert("  class IntArrayIterator implements Iterator<Integer> {");
    ret.Insert("    int current = 0;");
    ret.Insert("    public boolean hasNext() {");
    ret.Insert("      return current < "+type+".this.Size();");
    ret.Insert("    }");
    ret.Insert("    public Integer next() {");
    ret.Insert("      return "+type+".this.Get(current++);");
    ret.Insert("    }");
    ret.Insert("    public void remove() {");
    ret.Insert("      throw new UnsupportedOperationException();");
    ret.Insert("    }");
    ret.Insert("  }");
    ret.Insert("  public Iterator iterator() {");
    ret.Insert("    return new IntArrayIterator();");
    ret.Insert("  }");
    ret.Insert("  public int Size() {");
    ret.Insert("    return this._table.size();");
    ret.Insert("  }");
    ret.Insert("  public void Insert(int _v) {");
    ret.Insert("    this._table.add(new Integer(_v));");
    ret.Insert("  }");
    ret.Insert("  public int Get(int _ix) {");
    ret.Insert("    return ((Integer) this._table.get(_ix)).intValue();");
    ret.Insert("  }");
    ret.Insert("  public void Delete(int _ix) {");
    ret.Insert("    this._table.remove(_ix);");
    ret.Insert("  }");
    if (stream) {
      ret.Insert("  public void toStream(DataOutputStream _s) throws IOException {");
      if (strictNull) {
        ret.Insert("    if (_s==null)");
        ret.Insert("      throw new NullPointerException(\"Parametr is null\");");
      }
      ret.Insert("    _s.writeInt(this._table.size());");
      ret.Insert("    for (int i=0;i<this._table.size();i++)");
      ret.Insert("      "+mkToStream(data, array.getType(), "this.Get(i)"));
      ret.Insert("  }");
      ret.Insert("  static public "+type+" fromStream(DataInputStream _s) throws IOException {");
      if (strictNull) {
        ret.Insert("    if (_s==null)");
        ret.Insert("      throw new NullPointerException(\"Parametr is null\");");
      }
      ret.Insert("    "+type+" _ret = new "+type+"();");
      ret.Insert("    int _size = _s.readInt();");
      ret.Insert("    for (int i=0;i<_size;i++)");
      ret.Insert("      _ret.Insert("+mkFromStream(data, array.getType())+");");
      ret.Insert("    return _ret;");
      ret.Insert("  }");
    }
    if (ftl) {
      ret.Insert("  public Object toFTL() {");
      ret.Insert("    ArrayList<Object> _ftl = new ArrayList<Object>();");
      ret.Insert("    for (int _i=0;_i<this.Size();_i++)");
      ret.Insert("      _ftl.add(this.Get(_i));");
      ret.Insert("    return _ftl;");
      ret.Insert("  }");   
    }
    if (xml) {
      ret.Insert("  public String toXML() {");
      ret.Insert("    String _xml = \"<"+type+">\";");
      ret.Insert("    for (int _i=0;_i<this.Size();_i++)");
      ret.Insert("      _xml+=\"<"+array.getType()+">\"+this.Get(_i)+\"</"+array.getType()+">\";");
      ret.Insert("    _xml+=\"</"+type+">\";");
      ret.Insert("    return _xml;");
      ret.Insert("  }");
    }
    if (json) {
      ret.Insert("  public String toJSON() {");
      ret.Insert("    String _s = \"[\";");
      ret.Insert("    for (int i=0;i<this._table.size();i++)");
      ret.Insert("    if (i<this._table.size()-1)");
      ret.Insert("        _s+=\"\"+"+mkToJSON(data, array.getType(), "this.Get(i)")+"+\",\";");
      ret.Insert("      else");
      ret.Insert("        _s+=\"\"+"+mkToJSON(data, array.getType(), "this.Get(i)")+"+\"\";");
      ret.Insert("    _s+=\"]\";");
      ret.Insert("    return _s;");
      ret.Insert("  }");

      ret.Insert("  public static "+type+" fromJSON(String s) {");
      ret.Insert("    "+type+" arr = new "+type+"();");
      ret.Insert("    int ix=0;");
      AnsiString lengthTag = "s.length()";
      if (j2j)
        lengthTag = "s.length";
      ret.Insert("    while(ix <"+lengthTag+" && s.charAt(ix)!='[')");
      ret.Insert("      ix++;");
      ret.Insert("    ix++;");
      ret.Insert("    if (ix >="+lengthTag+") ");
      ret.Insert("      throw new RuntimeException(\""+type+"::fromJSON\");");
      ret.Insert("    while(ix<"+lengthTag+") {");
      ret.Insert("      int start = ix;");
      ret.Insert("      boolean inString = false;");
      ret.Insert("      int bracketLevel = 0;");
      ret.Insert("      while(ix<"+lengthTag+") {");
      ret.Insert("        if (s.charAt(ix) == '\\\\')");
      ret.Insert("          ix+=2;");
      ret.Insert("        else if (s.charAt(ix) == '\"')");
      ret.Insert("          inString = !inString;");
      ret.Insert("        else if (!inString && s.charAt(ix) == '[')");
      ret.Insert("          bracketLevel++;");
      ret.Insert("        else if (!inString && s.charAt(ix) == '{')");
      ret.Insert("          bracketLevel++;");
      ret.Insert("        else if (!inString && s.charAt(ix) == ']')");
      ret.Insert("          bracketLevel--;");
      ret.Insert("        else if (!inString && s.charAt(ix) == '}')");
      ret.Insert("          bracketLevel--;");
      ret.Insert("        if (bracketLevel <= 0 && !inString && (s.charAt(ix) == ',' || ix =="+lengthTag+"-1)) {");
      ret.Insert("          if (start == ix)");
      ret.Insert("            return arr;");
      ret.Insert("          String tmp = s.substring(start, ix);");
      ret.Insert("          arr.Insert("+mkFromJSON(j2j, data, array.getType(), "tmp")+");");
      ret.Insert("          ix+=2;");
      ret.Insert("          break;");
      ret.Insert("        }");
      ret.Insert("        ix++;");
      ret.Insert("      }");
      ret.Insert("    }");
      ret.Insert("    return arr;");
      ret.Insert("  }");
    }
  } else {
    AnsiString realType = getRealTypeName(data, array.getType());
        ret.Insert(AnsiString(onefile ? "final" : "public")+" class "+type+" implements Iterable<"+realType+">"+(serializable ? "  , java.io.Serializable, " : "")+"  {");
    ret.Insert("  private ArrayList _table;");
    ret.Insert("  public "+type+"() {");
    ret.Insert("    this._table = new ArrayList();");
    ret.Insert("  }");
    ret.Insert("  class ArrayIterator implements Iterator<"+realType+"> {");
    ret.Insert("    int current = 0;");
    ret.Insert("    public boolean hasNext() {");
    ret.Insert("      return current < "+type+".this.Size();");
    ret.Insert("    }");
    ret.Insert("    public "+realType+" next() {");
    ret.Insert("      return "+type+".this.Get(current++);");
    ret.Insert("    }");
    ret.Insert("    public void remove() {");
    ret.Insert("      throw new UnsupportedOperationException();");
    ret.Insert("    }");
    ret.Insert("  }");
    ret.Insert("  public Iterator iterator() {");
    ret.Insert("    return new ArrayIterator();");
    ret.Insert("  }");
    ret.Insert("  public int Size() {");
    ret.Insert("    return this._table.size();");
    ret.Insert("  }");
    ret.Insert("  public void Insert("+realType+" _v) {");
    if (strictNull && realType!="int") {
      ret.Insert("    if (_v==null)");
      ret.Insert("      throw new NullPointerException(\"Parametr is null\");");
    }
    ret.Insert("    this._table.add(_v);");
    ret.Insert("  }");
    ret.Insert("  public "+realType+" Get(int _ix) {");
    ret.Insert("    return ("+realType+") this._table.get(_ix);");
    ret.Insert("  }");
    ret.Insert("  public void Delete(int _ix) {");
    ret.Insert("    this._table.remove(_ix);");
    ret.Insert("  }");
    if (stream) {
      ret.Insert("  public void toStream(DataOutputStream _s) throws IOException {");
      if (strictNull) {
        ret.Insert("    if (_s==null)");
        ret.Insert("      throw new NullPointerException(\"Parametr is null\");");
      }
      ret.Insert("    _s.writeInt(this._table.size());");
      ret.Insert("    for (int i=0;i<this._table.size();i++)");
      ret.Insert("      "+mkToStream(data, array.getType(), "this.Get(i)"));
      ret.Insert("  }");
      ret.Insert("  static public "+type+" fromStream(DataInputStream _s) throws IOException {");
      if (strictNull) {
        ret.Insert("    if (_s==null)");
        ret.Insert("      throw new NullPointerException(\"Parametr is null\");");
      }
      ret.Insert("    "+type+" _ret = new "+type+"();");
      ret.Insert("    int _size = _s.readInt();");
      ret.Insert("    for (int i=0;i<_size;i++)");
      ret.Insert("      _ret.Insert("+mkFromStream(data, array.getType())+");");
      ret.Insert("    return _ret;");
      ret.Insert("  }");
    }
    if (ftl) {
      if (kind.isBasic()) {
        ret.Insert("  public Object toFTL() {");
        ret.Insert("    ArrayList<Object> _ftl = new ArrayList<Object>();");
        ret.Insert("    for (int _i=0;_i<this.Size();_i++)");
        ret.Insert("      _ftl.add(this.Get(_i));");
        ret.Insert("    return _ftl;");
        ret.Insert("  }"); 
      } else {
        ret.Insert("  public Object toFTL() {");
        ret.Insert("    ArrayList<Object> _ftl = new ArrayList<Object>();");
        ret.Insert("    for (int _i=0;_i<this.Size();_i++) ");
        ret.Insert("      _ftl.add(this.Get(_i).toFTL());");
        ret.Insert("    return _ftl;");
        ret.Insert("  }");   
      } 
    }
    if (xml) {
      ret.Insert(" public String toXML() {");
      ret.Insert("  String _xml = \"<"+type+">\";");
      ret.Insert("  for (int _i=0;_i<this.Size();_i++)");
      if (kind.isBasic())
        ret.Insert("    _xml+=\"<"+array.getType()+"><![CDATA[\"+this.Get(_i)+\"]]></"+array.getType()+">\";");
      else
        ret.Insert("    _xml+=(("+realType+") this.Get(_i)).toXML();");
      ret.Insert("    _xml+=\"</"+type+">\";");
      ret.Insert("    return _xml;");
      ret.Insert("}");
    }
    if (json) {
      ret.Insert("  public String toJSON() {");
      ret.Insert("    String _s = \"[\";");
      ret.Insert("    for (int i=0;i<this._table.size();i++)");
      ret.Insert("    if (i<this._table.size()-1)");
      ret.Insert("        _s+=\"\"+"+mkToJSON(data, array.getType(), "this.Get(i)")+"+\",\";");
      ret.Insert("      else");
      ret.Insert("        _s+=\"\"+"+mkToJSON(data, array.getType(), "this.Get(i)")+"+\"\";");
      ret.Insert("    _s+=\"]\";");
      ret.Insert("    return _s;");
      ret.Insert("  }");

      ret.Insert("  public static "+type+" fromJSON(String s) {");
      ret.Insert("    "+type+" arr = new "+type+"();");
      ret.Insert("    int ix=0;");
      AnsiString lengthTag = "s.length()";
      if (j2j)
        lengthTag = "s.length";
      ret.Insert("    while(ix < "+lengthTag+" && s.charAt(ix)!='[')");
      ret.Insert("      ix++;");
      ret.Insert("    ix++;");
      ret.Insert("    if (ix >="+lengthTag+") ");
      ret.Insert("      throw new RuntimeException(\""+type+"::fromJSON\");");
      ret.Insert("    while(ix<"+lengthTag+") {");
      ret.Insert("      int start = ix;");
      ret.Insert("      boolean inString = false;");
      ret.Insert("      int bracketLevel = 0;");
      ret.Insert("      while(ix<"+lengthTag+") {");
      ret.Insert("        if (s.charAt(ix) == '\\\\')");
      ret.Insert("          ix+=2;");
      ret.Insert("        else if (s.charAt(ix) == '\"')");
      ret.Insert("          inString = !inString;");
      ret.Insert("        else if (!inString && s.charAt(ix) == '[')");
      ret.Insert("          bracketLevel++;");
      ret.Insert("        else if (!inString && s.charAt(ix) == '{')");
      ret.Insert("          bracketLevel++;");
      ret.Insert("        else if (!inString && s.charAt(ix) == ']')");
      ret.Insert("          bracketLevel--;");
      ret.Insert("        else if (!inString && s.charAt(ix) == '}')");
      ret.Insert("          bracketLevel--;");
      ret.Insert("        if (bracketLevel <= 0 && !inString && (s.charAt(ix) == ',' || ix == "+lengthTag+"-1)) {");
      ret.Insert("          String tmp = s.substring(start, ix);");
      ret.Insert("          arr.Insert("+mkFromJSON(j2j,data, array.getType(), "tmp")+");");
      ret.Insert("          ix++;");
      ret.Insert("          break;");
      ret.Insert("        }");
      ret.Insert("        ix++;");
      ret.Insert("      }");
      ret.Insert("    }");
      ret.Insert("    return arr;");
      ret.Insert("  }");
    }
    if (isarr) {
      ret.Insert("  public JArray toArray() {");
      ret.Insert("    JArray _s = JArray.create();");
      ret.Insert("    JArray.putInt(_s, 0, this._table.size());");
      ret.Insert("    for (int i=0;i<this._table.size();i++)");
      ret.Insert("      "+mkToArray(data, array.getType(), "_s", "i+1", "this.Get(i)"));
      ret.Insert("    return _s;");
      ret.Insert("  }");
      ret.Insert("  static public "+type+" fromArray(JArray _s) {");
      if (strictNull) {
        ret.Insert("    if (_s==null)");
        ret.Insert("      throw new NullPointerException(\"Parametr is null\");");
      }
      ret.Insert("    if (_s==null)");
      ret.Insert("      return null;");
      ret.Insert("    int _size = JArray.getInt(_s, 0);");
      ret.Insert("    "+type+" _ret = new "+type+"();");
      ret.Insert("    for (int i=0;i<_size;i++) ");
      ret.Insert("      _ret.Insert("+mkFromArray(data, array.getType(), "_s", "i+1")+");");
      ret.Insert("    return _ret;");
      ret.Insert("  }");
    }
  }
  ret.Insert("};");
  
  return conv(ret);
}
AnsiString generateJavaVariantCode(const AnsiString& package, bool onefile, bool stream, bool json, bool xml, bool isarr, bool strictNull, bool ftl, bool j2j, bool serializable, bool iterable, const DataTypeArray& data, const AnsiString& type, const VariantType& variant) {
  DynSet<AnsiString> ret;
  
  if (!onefile) {
    ret.Insert("package "+package+";");
    DynSet<AnsiString> imports;
    for (int i=0;i<variant.Size();i++) {
      VariantField field = variant[i];
      VariantFieldKind kind = field.getKind();
      if (kind.isEmpty())
        ;
      else if (kind.isType())
        imports.Insert(kind.asType());
    }
    ret+=mkImports(data, imports);
    if (j2j)
      ret.Insert("import mednt.lib.IntUtil;");
    if (stream) {
      ret.Insert("import java.io.DataInputStream;");
      ret.Insert("import java.io.DataOutputStream;");
      ret.Insert("import java.io.IOException;");
    }
    if (isarr)
      ret.Insert("import mednt.mhtml.JArray;");
    if (ftl)
      ret.Insert("import java.util.HashMap;");
    if (iterable)
      ret.Insert("import java.util.Iterator;");
  }
  
  ret.Insert(AnsiString(onefile ? "final" : "public")+" class "+type+" "+(serializable ? " implements java.io.Serializable " : "")+" {");
  ret.Insert("  private int _type;");
  bool needObj = false;
  bool needInt = false;
  for (int i=0;i<variant.Size();i++)
    if (variant[i].getKind().isEmpty())
      ;
    else if (variant[i].getKind().isType()) {
      int ix = findTypeByName(data, variant[i].getKind().asType());
      if (ix == -1)
        throw Exception("Nieznany typ "+variant[i].getKind().asType());
      const DataTypeKind& kind = data[ix].getKind();
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
    ret.Insert("  private static final int _Type"+cap1st(variant[i].getName())+" = "+i+";");
  ret.Insert("");
  ret.Insert("  private "+type+"() {}");
  for (int i=0;i<variant.Size();i++) {
    ret.Insert("  public boolean is"+cap1st(variant[i].getName())+"() {");
    ret.Insert("    return this._type=="+type+"._Type"+cap1st(variant[i].getName())+";");
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
      ret.Insert("    if (this._type!="+type+"._Type"+cap1st(field.getName())+")");
      ret.Insert("      throw new RuntimeException(\""+type+"::as"+cap1st(field.getName())+"\");");
      int ix = findTypeByName(data, kind.asType());
      if (ix == -1)
        throw Exception("Nieznany typ "+kind.asType());
      const DataTypeKind& typeKind = data[ix].getKind();
      if (typeKind.isBasic() && typeKind.asBasic()=="int")
        ret.Insert("    return this._ptrInt;");
      else
        ret.Insert("    return ("+getRealTypeName(data, kind.asType())+") this._ptrObj;");
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
      ret.Insert("    _value._type = "+type+"._Type"+cap1st(variant[i].getName())+";");
      ret.Insert("    return _value;");
      ret.Insert("  }");
    } else if (kind.isType()) {
      ret.Insert("  static public "+type+" create"+cap1st(variant[i].getName())+"("+getRealTypeName(data, kind.asType())+" _v) {");
      if (strictNull && getRealTypeName(data, kind.asType())!="int") {
        ret.Insert("    if (_v==null)");
        ret.Insert("      throw new NullPointerException(\"Parametr is null\");");
      }
      ret.Insert("    "+type+" _value = new "+type+"();");
      ret.Insert("    _value._type = "+type+"._Type"+cap1st(variant[i].getName())+";");
      int ix = findTypeByName(data, kind.asType());
      if (ix == -1)
        throw Exception("Nieznany typ "+kind.asType());
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
  if (stream) {
    ret.Insert("  public void toStream(DataOutputStream _s) throws IOException {");
    if (strictNull) {
      ret.Insert("    if (_s==null)");
      ret.Insert("      throw new NullPointerException(\"Parametr is null\");");
    }
    ret.Insert("    _s.writeInt(this._type);");
    ret.Insert("    if (0==1)");
    ret.Insert("      ;");
    for (int i=0;i<variant.Size();i++) {
      VariantField field = variant[i];
      VariantFieldKind kind = field.getKind();
      ret.Insert("    else if (this._type=="+type+"._Type"+cap1st(variant[i].getName())+")");
      if (kind.isEmpty())
        ret.Insert("      ;");
      else if (kind.isType()) {
        int ix = findTypeByName(data, kind.asType());
        if (ix == -1)
          throw Exception("Nieznany typ "+kind.asType());
        const DataTypeKind& typeKind = data[ix].getKind();
        if (typeKind.isBasic() && typeKind.asBasic()=="int")
          ret.Insert("      "+mkToStream(data, kind.asType(), "(this._ptrInt)"));
        else
          ret.Insert("      "+mkToStream(data, kind.asType(), "(("+getRealTypeName(data, kind.asType())+") this._ptrObj)"));
      } else
        throw Exception("VariantFieldKind");
    }
    ret.Insert("    else");
    ret.Insert("      throw new RuntimeException(\""+type+"::toStream()\");");
    ret.Insert("  }");
    ret.Insert("  static public "+type+" fromStream(DataInputStream _s) throws IOException {");
    if (strictNull) {
      ret.Insert("    if (_s==null)");
      ret.Insert("      throw new NullPointerException(\"Parametr is null\");");
    }
    ret.Insert("    "+type+" _ret = new "+type+"();");
    ret.Insert("    _ret._type = _s.readInt();");
    ret.Insert("    if (0==1)");
    ret.Insert("      ;");
    for (int i=0;i<variant.Size();i++) {
      VariantField field = variant[i];
      VariantFieldKind kind = field.getKind();
      ret.Insert("    else if (_ret._type=="+type+"._Type"+cap1st(variant[i].getName())+")");
      if (kind.isEmpty())
        ret.Insert("      ;");
      else if (kind.isType()) {
        int ix = findTypeByName(data, kind.asType());
        if (ix == -1)
          throw Exception("Nieznany typ "+kind.asType());
        const DataTypeKind& typeKind = data[ix].getKind();
        if (typeKind.isBasic() && typeKind.asBasic()=="int")
          ret.Insert("      _ret._ptrInt = "+mkFromStream(data, kind.asType())+";");
        else
          ret.Insert("      _ret._ptrObj = "+mkFromStream(data, kind.asType())+";");
      } else
        throw Exception("VariantFieldKind");
    }
    ret.Insert("    else");
    ret.Insert("      throw new RuntimeException(\""+type+"::fromStream()\");");
    ret.Insert("    return _ret;");
    ret.Insert("  }");
  }
  if (xml) {
    ret.Insert("  public String toXML() {");
    ret.Insert("   String _xml = \"<"+type+">\";");
    for (int i=0;i<variant.Size();i++) {
      VariantField field = variant[i];
      VariantFieldKind kind = field.getKind();
      ret.Insert("    "+((i>0) ? AnsiString("else ") : AnsiString(""))+"if (this._type=="+type+"._Type"+cap1st(variant[i].getName())+")");
      if (variant[i].getKind().isEmpty()) {
        ret.Insert("      _xml+=\"<"+variant[i].getName()+"/>\";");
      } else if (variant[i].getKind().isType()) {
        DataType aType = getTypeByName(data, variant[i].getKind().asType());
        if (aType.getKind().isBasic()) {
          int ix = findTypeByName(data, kind.asType());
          if (ix == -1)
            throw Exception("Nieznany typ "+kind.asType());
          const DataTypeKind& typeKind = data[ix].getKind();
          if (typeKind.asBasic()=="int")
            ret.Insert("    _xml+=\"<"+variant[i].getName()+">\"+this._ptrInt+\"</"+variant[i].getName()+">\";");
      else if (typeKind.asBasic()=="bool")
      ret.Insert("    _xml+=\"<"+variant[i].getName()+"><\"+(("+getRealTypeName(data, kind.asType())+") this._ptrObj)+\"/></"+variant[i].getName()+">\";");
          else
            ret.Insert("    _xml+=\"<"+variant[i].getName()+"><![CDATA[\"+(("+getRealTypeName(data, kind.asType())+") this._ptrObj)+\"]]></"+variant[i].getName()+">\";");
        } else
          ret.Insert("    _xml+=\"<"+variant[i].getName()+">\"+(("+aType.getName()+") this._ptrObj).toXML()+\"</"+variant[i].getName()+">\";");
      } else
        throw Exception("toXML");
    }
    ret.Insert("    else");
    ret.Insert("      throw new RuntimeException(\""+type+"::toXML(\"+this._type+\")\");");
    ret.Insert("    _xml+=\"</"+type+">\";");
    ret.Insert("    return _xml;");
    ret.Insert("}");
  }
  if (ftl) {
    ret.Insert("  public Object toFTL() {");
    ret.Insert("    HashMap<String, Object> _ftl = new HashMap<String, Object>();");
    for (int i=0;i<variant.Size();i++) {
      VariantField field = variant[i];
      VariantFieldKind kind = field.getKind();
      ret.Insert("    "+((i>0) ? AnsiString("else ") : AnsiString(""))+"if (this._type=="+type+"._Type"+cap1st(variant[i].getName())+")");
      if (kind .isEmpty()) {
        ret.Insert("      _ftl.put(\""+variant[i].getName()+"\", \"\");");
      } else if (kind .isType()) {
        DataType aType = getTypeByName(data, variant[i].getKind().asType());
        if (aType.getKind().isBasic()) {
          int ix = findTypeByName(data, kind.asType());
          if (ix == -1)
            throw Exception("Nieznany typ "+kind.asType());
          const DataTypeKind& typeKind = data[ix].getKind();
          if (typeKind.asBasic()=="int")
            ret.Insert("    _ftl.put(\""+variant[i].getName()+"\", this._ptrInt);");
          else
            ret.Insert("    _ftl.put(\""+variant[i].getName()+"\", this._ptrObj);");
        } else
          ret.Insert("    _ftl.put(\""+variant[i].getName()+"\", ( ("+getRealTypeName(data, kind.asType())+") this._ptrObj).toFTL());");
      } else
        throw Exception("toFTL");
    }
    ret.Insert("    else");
    ret.Insert("      throw new RuntimeException(\""+type+"::toFTL(\"+this._type+\")\");");
    ret.Insert("    return _ftl;");
    ret.Insert("  }");
  }
  if (json) {
    ret.Insert("  public String toJSON() {");
    ret.Insert("    String _s = \"{\";");
    ret.Insert("    if (0==1) {");
    ret.Insert("      ;");
    for (int i=0;i<variant.Size();i++) {
      VariantField field = variant[i];
      VariantFieldKind kind = field.getKind();
      ret.Insert("    } else if (this._type=="+type+"._Type"+cap1st(variant[i].getName())+") {");
      if (kind.isEmpty())
        ret.Insert("      _s+=\"\\\""+variant[i].getName()+"\\\":\\\"\\\"\";");
      else if (kind.isType()) {
        int ix = findTypeByName(data, kind.asType());
        if (ix == -1)
          throw Exception("Nieznany typ "+kind.asType());
        const DataTypeKind& typeKind = data[ix].getKind();
        if (typeKind.isBasic() && typeKind.asBasic()=="int")
          ret.Insert("      _s+=\"\\\""+variant[i].getName()+"\\\":\"+"+mkToJSON(data, kind.asType(), "this._ptrInt")+";");
        else
          ret.Insert("      _s+=\"\\\""+variant[i].getName()+"\\\":\"+"+mkToJSON(data, kind.asType(), "(("+getRealTypeName(data, kind.asType())+") this._ptrObj)")+";");
      } else
        throw Exception("VariantFieldKind");
    } 
    ret.Insert("    } else");
    ret.Insert("      throw new RuntimeException(\""+type+"::toJSON()\");");
    ret.Insert("    _s = _s+\"}\";");
    ret.Insert("    return _s;");
    ret.Insert("  }");

    ret.Insert("  public static "+type+" fromJSON(String s) {");
    ret.Insert("    String variantName = \"\";");
    ret.Insert("    int ix = 0;");
    AnsiString lengthTag = "s.length()";
    if (j2j)
      lengthTag = "s.length";
    ret.Insert("    while(ix < "+lengthTag+" && s.charAt(ix) != ':')");
    ret.Insert("      ix++;");
    ret.Insert("    if (ix >="+lengthTag+") ");
    ret.Insert("      throw new RuntimeException(\""+type+"::fromJSON\");");
    ret.Insert("    variantName = s.substring(2, ix-1);");
    for (int i=0;i<variant.Size();i++) {
      VariantField field = variant[i];
      VariantFieldKind kind = field.getKind();
    if (j2j)
      ret.Insert("    "+AnsiString(i > 0 ? "} else" : "")+" if (variantName.localeCompare(\""+variant[i].getName()+"\")==0) {");
    else
      ret.Insert("    "+AnsiString(i > 0 ? "} else" : "")+" if (variantName.equals(\""+variant[i].getName()+"\")) {");
      if (kind.isEmpty()) {
        ret.Insert("      return "+type+".create"+toUpper(variant[i].getName())+"();");
      } else {
        ret.Insert("      s = s.substring(ix+1, "+lengthTag+"-1);");
        ret.Insert("      return "+type+".create"+toUpper(variant[i].getName())+"("+mkFromJSON(j2j,data, kind.asType(), "s")+");");
      }
    }
    ret.Insert("    } else ");
    ret.Insert("      throw new RuntimeException(\""+type+"::fromJSON\");");
    ret.Insert("  }");
  }
  if (isarr) {
    ret.Insert("  public JArray toArray() {");
    ret.Insert("    JArray _s = JArray.create();");
    ret.Insert("    JArray.putInt(_s, 0, this._type);");
    ret.Insert("    if (0==1) {");
    ret.Insert("      ;");
    for (int i=0;i<variant.Size();i++) {
      VariantField field = variant[i];
      VariantFieldKind kind = field.getKind();
      ret.Insert("    } else if (this._type=="+type+"._Type"+cap1st(variant[i].getName())+") {");
      if (kind.isEmpty())
        ret.Insert("      ;");
      else if (kind.isType()) {
        int ix = findTypeByName(data, kind.asType());
        if (ix == -1)
          throw Exception("Nieznany typ "+kind.asType());
        const DataTypeKind& typeKind = data[ix].getKind();
        if (typeKind.isBasic()) {
          const AnsiString& tt = typeKind.asBasic(); 
          if (tt=="int")
            ret.Insert("      JArray.putInt(_s, 1, this._ptrInt);");
          else if (tt=="string" || tt=="bool")
            ret.Insert("      JArray.putString(_s, 1, (("+getRealTypeName(data, kind.asType())+") this._ptrObj));");
          else
            throw Exception("Bad type "+tt);
        } else 
          ret.Insert("      JArray.putObject(_s, 1, (("+getRealTypeName(data, kind.asType())+") this._ptrObj).toArray());");
      } else
        throw Exception("VariantFieldKind");
    }
    ret.Insert("    } else");
    ret.Insert("      return null;");
    ret.Insert("    return _s;");
    ret.Insert("  }");
    ret.Insert("  static public "+type+" fromArray(JArray _s) {");
    if (strictNull) {
      ret.Insert("    if (_s==null)");
      ret.Insert("      throw new NullPointerException(\"Parametr is null\");");
    }
    ret.Insert("    "+type+" _ret = new "+type+"();");
    ret.Insert("    if (_s==null)");
    ret.Insert("      return null;");
    ret.Insert("    _ret._type = JArray.getInt(_s, 0);");
    ret.Insert("    if (0==1) {");
    ret.Insert("      ;");
    for (int i=0;i<variant.Size();i++) {
      VariantField field = variant[i];
      VariantFieldKind kind = field.getKind();
      ret.Insert("    } else if (_ret._type=="+type+"._Type"+cap1st(variant[i].getName())+") {");
      if (kind.isEmpty())
        ret.Insert("      ;");
      else if (kind.isType()) {
        int ix = findTypeByName(data, kind.asType());
        if (ix == -1)
          throw Exception("Nieznany typ "+kind.asType());
        const DataTypeKind& typeKind = data[ix].getKind();
        if (typeKind.isBasic()) {
          const AnsiString& tt = typeKind.asBasic(); 
          if (tt=="int")
            ret.Insert("      _ret._ptrInt = JArray.getInt(_s, 1);");
          else if (tt=="string" || tt=="bool")
            ret.Insert("      _ret._ptrObj = JArray.getString(_s, 1);");
          else
            throw Exception("Bad type "+tt);
        } else
          ret.Insert("     _ret._ptrObj = "+mkFromArray(data, kind.asType(), "_s", 1)+";");
      } else
        throw Exception("VariantFieldKind");
    }
    ret.Insert("    } else");
    ret.Insert("      return null;");
    ret.Insert("    return _ret;");
    ret.Insert("  }");
  }
  ret.Insert("};");
  return conv(ret);
}
static AnsiString mkJSONUtil(const AnsiString& package, bool j2j, bool onefile) {
  DynSet<AnsiString> ret;
  if (!onefile)
    ret.Insert("package "+package+";");
  if (onefile)
    ret.Insert("final class JSONUtil {");
  else
    ret.Insert("public class JSONUtil {");
  AnsiString lengthTag = "string.length()";
  if (j2j)
    lengthTag = "string.length";
  ret.Insert("  public static String escape(String string) {");
  ret.Insert("    if (string == null || "+lengthTag+" == 0)");
  ret.Insert("      return \"\";");
  ret.Insert("    char c = 0;");
  ret.Insert("    int i = 0;");
  ret.Insert("    int len = "+lengthTag+";");
  ret.Insert("    String sb = \"\";");
  ret.Insert("    String t;");
  ret.Insert("    for (i = 0; i < len; i+=1) {;");
  ret.Insert("      c = string.charAt(i);");
  ret.Insert("      switch (c) {");
  ret.Insert("        case '\\\\':");
  ret.Insert("        case '\"':");
  ret.Insert("          sb+=('\\\\');");
  ret.Insert("          sb+=(c);");
  ret.Insert("          break;");
  ret.Insert("        case '/':");
  ret.Insert("          sb+=('\\\\');");
  ret.Insert("          sb+=(c);");
  ret.Insert("          break;");
  ret.Insert("        case '\\b':");
  ret.Insert("          sb+=(\"\\\\b\");");
  ret.Insert("          break;");
  ret.Insert("        case '\\t':");
  ret.Insert("          sb+=(\"\\\\t\");");
  ret.Insert("          break;");
  ret.Insert("        case '\\n':");
  ret.Insert("          sb+=(\"\\\\n\");");
  ret.Insert("          break;");
  ret.Insert("        case '\\f':");
  ret.Insert("          sb+=(\"\\\\f\");");
  ret.Insert("          break;");
  ret.Insert("        case '\\r':");
  ret.Insert("          sb+=(\"\\\\r\");");
  ret.Insert("          break;");
  ret.Insert("        default:");
  ret.Insert("          sb+=(c);");
  ret.Insert("      }");
  ret.Insert("    }");
  ret.Insert("    return sb;");
  ret.Insert("  }");
  ret.Insert("  public static String unescape(String string) {");
  ret.Insert("    char c = 0;");
  ret.Insert("    int i = 0;");
  ret.Insert("    int len = "+lengthTag+";");
  ret.Insert("    boolean escaped = false;");
  ret.Insert("    String sb = \"\";");
  ret.Insert("    String t;");
  ret.Insert("    for (i = 0; i < len; i+=1) {");
  ret.Insert("      c = string.charAt(i);");
  ret.Insert("      if (escaped) {");
  ret.Insert("        switch (c) {");
  ret.Insert("          case '\\\\':");
  ret.Insert("            sb+=\"\\\\\";");
  ret.Insert("            break;");
  ret.Insert("          case '\\\"':");
  ret.Insert("            sb+=\"\\\"\";");
  ret.Insert("            break;");
  ret.Insert("          case '/':");
  ret.Insert("            sb+=\"/\";");
  ret.Insert("            break;");
  ret.Insert("          case 'b':");
  ret.Insert("            sb+=(\"\\b\");");
  ret.Insert("            break;");
  ret.Insert("          case 't':");
  ret.Insert("            sb+=(\"\\t\");");
  ret.Insert("            break;");
  ret.Insert("          case 'n':");
  ret.Insert("            sb+=(\"\\n\");");
  ret.Insert("            break;");
  ret.Insert("          case 'f':");
  ret.Insert("            sb+=(\"\\f\");");
  ret.Insert("            break;");
  ret.Insert("          case 'r':");
  ret.Insert("            sb+=(\"\\r\");");
  ret.Insert("            break;");
  ret.Insert("        }");
  ret.Insert("        escaped = false;");
  ret.Insert("      } else {");
  ret.Insert("        if (c == '\\\\') ");
  ret.Insert("          escaped = true;");
  ret.Insert("        else");
  ret.Insert("          sb+=c;");
  ret.Insert("      }");
  ret.Insert("    }");
  ret.Insert("    return sb;");
  ret.Insert("  }");
  ret.Insert("}");
  return conv(ret);
}
static GenerateFiles generateJavaFiles(const AnsiString& file, bool stream, bool json, bool xml, bool isarr, bool strictNull, bool ftl, bool j2j, bool serializable, bool iterable, const DataTypeArray& data) {
  GenerateFiles files;
  if (json)
    files.Insert(GenerateFile("JSONUtil.java", mkJSONUtil(file, j2j, false)));
  for (int i=0;i<data.Size();i++) {
    DataType type = data[i];
    DataTypeKind kind = type.getKind();
    if (kind.isBasic())
      ;
    else if (kind.isExternal())
      ;
    else if (kind.isRecord())
      files.Insert(GenerateFile(data[i].getName()+".java", generateJavaRecordCode(file, false, stream, json, xml, isarr, strictNull, ftl, j2j, serializable, iterable, data, data[i].getName(), data[i].getKind().asRecord())));
    else if (kind.isArray())
      files.Insert(GenerateFile(data[i].getName()+".java", generateJavaArrayCode(file, false, stream, json, xml, isarr, strictNull, ftl, j2j, serializable, iterable, data, data[i].getName(), data[i].getKind().asArray())));
    else if (kind.isVariant())
      files.Insert(GenerateFile(data[i].getName()+".java", generateJavaVariantCode(file, false, stream, json, xml, isarr,  strictNull, ftl, j2j, serializable, iterable, data, data[i].getName(), data[i].getKind().asVariant())));
    else
      throw Exception("");
  }
  return files;
}

static AnsiString mkJavaHeader(const AnsiString& package, bool stream, bool json, bool isarr, bool ftl, bool j2j, bool serializable, bool iterable, const DataTypeArray& data) {
  DynSet<AnsiString> ret;
  ret.Insert("package "+package+";");
  ret.Insert("");
  for (int i=0;i<data.Size();i++)
    if (data[i].getKind().isExternal())
      ret.Insert("import "+data[i].getKind().asExternal().getSource()+";");
  if (stream) {
    ret.Insert("import java.io.DataInputStream;");
    ret.Insert("import java.io.DataOutputStream;");
    ret.Insert("import java.io.IOException;");
  }
  if (isarr)
    ret.Insert("import mednt.mhtml.JArray;");
  if (ftl)
    ret.Insert("import java.util.HashMap;");
  if (iterable)
    ret.Insert("import java.util.Iterator;");
  ret.Insert("import java.util.ArrayList;");
  return conv(ret);
}
static GenerateFiles generateJavaFile(const AnsiString& file, bool stream, bool json, bool xml, bool isarr, bool strictNull, bool ftl, bool j2j, bool serializable, bool iterable, const DataTypeArray& data) {
  AnsiString code = mkJavaHeader(file, stream, json, isarr, ftl, j2j, serializable, iterable, data);
  if (json)
    code+=mkJSONUtil(file, j2j, true);
  for (int i=0;i<data.Size();i++) {
    DataType type = data[i];
    DataTypeKind kind = type.getKind();
    if (kind.isBasic())
      ;
    else if (kind.isExternal())
      ;
    else if (kind.isRecord())
      code+=generateJavaRecordCode(file, true, stream, json, xml, isarr, strictNull, ftl, j2j, serializable, iterable, data, data[i].getName(), data[i].getKind().asRecord());
    else if (kind.isArray())
      code+=generateJavaArrayCode(file, true, stream, json, xml, isarr, strictNull, ftl, j2j, serializable, iterable, data, data[i].getName(), data[i].getKind().asArray());
    else if (kind.isVariant())
      code+=generateJavaVariantCode(file, true, stream, json, xml, isarr, strictNull, ftl, j2j, serializable, iterable, data, data[i].getName(), data[i].getKind().asVariant());
    else
      throw Exception("");
  }
  GenerateFiles files;
  files.Insert(GenerateFile("Data.java", code));
  return files;
}

GenerateFiles generateJavaFiles(const AnsiString& file, bool onefile, bool arr, bool stream, bool json, bool xml, bool strictNull, bool ftl, bool j2j, bool serializable, bool iterable, const DataTypeArray& data) {
  if (onefile)
    return generateJavaFile(file, stream, json, xml, arr, strictNull, ftl, j2j, serializable, iterable, data);
  else
    return generateJavaFiles(file, stream, json, xml, arr, strictNull, ftl, j2j, serializable, iterable, data);
}

#pragma package(smart_init)
