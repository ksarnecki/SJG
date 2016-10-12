CFLAGS=-c -Wall -I../../Common -fpermissive -w
LFLAGS=-Wall -I../../Common -O2 -w -static-libgcc -static-libstdc++
CC=mingw32-g++

all: DbGen

DbGen: DbGen.o CodeGenParser.o DbGenParser.o Data.o Util.o File.o AnsiString.o Exception.o LineStream.o Binary.o SqlParser.o SqlParserData.o JavaGenerator.o
	$(CC) $(LFLAGS) -o DbGen DbGen.o CodeGenParser.o DbGenParser.o Data.o Util.o File.o AnsiString.o Exception.o LineStream.o Binary.o SqlParser.o SqlParserData.o JavaGenerator.o

DbGen.o: DbGen.cpp makeData SqlParser.o
	$(CC) $(CFLAGS) DbGen.cpp

Data.o: makeData
	$(CC) $(CFLAGS) data/Data.cpp

makeData: data/Data.dd CodeGen
	cd data; ../../../CodeGen4/CodeGen < Data.dd; cd ..
	
CodeGen: ../../CodeGen4/CodeGen.cpp
	cd ../../CodeGen4; mingw32-make

AnsiString.o: ../../Common/AnsiString.cpp
	$(CC) $(CFLAGS) ../../Common/AnsiString.cpp
  
SqlParserData.o: ../SqlParser/data/SqlParserData.cpp
	$(CC) $(CFLAGS) ../SqlParser/data/SqlParserData.cpp
  
SqlParser.o:
	cd ../SqlParser; mingw32-make; cd ../DbGen; $(CC) $(CFLAGS) ../SqlParser/SqlParser.cpp 
	
Exception.o: ../../Common/Exception.cpp
	$(CC) $(CFLAGS) ../../Common/Exception.cpp

Binary.o: ../../Common/Binary.cpp
	$(CC) $(CFLAGS) ../../Common/Binary.cpp

LineStream.o: ../../CodeGen4/LineStream.cpp
	$(CC) $(CFLAGS) ../../CodeGen4/LineStream.cpp

DbGenParser.o: DbGenParser.cpp DbGenLang.tab.c
	$(CC) $(CFLAGS) -I../../CodeGen4/ DbGenParser.cpp
	
DbGenLang.tab.c : lex.dbgen.c data/DbGenLang.y
	bison -d data/DbGenLang.y
 
lex.dbgen.c: data/DbGenLang.l 
	flex data/DbGenLang.l
 
JavaGenerator.o: ../../CodeGen4/JavaGenerator.cpp
	$(CC) $(CFLAGS) -o JavaGenerator.o ../../CodeGen4/JavaGenerator.cpp

CodeGenParser.o: ../../CodeGen4/Parser.cpp Codegen.php.tab.c 
	$(CC) $(CFLAGS) -o CodeGenParser.o ../../CodeGen4/Parser.cpp
	
Codegen.php.tab.c: ../../CodeGen4/lex.codegen.c ../../CodeGen4/data/php.y
	bison -d ../../CodeGen4/data/php.y

File.o: ../../CodeGen4/File.cpp
	$(CC) $(CFLAGS) ../../CodeGen4/File.cpp
	
Util.o: ../../CodeGen4/Util.cpp
	$(CC) $(CFLAGS) ../../CodeGen4/Util.cpp
 
lex.codegen.c: ../../CodeGen4/data/php.l 
	flex ../../CodeGen4/data/php.l

clean:
	rm -f *.o CodeGen *.exe lex.* php.tab.* data/Data.cpp data/Data.h
