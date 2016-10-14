//---------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include "DbGen.h"

using namespace std;

static void debug(AnsiString msg) {
  printf("%s\n", msg.c_str());
  fflush(stdout);
}

static AnsiString clearString(AnsiString str) {
  int ix = str.Pos(" ");
  if (ix <= 0)
    return str;
  return str.SubString(1, ix - 1);
}

static AnsiString parseSql(AnsiString sql) {
  for (int i = 1; i < sql.Length() - 1; i++) {
    if (sql[i] == '\n' || sql[i] == '\r') {
      sql = sql.SubString(1, i - 1) + (sql.SubString(i + 1, sql.Length() - i));
      i--;
    }
  }
  return sql;
}

static void doOpen(fstream& f, const AnsiString& InputFile) {
  f.open(InputFile.c_str(), ios::out | ios::trunc);
  if (!f.is_open())
    throw Exception("Cant open InputFile " + InputFile);
}

static void al(fstream& f, const AnsiString& l) {
  f << l.c_str() << endl;
}

static AnsiString typeMapper(const AnsiString& t) {
  if (t == "string")
    return "String";
  if (t == "bool")
    return "boolean";
  else
    return t;
}

static AnsiString typeMapper(const SelectParamType& t) {
  if (t.isPlain())
    return typeMapper(t.asPlain());
  else if (t.isArray())
    return typeMapper(t.asArray()) + "[]";
  else
    throw Exception("typeMapper::SelectParamType");
}

static AnsiString toUpper(const AnsiString& str) {
  AnsiString ret = str;
  if (ret.Length()>1 && ret[1]>='a' && ret[1]<='z')
    ret[1] -= 32;
  return ret;
}
AnsiString toLower(const AnsiString& str) {
  AnsiString ret = str;
  if(ret.Length()>1 && ret[1] >= 'A' && ret[1] <= 'Z')
    ret[1] += 32;
  return ret;
}
static bool isRaw(const AnsiString& t) {
  return t == "int" || t == "string" || t == "bool";
}

static const OutputFile& getJavaSyncOutputFile(const DbFile& dbFile) {
  for(int i=0;i<dbFile.getOutputFiles().Size();i++) {
    if(dbFile.getOutputFiles()[i].getKind().isJavaSync())
      return dbFile.getOutputFiles()[i];
  }
  throw Exception("OutputFile not found");
}

static const OutputFile& getJavaProcessorOutputFile(const DbFile& dbFile) {
  for(int i=0;i<dbFile.getOutputFiles().Size();i++) {
    if(dbFile.getOutputFiles()[i].getKind().isJavaApiProcessor())
      return dbFile.getOutputFiles()[i];
  }
  throw Exception("OutputFile not found");
}

static const SelectParams& getElemParams(const Elem& e) {
  if(e.isSelect())  {
    return e.asSelect().getParams();
  } else if(e.isInsert())  {
    return e.asInsert().getParams();
  } if(e.isUpdate())  {
    return e.asUpdate().getParams();
  } if(e.isDelete())  {
    return e.asDelete().getParams();
  }
  throw Exception("getElemParams::not found");
}

static AnsiString getElemName(const Elem& e) {
  if(e.isSelect())  {
    return e.asSelect().getName();
  } else if(e.isInsert())  {
    return e.asInsert().getName();
  } if(e.isUpdate())  {
    return e.asUpdate().getName();
  } if(e.isDelete())  {
    return e.asDelete().getName();
  }
  throw Exception("getElemName::not found");
}

static AnsiString mkParams(const SelectParams& params) {
  AnsiString t;
  for (int i = 0; i < params.Size(); i++)
    t += ", " + typeMapper(params[i].getType()) + " " + params[i].getName();
  return t;
}

static const DataType& getType(const DataTypeArray& types, const AnsiString& name) {
  for (int i = 0; i < types.Size(); i++)
    if (types[i].getName() == name)
      return types[i];
  throw Exception("Type not found [" + name + "]");
}

static const DataType& getRecord(const DataTypeArray& types, const AnsiString& name) {
  const DataType& e = getType(types, name);
  if (!e.getKind().isRecord())
    throw Exception("Record not found [" + name + "]");
  return e;
}

static int getFiledPosByName(AnsiString name, const RecordType& relems) {
  for (int i = 0; i < relems.Size(); i++)
    if (relems[i].getName() == name)
      return i;
  throw Exception("getFiledTypeByName::not found " + name);
}

