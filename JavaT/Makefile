CFLAGS=-c -Wall -I. -I../Common -I./langs/cs -I./langs/php -fpermissive -w
LFLAGS=-Wall -O2 -w -static-libgcc -static-libstdc++
CC=g++

CORE= JavaT.o StringBuffer.o AnsiString.o Exception.o LineStream.o LexicalData.o SyntaxData.o Translator.o  Builder.o
CSOBJ= CSTranslator.o CSHashMap.o CSArray.o CSMatcher.o CSPattern.o CSDBConn.o CSString.o CSSDBResult.o CSMapEntry.o CSInteger.o
PHPOBJ= PHPTranslator.o PHPArray.o PHPHashMap.o PHPArrayList.o PHPString.o

all: JavaT

JavaT: $(CORE) $(CSOBJ) $(PHPOBJ)
	$(CC) $(LFLAGS) -o JavaT $(CORE) $(CSOBJ) $(PHPOBJ)

Data.o: Data.cpp
	$(CC) $(CFLAGS) Data.cpp
 
LexicalData.o: LexicalData.cpp
	$(CC) $(CFLAGS) LexicalData.cpp
	
SyntaxData.o: SyntaxData.cpp
	$(CC) $(CFLAGS) SyntaxData.cpp
	
LexicalData.cpp: data/LexicalData.dd
	../CodeGen/Codegen -xml < data/LexicalData.dd

SyntaxData.cpp: data/SyntaxData.dd
	../CodeGen/Codegen -xml < data/SyntaxData.dd

Builder.o: Builder.cpp
	$(CC) $(CFLAGS) Builder.cpp
  
Translator.o: Translator.cpp
	$(CC) $(CFLAGS) Translator.cpp
	
CSTranslator.o: langs/cs/CSTranslator.cpp 
	$(CC) $(CFLAGS) langs/cs/CSTranslator.cpp
 
CSHashMap.o: langs/cs/support/CSHashMap.cpp
	$(CC) $(CFLAGS) langs/cs/support/CSHashMap.cpp
  
CSMapEntry.o: langs/cs/support/CSMapEntry.cpp
	$(CC) $(CFLAGS) langs/cs/support/CSMapEntry.cpp
  
CSMatcher.o: langs/cs/support/CSMatcher.cpp
	$(CC) $(CFLAGS) langs/cs/support/CSMatcher.cpp
  
CSPattern.o: langs/cs/support/CSPattern.cpp
	$(CC) $(CFLAGS) langs/cs/support/CSPattern.cpp
  
CSSDBResult.o: langs/cs/support/CSSDBResult.cpp
	$(CC) $(CFLAGS) langs/cs/support/CSSDBResult.cpp
  
CSInteger.o: langs/cs/support/CSInteger.cpp
	$(CC) $(CFLAGS) langs/cs/support/CSInteger.cpp
 
CSArray.o: langs/cs/support/CSArray.cpp
	$(CC) $(CFLAGS) langs/cs/support/CSArray.cpp
  
CSDBConn.o: langs/cs/support/CSDBConn.cpp
	$(CC) $(CFLAGS) langs/cs/support/CSDBConn.cpp
  
CSString.o: langs/cs/support/CSString.cpp
	$(CC) $(CFLAGS) langs/cs/support/CSString.cpp
  
PHPTranslator.o: langs/php/PHPTranslator.cpp 
	$(CC) $(CFLAGS) langs/php/PHPTranslator.cpp 
  
PHPArray.o: langs/php/support/PHPArray.cpp 
	$(CC) $(CFLAGS) langs/php/support/PHPArray.cpp 

PHPArrayList.o: langs/php/support/PHPArrayList.cpp 
	$(CC) $(CFLAGS) langs/php/support/PHPArrayList.cpp  

PHPHashMap.o: langs/php/support/PHPHashMap.cpp 
	$(CC) $(CFLAGS) langs/php/support/PHPHashMap.cpp 
  
PHPString.o: langs/php/support/PHPString.cpp 
	$(CC) $(CFLAGS) langs/php/support/PHPString.cpp 
  
AnsiString.o: ../Common/AnsiString.cpp
	$(CC) $(CFLAGS) ../Common/AnsiString.cpp

Exception.o: ../Common/Exception.cpp
	$(CC) $(CFLAGS) ../Common/Exception.cpp

StringBuffer.o: ../Common/StringBuffer.cpp
	$(CC) $(CFLAGS) ../Common/StringBuffer.cpp
LineStream.o: LineStream.cpp
	$(CC) $(CFLAGS) LineStream.cpp

Util.o: Util.cpp
	$(CC) $(CFLAGS) Util.cpp

php.tab.c: lex.javat.c data/php.y
	bison -d data/php.y
 
lex.javat.c: data/php.l 
	flex data/php.l

JavaT.o: JavaT.cpp php.tab.c
	$(CC) $(CFLAGS) JavaT.cpp
	
clean:
	rm -f *.o JavaT *.exe lex.javat.* php.tab.*
