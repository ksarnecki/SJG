CFLAGS=-c -Wall -I../Common -fpermissive -w
LFLAGS=-Wall -O2 -w -static-libgcc -static-libstdc++
CC=g++

all: CodeGen Converter

Converter: File.o Converter.o AnsiString.o Exception.o LineStream.o CPPGenerator.o PHPGenerator.o JavascriptGenerator.o JavaGenerator.o OldParser.o Util.o SimpleData.o Binary.o CSGenerator.o
	$(CC) $(LFLAGS) -o Converter Converter.o AnsiString.o Exception.o File.o LineStream.o CPPGenerator.o PHPGenerator.o JavascriptGenerator.o JavaGenerator.o OldParser.o Util.o SimpleData.o Binary.o CSGenerator.o

CodeGen: CodeGen.o Parser.o File.o  Converter.o AnsiString.o Exception.o LineStream.o CPPGenerator.o PHPGenerator.o JavascriptGenerator.o JavaGenerator.o Util.o SimpleData.o Binary.o CSGenerator.o
	$(CC) $(LFLAGS) -o CodeGen CodeGen.o Parser.o AnsiString.o Exception.o File.o LineStream.o CPPGenerator.o PHPGenerator.o JavascriptGenerator.o JavaGenerator.o Util.o SimpleData.o Binary.o CSGenerator.o

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

CPPGenerator.o: CPPGenerator.cpp
	$(CC) $(CFLAGS) CPPGenerator.cpp

CSGenerator.o: CSGenerator.cpp
	$(CC) $(CFLAGS) CSGenerator.cpp

PHPGenerator.o: PHPGenerator.cpp
	$(CC) $(CFLAGS) PHPGenerator.cpp

JavaGenerator.o: JavaGenerator.cpp
	$(CC) $(CFLAGS) JavaGenerator.cpp

JavascriptGenerator.o: JavascriptGenerator.cpp
	$(CC) $(CFLAGS) JavascriptGenerator.cpp

Parser.o: Parser.cpp php.tab.c
	$(CC) $(CFLAGS) Parser.cpp

OldParser.o: OldParser.cpp
	$(CC) $(CFLAGS) OldParser.cpp

Util.o: Util.cpp
	$(CC) $(CFLAGS) Util.cpp

php.tab.c: lex.codegen.c data/php.y
	bison -d data/php.y
 
lex.codegen.c: data/php.l 
	flex data/php.l

CodeGen.o: CodeGen.cpp php.tab.c
	$(CC) $(CFLAGS) CodeGen.cpp
	
Converter.o: Converter.cpp
	$(CC) $(CFLAGS) Converter.cpp
	
clean:
	rm -f *.o CodeGen *.exe lex.codegen.* php.tab.*
