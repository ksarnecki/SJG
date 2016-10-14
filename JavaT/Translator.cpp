#include <iostream>
#include <fstream>

#include "AnsiString.h"
#include "DynSet.h"
#include "LineStream.h"
#include "Data.h"

#include "Translator.h"

void Translator::prepareExpression(const Expression& e, Types& types, Builder& builder) {
  if(e.isVariableAssigment()) {
    prepareVariableAssigmentExpression(e.asVariableAssigment(), types, builder);
  } else if(e.isVariableDeclarator()) {
    prepareVariableDeclarator(e.asVariableDeclarator(), types, builder);
  } else if(e.isCreatingExpression()) {
    prepareCreatingExpression(e.asCreatingExpression(), types, builder);
  } else if(e.isIdentifier()) {
    prepareIdentifierExpression(e.asIdentifier(), types, builder);
  } else if(e.isArrayIdentifier()) {
    prepareArrayIdentifierExpression(e.asArrayIdentifier(), types, builder);
  } else if(e.isMultiIdentifier()) {
    prepareMultiIdentifierExpression(e.asMultiIdentifier(), types, builder);
  } else if(e.isTemplateIdentifier()) {
    prepareTemplateIdentifierExpression(e.asTemplateIdentifier(), types, builder);
  } else if(e.isFunctionCallExpression()) {
    prepareFunctionCallExpression(e.asFunctionCallExpression(), types, builder);
  } else if(e.isTestingExpression()) {
    prepareTestingExpression(e.asTestingExpression(), types, builder);
  } else if(e.isNumericBinaryExpression()) {
    prepareNumericBinaryExpression(e.asNumericBinaryExpression(), types, builder);
  } else if(e.isNumericUnaryExpression()) {
    prepareNumericUnaryExpression(e.asNumericUnaryExpression(), types, builder);
  } else if(e.isCondOperatorExpression()) {
    prepareCondOperatorExpression(e.asCondOperatorExpression(), types, builder);
  } else if(e.isStringExpression()) {
    prepareStringExpression(e.asStringExpression(), types, builder);
  } else if(e.isCharExpression()) {
    prepareCharExpression(e.asCharExpression(), types, builder);
  } else if(e.isFloatExpression()) {
    prepareFloatExpression(e.asFloatExpression(), types, builder);
  } else if(e.isArrayCreatingExpression()) {
    prepareArrayCreatingExpression(e.asArrayCreatingExpression(), types, builder);
  } else if(e.isAwaitExpression()) { // c# util
    prepareAwaitExpression(e.asAwaitExpression(), types, builder);
  } else if(!e.isEmpty()) {
    throw Exception("Unknown expression!");
  }
}

void Translator::prepareStatement(const Statement& s, Types& types, Builder& builder) {
  if(s.isForStatement()) {
    prepareForStatement(s.asForStatement(), types, builder);
  } else if(s.isForeachStatement()) {
    prepareForeachStatement(s.asForeachStatement(), types, builder);
  } else if(s.isBlockStatement()) {
    prepareBlockStatement(s.asBlockStatement(), types, builder);
  } else if(s.isVariableDeclaration()) {
    prepareVariableDeclaratorStatement(s.asVariableDeclaration(), types, builder);
  } else if(s.isExpressionStatement()) {
    prepareExpressionStatement(s.asExpressionStatement(), types, builder);
  } else if(s.isMergeStatement()) {
    prepareStatement(s.asMergeStatement().getFirst(), types, builder);
    prepareStatement(s.asMergeStatement().getSecond(), types, builder);
  } else if(s.isReturnStatement()) {
    prepareReturnStatement(s.asReturnStatement(), types, builder);
  } else if(s.isWhileStatement()) {
    prepareWhileStatement(s.asWhileStatement(), types, builder);
  } else if(s.isIfStatement()) {
    prepareIfStatement(s.asIfStatement(), types, builder);
  } else if(!s.isEmpty()) {
    throw Exception("Unknown statement!");
  } 
  builder.next();
}

RealType getBasicRealType(const AnsiString& type) {
  if(type=="int" || type=="Integer") 
    return RealType::createJavaLangInteger();
  if(type=="String") 
    return RealType::createJavaLangString();
  if(type=="DBConn") 
    return RealType::createLkDBConn();
  if(type=="SDBResult") 
    return RealType::createLkSDBResult();
  if(type=="Matcher")
    return RealType::createJavaUtilRegexMatcher();
  if(type=="Pattern")
    return RealType::createJavaUtilRegexPattern();
  return RealType::createUnknown();
}

int Translator::findTypePos(const AnsiString& str, const Types& types) {
  for(int i=0;i<types.Size();i++) {
    if(types[i].getName()==str)
      return i;
  }
  return -1;
}

