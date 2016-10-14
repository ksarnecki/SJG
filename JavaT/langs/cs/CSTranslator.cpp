#include "CSTranslator.h"

void CSTranslator::translatePackages(const Packages& p, Types& types, Builder& builderr) {
	
}

void CSTranslator::translateImports(const Imports&, Types& types, Builder& builder) {
}

    
void CSTranslator::prepareClassBeg(const Modifiers&, const AnsiString& name, Types& types, Builder& builder) {
  builder.append("class " + name + " {");
}

void CSTranslator::prepareClassEnd(Types& types, Builder& builder) {
  builder.append("}");
}
    
void CSTranslator::prepareClassVariableDeclaration(const VariableDeclarator& v, Types& types, Builder& builder) {
	builder.append("/*prepareClassVariableDeclaration*/");
}

void CSTranslator::prepareModifier(const Modifier& m, Types& types, Builder& builder) {
  if(m.isPublic()) {
    builder.append("public");
  } else if(m.isPrivate()) {
    builder.append("private");
  } else if(m.isStatic()) {
    builder.append("static");
  } else if(m.isAsync()) {
    builder.append("async");
  } else 
    throw Exception("Unsupported modifier");
}

void CSTranslator::prepareModifiers(const Modifiers& m, Types& types, Builder& builder) {
  for(int i=0;i<m.Size();i++) {
    prepareModifier(m[i], types, builder);
    builder.append(" ");
  }
}

void CSTranslator::prepareMethodHeader(const MethodDeclarator& m, Types& types, Builder& builder) {
  prepareModifiers(m.getModifiers(), types, builder);
  prepareExpression(m.getType(), types, builder);
  builder.append(" " + m.getName() + "(");
	for(int i=0;i<m.getParams().Size();i++) {
		if(i>0)
      builder.append(",");  
    prepareVariableDeclarator(m.getParams()[i], types, builder);
	}
	builder.append(")");
}

void CSTranslator::preapreNumericOperator(const NumericOperator& op, Types& types, Builder& builder) {
  if(op.isInc()) {
    builder.append("++");
  } else if(op.isDec()) {
    builder.append("--");
  } else if(op.isAdd()) {
    builder.append("+");
  } else if(op.isSub()) {
    builder.append("-");
  } else if(op.isMul()) {
    builder.append("*");
  } else if(op.isDiv()) {
    builder.append("/");
  } else if(op.isSas()) {
    builder.append("-=");
  } else if(op.isAas()) {
    builder.append("+=");
  } else 
    throw Exception("Unsupported numeric operator");
}

void CSTranslator::preapreTestingOperator(const TestingOperator& op, Types& types, Builder& builder) {
  if(op.isGr()) {
    builder.append(">");
  } else if(op.isSm()) {
    builder.append("<");
  } else if(op.isEgr()) {
    builder.append(">=");
  } else if(op.isEsm()) {
    builder.append("<=");
  } else if(op.isEq()) {
    builder.append("==");
  } else if(op.isNeq()) {
    builder.append("!=");
  } else 
    throw Exception("Unsupported testing operator");
}