static AnsiString getFiledTypeByName(AnsiString name, const RecordType& relems) {
  int ix = getFiledPosByName(name, relems);
  if (ix >= 0)
    return relems[ix].getType();
  throw Exception("getFiledTypeByName::not found " + name);
}

static AnsiString clearChildName(const AnsiString& str) {
  AnsiString childType = str;
  if (childType != "") {
    AnsiString parentKeyWork = "child";
    if (childType.Pos(parentKeyWork) > 0) {
      str = childType.SubString(childType.Pos(parentKeyWork) + parentKeyWork.Length() + 1, childType.Length() - parentKeyWork.Length() - childType.Pos(parentKeyWork) + 1);
    }
  }
  return str;
}

static AnsiString clearParentName(const AnsiString& str) {
  AnsiString childType = str;
  if (childType != "") {
    AnsiString parentKeyWork = "parent";
    if (childType.Pos(parentKeyWork) > 0) {
      str = childType.SubString(childType.Pos(parentKeyWork) + parentKeyWork.Length() + 1, childType.Length() - parentKeyWork.Length() - childType.Pos(parentKeyWork) + 1);
    }
  }
  return str;
}

static AnsiString convDbResType(const AnsiString& typeName, const AnsiString& access) {
  if (typeName == "string")
    return "_res.s(" + access + ")";
  if (typeName == "int")
    return "_res.i(" + access + ")";
  if (typeName == "bool")
    return "_res.i(" + access + ") == 1";
  throw Exception("convDbResType ::" + typeName + " " + access);
}
static AnsiString mkSelectNewRecord(const DataTypeArray& types, const Joins& joins, const DataType& returnObjType, const AnsiString& row, int& column) {
  /*
  * Przygotowanie nowej instancji obiektu (rekordu)
  * types - tablica typów (do walidacji typów)
  * joins - informacja o JOINach związanych z aktualnie generowanym zapytaniem
  * returnObjType - typ nowej instancji tworzonego obiektu
  * row - numer wiersza z którego pobierane są dane dla pól typu podstawowego
  * column - numer kolejnej kolumny z której pobrane będą dane dla pola typu podstawowego
  */
  const RecordType& elems = returnObjType.getKind().asRecord();
  AnsiString newInstanceString;
  int joinPos = 0;
  for (int i = 0; i < elems.Size(); i++) {
    const RecordField& e = elems[i];
    newInstanceString += (i == 0) ? "" : ",";
    if (!isRaw(e.getType())) {
      const DataType& et = getType(types, e.getType());
      if (et.getKind().isArray()) {
        if (joins[joinPos].getParentName() == "")
          newInstanceString += "arr" + AnsiString(joinPos++);
        else {
          AnsiString fieldName = clearParentName(joins[joinPos].getParentName());
          AnsiString fieldType = getFiledTypeByName(fieldName, elems);
          AnsiString fieldPos = AnsiString(getFiledPosByName(fieldName, elems));
          newInstanceString += "hmap" + AnsiString(joinPos) + ".get("+convDbResType(fieldType , "i," + fieldPos) + ") != null ? hmap" + AnsiString(joinPos++) + ".get("+convDbResType(fieldType , "i," + fieldPos) + ") : new " + et.getName() + "()";
        }
      } else if (et.getKind().isRecord()) {
        if(joinPos >= joins.Size() || joins[joinPos].getFieldName() != e.getName()) {
          newInstanceString += mkSelectNewRecord(types, joins, getType(types, e.getType()), row, column);
        } else if (joins[joinPos].getParentName() == "")
          newInstanceString += "arr" + AnsiString(joinPos++);
        else {
          AnsiString fieldName = clearParentName(joins[joinPos].getParentName());
          AnsiString fieldType = getFiledTypeByName(fieldName, elems);
          AnsiString fieldPos = AnsiString(getFiledPosByName(fieldName, elems));
          newInstanceString += "hmap" + AnsiString(joinPos++) + ".get("+convDbResType(fieldType, "i," + fieldPos) + ").Get(0) != null ? hmap" + AnsiString(joinPos++) + ".get("+convDbResType(fieldType, "i," + fieldPos) + ").Get(0) : throw new RuntimeException(\"Join record fail\")";
        }
      } else 
        throw Exception("Type not supported as field");
    } else {
      newInstanceString += convDbResType(e.getType(), "" + row + ", " + AnsiString(column++));
    }
  }
  return "new " + returnObjType.getName() + "(" + newInstanceString + ")";
}

