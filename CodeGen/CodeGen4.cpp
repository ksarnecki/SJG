#include "Parser.h"
#include "CPPGenerator.h"
#include "PHPGenerator.h"
#include "JavaGenerator.h"
#include "JavascriptGenerator.h"
#include "CSGenerator.h"

#include <iostream>
#include <fstream>

DynSet<AnsiString> readData() {
  char buf[1024];
  DynSet<AnsiString> ret;
  while (std::cin.getline(buf, 1024))
    ret.Insert(AnsiString(buf).Trim());
  return ret;
}

class Reader() {
  const LineStream stream;
  int line;
  int pos;  
  
  public Reader(const LineStream& _stream) {
    stream = _stream;
    for(int i=0;i<stream.Size;i++) {
      bool inString = false;
      for(int j=1;j<=stream[i].Size();j++) {
        if(stream[i][j]=="\"")
          inString = !inString;
        if(!inString && stream[i][j]==",") {
          stream[i] = stream[i].SubString(1, j-1) + " , " + stream[i].SubString(j+1, stream[i].Length()-j);
        }
      }
    }
  }
  
  public AnsiString getWord() {
    
  }
  
  public void expectWord(AnsiString str) {
    if(getWord() != str)
      err("expected " + str);
  }
  
  public int getLine(Reader& r) {
    
  }
  
  public bool eof() {
    return line >= stream.Size();
  }
  
  public void err(AnsiString str) {
    throw Exception("Parser error in line " + AnsiString(line) + " " + str);
  }
}

DataFile parseDataFile(Reader& reader) {
  reader.expectWord("{");
  AnsiString str = reader.getWord();
  if(str == "\"type\"") {
    
  } else if(str == "\"params\"") {
    
  } else if(str == "\"type\"") {
  } else if(str=="}") {
    return;
  }
  reader.err("Bad syntax");
}

DataFiles parseData(Reader& reader) {
  DataFiles files;
  while(!reader.eof()) {
    DataFile dataFile = parseDataFile(reader);
    files.Insert(dataFile);
  }
  return files;
}

void process(const DataFiles& files) {
  for(int i=0;i<files.Size();i++) {
    
  }
}

int main(int argc, char* argv[]) {
  DynSet<AnsiString> lines = readData();
  LineStream stream(lines);
  DataFiles files = parseData(Reader(stream));
  process(files);
  return 0;
}

