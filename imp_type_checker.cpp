#include "imp_type_checker.h"

void AssignStatement::accept(TypeVisitor* v) {
  return v->visit(this);
}
void PrintStatement::accept(TypeVisitor* v) {
  return v->visit(this);
}
void IfStatement:: accept(TypeVisitor* v) {
  return v->visit(this);
}
void WhileStatement::accept(TypeVisitor* v) {
  return v->visit(this);
}
void ForStatement::accept(TypeVisitor* v) {
  return v->visit(this);
}
void FCallStatement::accept(TypeVisitor* v) {
  return v->visit(this);
}
void RepeatStatement::accept(TypeVisitor* v) {
  return v->visit(this);
}
void BlockStatement::accept(TypeVisitor* v) {
  return v->visit(this);
}
void StatementList::accept(TypeVisitor* v) {
  return v->visit(this);
}
void Body::accept(TypeVisitor* v) {
  return v->visit(this);
}
void ConstDec::accept(TypeVisitor* v) {
  return v->visit(this);
}
void ConstDecList::accept(TypeVisitor* v) {
  return v->visit(this);
}
void TypeDec::accept(TypeVisitor* v) {
  return v->visit(this);
}
void TypeDecList::accept(TypeVisitor* v) {
  return v->visit(this);
}
void VarDec::accept(TypeVisitor* v) {
  return v->visit(this);
}
void VarDecList::accept(TypeVisitor* v) {
  return v->visit(this);
}
void SubProgram::accept(TypeVisitor* v) {
  return v->visit(this);
}
void SubProgramList:: accept(TypeVisitor* v) {
  return v->visit(this);
}
void Program:: accept(TypeVisitor* v) {
  return v->visit(this);
}
ImpType NumberExp:: accept(TypeVisitor* v) {
  return v->visit(this);
}
ImpType BoolExp:: accept(TypeVisitor* v) {
  return v->visit(this);
}
ImpType UnaryExp::accept(TypeVisitor* v) {
  return v->visit(this);
}
ImpType BinaryExp::accept(TypeVisitor* v) {
  return v->visit(this);
};
ImpType IdentifierExp::accept(TypeVisitor* v) {
  return v->visit(this);
}
ImpType FCallExp::accept(TypeVisitor* v) {
  return v->visit(this);
}


ImpTypeChecker::ImpTypeChecker():inttype(),booltype(),voidtype() {
  inttype.set_basic_type("integer");
  longinttype.set_basic_type("longint");
  booltype.set_basic_type("boolean");
  voidtype.set_basic_type("void");
  consttype.set_basic_type("const");
  list<string> noparams;
  maintype.set_fun_type(noparams,"void");
  has_main = false;
}

void ImpTypeChecker::sp_incr(int n) {
  sp++;
  if (sp > max_sp) max_sp = sp;
}

void ImpTypeChecker::sp_decr(int n) {
  sp--;
  if (sp < 0) {
    cout << "stack less than 0" << endl;
    exit(0);
  }
}

void ImpTypeChecker::typecheck(Program* p) {
  env.clear();
  p->accept(this);
  return;
}
//program
void ImpTypeChecker::visit(Program* p) {
  tipos.add_level();
  env.add_level();
  ftable.add_level();
  tipos.add_var("integer","integer");
  tipos.add_var("longint","longint");
  tipos.add_var("boolean","boolean");
  tipos.add_var("void","void");
  // p->vardecs->accept(this);
  // p->fundecs->accept(this);
  // if (!has_main) {
  //   cout << "Programa no tiene main" << endl;
  //   exit(0);
  // }
  list<Section*>::iterator it;
  for (it = p->sections.begin(); it != p->sections.end(); it++) {
    (*it)->accept(this);
  }
  //para el body
  sp = max_sp = 0;
  dir = max_dir = 0;
  p->body->accept(this);
  fentrybody.max_stack = max_sp;
  fentrybody.mem_locals = max_dir;
  //:::::::::::
  add_contsdec(p->consts);
  tipos.remove_level();
  env.remove_level();

  for(int i = 0; i < fnames.size(); i++) {
    cout << "-- Function: " << fnames[i] << endl;
    FEntry fentry = ftable.lookup(fnames[i]);
    cout << fentry.fname << " : " << fentry.ftype << endl;
    // added
    cout << "max stack height: " << fentry.max_stack << endl;
    cout << "mem local variables: " << fentry.mem_locals << endl;
  }
  cout<<fentryConst.max_stack<<endl;
  cout<<fentryConst.mem_locals<<endl;
  return;
}

//CONSTLIST
void ImpTypeChecker::visit(ConstDecList* stm) {
  list<ConstDec*>::iterator it;
  for (it = stm->constdecs.begin(); it != stm->constdecs.end(); ++it) {
    (*it)->accept(this);
  }
  return;
}