static AnsiString getSelectReturnType(const Elems& felems, const AnsiString& methodName) {
  for (int j = 0; j < felems.Size(); j++)
    if (felems[j].isSelect() && felems[j].asSelect().getName() == methodName)
      return felems[j].asSelect().getType();
  throw Exception ("Method not found " + methodName);
}

static const Elem& getSelectByName(const Elems& felems, const AnsiString& methodName) {
  for (int j = 0; j < felems.Size(); j++)
    if (felems[j].isSelect() && felems[j].asSelect().getName() == methodName)
      return felems[j];
}

static AnsiString mkJoinCallParam(fstream& fs,  const Select& s, const Join& join, AnsiString typeName, const RecordType& relems, const Elems& felems, const int& paramNumber) {
  AnsiString thisKeyWord = "this.";
  AnsiString sqlKeyWord = "sql.";
  if (typeName.Pos(thisKeyWord) > 0) {
    typeName = typeName.SubString((thisKeyWord).Length() + 1, typeName.Length() - thisKeyWord.Length() + 1);
    for (int i = 0; i < relems.Size(); i++) {
      if (relems[i].getName() == typeName) {
        const Select& joinSelect = getSelectByName(felems, join.getMethodName()).asSelect();
        AnsiString argType = typeMapper(joinSelect.getParams()[paramNumber].getType());
        if (isRaw(toLower(argType))) {
          return convDbResType(toLower(argType), "0, " + AnsiString(i));
        }
        else {
          AnsiString obj = join.getMethodName() + "obj" + AnsiString(i);
          AnsiString argContructor = "[_res.rows()]";
          if (argType.Pos("[") <= 0) {
            al(fs, "    " + argType + "[] " + obj + " = new " + argType + " " + argContructor + ";");
            al(fs, "    for (int i=0;i<_res.rows();i++)");
            al(fs, "      " + obj +  "[i]= " +convDbResType(toLower(argType), "i, " + AnsiString(i))+ ";");
            return obj;
          }
          else {
            AnsiString arrayType = argType.SubString(1, argType.Pos("[") - 1);
            al(fs, "    " + argType + " " + obj + + " = new " + arrayType + argContructor + ";");
            al(fs, "    for (int i=0;i<_res.rows();i++)");
            al(fs, "      " + obj +  "[i]= "+convDbResType(toLower(arrayType), "i, " + AnsiString(i)) + ";");
            return obj;
          }
        }
      }
    }
  } else if (typeName.Pos(sqlKeyWord) > 0) {
    //todo
  } else
    return typeName;

  throw Exception("Field " + typeName + " not found in record");
}

static AnsiString mkJoinCallParams(fstream& fs,  const Select& s, const Join& join, const RecordType& relems, const Elems& felems) {
  StringArray arr = join.getParams();
  if(arr.Size()==0)
    return "";
  int paramNumber = 0;
  AnsiString ret = ",";
  for(int i=0;i<arr.Size();i++)
    ret += mkJoinCallParam(fs, s, join, arr[i], relems, felems, paramNumber++) + (i<arr.Size()-1 ? "," : "");
  return ret;
}

