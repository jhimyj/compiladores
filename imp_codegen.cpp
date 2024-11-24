#include "imp_codegen.h"
#include <fstream>


ImpCodeGen::ImpCodeGen(ImpTypeChecker* a):analysis(a) {

}

void ImpCodeGen::codegen(string label, string instr) {
  if (label !=  nolabel)
    code << label << ": ";
  code << instr << endl;
}

void ImpCodeGen::codegen(string label, string instr, int arg) {
  if (label !=  nolabel)
    code << label << ": ";
  code << instr << " " << arg << endl;
}

void ImpCodeGen::codegen(string label, string instr, string jmplabel) {
  if (label !=  nolabel)
    code << label << ": ";
  code << instr << " " << jmplabel << endl;
}

string ImpCodeGen::next_label() {
  string l = "L";
  string n = to_string(current_label++);
  l.append(n);
  return l;
}

string ImpCodeGen::get_flabel(string fname) {
  string l = "L";
  l.append(fname);
  return l;
}

void ImpCodeGen::codegen(Program* p, string outfname) {
  nolabel = "";
  current_label = 0;

  p->accept(this);
  ofstream outfile;
  outfile.open(outfname);
  outfile << code.str();
  outfile.close();

  return;
}

void ImpCodeGen::visit(Program* p) {
  // codegen
  // codegen("start","skip");
  // codegen(nolabel,"enter",mem_globals);
  // codegen(nolabel,"alloc",mem_globals);
  // codegen(nolabel,"mark");
  // codegen(nolabel,"pusha",get_flabel("main"));
  // codegen(nolabel,"call");
  // codegen(nolabel,"halt");
  current_dir = 0;
  direcciones.add_level();
  process_global = true;
  // p->vardecs->accept(this);
  list<Section* >::iterator it;
  for (it = p->vars.begin(); it != p->vars.end(); ++it) {
    (*it)->accept(this);
  }

  mem_globals = current_dir;

   // codegen
   codegen("start","skip");
   codegen(nolabel,"enter",mem_globals+analysis->fentryConst.max_stack+analysis->fentryConst.mem_locals);
   codegen(nolabel,"alloc",mem_globals+analysis->fentryConst.mem_locals);
  list<Section* >::iterator itc;
  for (itc = p->consts.begin(); itc != p->consts.end(); ++itc) {
    (*itc)->accept(this);
  }
   codegen(nolabel,"mark");
   codegen(nolabel,"pusha",get_flabel("main"));
   codegen(nolabel,"call");
   codegen(nolabel,"halt");
  process_global = false;

  list<Section* >::iterator it1;
  for (it1 = p->programs.begin(); it1 != p->programs.end(); ++it1) {
    (*it1)->accept(this);
  }
  codegen(get_flabel("main"),"skip");
  p->body->accept(this);
  codegen(nolabel,"return",3);
  direcciones.remove_level();
  return ;
}

void ImpCodeGen::visit(VarDecList* s) {
  list<VarDec*>::iterator it;
  for (it = s->vardecs.begin(); it != s->vardecs.end(); ++it) {
    (*it)->accept(this);
  }
  return;
}

void ImpCodeGen::visit(VarDec* vd) {
  list<string>::iterator it;
  for (it = vd->vars.begin(); it != vd->vars.end(); ++it){
    current_dir++;
    VarEntry ventry;
    ventry.dir = current_dir;
    ventry.is_global = process_global;
    direcciones.add_var(*it, ventry);
  }
  return ;
}


void ImpCodeGen::visit(ConstDecList* s) {
  list<ConstDec*>::iterator it;
  for (it = s->constdecs.begin(); it != s->constdecs.end(); ++it) {
    (*it)->accept(this);
  }
  return;
}
void ImpCodeGen::visit(ConstDec* ct) {
  current_dir++;
  VarEntry ventry{};//
  ventry.dir = current_dir;
  ventry.is_global = process_global;
  direcciones.add_var(ct->id, ventry);
  ct->value->accept(this);

  if (ventry.is_global)
    codegen(nolabel,"store", ventry.dir);
  else
    codegen(nolabel,"storer", ventry.dir);
  return ;
}

void ImpCodeGen::visit(SubProgramList* sl) {
  list<SubProgram*>::iterator it;
  for (it = sl->sub_programs_list.begin(); it != sl->sub_programs_list.end(); ++it) {
    (*it)->accept(this);
  }
  return ;
}