void CSTranslator::prepareVariableAssigmentExpression(const VariableAssigment& va, Types& types, Builder& builder) {
  prepareExpression(va.getObj(), types, builder);
  builder.append("=");
  prepareExpression(va.getValue(), types, builder );
}
void CSTranslator::prepareCreatingExpression(const CreatingExpression& ce, Types& types, Builder& builder) {
  builder.append("new ");
  prepareExpression(ce.getType(), types, builder);
  builder.append("(");
  CallParams cp = ce.getParams();
  for(int i=0;i<cp.Size();i++) {
    if(i>0)
      builder.append(",");  
    prepareExpression(cp[i], types, builder);
  }
  builder.append(")");
}
void CSTranslator::prepareIdentifierExpression(const IdentifierExpression& ie, Types& types, Builder& builder) {
  AnsiString identifier = ie.getValue();
  if(identifier == CSHashMap::name()) {
    identifier = CSHashMap::rename();
  } else if(identifier == CSMatcher::name()) {
    identifier = CSMatcher::rename();
  } else if(identifier == CSPattern::name()) {
    identifier = CSPattern::rename();
  } else if(identifier == CSInteger::name()) {
    identifier = CSInteger::rename();
  } else if(identifier == CSString::name()) {
    identifier = CSString::rename();
  }
  builder.append(identifier);
}
void CSTranslator::prepareArrayIdentifierExpression(const ArrayIdentifier& aie, Types& types, Builder& builder) {
  prepareExpression(aie.getArray(), types, builder);
  builder.append("[");
  prepareExpression(aie.getIndex(), types, builder);
  builder.append("]");
}
void CSTranslator::prepareMultiIdentifierExpression(const MultiIdentifier& mi, Types& types, Builder& builder) {
  RealType r = getType(mi.getLex(), types);
   
  printf("/* init obj %s\n exp %s */\n\n", r.toXML().c_str(), mi.toXML().c_str());
   
	  if(r.isJavaLangArray()) {
      if(mi.getLex().isArrayIdentifier()) {  //do poprawy z poziomu gramatyki 
        
      }
      Expression e = CSArray::changeMethod(mi);
      if(!e.isEmpty()) {
        prepareExpression(e, types, builder);
        return;
      }
	  }
	  if(r.isLkSDBResult()) {
		Expression e = CSSDBResult::changeMethod(mi);
		if(!e.isEmpty()) {
		  prepareExpression(e, types, builder);
		  return;
		}
	  }
	  if(r.isJavaUtilHashMap()) {
		  Expression e = CSHashMap::changeMethod(mi);
		  if(!e.isEmpty()) {
		    prepareExpression(e, types, builder);
		  return;
		}
	  }
	  if(r.isJavaUtilRegexPattern()) {
		Expression e = CSPattern::changeMethod(mi);
		if(!e.isEmpty()) {
		  prepareExpression(e, types, builder);
		  return;
		}
	  }
	  if(r.isJavaUtilRegexMatcher()) {
		Expression e = CSMatcher::changeMethod(mi);
		  if(!e.isEmpty()) {
		  prepareExpression(e, types, builder);
		  return;
		}
	  }
	  if(r.isLkDBConn()) {
		Expression e = CSDBConn::changeMethod(mi);
		if(!e.isEmpty()) {
		  prepareExpression(e, types, builder);
		  return;
		}
	  }
	  if(r.isJavaLangString()) {
		Expression e = CSString::changeMethod(mi);
		if(!e.isEmpty()) {
		  prepareExpression(e, types, builder);
		  return;
		}
    if(r.isJavaUtilMapEntry()) {
      Expression e = CSMapEntry::changeMethod(mi);
      printf("/* isJavaUtilMapEntry %s => %s */\n\n", mi.getLex().toXML().c_str(), e.toXML().c_str());
      if(!e.isEmpty()) {
        prepareExpression(e, types, builder);
        return;
      }
    }
  }
  
  prepareExpression(mi.getLex(), types, builder);
  builder.append(".");
  prepareExpression(mi.getRex(), types, builder);
}
void CSTranslator::prepareTemplateIdentifierExpression(const TemplateIdentifier& ti, Types& types, Builder& builder) {
  prepareExpression(ti.getType(), types, builder);
  Expressions es = ti.getParams();
  builder.append("<");
  for(int i=0;i<es.Size();i++) {
    if(i>0)
      builder.append(",");
    prepareExpression(es[i], types, builder);
  }
  builder.append(">");
}
void CSTranslator::prepareFunctionCallExpression(const FunctionCallExpression& fc, Types& types, Builder& builder) {
  prepareExpression(fc.getName(), types, builder);
  builder.append("(");
  CallParams cp = fc.getParams();
  for(int i=0;i<cp.Size();i++) {
    if(i>0)
      builder.append(",");  
    prepareExpression(cp[i], types, builder);
  }
  builder.append(")");
}
void CSTranslator::prepareAwaitExpression(const AwaitExpression& ae, Types& types, Builder& builder) {
  builder.append("await ");
  prepareExpression(ae.getExp(), types, builder);
}
void CSTranslator::prepareTestingExpression(const TestingExpression& te, Types& types, Builder& builder) {
  prepareExpression(te.getLex(), types, builder);
  preapreTestingOperator(te.getOp(), types, builder);
  prepareExpression(te.getRex(), types, builder);
}
void CSTranslator::prepareNumericBinaryExpression(const NumericBinaryExpression& nbe, Types& types, Builder& builder) {
  prepareExpression(nbe.getLex(), types, builder);
  preapreNumericOperator(nbe.getOp(), types, builder);
  prepareExpression(nbe.getRex(), types, builder);
}
void CSTranslator::prepareNumericUnaryExpression(const NumericUnaryExpression& nue, Types& types, Builder& builder) {
  if(nue.getKind().isPrefix())
    preapreNumericOperator(nue.getOp(), types, builder);
  prepareExpression(nue.getExp(), types, builder);
  if(nue.getKind().isSufix())
    preapreNumericOperator(nue.getOp(), types, builder);
}
void CSTranslator::prepareCondOperatorExpression(const CondOperatorExpression& coe, Types& types, Builder& builder) {
  builder.append("(");
  prepareExpression(coe.getCond(), types, builder);
  builder.append(" ? ");
  prepareExpression(coe.getTrueExp(), types, builder);
  builder.append(" : ");
  prepareExpression(coe.getFalseExp(), types, builder);
  builder.append(")");
}
void CSTranslator::prepareCharExpression(const CharExpression& ce, Types& types, Builder& builder) {
  builder.append(ce.getValue());
}
void CSTranslator::prepareStringExpression(const StringExpression& se, Types& types, Builder& builder) {
  builder.append("\""+se.getValue()+"\"");
}
void CSTranslator::prepareFloatExpression(const FloatExpression& fe, Types& types, Builder& builder) {
  builder.append(fe.getValue());
}
void CSTranslator::prepareArrayCreatingExpression(const ArrayCreatingExpression& ace, Types& types, Builder& builder) {
  builder.append("new ");
  prepareExpression(ace.getArr(), types, builder);
  builder.append("[");
  prepareExpression(ace.getSize(), types, builder);
  builder.append("]");
}
  
