#include <iostream>
#include "exp.h"
#include "visitor.h"
#include <unordered_map>
#include <variant>
using namespace std;

///////////////////////////////////////////////////////////////////////////////////

int NumberExp::accept(Visitor* v) {
    return v->visit(this);
}
int BoolExp::accept(Visitor* v) {
    return v->visit(this);
}
int UnaryExp::accept(Visitor* v) {
    return v->visit(this);
}
int BinaryExp::accept(Visitor* v) {
    return v->visit(this);
}
int IdentifierExp::accept(Visitor* v) {
    return v->visit(this);
}
int FCallExp::accept(Visitor* v) {
    return v->visit(this);
}
int AssignStatement::accept(Visitor* v) {
    v->visit(this);
    return 0;
}
int PrintStatement::accept(Visitor* v) {
    v->visit(this);
    return 0;
}
int IfStatement::accept(Visitor* v) {
    v->visit(this);
    return 0;
}
int WhileStatement::accept(Visitor* v) {
    v->visit(this);
    return 0;
}
int ForStatement::accept(Visitor* v) {
    v->visit(this);
    return 0;
}
int FCallStatement::accept(Visitor* v) {
    v->visit(this);
    return 0;
}
int RepeatStatement::accept(Visitor* v) {
    v->visit(this);
    return 0;
}
int BlockStatement::accept(Visitor* v) {
    v->visit(this);
    return 0;
}
int StatementList::accept(Visitor* v) {
    v->visit(this);
    return 0;
}
int Body::accept(Visitor* v) {
    v->visit(this);
    return 0;
}
int ConstDec::accept(Visitor* v) {
    v->visit(this);
    return 0;
}
int ConstDecList::accept(Visitor* v) {
    v->visit(this);
    return 0;
}
int TypeDec::accept(Visitor* v) {
    v->visit(this);
    return 0;
}
int TypeDecList::accept(Visitor* v) {
    v->visit(this);
    return 0;
}
int VarDec::accept(Visitor* v) {
    v->visit(this);
    return 0;
}
int VarDecList::accept(Visitor* v) {
    v->visit(this);
    return 0;
}
int SubProgram::accept(Visitor* v) {
    v->visit(this);
    return 0;
}
int SubProgramList::accept(Visitor* v) {
    v->visit(this);
    return 0;
}
int Program::accept(Visitor* v) {
    v->visit(this);
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////
//
//int PrintVisitor::visit(BinaryExp* exp) {
//    exp->left->accept(this);
//    cout << ' ' << Exp::binopToChar(exp->op) << ' ';
//    exp->right->accept(this);
//    return 0;
//}
//
//int PrintVisitor::visit(NumberExp* exp) {
//    cout << exp->value;
//    return 0;
//}
//
//int PrintVisitor::visit(BoolExp* exp) {
//    if(exp->value) cout << "true";
//    else cout << "false";
//    return 0;
//}
//
//int PrintVisitor::visit(IdentifierExp* exp) {
//    cout << exp->name;
//    return 0;
//}
//
//void PrintVisitor::visit(AssignStatement* stm) {
//    cout << stm->id << " = ";
//    stm->rhs->accept(this);
//    cout << ";";
//}
//
//void PrintVisitor::visit(PrintStatement* stm) {
//    cout << "print(";
//    stm->e->accept(this);
//    cout << ");";
//}
//
//void PrintVisitor::visit(IfStatement* stm) {
//    cout << "if ";
//    stm->condition->accept(this);
//    cout << " then" << endl;
//    stm->then->accept(this);
//    if(stm->els){
//        printIndent();
//        cout << "else" << endl;
//        stm->els->accept(this);
//    }
//    printIndent();
//    cout << "endif";
//}
//
//void PrintVisitor::imprimir(Program* program){
//    program->accept(this);
//}
//
//void PrintVisitor::visit(Program* program){
//    program->vardecs->accept(this);
//    program->fundecs->accept(this);
//};
//
//
//int PrintVisitor::visit(IFExp* pepito) {
//    cout<< "ifexp(";
//    pepito->cond->accept(this);
//    cout<< ",";
//    pepito->left->accept(this);
//    cout<< ",";
//    pepito->right->accept(this);
//    cout << ")" ;
//    return 0;
//}
//
//void PrintVisitor::visit(WhileStatement* stm){
//    cout << "while ";
//    stm->condition->accept(this);
//    cout << " do" << endl;
//    stm->b->accept(this);
//    printIndent();
//    cout << "endwhile";
//}
//
//void PrintVisitor::visit(ForStatement* stm){
//    cout << "for ";
//    stm->start->accept(this);
//    cout << " to ";
//    stm->end->accept(this);
//    cout << " step ";
//    stm->step->accept(this);
//    cout << " do" << endl;
//    stm->b->accept(this);
//    cout << "endfor";
//}
//
//void PrintVisitor::visit(VarDec* stm){
//    cout << "var ";
//    cout << stm->type;
//    cout << " ";
//    for(auto i: stm->vars){
//        cout << i;
//        if(i != stm->vars.back()) cout << ", ";
//    }
//    cout << ";";
//}
//
//void PrintVisitor::visit(VarDecList* stm){
//    for(auto i: stm->vardecs){
//        printIndent();
//        i->accept(this);
//        cout << endl;
//    }
//}
//
//void PrintVisitor::visit(StatementList* stm){
//    for(auto i: stm->stms){
//        printIndent();
//        i->accept(this);
//        cout << endl;
//    }
//}
//
//void PrintVisitor::visit(Body* stm){
//    increaseIndent();
//    stm->vardecs->accept(this);
//    stm->slist->accept(this);
//    decreaseIndent();
//}
//
//void PrintVisitor::visit(FunDec* stm){
//    cout << "fun " << stm->rtype <<  " " << stm->fname << "(";
//    bool first = true;
//    list<string>::iterator type, name;
//    for (type = stm->types.begin(), name = stm->vars.begin(); type != stm->types.end(); type++, name++) {
//        if (!first) cout << ", ";
//        cout << *type << " " << *name;
//        first = false;
//    }
//    cout << ")" << endl;
//    stm->body->accept(this);
//    cout << "endfun";
//}
//
//void PrintVisitor::visit(FunDecList* stm){
//    for(auto i: stm->flist){
//        i->accept(this);
//        cout << endl;
//    }
//}
//
//void PrintVisitor::visit(ReturnStatement* s) {
//  cout << "return (";
//  if (s->e != NULL) s->e->accept(this);
//  cout << ")";
//  return;
//}
//
//void PrintVisitor::visit(FCallStatement* e) {
//    cout << e->fname << "(";
//    list<Exp*>::iterator it;
//    bool first = true;
//    for (it = e->args.begin(); it != e->args.end(); ++it) {
//        if (!first) cout << ",";
//        first = false;
//        (*it)->accept(this);
//    }
//    cout << ')';
//    return;
//}
//
//int PrintVisitor::visit(FCallExp* e) {
//  cout << e->fname << "(";
//  list<Exp*>::iterator it;
//  bool first = true;
//  for (it = e->args.begin(); it != e->args.end(); ++it) {
//    if (!first) cout << ",";
//    first = false;
//    (*it)->accept(this);
//  }
//  cout << ')';
//  return 0;
//}
//
//void PrintVisitor::printIndent() {
//    for (int i = 0; i < indentLevel*2; i++) {
//    cout << ' ';
//    }
//
//}

///////////////////////////////////////////////////////////////////////////////////
