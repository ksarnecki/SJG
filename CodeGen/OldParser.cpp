//---------------------------------------------------------------------------

#include "OldParser.h"
#include <cstdio>
//---------------------------------------------------------------------------

int pos(const AnsiString& line, char c) {
  for (int i=1;i<=line.Length();i++)
    if (line[i]==c)
      return i;
  return 0;
}
AnsiString eraseComment(const AnsiString& line) {
    AnsiString ret = line;
    int iy = ret.Pos("//");
    if (iy==0)
        return ret;
  while (ret[iy-1]==' ')
      iy--;
  ret = ret.SubString(1, iy-1);
  return ret;
}
DynSet<AnsiString> readFieldDesc(const AnsiString& line) {
  DynSet<AnsiString> ret;
  int ix = pos(line, ':');
  if (ix==0)
    ret.Insert(line.Trim());
  else {
    ret.Insert(line.SubString(1, ix - 1).Trim());
    ret.Insert(line.SubString(ix + 1, line.Length() - ix).Trim());
  }
  return ret;
}
DynSet< DynSet<AnsiString> > readFieldsDesc(LineStream& stream) {
  DynSet< DynSet<AnsiString> > ret;
  while (stream.getLine()!="*") {
    ret.Insert(readFieldDesc(stream.getLine()));
    stream.next();
  }
  stream.next();
  return ret;
}
ExternalType readExternal(LineStream& stream) {
  AnsiString type = stream.getLine();
  stream.next();
  return ExternalType(type);
}
RecordType readRecord(LineStream& stream) {
  DynSet< DynSet<AnsiString> > lines = readFieldsDesc(stream);
  RecordType ret;
  for (int i=0;i<lines.Size();i++) {
	ret.Insert(RecordField(lines[i][0], lines[i][1]));
  }
    
  return ret;
}
VariantType readVariant(LineStream& stream) {
  DynSet< DynSet<AnsiString> > lines = readFieldsDesc(stream);
  VariantType ret;
  for (int i=0;i<lines.Size();i++)
    if (lines[i].Size()==1)
      ret.Insert(VariantField(lines[i][0], VariantFieldKind::createEmpty()));
    else
      ret.Insert(VariantField(lines[i][0], VariantFieldKind::createType(lines[i][1])));
  return ret;
}
ArrayType readArray(LineStream& stream) {
  AnsiString type = stream.getLine();
  stream.next();
  return ArrayType(type);
}
bool isWhite(int ascii) {
  if(ascii==32)
    return true;
  if(ascii==9)
    return true;
  return false;
}
bool isSpecial(int ascii) {
  return ascii == '{' || ascii == '}' || ascii == ',' || ascii == ':';
}
AnsiString getWord(AnsiString& line, int& ix, int direction=1) {
  AnsiString ret = "";
  if(ix>=line.Length())
    return ret;
  while(line[ix]==32 || line[ix]==9) {
    ix+=direction;
    if(ix>=line.Length() || ix==0)
      break;
  }
  while(line[ix]!=32 && line[ix]!=9) {
    ret += line[ix];
    ix+=direction;
    if(ix>=line.Length() || ix==0)
      break;
  }
  if(direction==-1)
    ix++;
  return ret;
}
int findTypeEnd(AnsiString& line, int ix) {
  int c = 0;
  while(true) {
    if(line[ix]==',' && c == 0)
      return ix-1;
    if(line[ix]=='{')
      c++;
    if(line[ix]=='}') {
      c--;
      if(c==0)
        return ix;
      if(c<0)
        return ix-1;
    }
    if(ix >= line.Length())
      break;
      ix++;
  }
  return 0;
}
struct tmpType {
  AnsiString name;
  DynSet<AnsiString> value;
  DynSet<AnsiString> requiredTypes;
};
DynSet<tmpType> tmpTypes;
DynSet<AnsiString> actTypes;
bool exist(AnsiString& name) {
  for(int i=0;i<actTypes.Size();i++)
    if(actTypes[i]==name)
      return true;
  return false;
}
DynSet<AnsiString> order() {
  DynSet<AnsiString> ret;
  while(tmpTypes.Size()>0) {
    AnsiString emptyType = "";
    for(int i=0;i<tmpTypes.Size();i++) {
      if(tmpTypes[i].requiredTypes.Size()==0) {
        emptyType = tmpTypes[i].name;
        for(int j=0;j<tmpTypes[i].value.Size();j++)
          ret.Insert(tmpTypes[i].value[j]);
        actTypes.Insert(emptyType);
        tmpTypes.Delete(i);
        break;
      }
    }
    if(emptyType == "")
      break;
    for(int i=0;i<tmpTypes.Size();i++) {
      for(int j=0;j<tmpTypes[i].requiredTypes.Size();j++) 
        if(tmpTypes[i].requiredTypes[j] == emptyType) {
          tmpTypes[i].requiredTypes.Delete(j--);    
        }
    }  
  }
  if(tmpTypes.Size()>1) 
    throw Exception("Wrong types depending!");
  if(tmpTypes.Size()==1) {
    actTypes.Insert(tmpTypes[0].name);
    tmpTypes.Delete(0);
  }
  return ret;
}
void parseType(AnsiString line) {
  tmpType t;
  DynSet<AnsiString> ret;
  int ix=1;
  AnsiString name = getWord(line, ix);
  AnsiString tmp = getWord(line, ix);
  AnsiString type = getWord(line, ix);
  ret.Insert(name);
  ret.Insert(type);
  tmp = getWord(line, ix);
  t.name = name;
  if(tmp=="{") {
    while(ix<=line.Length()) {      
      name = getWord(line, ix);
      tmp = getWord(line, ix);
      if(tmp!=":") {
        ret.Insert(name);
        if(tmp=="}")
          break;
      } else {          
        type = getWord(line, ix);
        if(!exist(type))
          t.requiredTypes.Insert(type);
        ret.Insert(name + " : " + type);
        tmp = getWord(line, ix);
        if(tmp=="}")
          break;
      }
    }
    ret.Insert("*");
  }
  if(tmp=="of") {
    ret.Insert(getWord(line, ix));
  }
  t.value = ret;
  tmpTypes.Insert(t);
}
DynSet<AnsiString> parseLine(AnsiString& line) {
  for(int i=1;i<=line.Length();i++) {
    if(isSpecial(line[i]) && i>1 && !isWhite(line[i-1])) {
      line = line.SubString(1, i-1) + " ," + line.SubString(i+1, line.Length()-i);
      i++;
    }
  }
  int ix = line.Length();
  while(ix>0) {
    if(line[ix]=='=') {
	  printf("1.1\n");
      int ex = findTypeEnd(line, ix--);
	  printf("1.2\n");
      getWord(line, ix, -1);
	  printf("1.3\n");
      parseType(line.SubString(ix, ex-ix+1).c_str());
	  printf("1.4\n");
      if(ix<1)
        break;
	   printf("1.5\n");
      getWord(line, ix);
	   printf("1.6\n");
      line = line.SubString(1, ix) + " " + line.SubString(ex+1, line.Length()-ex);
	   printf("1.7\n");
    }
    ix--;
  }
  return order();
}
DynSet<AnsiString> parse(LineStream& stream) {
  DynSet<AnsiString> ret;
  while (!stream.isEof()) {
    AnsiString line = stream.getLine();
    stream.next();
    if(line.Pos("=")>0) {
      while (!stream.isEof()) {
        AnsiString line2 = stream.getLine();
        stream.next();
        line+= " " + line2;
        if(line2=="}")
          break;
      }
      DynSet<AnsiString> par = parseLine(line);
      for(int i=0;i<par.Size();i++)
        ret.Insert(par[i]);
    } else {
      ret.Insert(line);
      actTypes.Insert(line);
    }
  }
  return ret;
}

