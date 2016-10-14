#include <iostream>
#include <fstream>

#include "php.tab.c"

#include "AnsiString.h"
#include "DynSet.h"
#include "LineStream.h"
#include "Data.h"

#include "CSTranslator.h"
#include "PHPTranslator.h"

DynSet<AnsiString> readData() {
  char buf[1024];
  DynSet<AnsiString> ret;
  while (std::cin.getline(buf, 1024))
    ret.Insert(AnsiString(buf).Trim());
  return ret;
}

static bool checkArg(int argc, char* argv[], const AnsiString& v) {
  for (int i=1;i<argc;i++)
    if (v==argv[i])
      return true;
  return false;
}

int main(int argc, char* argv[]) {
  DynSet<AnsiString> lines = readData();
  LineStream stream(lines);
  if(checkArg(argc, argv, "-cs")) {
    try {
      JavaFile data = javat_yacc_parse(stream);
      CSTranslator cs = CSTranslator();
      cs.translate(data);
    } catch (const Exception& exc) {
      std::cout << "Błąd: " << exc.Message.c_str() << std::endl;
    }
  } else if(checkArg(argc, argv, "-php")) {
    try {
      JavaFile data = javat_yacc_parse(stream);
      PHPTranslator php = PHPTranslator();
      printf("<?php\n");
      php.translate(data);
      printf("?>");
    } catch (const Exception& exc) {
      std::cout << "Błąd: " << exc.Message.c_str() << std::endl;
    }
  } else {
    printf("usage: JavaT [-cs] [-php] < file.java\n");
    return 0;
  }
  
  return 0;
}

