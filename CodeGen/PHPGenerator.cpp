//---------------------------------------------------------------------------

#include "PHPGenerator.h"
#include "Util.h"

//---------------------------------------------------------------------------

bool isBasicType(const DataTypeArray& data, const AnsiString& type) {
  return getTypeByName(data, type).getKind().isBasic();
}

DynSet<AnsiString> generateExternal(const AnsiString& name, const ExternalType& type) {
  DynSet<AnsiString> ret;
  ret.Insert("require_once('"+type.getSource()+"');");
  return ret;
}

DynSet<AnsiString> generateArray(const AnsiString& name, const ArrayType& type, const DataTypeArray& data) {
  DynSet<AnsiString> ret;
  ret.Insert("class "+name+" {");
  ret.Insert("  /*private */var $arr = array();");
  ret.Insert("  /*public */function Size() {");
  ret.Insert("    return count($this->arr);");
  ret.Insert("  }");
  ret.Insert("  /*public */function Insert($obj) {");
  ret.Insert("    $this->arr[] = $obj;");
  ret.Insert("  }");
  ret.Insert("  /*public */function Get($ix) {");
  ret.Insert("    $l = count($this->arr);");
  ret.Insert("    if (0<=$ix && $ix<$l)");
  ret.Insert("      return $this->arr[$ix];");
  ret.Insert("    /*throw \""+name+"::Get(\".$ix.\")\";*/");
  ret.Insert("  }");
  ret.Insert("  /*public */function Put($ix, $_v) {");
  ret.Insert("    $l = count($this->arr);");
  ret.Insert("    if (0<=$ix && $ix<$l)");
  ret.Insert("      $this->arr[$ix] = $_v;");
  ret.Insert("    /*throw \""+name+"::Put(\".$ix.\")\";*/");
  ret.Insert("  }");
  ret.Insert("  /*public */function Delete($ix) {");
  ret.Insert("    $l = count($this->arr);");
  ret.Insert("    if (0<=$ix && $ix<$l) {");
  ret.Insert("      $this->arr[$ix] = $this->arr[$l - 1];");
  ret.Insert("      array_pop($this->arr);");
  ret.Insert("    }");
  ret.Insert("    /*throw \""+name+"::Delete(\".$ix.\")\";*/");
  ret.Insert("  }");
  ret.Insert("  /*public */function toXML() {");
  ret.Insert("    $xml = '<"+name+">';");
  ret.Insert("    $l = count($this->arr);");
  ret.Insert("    for ($i=0;$i<$l;$i++)");
  if (isBasicType(data, type.getType()))
    ret.Insert("      $xml .= '<"+type.getType()+"><![CDATA[' . $this->arr[$i] . ']]></"+type.getType()+">';");
  else
    ret.Insert("      $xml .= $this->arr[$i]->toXML();");
  ret.Insert("    $xml .= '</"+name+">';");
  ret.Insert("    return $xml;");
  ret.Insert("  }");
  ret.Insert("  /*public */function toString() {");
  ret.Insert("    return serialize($this);");
  ret.Insert("  }");
  ret.Insert("  /*public static */function fromString($str) {");
  ret.Insert("    return unserialize($str);");
  ret.Insert("  }");
  ret.Insert("  /*public */function toArray() {");
  ret.Insert("    $ret = Array();");
  ret.Insert("    $l = count($this->arr);");
  ret.Insert("    for ($i=0;$i<$l;$i++)");
  if (isBasicType(data, type.getType()))
    ret.Insert("      $ret[] = $this->arr[$i];");
  else
    ret.Insert("      $ret[] = $this->arr[$i]->toArray();");
  ret.Insert("    return $ret;");
  ret.Insert("  }");
  ret.Insert("  /*public static*/function fromArray($ret) {");
  ret.Insert("    $arr = new "+name+"();");
  ret.Insert("    $l = count($ret);");
  ret.Insert("    for ($i=0;$i<$l;$i++)");
  if (isBasicType(data, type.getType()))
    ret.Insert("      $arr->Insert($ret[$i]);");
  else
    ret.Insert("      $arr->Insert("+type.getType()+"::fromArray($ret[$i]));");
  ret.Insert("    return $arr;");
  ret.Insert("  }");
  ret.Insert("}");
  return ret;
}

AnsiString mkParam(const RecordField& field) {
  return "$" + field.getName();
}

AnsiString mkParamList(const RecordType& type) {
  AnsiString params = mkParam(type[0]);
  for (int i=1;i<type.Size();i++)
    params += ", " + mkParam(type[i]);
  return params;
}