static void prepareJoin(fstream& fs, const Select& s, const InputFile& f, const Joins& joins, const RecordType& relems, const int& joinNumber) {
  al(fs, "    " + getSelectReturnType(f.getElems(), joins[joinNumber].getMethodName()) + " arr" + AnsiString(joinNumber) + " =" + joins[joinNumber].getMethodName() + "(_db " + mkJoinCallParams(fs, s, joins[joinNumber], relems, f.getElems()) + ");");
  AnsiString type = getSelectReturnType(f.getElems(), joins[joinNumber].getMethodName());
  AnsiString parentType = joins[joinNumber].getParentName();
  AnsiString childType = joins[joinNumber].getChildName();
  if (parentType != "") {
    AnsiString parentKeyWork = "parent";
    if (parentType.Pos(parentKeyWork) > 0) {
      parentType = parentType.SubString(parentType.Pos(parentKeyWork) + parentKeyWork.Length() + 1, parentType.Length() - parentKeyWork.Length() - parentType.Pos(parentKeyWork) + 1);
    }
    AnsiString childKeyWork = "child";
    if (childType.Pos(childKeyWork) > 0) {
      childType = childType.SubString(childType.Pos(childKeyWork) + childKeyWork.Length() + 1, childType.Length() - childKeyWork.Length() - childType.Pos(childKeyWork) + 1);
    }
    if (getFiledTypeByName(parentType, relems) != "string")
      al(fs, "    HashMap<Integer, " + type + "> hmap" + AnsiString(joinNumber) + " = new HashMap<Integer, " + type + ">();");
    else
      al(fs, "    HashMap<" + typeMapper(getFiledTypeByName(parentType, relems)) + ", " + type + "> hmap" + AnsiString(joinNumber) + " = new HashMap<" + typeMapper(getFiledTypeByName(parentType, relems)) + ", " + type + ">();");
    al(fs, "    for (int i=0;i<arr" + AnsiString(joinNumber) + ".Size();i++) {");
    al(fs, "      " + type + " s = hmap" + AnsiString(joinNumber) + ".get(arr" + AnsiString(joinNumber) + ".Get(i).get" + toUpper(childType) + "());");
    al(fs, "      if(s == null)");
    al(fs, "      s = new " + type + "();");
    al(fs, "      s.Insert(arr" + AnsiString(joinNumber) + ".Get(i));");
    al(fs, "      hmap" + AnsiString(joinNumber) + ".put(arr" + AnsiString(joinNumber) + ".Get(i).get" + toUpper(childType) + "(), s);");
    al(fs, "    }");
  }
}

static void validateSelectSql(AnsiString sqlString, const RecordType& returnType) {
  debug("[INFO] Validacja zapytań\n");
  int basicFields = 0;
  for (int i = 0; i < returnType.Size(); i++) {
    if (isRaw(returnType[i].getType()))
      basicFields++;
  }
  DynSet<AnsiString> set;
  sqlString = sqlString.SubString(2, sqlString.Length() - 2);
  set.Insert(sqlString);
  LineStream stream(set);
  Sql sql = sqlProcessData(stream);
  //if (!sql.isSelectQuery())
    //throw Exception(sqlString + "is not select query");
  if (sql.asSelectQuery().getFields().Size() != basicFields) {
    for (int i = 0; i < sql.asSelectQuery().getFields().Size(); i++) {
      //if(sql.asSelectQuery().getFields()[i].getFieldKind().isAllField())
        //throw Exception(sqlString + " '*' not allowed in query, replace with columns/fields declarations");
    }
    //throw Exception(sqlString + " bad fields count");
  }
}

static void prepareSqlCall(fstream& fs, const SelectParams& params, const AnsiString& sql, const bool& isSelect, const OutputFile& out) {
  al(fs, "    HashMap<String, String> _pmap = new HashMap<String, String>();");
  for (int i = 0; i < params.Size(); i++) {
    const SelectParamType& t = params[i].getType();
    if (t.isPlain()) {
      AnsiString tt = t.asPlain();
      if (tt != "string")
        al(fs, "    _pmap.put(\"" + params[i].getName() + "\", \"\" + " + params[i].getName() + ");");
      else
        al(fs, "    _pmap.put(\"" + params[i].getName() + "\", \"\" + _db.escape(" + params[i].getName() + "));");
    }
    else if (t.isArray()) {
      AnsiString tt = t.asArray();
      if (tt != "string")
        al(fs, "    _pmap.put(\"" + params[i].getName() + "\", \"\" + " + out.getName() + ".boxI(" + params[i].getName() + "));");
      else
        al(fs, "    _pmap.put(\"" + params[i].getName() + "\", \"\" + " + out.getName() + ".boxS(_db, " + params[i].getName() + "));");
    }
    else
      throw Exception("getSelect::SelectParamType");
  }
  if(!isSelect)
    al(fs, "    _db.execute(" + out.getName() + ".prepare(" + parseSql(sql) + ", _pmap));");
  else
    al(fs, "    SDBResult _res = _db.query(" + out.getName() + ".prepare(" + parseSql(sql) + ", _pmap));");
}

static void genUpdate(fstream& fs, const Update& u, const DataTypeArray& types, const DbFile& dbFile, const OutputFile& out) {
  al(fs, "  static public void " + u.getName() + "(DBConn _db" + mkParams(u.getParams()) + ") {");
  prepareSqlCall(fs, u.getParams(), u.getQuery(), false, out);
  al(fs, "  }");
}