void ImpCodeGen::visit(SubProgram* fd) {
  process_global = false;
  FEntry fentry = analysis->ftable.lookup(fd->fname);
  current_dir = 0;
  list<string>::iterator it, vit;
  // Parameters
  int i = 1;
  int m = fd->types.size();
  VarEntry ventry;
  for (it = fd->types.begin(), vit = fd->vars.begin();
       it != fd->types.end(); ++it, ++vit){
    ventry.is_global = false;
    ventry.dir = i-(m+3);
    direcciones.add_var(*vit,ventry);
    i++;
    // cout << *it << " " << *vit;
       }
  ImpType ftype = fentry.ftype;
  if (ftype.types[ftype.types.size()-1] != ImpType::VOID) {
    ventry.dir = -(m+3);
    direcciones.add_var(fd->fname, ventry);
  }

  codegen(get_flabel(fd->fname),"skip");
  codegen(nolabel,"enter",fentry.mem_locals+fentry.max_stack);
  codegen(nolabel,"alloc",fentry.mem_locals);

  num_params = m;
  //
  int dir = current_dir;
  direcciones.add_level();
  fd->var_dec_list->accept(this);
  fd->body->accept(this);
  direcciones.remove_level();
  current_dir = dir;
  //

  codegen(nolabel,"return",num_params+3);  // fp-m-3
  process_global = true;
  return ;
}

void ImpCodeGen::visit(TypeDecList* ty){
  return ;
}
void ImpCodeGen::visit(TypeDec* td) {
  return;
}

void ImpCodeGen::visit(Body * b) {
  // int dir = current_dir;
  // direcciones.add_level();
  // b->vardecs->accept(this);
  b->slist->accept(this);

  // direcciones.remove_level();
  //
  // current_dir = dir;
  return ;
}

//stamenls

void ImpCodeGen::visit(StatementList* s) {
  list<Stm*>::iterator it;
  for (it = s->stms.begin(); it != s->stms.end(); ++it) {
    (*it)->accept(this);
  }
  return ;
}


//::::::::::::::::::::::::::st
void ImpCodeGen::visit(FCallStatement* s) {
  // nuevo
  FEntry fentry = analysis->ftable.lookup(s->fname);
  ImpType ftype = fentry.ftype;
  if (ftype.types[ftype.types.size()-1] != ImpType::VOID) {
    codegen(nolabel,"alloc",1);
  }

  list<Exp*>::iterator it;
  for (it = s->args.begin(); it != s->args.end(); ++it) {
    (*it)->accept(this);
  }
  codegen(nolabel,"mark");
  codegen(nolabel,"pusha",get_flabel(s->fname));
  codegen(nolabel,"call");
  return ;
}

void ImpCodeGen::visit(AssignStatement* s) {
  s->rhs->accept(this);
  VarEntry ventry = direcciones.lookup(s->id);
  if (ventry.is_global)
    codegen(nolabel,"store", ventry.dir);
  else
    codegen(nolabel,"storer", ventry.dir);
  return ;
}

void ImpCodeGen::visit(PrintStatement* s) {
  s->e->accept(this);
  code << "print" << endl;;
  return ;
}

void ImpCodeGen::visit(IfStatement* s) {
  string l1 = next_label();
  string l2 = next_label();

  s->condition->accept(this);
  codegen(nolabel,"jmpz",l1);
  s->then_stm->accept(this);
  codegen(nolabel,"goto",l2);
  codegen(l1,"skip");
  if (s->els_stm!=NULL) {
    s->els_stm->accept(this);
  }
  codegen(l2,"skip");

  return ;
}

void ImpCodeGen::visit(WhileStatement* s) {
  string l1 = next_label();
  string l2 = next_label();

  codegen(l1,"skip");
  s->condition->accept(this);
  codegen(nolabel,"jmpz",l2);
  s->stm->accept(this);
  codegen(nolabel,"goto",l1);
  codegen(l2,"skip");
  return ;
}

void ImpCodeGen::visit(RepeatStatement* s) {
  string l1 = next_label();
  string l2 = next_label();

  // codegen(l1,"skip");
  // s->b->accept(this);
  // s->condition->accept(this);
  // codegen(nolabel,"jmpz",l1);
  // codegen(nolabel,"goto",l1);
  // //codegen(l2,"skip");

  codegen(l1,"skip");
  s->slist->accept(this);
  s->exp->accept(this);
  codegen(nolabel,"jmpz",l1);
  codegen(nolabel,"goto",l2);
  codegen(l2,"skip");

  return ;
}

// void ImpCodeGen::visit(ReturnStatement* s) {
//   //nuevo
//   if (s->e != NULL) {
//     VarEntry ventry = direcciones.lookup("return");
//     s->e->accept(this);
//     codegen(nolabel,"storer", ventry.dir);
//   }
//   codegen(nolabel,"return",num_params+3);  // fp-m-3
//   return ;
// }