DynSet<AnsiString> generateRecord(const AnsiString& name, const RecordType& type, const DataTypeArray& data) {
  DynSet<AnsiString> ret;
  ret.Insert("class "+name+" {");
  ret.Insert("  /*private */var $_arr = array();");
  ret.Insert("  /*public */function "+name+"("+mkParamList(type)+") {");
  for (int i=0;i<type.Size();i++)
    ret.Insert("    $this->_arr['"+type[i].getName()+"'] = $"+type[i].getName()+";");
  ret.Insert("  }");
  for (int i=0;i<type.Size();i++) {
    ret.Insert("  /*public */function get"+cap1st(type[i].getName())+"() {");
    ret.Insert("    return $this->_arr['"+type[i].getName()+"'];");
    ret.Insert("  }");
  }
  for (int i=0;i<type.Size();i++) {
    ret.Insert("  /*public */function set"+cap1st(type[i].getName())+"($_v) {");
    ret.Insert("    $this->_arr['"+type[i].getName()+"'] = $_v;");
    ret.Insert("  }");
  }
  ret.Insert("  /*public */function toXML() {");
  ret.Insert("    $xml = '<"+name+">';");
  for (int i=0;i<type.Size();i++)
    if (isBasicType(data, type[i].getType()))
      ret.Insert("    $xml .= '<"+type[i].getName()+"><![CDATA[' .$this->_arr['"+type[i].getName()+"'] . ']]></"+type[i].getName()+">';");
    else
      ret.Insert("    $xml .= '<"+type[i].getName()+">' .$this->_arr['"+type[i].getName()+"']->toXML(). '</"+type[i].getName()+">';");
  ret.Insert("    $xml .= '</"+name+">';");
  ret.Insert("    return $xml;");
  ret.Insert("  }");
  ret.Insert("  /*public */function toString() {");
  ret.Insert("    return serialize($this);");
  ret.Insert("  }");
  ret.Insert("  /*public static */function fromString($str) {");
  ret.Insert("    return unserialize($str);");
  ret.Insert("  }");
  ret.Insert("  /*public */function toArray() {");
  ret.Insert("    $ret = Array();");
  for (int i=0;i<type.Size();i++)
    if (isBasicType(data, type[i].getType()))
      ret.Insert("    $ret['"+type[i].getName()+"'] = $this->_arr['"+type[i].getName()+"'];");
    else
      ret.Insert("    $ret['"+type[i].getName()+"'] = $this->_arr['"+type[i].getName()+"']->toArray();");
  ret.Insert("    return $ret;");
  ret.Insert("  }");
  ret.Insert("  /*public static*/function fromArray($ret) {");
  for (int i=0;i<type.Size();i++)
    if (isBasicType(data, type[i].getType()))
      ret.Insert("    $_f_"+AnsiString(i)+" = $ret['"+type[i].getName()+"'];");
    else
      ret.Insert("    $_f_"+AnsiString(i)+" = "+type[i].getType()+"::fromArray($ret['"+type[i].getName()+"']);");
  ret.Insert("    return new "+name+"(");
  for (int i=0;i<type.Size();i++)
    ret.Insert("      $_f_" + AnsiString(i) + ((i==type.Size()-1) ? "" : ","));
  ret.Insert("    );");
  ret.Insert("  }");
  ret.Insert("}");
  return ret;
}

