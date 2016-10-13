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
	cd data; ../../../CodeGen/CodeGen < Data.dd; cd ..
	
CodeGen: ../../CodeGen/CodeGen.cpp
	cd ../../CodeGen; mingw32-make

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

LineStream.o: ../../CodeGen/LineStream.cpp
	$(CC) $(CFLAGS) ../../CodeGen/LineStream.cpp

DbGenParser.o: DbGenParser.cpp DbGenLang.tab.c
	$(CC) $(CFLAGS) -I../../CodeGen/ DbGenParser.cpp
	
DbGenLang.tab.c : lex.dbgen.c data/DbGenLang.y
	bison -d data/DbGenLang.y
 
lex.dbgen.c: data/DbGenLang.l 
	flex data/DbGenLang.l
 
JavaGenerator.o: ../../CodeGen/JavaGenerator.cpp
	$(CC) $(CFLAGS) -o JavaGenerator.o ../../CodeGen/JavaGenerator.cpp

CodeGenParser.o: ../../CodeGen/Parser.cpp Codegen.php.tab.c 
	$(CC) $(CFLAGS) -o CodeGenParser.o ../../CodeGen/Parser.cpp
	
Codegen.php.tab.c: ../../CodeGen/lex.codegen.c ../../CodeGen/data/php.y
	bison -d ../../CodeGen/data/php.y

File.o: ../../CodeGen/File.cpp
	$(CC) $(CFLAGS) ../../CodeGen/File.cpp
	
Util.o: ../../CodeGen/Util.cpp
	$(CC) $(CFLAGS) ../../CodeGen/Util.cpp
 
lex.codegen.c: ../../CodeGen/data/php.l 
	flex ../../CodeGen/data/php.l

clean:
	rm -f *.o CodeGen *.exe lex.* php.tab.* data/Data.cpp data/Data.h