DataType readType(LineStream& stream) {
  AnsiString name = stream.getLine();
  stream.next();
  AnsiString type = stream.getLine();
  stream.next();
  if (type=="basic")
    return DataType(name, DataTypeKind::createBasic(name));
  else if (type=="external")
    return DataType(name, DataTypeKind::createExternal(readExternal(stream)));
  else if (type=="record")
    return DataType(name, DataTypeKind::createRecord(readRecord(stream)));
  else if (type=="array")
    return DataType(name, DataTypeKind::createArray(readArray(stream)));
  else if (type=="variant")
    return DataType(name, DataTypeKind::createVariant(readVariant(stream)));
  else
    throw Exception("readType(" + type + ")");
}
DataTypeArray readTypeArray(LineStream& stream) {
  DataTypeArray ret;
  while (!stream.isEof()) {
    ret.Insert(readType(stream));
  }
  return ret;
}
DataFileKind mkFileType(const AnsiString& type) {
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
DataFileBase processData(LineStream& stream) {
  DynSet<AnsiString> cleanStream;
  stream.next();
  while(!stream.isEof()) {
    AnsiString line = eraseComment(stream.getLine());
    if(line.Length()>0)
      cleanStream.Insert(line);
    stream.next();
  }
  stream = LineStream(cleanStream);
  stream.next();
  AnsiString file = stream.getLine();
  stream.next();
  AnsiString type = stream.getLine();
  stream.next(); 
  stream = LineStream(parse(stream));
  stream.next(); 
  return DataFileBase(file, mkFileType(type), readTypeArray(stream));
}

#pragma package(smart_init)