DynSet<AnsiString> generateVariant(const AnsiString& name, const VariantType& type, const DataTypeArray& data) {
  DynSet<AnsiString> ret;
  ret.Insert("class "+name+" {");
  ret.Insert("  /*private */var $type;");
  ret.Insert("  /*private */var $obj;");
  for (int i=0;i<type.Size();i++) {
    ret.Insert("  /*public */function is"+cap1st(type[i].getName())+"() {");
    ret.Insert("    return $this->type=="+AnsiString(i)+";");
    ret.Insert("  }");
    if (type[i].getKind().isType()) {
      ret.Insert("  /*public */function as"+cap1st(type[i].getName())+"() {");
      ret.Insert("    if ($this->type=="+AnsiString(i)+")");
      ret.Insert("      return $this->obj;");
      ret.Insert("    /*throw "+name+"::as"+cap1st(type[i].getName())+";*/");
      ret.Insert("  }");
    }
  }
  ret.Insert("  /*public */function toXML() {");
  ret.Insert("    $xml = '<"+name+">';");
  for (int i=0;i<type.Size();i++) {
    ret.Insert("    "+((i>0) ? AnsiString("else ") : AnsiString(""))+"if ($this->type=="+AnsiString(i)+")");
    if (type[i].getKind().isEmpty()) {
      ret.Insert("      $xml .= '<"+type[i].getName()+"/>';");
    } else if (type[i].getKind().isType()) {
      if (isBasicType(data, type[i].getKind().asType()))
        ret.Insert("      $xml .= '<"+type[i].getName()+"><![CDATA[' . $this->obj . ']]></"+type[i].getName()+">';");
      else
        ret.Insert("      $xml .= '<"+type[i].getName()+">' . $this->obj->toXML() . '</"+type[i].getName()+">';");
    } else
      throw Exception("");
  }
  ret.Insert("    else");
  ret.Insert("      /*throw '"+name+"::toXML('.$this->type.')'*/;");
  ret.Insert("    $xml .= '</"+name+">';");
  ret.Insert("    return $xml;");
  ret.Insert("  }");
  ret.Insert("  /*public */function toString() {");
  ret.Insert("    return serialize($this);");
  ret.Insert("  }");
  ret.Insert("  /*public static */function fromString($str) {");
  ret.Insert("    return unserialize($str);");
  ret.Insert("  }");
  ret.Insert("  /*public */function toArray() {");
  ret.Insert("    $ret = Array();");
  ret.Insert("    $ret['type'] = $this->type;");
  for (int i=0;i<type.Size();i++) {
    ret.Insert("    "+((i>0) ? AnsiString("else ") : AnsiString(""))+"if ($this->type=="+AnsiString(i)+")");
    if (type[i].getKind().isEmpty()) {
      ret.Insert("      ;");
    } else if (type[i].getKind().isType()) {
      if (isBasicType(data, type[i].getKind().asType()))
        ret.Insert("      $ret['value'] = $this->obj;");
      else
        ret.Insert("      $ret['value'] = $this->obj->toArray();");
    } else
      throw Exception("");
  }
  ret.Insert("    else");
  ret.Insert("      /*throw '"+name+"::toXML('.$this->type.')'*/;");
  ret.Insert("    return $ret;");
  ret.Insert("  }");
  ret.Insert("  /*public static*/function fromArray($ret) {");
  ret.Insert("    $v = new "+name+"();");
  ret.Insert("    $v->type = $ret['type'];");
  for (int i=0;i<type.Size();i++) {
    ret.Insert("    "+((i>0) ? AnsiString("else ") : AnsiString(""))+"if ($v->type=="+AnsiString(i)+")");
    if (type[i].getKind().isEmpty()) {
      ret.Insert("      ;");
    } else if (type[i].getKind().isType()) {
      if (isBasicType(data, type[i].getKind().asType()))
        ret.Insert("      $v->obj = $ret['value'];");
      else
        ret.Insert("      $v->obj = "+type[i].getKind().asType()+"::fromArray($ret['value']);");
    } else
      throw Exception("");
  }
  ret.Insert("    else");
  ret.Insert("      /*throw '"+name+"::toXML('.$this->type.')'*/;");
  ret.Insert("    return $v;");
  ret.Insert("  }");
  
  for (int i=0;i<type.Size();i++)
    if (type[i].getKind().isEmpty()) {
      ret.Insert("  /*static public */function create"+cap1st(type[i].getName())+"() {");
      ret.Insert("    $v = new "+name+";");
      ret.Insert("    $v->type = "+AnsiString(i)+";");
      ret.Insert("    return $v;");
      ret.Insert("  }");
    } else if (type[i].getKind().isType()) {
      ret.Insert("  /*static public */function create"+cap1st(type[i].getName())+"($obj) {");
      ret.Insert("    $v = new "+name+";");
      ret.Insert("    $v->type = "+AnsiString(i)+";");
      ret.Insert("    $v->obj = $obj;");
      ret.Insert("    return $v;");
      ret.Insert("  }");
    } else
      throw Exception("");
  ret.Insert("}");
  return ret;  
}

DynSet<AnsiString> generateType(const DataType& type, const DataTypeArray& data) {
  DynSet<AnsiString> ret;
  AnsiString name = type.getName();
  DataTypeKind kind = type.getKind();
  ret.Insert("//------------------------"+name+"------------------------");
  if (kind.isBasic())
    ;
  else if (kind.isExternal())
    ret += generateExternal(name, kind.asExternal());
  else if (kind.isArray())
    ret += generateArray(name, kind.asArray(), data);
  else if (kind.isRecord())
    ret += generateRecord(name, kind.asRecord(), data);
  else if (kind.isVariant())
    ret += generateVariant(name, kind.asVariant(), data);
  else
    throw Exception("generateType");
  ret.Insert("//-------------------------------------------------------");
  return ret;
}

DynSet<AnsiString> generatePHPFile(const AnsiString& file, const DataTypeArray& data) {
  DynSet<AnsiString> ret;

  ret.Insert("<?");
  for (int i=0;i<data.Size();i++)
    ret += generateType(data[i], data);
  ret.Insert("?>");

  return ret;
}

#pragma package(smart_init)
