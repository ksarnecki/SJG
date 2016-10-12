CFLAGS=-c -Wall -I../../Common -fpermissive -w
LFLAGS=-Wall -I../../Common -O2 -w -static-libgcc -static-libstdc++
CC=mingw32-g++

all: Test

Test: Test.o SqlParserData.o SqlParser.o Util.o File.o AnsiString.o Exception.o LineStream.o Binary.o 
	$(CC) $(LFLAGS) -o Test Test.o SqlParserData.o SqlParser.o Util.o File.o AnsiString.o Exception.o LineStream.o Binary.o 

Test.o: Test.cpp SqlParserData.o
	$(CC) $(CFLAGS) Test.cpp

SqlParserData.o: SqlParserData
	$(CC) $(CFLAGS) data/SqlParserData.cpp

SqlParserData: CodeGen
	cd data; ../../../CodeGen4/CodeGen < SqlParserData.dd
	
CodeGen: ../../CodeGen4/CodeGen.cpp
	cd ../../CodeGen4; make

AnsiString.o: ../../Common/AnsiString.cpp
	$(CC) $(CFLAGS) ../../Common/AnsiString.cpp
	
Exception.o: ../../Common/Exception.cpp
	$(CC) $(CFLAGS) ../../Common/Exception.cpp

Binary.o: ../../Common/Binary.cpp
	$(CC) $(CFLAGS) ../../Common/Binary.cpp

LineStream.o: ../../CodeGen4/LineStream.cpp
	$(CC) $(CFLAGS) ../../CodeGen4/LineStream.cpp

SqlParser.o: SqlParser.cpp SqlLang.tab.c
	$(CC) $(CFLAGS) -I../../CodeGen4/ SqlParser.cpp
	
SqlLang.tab.c : lex.sql.c data/SqlLang.y
	bison -d data/SqlLang.y
 
lex.sql.c: data/SqlLang.l 
	flex data/SqlLang.l

File.o: ../../CodeGen4/File.cpp
	$(CC) $(CFLAGS) ../../CodeGen4/File.cpp
	
Util.o: ../../CodeGen4/Util.cpp
	$(CC) $(CFLAGS) ../../CodeGen4/Util.cpp
 
clean:
	rm -f *.o CodeGen *.exe lex.* SqlLang.tab.* data/Data.cpp data/*.cpp data/*.h