static void genDelete(fstream& fs, const Delete& u, const DataTypeArray& types, const DbFile& dbFile, const OutputFile& out) {
  al(fs, "  static public void " + u.getName() + "(DBConn _db" + mkParams(u.getParams()) + ") {");
  prepareSqlCall(fs, u.getParams(), u.getQuery(), false, out);
  al(fs, "  }");
}


static void genInsert(fstream& fs, const Insert& i, const DataTypeArray& types, const DbFile& dbFile, const OutputFile& out) {
  al(fs, "  static public void " + i.getName() + "(DBConn _db" + mkParams(i.getParams()) + ") {");
  prepareSqlCall(fs, i.getParams(), i.getQuery(), false, out);
  al(fs, "  }");
}

static void genSelect(fstream& fs, const Select& s, const DataTypeArray& types, const DbFile& dbFile, const OutputFile& out) {
  const InputFile& in = dbFile.getInputFile();
  const DataType& retType = getType(types, s.getType());
  const SelectParams& params = s.getParams();
  al(fs, "  static public " + typeMapper(s.getType()) + " " + s.getName() + "(DBConn _db" + mkParams(params) + ") {");
  if(s.getQuery().Length() > 0)
     prepareSqlCall(fs, s.getParams(), s.getQuery(), true, out);
  
  const Joins& joins = s.getJoins();
  if(joins.Size() > 0) {
    /*
    * 1. Sprawdzamy typ zwracanego obiektu,
    * dozwolony rekord i tablica
    * 2. Zapamiętujemy w 're': 
    * w przypadku gdy zapytanie zwraca tablicę typ elemntów tablicy
    * w przypadku gdy zapytanie zwraca rekord typ rekordu
    */
    if(retType.getKind().isArray()) {
      al(fs, "    if(_res.rows()==0)");
      al(fs, "      return new " + retType.getName() + "();");
    }
    const RecordType& re = RecordType();
    if (retType.getKind().isRecord()) {
      re = retType.getKind().asRecord();
    } else if (retType.getKind().isArray()) {
      re = getRecord(types, retType.getKind().asArray().getType()).getKind().asRecord();
    } else
      throw Exception("Bad type at " + s.getName());

    /*
    * Dodanie kodu przygotowującego
    * dane pobrane z JOINów
    */
    for (int i = 0; i < joins.Size(); i++)
      prepareJoin(fs, s, in, joins, re, i);
  }

  /*
  * Walidacja Sqla oraz zwracanie obiektu (wyłączona)
  */
  if (retType.getKind().isRecord()) {
    //validateSelectSql(s.getQuery(), retType.getKind().asRecord()); //todo dodać joiny w parserze sql + walidacja joinow
    if(s.getQuery().Length() > 0) {
      al(fs, "    if (_res.rows()<1)");
      al(fs, "      throw new RuntimeException(\"" + s.getName() + " - result not found\");");
    }
    int column = 0;
    al(fs, "    " + retType.getName() + " _ret = " + mkSelectNewRecord(types, joins, retType, "0", column) + ";");
  } else if (retType.getKind().isArray()) {
    
    const ArrayType& a = retType.getKind().asArray();
    if(isRaw(a.getType())) {
      //validateSelectSql(s.getQuery(), r.getKind().asRecord()); //todo dodać joiny w parserze sql + walidacja joinow
      al(fs, "    " + retType.getName() + " _ret = new " + retType.getName() + "();");
      al(fs, "    for (int i=0;i<_res.rows();i++)");
      al(fs, "      _ret.Insert("+convDbResType(a.getType(), "i,0")+");");
    } else {
      
      const ArrayType& a = retType.getKind().asArray();
      const DataType& r = getRecord(types, a.getType());
      
      //validateSelectSql(s.getQuery(), r.getKind().asRecord()); //todo dodać joiny w parserze sql + walidacja joinow
      al(fs, "    " + retType.getName() + " _ret = new " + retType.getName() + "();");
      al(fs, "    for (int i=0;i<_res.rows();i++)");
      int column = 0;
      al(fs, "      _ret.Insert(" + mkSelectNewRecord(types, joins, r, "i", column) + ");");
      
    }
   
  } else if(retType.getKind().isBasic()) {
    al(fs, "    if (_res.rows()<1)");
    al(fs, "      throw new RuntimeException(\"" + s.getName() + " - result not found\");");
    al(fs, "    " + typeMapper(retType.getKind().asBasic()) + " _ret =" + convDbResType(retType.getKind().asBasic(), "0, 0") + ";");
  } else
    throw Exception("Bad type at " + s.getName());
  al(fs, "    return _ret;");
  al(fs, "  }");
}

