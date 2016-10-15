CFLAGS=-c -Wall -I../Common -fpermissive -w
LFLAGS=-Wall -O2 -w -static-libgcc -static-libstdc++
CC=g++

all: CodeGen 

CodeGen: CodeGen.o Parser.o File.o  AnsiString.o Exception.o LineStream.o JavaGenerator.o Util.o SimpleData.o Binary.o
	$(CC) $(LFLAGS) -o CodeGen CodeGen.o Parser.o AnsiString.o Exception.o File.o LineStream.o JavaGenerator.o Util.o SimpleData.o Binary.o

File.o: File.cpp
	$(CC) $(CFLAGS) File.cpp

AnsiString.o: ../Common/AnsiString.cpp
	$(CC) $(CFLAGS) ../Common/AnsiString.cpp

Exception.o: ../Common/Exception.cpp
	$(CC) $(CFLAGS) ../Common/Exception.cpp

SimpleData.o: ../Common/SimpleData.cpp
	$(CC) $(CFLAGS) ../Common/SimpleData.cpp

Binary.o: ../Common/Binary.cpp
	$(CC) $(CFLAGS) ../Common/Binary.cpp

LineStream.o: LineStream.cpp
	$(CC) $(CFLAGS) LineStream.cpp

JavaGenerator.o: JavaGenerator.cpp
	$(CC) $(CFLAGS) JavaGenerator.cpp

Parser.o: Parser.cpp php.tab.c
	$(CC) $(CFLAGS) Parser.cpp

Util.o: Util.cpp
	$(CC) $(CFLAGS) Util.cpp

php.tab.c: lex.codegen.c data/php.y
	bison -d data/php.y
 
lex.codegen.c: data/php.l 
	flex data/php.l

CodeGen.o: CodeGen.cpp php.tab.c
	$(CC) $(CFLAGS) CodeGen.cpp
	
clean:
	rm -f *.o CodeGen *.exe lex.codegen.* php.tab.*