//CONST
void ImpTypeChecker::visit(ConstDec* stm) {
  ImpType type;
  ImpType vtype = stm->value->accept(this);
  type.set_const_type(vtype.ttype);
  if (type.ctype==ImpType::NOTYPE || type.ctype==ImpType::VOID) {
    cout << "Tipo invalido: " << vtype << endl;
    exit(0);
  }
  env.add_var(stm->id, type);
  dir++;
  if (dir > max_dir) max_dir = dir;

  sp_decr(1);
  return;
}

void ImpTypeChecker::visit(TypeDecList* stm) {
  list<TypeDec*>::iterator it;
  for(it= stm->typedecs.begin(); it != stm->typedecs.end(); it++) {
    (*it)->accept(this);
  }
  return;
}
void ImpTypeChecker::visit(TypeDec* stm) {
  if(!tipos.check(stm->type)) {
    cout << "Tipo invalido: " << stm->type << endl;
    exit(0);
  }
  tipos.add_var(stm->name,tipos.lookup(stm->type));
  return;
}


void ImpTypeChecker::visit(VarDecList* decs) {

  list<VarDec*>::iterator it;
  for (it = decs->vardecs.begin(); it != decs->vardecs.end(); ++it) {
    (*it)->accept(this);
  }
  return;
}

void ImpTypeChecker::visit(VarDec* vd) {

  if(!tipos.check(vd->type)) {
    cout << "Tipo invalido: " << vd->type << endl;
    exit(0);
  }
  vd->type = tipos.lookup(vd->type);
  ImpType type;
  type.set_basic_type(vd->type);
  if (type.ttype==ImpType::NOTYPE || type.ttype==ImpType::VOID) {
    cout << "Tipo invalido: " << vd->type << endl;
    exit(0);
  }
  list<string>::iterator it;
  for (it = vd->vars.begin(); it != vd->vars.end(); ++it) {
    env.add_var(*it, type);
    dir++;
    if (dir > max_dir) max_dir = dir;
  }
  return;
}
//SUBPROGRAMA LIST
void ImpTypeChecker::visit(SubProgramList* s) {
  list<SubProgram*>::iterator it;
  for (it = s->sub_programs_list.begin(); it != s->sub_programs_list.end(); ++it) {
    add_fundec(*it);
  }
  for (it = s->sub_programs_list.begin(); it != s->sub_programs_list.end(); ++it) {
    // added
    sp = max_sp = 0;
    dir = max_dir = 0;
    // end-added
    (*it)->accept(this);
    FEntry fentry;
    string fname  = (*it)->fname;
    fentry.fname = fname;
    fentry.ftype = env.lookup(fname);
    fnames.push_back(fname);
    // added
    fentry.max_stack = max_sp;
    fentry.mem_locals = max_dir;
    // end added
    ftable.add_var(fname, fentry);
  }
}
void ImpTypeChecker::visit(SubProgram* fd) {
  env.add_level();
  ImpType funtype = env.lookup(fd->fname);
  ImpType rtype, ptype;
  rtype.set_basic_type(funtype.types.back());
  list<string>::iterator it;
  int i=0;
  for (it = fd->vars.begin(); it != fd->vars.end(); ++it, i++) {
    ptype.set_basic_type(funtype.types[i]);
    env.add_var(*it,ptype);
  }
  env.add_var(fd->fname,rtype);
  fd->var_dec_list->accept(this);
  fd->body->accept(this);
  env.remove_level();
  return;
}


void ImpTypeChecker::visit(Body* b) {

  int start_dir = dir;  // added
  //env.add_level();
  b->slist->accept(this);
  //env.remove_level();
  dir = start_dir;  // added
  return;
}


void ImpTypeChecker::visit(BlockStatement* b) {
  int start_dir = dir;  // added
  //env.add_level();
  b->slist->accept(this);
  //env.remove_level();
  dir = start_dir;  // added
  return;
}




void ImpTypeChecker::visit(StatementList* s) {
  list<Stm*>::iterator it;
  for (it = s->stms.begin(); it != s->stms.end(); ++it) {
    (*it)->accept(this);
  }
  return;
}

void ImpTypeChecker::visit(AssignStatement* s) {
  ImpType type = s->rhs->accept(this);
  if (!env.check(s->id)) {
    cout << "Variable " << s->id << " undefined" << endl;
    exit(0);
  }

  ImpType var_type = env.lookup(s->id);
  if(var_type.ttype==ImpType::CONST) {
    cout  << "Variable constante '"<< s->id <<"' no puede modificarse."<< endl;
    exit(0);
  }

  sp_decr(1);
  if (!type.match(var_type)) {
    cout << "Tipo incorrecto en Assign a " << s->id << endl;
    exit(0);
  }
  return;
}