RealType getMethodType(const RealType& rt, const Expression& e) {
  if(e.isIdentifier()) {
	  //zmienne
	  AnsiString method = e.asIdentifier().getValue();  
	  if(rt.isJavaLangString()) {
		if(method=="Length")
		  return RealType::createJavaLangInteger();  
	  }
  } else if(e.isFunctionCallExpression()) {
	  AnsiString method = e.asFunctionCallExpression().getName().asIdentifier().getValue();
	  if(rt.isJavaUtilHashMap()) {
		  if(method=="get")
		    return rt.asJavaUtilHashMap().getValue();
	    if(method=="entrySet") //oszustwo
		    return rt;
		  if(method=="toArray") //oszustwo
		    return RealType::createJavaLangArray(RealType::createJavaUtilMapEntry(MapEntry(rt.asJavaUtilHashMap().getKey(), rt.asJavaUtilHashMap().getValue())));  
	  }
  }
  return RealType::createUnknown();
}

RealType Translator::getType(const Expression& e, const Types& types) {
  //printf("/*[getType] ? %s*/\n\n", e.toXML().c_str());
  if(e.isIdentifier()) {
    if(findTypePos(e.asIdentifier().getValue(), types)!=-1)
      return types[findTypePos(e.asIdentifier().getValue(), types)].getRealType();
    return getBasicRealType(e.asIdentifier().getValue());
  }
  if(e.isArrayIdentifier()) {
    if(e.asArrayIdentifier().getArray().isIdentifier() && findTypePos(e.asArrayIdentifier().getArray().asIdentifier().getValue(), types)!=-1)
      return types[findTypePos(e.asArrayIdentifier().getArray().asIdentifier().getValue(), types)].getRealType().asJavaLangArray();
    return getType(e.asArrayIdentifier().getArray(), types);
  }
  if(e.isMultiIdentifier()) {
    RealType rt = getType(e.asMultiIdentifier().getLex(), types);
    return getMethodType(rt, e.asMultiIdentifier().getRex());
  }
  if(e.isStringExpression())
    return RealType::createJavaLangString();
  return RealType::createUnknown();
}

TypeInfo Translator::getTypeInfo(const VariableDeclarator& v, Types& types) {
  AnsiString type;
  RealType rt = RealType::createUnknown();
  bool array = false;
  bool temp = false;
  if(v.getType().isIdentifier()) {
    type = v.getType().asIdentifier().getValue();
  } else if(v.getType().isArrayIdentifier()) {
    array = true;
    if(v.getType().asArrayIdentifier().getArray().isIdentifier())
      type = v.getType().asArrayIdentifier().getArray().asIdentifier().getValue();
    else
      ;//throw Exception("/*[Warning] Unsupported declaration */");
  } else if(v.getType().isTemplateIdentifier()) {
    type = v.getType().asTemplateIdentifier().getType().asIdentifier().getValue();
    temp = true;
  } else
      ;//throw Exception("/*[Warning] Unsupported declaration */");
  
  rt = getBasicRealType(type);
    
  if(type.Pos("HashMap")==1) {
    Expressions es = v.getType().asTemplateIdentifier().getParams();
    if(es.Size()==2) {
      //do poprawy asIdentifier
      rt = RealType::createJavaUtilHashMap(HashMap(getBasicRealType(es[0].asIdentifier().getValue()), getBasicRealType(es[1].asIdentifier().getValue())));
    } else
      ;//throw Exception("getTypeInfo::HashMap");
  }
  if(array) {
    rt = RealType::createJavaLangArray(rt);
  }
  
  AnsiString name;
  if(v.getName().isIdentifier()) {
    name = v.getName().asIdentifier().getValue();
  } else {
   ;//throw Exception("/*[Warning] Unsupported variable name */"); 
  }
  return TypeInfo(name, rt);
}

void Translator::prepareMethod(const MethodDeclarator& m, Types& types, Builder& builder) {
  prepareMethodHeader(m, types, builder);
	prepareStatement(m.getStatement(), types, builder);
}

void Translator::translateClass(const Class& c, Types& types, Builder& builder) {
  Enviroment e;
  prepareClassBeg(c.getModifiers(), c.getName(), types, builder);
  const ClassElems& es = c.getClassElems();
  for(int i=0;i<es.Size();i++) {
    if(es[i].isVariableDeclarator()) {
      prepareClassVariableDeclaration(es[i].asVariableDeclarator(), types, builder);
    } else if(es[i].isMethodDeclarator()) {
      prepareMethod(es[i].asMethodDeclarator(), types, builder);
    }
  }
  prepareClassEnd(types, builder);
}

void Translator::translate(const JavaFile& f) {
  //supported types
  Types types;
  types.Insert(TypeInfo("Pattern", RealType::createJavaUtilRegexPattern()));
  //
  
  
  Builder builder;
	const Packages& p = f.getPackages();
	const Imports& i = f.getImports();
	const Classes& cs = f.getClasses();
	translatePackages(p, types, builder);
	translateImports(i, types, builder);
	for(int i=0;i<cs.Size();i++)
		translateClass(cs[i], types, builder);
  builder.print();
}
