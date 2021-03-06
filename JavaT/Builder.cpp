#include "Builder.h"

AnsiString Builder::expressionToString(const Expression& e) {
  return AnsiString("");
}

void Builder::append(const AnsiString& a) {
  if(lines.Size()==0)
    lines.Insert(a);
  else
    lines[lines.Size()-1] += a;
}

void Builder::appendLine(const AnsiString& a) {
  lines.Insert(a);
}

void ind(int x) {
  for(int i=0;i<x*2;i++)
    printf(" ");
}

AnsiString Builder::act() {
  return lines[lines.Size()-1];
}

void Builder::next() {
  lines.Insert("");
}

void Builder::print() {
  int ix=0;
  bool inString = false;
  for(int i=0;i<lines.Size();i++) {
    lines[i] = lines[i].Trim();
    if(lines[i].Length()==0)
      continue;
    ind(ix*2);
    for(int j=1;j<=lines[i].Length();j++) {
      if( (lines[i][j]=='\"' || lines[i][j]=='\'') && (j==1 || lines[i][j-1]!='\\')) {
        inString=!inString;
      }
      
      if(!inString && lines[i][j]=='{') {
        printf("{\n");
        ix++;
        ind(ix*2);
        continue;
      } else if(!inString && lines[i][j]=='}') {
        printf("\n");
        ix--;
        ind(ix*2);
        printf("}\n");
        continue;
      } else {
        printf("%c", lines[i][j]);
      }
    }
    printf("\n");
  }
}