void generateSyncFile(const DbFile& dbFile, const OutputFile& out, const DataTypeArray& types) {
  std::fstream fs;
  doOpen(fs,  out.getName() + ".java");
  al(fs, "package " + out.getPackage() + ";");
  al(fs, "import java.util.ArrayList;");
  al(fs, "import java.util.HashMap;");
  al(fs, "import java.util.Map;");
  al(fs, "import mednt.dbconn.DBConn;");
  al(fs, "import mednt.dbconn.SDBResult;");
  for(int i=0;i<out.getImports().Size();i++)
    al(fs, out.getImports()[i]); 
  al(fs, "public class " + out.getName() + " {");
  const Elems& elems = dbFile.getInputFile().getElems();
  for (int i = 0; i < elems.Size(); i++) {
    
    Elem e = elems[i];
    if (e.isSelect())
      genSelect(fs, e.asSelect(), types, dbFile, out);
    else if (e.isInsert())
      genInsert(fs, e.asInsert(), types, dbFile, out);
    else if (e.isUpdate())
      genUpdate(fs, e.asUpdate(), types, dbFile, out);
    else if (e.isDelete())
      genDelete(fs, e.asDelete(), types, dbFile, out);
  }
  al(fs, "}");
}

static void generateJavaApiProcessor(const DbFile& dbFile, const OutputFile& out, const DataTypeArray& types) {
  const InputFile& in = dbFile.getInputFile();
  std::fstream fs;
  doOpen(fs, out.getName() + ".java");
  al(fs, "package " + out.getPackage() + ";");
  al(fs, "import java.util.ArrayList;");
  al(fs, "import java.util.HashMap;");
  al(fs, "import java.util.Map;");
  al(fs, "import data.*;");
  al(fs, "import mednt.dbconn.DBConn;");
  al(fs, "import mednt.dbconn.SDBResult;");
  al(fs, "public class " + out.getName() + " {");
  al(fs, "  public static int[] convCodegenArray(IntArray array) {");
  al(fs, "    int[] ret = new int[array.Size()];");
  al(fs, "    for(int i=0;i<array.Size();i++)");
  al(fs, "      ret[i] = array.Get(i);");
  al(fs, "    return ret;");
  al(fs, "  }");
  al(fs, "  public static boolean[] convCodegenArray(BoolArray array) {");
  al(fs, "    boolean[] ret = new boolean[array.Size()];");
  al(fs, "    for(int i=0;i<array.Size();i++)");
  al(fs, "      ret[i] = array.Get(i);");
  al(fs, "    return ret;");
  al(fs, "  }");
  al(fs, "  public static String[] convCodegenArray(StringArray array) {");
  al(fs, "    String[] ret = new String[array.Size()];");
  al(fs, "    for(int i=0;i<array.Size();i++)");
  al(fs, "      ret[i] = array.Get(i);");
  al(fs, "    return ret;");
  al(fs, "  }");
  al(fs, "  public static String process(DBConn db, String request) throws Exception {");
  al(fs, "      ApiQuery query = ApiQuery.fromJSON(request);");
  al(fs, "      if(query.isSelect()) {");
  al(fs, "        SelectQuery select = query.asSelect();");
  const Elems& elems = in.getElems();
  for (int i = 0; i < elems.Size(); i++) {
    const SelectParams& params = getElemParams(elems[i]);
    AnsiString name = getElemName(elems[i]);
    AnsiString ifStmnt = "";
    AnsiString ifString = "        if(";
    ifString += "\"" + name + "\"" + ".equals(select.getMethodName()) && select.getParams().Size() == " + AnsiString(params.Size());
    if(!elems[i].isSelect())
      ifStmnt = "          " + getJavaSyncOutputFile(dbFile).getName() + "" + "." + name + "(db" + (params.Size() > 0 ?  " ," : "");
    else
      ifStmnt = "          " + elems[i].asSelect().getType() + " result = " + getJavaSyncOutputFile(dbFile).getName() + "" + "." + name + "(db" + (params.Size() > 0 ?  " ," : "");
    for (int j = 0; j < params.Size(); j++) {
      if (typeMapper(params[j].getType()) == "int") {
        ifString += " &&  select.getParams().Get(" + AnsiString(j) + ").isIntParam() ";
        ifStmnt += AnsiString(j>0 ? ", " : "") + "select.getParams().Get(" + AnsiString(j) + ").asIntParam()";
      } else if (typeMapper(params[j].getType()) == "boolean") {
        ifString += " &&  select.getParams().Get(" + AnsiString(j) + ").isStringParam() ";
        ifStmnt += AnsiString(j>0 ? ", " : "") + "select.getParams().Get(" + AnsiString(j) + ").asBoolParam()";
      } else if (typeMapper(params[j].getType()) == "String") {
        ifString += " &&  select.getParams().Get(" + AnsiString(j) + ").isStringParam() ";
        ifStmnt += AnsiString(j>0 ? ", " : "") + "select.getParams().Get(" + AnsiString(j) + ").asStringParam()";
      } else if  (typeMapper(params[j].getType()) == "int[]") {
        ifString += " &&  select.getParams().Get(" + AnsiString(j) + ").isIntAParam() ";
        ifStmnt += AnsiString(j>0 ? ", " : "") + "convCodegenArray(select.getParams().Get(" + AnsiString(j) + ").asIntAParam())";
      } else if  (typeMapper(params[j].getType()) == "String[]") {
        ifString += " &&  select.getParams().Get(" + AnsiString(j) + ").isStringAParam() ";
        ifStmnt += AnsiString(j>0 ? ", " : "") + "convCodegenArray(select.getParams().Get(" + AnsiString(j) + ").asStringAParam())";
      } else if  (typeMapper(params[j].getType()) == "boolean[]") {
        ifString += " &&  select.getParams().Get(" + AnsiString(j) + ").isStringAParam() ";
        ifStmnt += AnsiString(j>0 ? ", " : "") + "convCodegenArray(select.getParams().Get(" + AnsiString(j) + ").asBoolAParam())";
      }
    }
    ifString += ") {";
    ifStmnt += ");";
    al(fs, ifString);
    al(fs, ifStmnt);
    if(!elems[i].isSelect())
    al(fs, "          return \"\";");
    else 
    al(fs, "          return result.toJSON();");
    al(fs, "        }");
  }
  al(fs, "      }");
  al(fs, "    throw new Exception(\"bad request\");");
  al(fs, "  }");
  al(fs, "}");
}