void ImpTypeChecker::visit(PrintStatement* s) {
  s->e->accept(this);
  sp_decr(1);
  return;
}

void ImpTypeChecker::visit(IfStatement* s) {
  if (!s->condition->accept(this).match(booltype)) {
    cout << "Expresion conditional en IF debe de ser bool" << endl;
    exit(0);
  }
  sp_decr(1);
  s->then_stm->accept(this);
  if (s->els_stm != NULL)
    s->els_stm->accept(this);
  return;
}

void ImpTypeChecker::visit(WhileStatement* s) {
  if (!s->condition->accept(this).match(booltype)) {
    cout << "Expresion conditional en WHILE debe de ser bool" << endl;
    exit(0);
  }
  sp_decr(1);
  s->stm->accept(this);
 return;
}

void ImpTypeChecker::visit(RepeatStatement* s) {

  s->slist->accept(this);

  if (!s->exp->accept(this).match(booltype)) {
    cout << "Expresion conditional en REPEAT debe de ser bool" << endl;
    exit(0);
  }

  sp_decr(1);
  return;
}

// void ImpTypeChecker::visit(ReturnStatement* s) {
//   ImpType rtype = env.lookup("return");
//   ImpType etype;
//   if (s->e != NULL) {
//     etype = s->e->accept(this);
//     sp_decr(1);
//   }
//   else
//     etype = voidtype;
//   if (!rtype.match(etype)) {
//     cout << "Return type mismatch: " << rtype << "<->" << etype << endl;
//     exit(0);
//   }
//   return;
// }

void ImpTypeChecker::visit(ForStatement* s) {

  if((!s->start->accept(this).match(inttype) || !s->end->accept(this).match(inttype)) && (!s->start->accept(this).match(longinttype) || !s->end->accept(this).match(longinttype)) ) {
    cout << "Expresiones en for deben de ser integer o longint" << endl;
    exit(0);
  }
  sp_decr(3);
  s->stm->accept(this);
  return;
}


ImpType ImpTypeChecker::visit(BinaryExp* e) {
  ImpType t1 = e->left->accept(this);
  ImpType t2 = e->right->accept(this);
  ImpType result;
  if ((!t1.match(inttype) || !t2.match(inttype)) && (!t1.match(longinttype) || !t2.match(longinttype))){
    if((!t1.match(booltype) || !t2.match(booltype))) {
      cout << "Tipos en BinExp deben de ser iguales"<< endl;
      exit(0);
    }

    switch(e->op) {
      case OR_OP:
        case AND_OP:
      result = booltype;
    }
    sp_decr(1);
    return result;
  }

  switch(e->op) {
  case PLUS_OP:
  case MINUS_OP:
  case MUL_OP:
  case DIV_OP:
    result = inttype;
    break;
  case LT_OP:
  case LE_OP:
    case EQ_OP:
    case GE_OP:
    case GT_OP:
    result = booltype;
    break;
  }
  sp_decr(1);
  return result;
}

ImpType ImpTypeChecker::visit(UnaryExp *e) {
  ImpType type = e->exp->accept(this);

  if(!type.match(inttype) && !type.match(longinttype) && !type.match(booltype)) {
    cout<< "Tipos en UnaryExp deben de ser longint, int,boolean " << endl;
    exit(0);
  }
  if(type.match(booltype) && e->op == MINUS_OP) {
    cout<< "Operador (-) debe de ir antes de un expresion de tipo int o longint" << endl;
    exit(0);
  }
  if((type.match(longinttype)|| type.match(inttype)) && e->op == NOT_OP) {
    cout<< "operador (not) debe ir antes de un expresion boleana" << endl;
    exit(0);
  }
  //no decrece porqeu solo cambia el resultado final
  return type;

}


ImpType ImpTypeChecker::visit(NumberExp* e) {
  sp_incr(1);
  if(e->value>-32768 && e->value<32767) return inttype;
  return longinttype;
}

ImpType ImpTypeChecker::visit(BoolExp* e) {
  sp_incr(1);
  return booltype;
}

ImpType ImpTypeChecker::visit(IdentifierExp* e) {
  sp_incr(1);
  if (env.check(e->name))
    return env.lookup(e->name);
  else {
    cout << "Variable indefinida: " << e->name << endl;
    exit(0);
  }
}


ImpType ImpTypeChecker::visit(FCallExp* e) {
  return process_fcall(e);
}



