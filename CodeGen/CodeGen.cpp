#include "Parser.h"
#include "JavaGenerator.h"

#include <iostream>
#include <fstream>

DynSet<AnsiString> readData() {
  char buf[1024];
  DynSet<AnsiString> ret;
  while (std::cin.getline(buf, 1024))
    ret.Insert(AnsiString(buf).Trim());
  return ret;
}

void saveToFile(const AnsiString& file, const DynSet<AnsiString>& lines) {
  std::fstream f(file.c_str(), std::ios::out | std::ios::trunc);
  if (!f.is_open())
    throw Exception("Cant open file " + file);
  for (int i=0;i<lines.Size();i++)
    f << lines[i].c_str() << std::endl;
}

void saveToFile(const AnsiString& file, const AnsiString& content) {
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

static bool checkArg(int argc, char* argv[], const AnsiString& v) {
  for (int i=1;i<argc;i++)
    if (v==argv[i])
      return true;
  return false;
}

int main(int argc, char* argv[]) {
  bool json = checkArg(argc, argv, "-json");
  bool xml = checkArg(argc, argv, "-xml");
  bool bin = checkArg(argc, argv, "-bin");
  bool sd = checkArg(argc, argv, "-sd");
  bool arr = checkArg(argc, argv, "-array");
  bool onefile = checkArg(argc, argv, "-onefile");
  bool gstream = checkArg(argc, argv, "-stream");
  bool strictNUll = checkArg(argc, argv, "-strictNull");
  bool serializable = checkArg(argc, argv, "-serializable");
  bool iterable = checkArg(argc, argv, "-iterable");
  bool ftl = checkArg(argc, argv, "-ftl");
  bool j2j = checkArg(argc, argv, "-j2j");
  DynSet<AnsiString> lines = readData();
  LineStream stream(lines);
  try {
    DataFileBase data = processData(stream);
    if (data.getKind().isJava())
	  saveToFile(generateJavaFiles(data.getFile(), onefile, arr, gstream, json, xml, strictNUll, ftl, j2j, serializable, iterable, data.getTypes()));
    else	  
      throw Exception("DataFileKind");
  } catch (const Exception& exc) {
    std::cout << "Błąd: " << exc.Message.c_str() << std::endl;
    return 1;
  }
  return 0;
}