static void generateJavaApiServer(const DbFile& dbFile, const OutputFile& out, const DataTypeArray& types) {
  generateJavaApiProcessor(dbFile, out, types);
}

LineStream readData() {
  DynSet<AnsiString> lines;
  string line;
  while(std::getline(std::cin, line)) {
    lines.Insert(line);
  }
  return LineStream(lines);
}

LineStream readFile(AnsiString path) {
  DynSet<AnsiString> lines;
  ifstream stream(path.c_str());
  if (stream) {
    string line;
    while (getline(stream, line)) {
      lines.Insert(line);
    }
  } else
    throw Exception("InputFile not found " + path);
  stream.close();
  return LineStream(lines);
}

int main(int argc, char* argv[]) {
  debug("Parsowanie pliku zapytań\n");
  LineStream dbFileStream = readData();
  debug("[INFO] Parsowanie zakończone, przetwarzanie\n");
  DbFile f = dbGenProcessData(dbFileStream);
  debug("[INFO] Przetwarzanie zakończone\n");
  debug("[INFO] Parsowanie pliku z danymi\n");
  LineStream appDataFileStream = readFile(f.getInputFile().getAppData());
  DataFileBase dfb = processData(appDataFileStream);
  debug("[INFO] Parsowanie zakończone\n");
  debug("[INFO] Generowanie pliku\n");
  for(int i=0;i<f.getOutputFiles().Size();i++) {
    if(f.getOutputFiles()[i].getKind().isJavaSync()) {
      generateSyncFile(f, f.getOutputFiles()[i], dfb.getTypes());
    }
    if(f.getOutputFiles()[i].getKind().isJavaApiProcessor()) {
      generateJavaApiServer(f, f.getOutputFiles()[i], dfb.getTypes());
    }
  }
}
