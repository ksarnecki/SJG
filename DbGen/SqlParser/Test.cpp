//---------------------------------------------------------------------------

#include "SqlParser.h"
#include "data/SqlParserData.h"
#include <cstdio>
#include <iostream>
//---------------------------------------------------------------------------

LineStream readData() {
  char buf[1024];
  DynSet<AnsiString> ret;
  while (std::cin.getline(buf, 1024))
    ret.Insert(AnsiString(buf).Trim());
  return LineStream(ret);
}

/*
AnsiString dumpOrder(Field f) {
  if (f.getFieldKind().isBasicField()) {
    return "order by name = " + f.getFieldName() + ", column = " + f.getFieldKind().asBasicField().getColumn() + ", table = " + f.getFieldKind().asBasicField().getTable() + " : (Order.basic) ";
  }
  return    "";
}

AnsiString dumpField(Field f) {
  if (f.getFieldKind().isBasicField()) {
    return "field name = " + f.getFieldName() + ", column = " + f.getFieldKind().asBasicField().getColumn() + ", table = " + f.getFieldKind().asBasicField().getTable() + " : (Field.basic) ";
  }
  else if (f.getFieldKind().isQuery()) {
    return "field name = " + f.getFieldName() + ", query = " + f.getFieldKind().asQuery() + " : (Field.query) ";
  }
  else if (f.getFieldKind().isSpecialField()) {
    return "special = " + f.getFieldKind().asSpecialField() + " : (Field.special) ";
  }
 
 return    "";
}

AnsiString dumpCondition(int act, ConditionElems c) {
  printf("%d ", act);
  if (c[act].isField()) {
    return "(" + dumpField(c[act].asField()) + ")";
  } else if (c[act].isAndCondition()) {
    return "(" + dumpCondition (c[act].asAndCondition().getFirst(), c) +" AND " + dumpCondition(c[act].asAndCondition().getSecond(), c) +  ")";
  }
  else if (c[act].isEqualCondition()) {
    return "(" + dumpCondition(c[act].asEqualCondition().getFirst(), c) + " = " + dumpCondition(c[act].asEqualCondition().getSecond(), c) + ")";
  }
  return "";
}

AnsiString dumpTable(Table t) {
  if (t.getKind().isBasic()) {
    return "table = " + t.getKind().asBasic() + " as " + t.getAs() + " : (Table.basic)";
  }
  else {
    return "";
  }
}

void dump(Sql sql) {
 
  if (sql.isSelectQuery()) {
    SelectQuery query = sql.asSelectQuery();
    printf("Query type: SELECT\n");
    for (int i = 0; i < query.getFields().Size(); i++) {
      printf("  %s\n", dumpField(query.getFields()[i]).c_str());
    }
    for (int i = 0; i < query.getTables().Size(); i++) {
      printf("  %s\n", dumpTable(query.getTables()[i]).c_str());
    }
    printf("  %s\n", dumpCondition(query.getCondition().Size()-1, query.getCondition()).c_str());
    for (int i = 0; i < query.getOrders().Size(); i++) {
      printf("  %s\n", dumpOrder(query.getOrders()[i]).c_str());
    }
  } else {
    printf("wtf?\n");
  }
}

*/

int main() {
  printf("Start\n");
  LineStream stream = readData();
  Sql sql = sqlProcessData(stream);
  printf("parsed\n");
  //dump(sql);
  printf("End\n");
}