ImpType ImpTypeChecker::process_fcall(FCallExp* e) {
    if (!env.checkFun(e->fname)) {
      cout << "(Function call): " << e->fname <<  " no existe" << endl;
      exit(0);
    }
    ImpType funtype = env.lookupFun(e->fname);
    if (funtype.ttype != ImpType::FUN) {
      cout << "(Function call): " << e->fname <<  " no es una funcion" << endl;
      exit(0);
    }

    // check args
    int num_fun_args = funtype.types.size()-1;
    int num_fcall_args = e->args.size();
    ImpType rtype;
    rtype.set_basic_type(funtype.types[num_fun_args]);
    // added
    if (!rtype.match(voidtype)) {
      sp_incr(1);
    }
    if (num_fun_args != num_fcall_args) {
      cout << "(Function call) Numero de argumentos no corresponde a declaracion de: " << e->fname << endl;
      exit(0);
    }
    ImpType argtype;
    list<Exp*>::iterator it;
    int i = 0;
    for (it = e->args.begin(); it != e->args.end(); ++it) {
      argtype = (*it)->accept(this);
      if (argtype.ttype==ImpType::CONST) {
        if(argtype.ctype != funtype.types[i]) {
          cout << "(Function call) Tipo de argumento no corresponde a tipo de parametro en fcall de: " << e->fname << endl;
          exit(0);
        }
      } else if (argtype.ttype != funtype.types[i]) {
          cout << "(Function call) Tipo de argumento no corresponde a tipo de parametro en fcall de: " << e->fname << endl;
          exit(0);
      }
      i++;
    }
    sp_decr(i);
    return rtype;
}

//Si o si debe ser de tipo void
void ImpTypeChecker::visit(FCallStatement* s) {

  if (!env.checkFun(s->fname)) {
    cout << "(Function call): " << s->fname <<  " no existe" << endl;
    exit(0);
  }
  ImpType funtype = env.lookupFun(s->fname);

  if (funtype.ttype != ImpType::FUN) {
    cout << "(Function call): " << s->fname <<  " no es una funcion" << endl;
    exit(0);
  }

  // check args
  int num_fun_args = funtype.types.size()-1;
  int num_fcall_args = s->args.size();
  ImpType rtype;
  rtype.set_basic_type(funtype.types[num_fun_args]);
  // added
  if (!rtype.match(voidtype)) {
    cout << "(Function call): " << s->fname <<  " no es de tipo void" << endl;
    exit(0);
  }
      if (num_fun_args != num_fcall_args) {
      cout << "(Function call) Numero de argumentos no corresponde a declaracion de: " << s->fname << endl;
      exit(0);
    }

    ImpType argtype;
    list<Exp*>::iterator it;
    int i = 0;
    for (it = s->args.begin(); it != s->args.end(); ++it) {
      argtype = (*it)->accept(this);
      if (argtype.ttype==ImpType::CONST) {
        if(argtype.ctype != funtype.types[i]) {
          cout << "(Function call) Tipo de argumento no corresponde a tipo de parametro en fcall de: " << s->fname << endl;
          exit(0);
        }
      }else if (argtype.ttype != funtype.types[i]) {
          cout << "(Function call) Tipo de argumento no corresponde a tipo de parametro en fcall de: " << s->fname << endl;
          exit(0);
      }
      i++;
    }
    if(i)sp_decr(i);

  return;
}


void ImpTypeChecker::add_fundec(SubProgram* fd) {
  ImpType funtype;
  list<string>::iterator it;
  for(it= fd->types.begin(); it != fd->types.end(); ++it) {
    if(!tipos.check(*it)) {
      cout << "Tipo invalido ("<<*it<<") en la declaracion de la funcion: " <<fd->fname<< endl;
      exit(0);
    }
    (*it) = tipos.lookup(*it);
  }
  if(!tipos.check(fd->rtype)) {
    cout << "Tipo invalido ("<<fd->rtype<<") en la declaracion de la funcion: " <<fd->fname<< endl;
    exit(0);
  }
  fd->rtype = tipos.lookup(fd->rtype);
  if (!funtype.set_fun_type(fd->types,fd->rtype)) {
    cout << "Tipo invalido en declaracion de funcion: " << fd->fname << endl;
    exit(0);
  }
  // if (fd->fname.compare("main") == 0) {
  //   if (!funtype.match(maintype)) {
  //     cout << "Tipo incorrecto de main: " << funtype << endl;
  //     exit(0);
  //   }
  //   has_main=true;
  // }
  env.add_var(fd->fname,funtype);
  return;
}
 void ImpTypeChecker::add_contsdec(list<Section *> conts) {
  list<Section*>::iterator it;
  sp = max_sp = 0;
  dir = max_dir = 0;

  for (it = conts.begin(); it != conts.end(); ++it) {
    // added
    // end-added
    (*it)->accept(this);
  }
  fentryConst.max_stack = max_sp;
  fentryConst.mem_locals = max_dir;
}