void CSTranslator::prepareBlockStatement(const BlockStatement& s, Types& types, Builder& builder) {
  builder.append("{");
  prepareStatement(s.getBody(), types, builder);
  builder.append("}");
}

void CSTranslator::prepareVariableDeclarator(const VariableDeclarator& v, Types& types, Builder& builder) {
 types.Insert(getTypeInfo(v, types));
 prepareExpression(v.getType(), types, builder);
 builder.append(" ");
 prepareExpression(v.getName(), types, builder);
 if(!v.getValue().isDefault()) {
   builder.append(" = ");
   prepareExpression(v.getValue().asValue(), types, builder);
 }
}

void CSTranslator::prepareVariableDeclaratorStatement(const VariableDeclarator& v, Types& types, Builder& builder) {
 prepareVariableDeclarator(v, types, builder);
 builder.append(";");
}

void CSTranslator::prepareExpressionStatement(const Expression& e, Types& types, Builder& builder) {
  prepareExpression(e, types, builder);
  builder.append(";");
}

void CSTranslator::prepareReturnStatement(const Expression& e, Types& types, Builder& builder) {
  builder.append("return ");
  prepareExpression(e, types, builder);
  builder.append(";");
}

void CSTranslator::prepareWhileStatement(const WhileStatement& whileStatement, Types& types, Builder& builder) {
  builder.append("while(");
  prepareExpression(whileStatement.getCondition(), types, builder);
  builder.append(")");
  prepareStatement(whileStatement.getBody(), types, builder);
}

void CSTranslator::prepareIfStatement(const IfStatement& ifs, Types& types, Builder& builder) {
  builder.append("if(");
  prepareExpression(ifs.getCondition(), types, builder);
  builder.append(")");
  prepareStatement(ifs.getBody(), types, builder);
  if(ifs.getIfElse().isValue()) {
    builder.append(" else ");
    prepareStatement(ifs.getIfElse().asValue(), types, builder);
  }
}

void CSTranslator::prepareForStatement(const ForStatement& f, Types& types, Builder& builder) {
  builder.append("for(");
  if(f.getInit().isDecl()) {
    prepareVariableDeclaratorStatement(f.getInit().asDecl(), types, builder);
  } else {
    prepareExpression(f.getInit().asExpr(), types, builder);
    builder.append(";");
  }
  prepareExpression(f.getCondition(), types, builder);
  builder.append(";");
  prepareExpression(f.getAfter(), types, builder);
  builder.append(")");
  prepareStatement(f.getBody(), types, builder);
}

void CSTranslator::prepareForeachStatement(const ForeachStatement& f, Types& types, Builder& builder) {
  builder.append("foreach(");
  prepareVariableDeclarator(f.getIterator(), types, builder);
  builder.append(":");
  prepareExpression(f.getObject(), types, builder);
  builder.append(")");
  prepareStatement(f.getBody(), types, builder);
}