void ImpCodeGen::visit(ForStatement* s) {

    string l1 = next_label();
    string l2 = next_label();
    string l3 = next_label();

    //alloc 1
    //codegen(nolabel, "alloc", 1);
    //current_dir++;

    // Inicializar el contador
    s->start->accept(this);
    //codegen(nolabel, "storer", current_dir);
  VarEntry ventry = direcciones.lookup(s->it_id);
  if (ventry.is_global)
    codegen(nolabel,"store", ventry.dir);
  else
    codegen(nolabel,"storer", ventry.dir);

    codegen(l1, "skip");

    // Evaluar la condición
    // codegen(nolabel, "loadr", current_dir);
  if (ventry.is_global)
    codegen(nolabel,"load",ventry.dir);
  else
    codegen(nolabel,"loadr",ventry.dir);

    s->end->accept(this);
  if(s->type_for=="to") codegen(nolabel, "le");
    else codegen(nolabel, "ge");
    codegen(nolabel, "jmpz", l2);

    // Ejecutar el cuerpo del bucle
    s->stm->accept(this);

    // Incrementar el contador
    // codegen(nolabel, "loadr", current_dir);
  if (ventry.is_global)
    codegen(nolabel,"load",ventry.dir);
  else
    codegen(nolabel,"loadr",ventry.dir);

    if(s->type_for=="to") {
      codegen(nolabel,"push ","1");
    }else {
      codegen(nolabel,"push ","-1");
    }

    //s->step->accept(this);
    codegen(nolabel, "add");

    //codegen(nolabel, "storer", current_dir);
  if (ventry.is_global)
    codegen(nolabel,"store", ventry.dir);
  else
    codegen(nolabel,"storer", ventry.dir);

    codegen(nolabel, "goto", l1);
    codegen(l2, "skip");

  return ;
}

void ImpCodeGen::visit(BlockStatement* stm) {
  stm->slist->accept(this);
}

// expresiones


int ImpCodeGen::visit(NumberExp* e) {
  codegen(nolabel,"push ",e->value);
  return 0;
}

int ImpCodeGen::visit(BoolExp* e) {
  codegen(nolabel,"push",e->value?1:0);

  return 0;
}
int ImpCodeGen::visit(UnaryExp *e) {
  e->exp->accept(this);
  string op = "";
  switch(e->op) {
    case  MINUS_OP: op = "neg";break;
    case  NOT_OP: op = "not";break;
    default: cout << "binop " << Exp::binopToChar(e->op) << " not implemented" << endl;
  }
  codegen(nolabel, op);
  return 0;
}
int ImpCodeGen::visit(BinaryExp* e) {

  e->left->accept(this);
  e->right->accept(this);
  string op = "";
  switch(e->op) {
    case PLUS_OP: op =  "add"; break;
    case MINUS_OP: op = "sub"; break;
    case MUL_OP:  op = "mul"; break;
    case DIV_OP:  op = "div"; break;
    case LT_OP:  op = "lt"; break;
    case LE_OP: op = "le"; break;
    case EQ_OP:  op = "eq"; break;
    case GT_OP:  op = "gt"; break;
    case GE_OP:  op = "ge"; break;
    case OR_OP: op = "or";break;
    case  AND_OP: op = "and";break;
    default: cout << "binop " << Exp::binopToChar(e->op) << " not implemented" << endl;
  }
  codegen(nolabel, op);
  return 0;
}

int ImpCodeGen::visit(IdentifierExp* e) {
  VarEntry ventry = direcciones.lookup(e->name);
  if (ventry.is_global)
    codegen(nolabel,"load",ventry.dir);
  else
    codegen(nolabel,"loadr",ventry.dir);
  return 0;
}

// int ImpCodeGen::visit(IFExp* e) {
//   string l1 = next_label();
//   string l2 = next_label();
//
//   e->cond->accept(this);
//   codegen(nolabel, "jmpz", l1);
//   e->left->accept(this);
//   codegen(nolabel, "goto", l2);
//   codegen(l1,"skip");
//   e->right->accept(this);
//   codegen(l2, "skip");
//   return 0;
// }

int ImpCodeGen::visit(FCallExp* e) {
  // nuevo
  FEntry fentry = analysis->ftable.lookup(e->fname);
  ImpType ftype = fentry.ftype;
  if (ftype.types[ftype.types.size()-1] != ImpType::VOID) {
    codegen(nolabel,"alloc",1);
  }
  list<Exp*>::iterator it;
  for (it = e->args.begin(); it != e->args.end(); ++it) {
    (*it)->accept(this);
  }
  codegen(nolabel,"mark");
  codegen(nolabel,"pusha",get_flabel(e->fname));
  codegen(nolabel,"call");
  return 0;
}



