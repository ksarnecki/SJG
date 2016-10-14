#include "PHPTranslator.h"

void PHPTranslator::translatePackages(const Packages& p, Types& types, Builder& builderr) {
	
}

void PHPTranslator::translateImports(const Imports&, Types& types, Builder& builder) {
}

    
void PHPTranslator::prepareClassBeg(const Modifiers&, const AnsiString& name, Types& types, Builder& builder) {
  builder.append("class " + name + " {");
}

void PHPTranslator::prepareClassEnd(Types& types, Builder& builder) {
  builder.append("}");
}
    
void PHPTranslator::prepareClassVariableDeclaration(const VariableDeclarator& v, Types& types, Builder& builder) {
	builder.append("/*prepareClassVariableDeclaration*/");
}

void PHPTranslator::prepareModifier(const Modifier& m, Types& types, Builder& builder) {
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

void PHPTranslator::prepareModifiers(const Modifiers& m, Types& types, Builder& builder) {
  for(int i=0;i<m.Size();i++) {
    prepareModifier(m[i], types, builder);
    builder.append(" ");
  }
}

void PHPTranslator::prepareMethodHeader(const MethodDeclarator& m, Types& types, Builder& builder) {
  prepareModifiers(m.getModifiers(), types, builder);
  builder.append(" function ");
  builder.append(" " + m.getName() + "(");
	for(int i=0;i<m.getParams().Size();i++) {
		if(i>0)
      builder.append(",");  
    prepareVariableDeclarator(m.getParams()[i], types, builder);
	}
	builder.append(")");
}

void PHPTranslator::preapreNumericOperator(const NumericOperator& op, Types& types, Builder& builder) {
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

void PHPTranslator::preapreTestingOperator(const TestingOperator& op, Types& types, Builder& builder) {
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

void PHPTranslator::prepareVariableAssigmentExpression(const VariableAssigment& va, Types& types, Builder& builder) {
  prepareExpression(va.getObj(), types, builder);
  builder.append("=");
  prepareExpression(va.getValue(), types, builder );
}
void PHPTranslator::prepareCreatingExpression(const CreatingExpression& ce, Types& types, Builder& builder) {
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

void PHPTranslator::prepareIdentifierExpression(const IdentifierExpression& ie, Types& types, Builder& builder) {
  AnsiString identifier = ie.getValue();
  /*if(identifier == CSHashMap::name()) {
    identifier = CSHashMap::rename();
  } else if(identifier == CSMatcher::name()) {
    identifier = CSMatcher::rename();
  } else if(identifier == CSPattern::name()) {
    identifier = CSPattern::rename();
  } else if(identifier == CSInteger::name()) {
    identifier = CSInteger::rename();
  } else if(identifier == CSString::name()) {
    identifier = CSString::rename();
  }*/
  if(identifier[identifier.Length()]=='"' || (identifier[identifier.Length()]>='0' && identifier[identifier.Length()]<='9')) {
    builder.append(identifier);
    return;
  }
  //funkcje wbudowane
  if(identifier=="count") { 
    builder.append(identifier);
    return;
  }
  AnsiString act = builder.act();
  if(act.Length()==0 || (act.Length()>1 && act[act.Length()-1]!='-' && act[act.Length()]!='>'))
    builder.append("$");
  builder.append(identifier);
}
void PHPTranslator::prepareArrayIdentifierExpression(const ArrayIdentifier& aie, Types& types, Builder& builder) {
  prepareExpression(aie.getArray(), types, builder);
  builder.append("[");
  prepareExpression(aie.getIndex(), types, builder);
  builder.append("]");
}
void PHPTranslator::prepareMultiIdentifierExpression(const MultiIdentifier& mi, Types& types, Builder& builder) {
  RealType r = getType(mi.getLex(), types);
   
   
	  if(r.isJavaLangArray()) {
      Expression e = PHPArray::changeMethod(mi);
      if(!e.isEmpty()) {
        prepareExpression(e, types, builder);
        return;
      }
	  }
    /*
	  if(r.isLkSDBResult()) {
		Expression e = CSSDBResult::changeMethod(mi);
		if(!e.isEmpty()) {
		  prepareExpression(e, types, builder);
		  return;
		}
	  }*/
	  if(r.isJavaUtilHashMap()) {
		  Expression e = PHPHashMap::changeMethod(mi);
		  if(!e.isEmpty()) {
		    prepareExpression(e, types, builder);
		  return;
		}
	  }
    /*
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
      if(!e.isEmpty()) {
        prepareExpression(e, types, builder);
        return;
      }
    }
  }
  */
  prepareExpression(mi.getLex(), types, builder);
  builder.append("->");
  prepareExpression(mi.getRex(), types, builder);
}
void PHPTranslator::prepareTemplateIdentifierExpression(const TemplateIdentifier& ti, Types& types, Builder& builder) {
  //oszustwo
  builder.append("array");
  /*
  prepareExpression(ti.getType(), types, builder);
  Expressions es = ti.getParams();
  builder.append("<");
  for(int i=0;i<es.Size();i++) {
    if(i>0)
      builder.append(",");
    prepareExpression(es[i], types, builder);
  }
  builder.append(">");
  */
}
void PHPTranslator::prepareFunctionCallExpression(const FunctionCallExpression& fc, Types& types, Builder& builder) {
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
void PHPTranslator::prepareAwaitExpression(const AwaitExpression& ae, Types& types, Builder& builder) {
  builder.append("await ");
  prepareExpression(ae.getExp(), types, builder);
}
void PHPTranslator::prepareTestingExpression(const TestingExpression& te, Types& types, Builder& builder) {
  prepareExpression(te.getLex(), types, builder);
  preapreTestingOperator(te.getOp(), types, builder);
  prepareExpression(te.getRex(), types, builder);
}
void PHPTranslator::prepareNumericBinaryExpression(const NumericBinaryExpression& nbe, Types& types, Builder& builder) {
  prepareExpression(nbe.getLex(), types, builder);
  preapreNumericOperator(nbe.getOp(), types, builder);
  prepareExpression(nbe.getRex(), types, builder);
}
void PHPTranslator::prepareNumericUnaryExpression(const NumericUnaryExpression& nue, Types& types, Builder& builder) {
  if(nue.getKind().isPrefix())
    preapreNumericOperator(nue.getOp(), types, builder);
  prepareExpression(nue.getExp(), types, builder);
  if(nue.getKind().isSufix())
    preapreNumericOperator(nue.getOp(), types, builder);
}
void PHPTranslator::prepareCondOperatorExpression(const CondOperatorExpression& coe, Types& types, Builder& builder) {
  builder.append("(");
  prepareExpression(coe.getCond(), types, builder);
  builder.append(" ? ");
  prepareExpression(coe.getTrueExp(), types, builder);
  builder.append(" : ");
  prepareExpression(coe.getFalseExp(), types, builder);
  builder.append(")");
}
void PHPTranslator::prepareStringExpression(const StringExpression& se, Types& types, Builder& builder) {
  builder.append("\""+se.getValue()+"\"");
}
void PHPTranslator::prepareFloatExpression(const FloatExpression& fe, Types& types, Builder& builder) {
  builder.append(fe.getValue());
}
void PHPTranslator::prepareArrayCreatingExpression(const ArrayCreatingExpression& ace, Types& types, Builder& builder) {
  builder.append("array()");
}
  
void PHPTranslator::prepareBlockStatement(const BlockStatement& s, Types& types, Builder& builder) {
  builder.append("{");
  prepareStatement(s.getBody(), types, builder);
  builder.append("}");
}

void PHPTranslator::prepareVariableDeclarator(const VariableDeclarator& v, Types& types, Builder& builder) {
 types.Insert(getTypeInfo(v, types));
 prepareExpression(v.getName(), types, builder);
 if(!v.getValue().isDefault()) {
   builder.append(" = ");
   prepareExpression(v.getValue().asValue(), types, builder);
 }
}

void PHPTranslator::prepareVariableDeclaratorStatement(const VariableDeclarator& v, Types& types, Builder& builder) {
 prepareVariableDeclarator(v, types, builder);
 builder.append(";");
}

void PHPTranslator::prepareExpressionStatement(const Expression& e, Types& types, Builder& builder) {
  prepareExpression(e, types, builder);
  builder.append(";");
}

void PHPTranslator::prepareReturnStatement(const Expression& e, Types& types, Builder& builder) {
  builder.append("return ");
  prepareExpression(e, types, builder);
  builder.append(";");
}

void PHPTranslator::prepareWhileStatement(const WhileStatement& whileStatement, Types& types, Builder& builder) {
  builder.append("while(");
  prepareExpression(whileStatement.getCondition(), types, builder);
  builder.append(")");
  prepareStatement(whileStatement.getBody(), types, builder);
}

void PHPTranslator::prepareIfStatement(const IfStatement& ifs, Types& types, Builder& builder) {
  builder.append("if(");
  prepareExpression(ifs.getCondition(), types, builder);
  builder.append(")");
  prepareStatement(ifs.getBody(), types, builder);
  if(ifs.getIfElse().isValue()) {
    builder.append(" else ");
    prepareStatement(ifs.getIfElse().asValue(), types, builder);
  }
}

void PHPTranslator::prepareForStatement(const ForStatement& f, Types& types, Builder& builder) {
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

void PHPTranslator::prepareForeachStatement(const ForeachStatement& f, Types& types, Builder& builder) {
  builder.append("foreach(");
  prepareVariableDeclarator(f.getIterator(), types, builder);
  builder.append(":");
  prepareExpression(f.getObject(), types, builder);
  builder.append(")");
  prepareStatement(f.getBody(), types, builder);
}