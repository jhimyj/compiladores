#include <iostream>
#include "exp.h"
using namespace std;


//:::::::::::::::::EXP
Exp::~Exp() {}

NumberExp::NumberExp(int v):value(v) {}
NumberExp::~NumberExp() { }


BoolExp::BoolExp(bool v):value(v) {}
BoolExp::~BoolExp() {}

UnaryExp::UnaryExp(Exp* exp, BinaryOp op):op(op),exp(exp){}
UnaryExp::~UnaryExp() {delete exp;}

BinaryExp::BinaryExp(Exp* l, Exp* r, BinaryOp op):left(l),right(r),op(op) {}
BinaryExp::~BinaryExp() { delete left; delete right; }

IdentifierExp::IdentifierExp(const string& n):name(n) {}
IdentifierExp::~IdentifierExp() { }


FCallExp::FCallExp(string fname, list<Exp*> args):fname(fname),args(args) {}
FCallExp::~FCallExp() {
    while (!args.empty()) {
        delete args.front();
        args.pop_front();
    }
}

//:::::::::::::::::::STM
Stm::~Stm() {}

AssignStatement::AssignStatement(string id, Exp* e): id(id), rhs(e) {}
AssignStatement::~AssignStatement() {
    delete rhs;
}

PrintStatement::PrintStatement(Exp* e): e(e) {}
PrintStatement::~PrintStatement() {
    delete e;
}

IfStatement::IfStatement(Exp* c, Stm* then_stm, Stm* els_stm): condition(c), then_stm(then_stm), els_stm(els_stm) {}
IfStatement::~IfStatement() {
    delete condition;
    delete then_stm;
    if(els_stm)delete els_stm;
}


WhileStatement::WhileStatement(Exp* c, Stm* stm): condition(c), stm(stm) {}
WhileStatement::~WhileStatement() {
    delete condition;
    delete stm;
}

ForStatement::ForStatement(string itid,Exp* start, Exp* end, Stm* stm, string type_for):it_id(itid),start(start),end(end),stm(stm),type_for(type_for){};
ForStatement::~ForStatement() {
    delete start;
    delete end;
    delete stm;
}

FCallStatement::FCallStatement(string fname, list<Exp*> args):fname(fname),args(args) {}
FCallStatement::~FCallStatement() {
    while (!args.empty()) {
        delete args.front();
        args.pop_front();
    }
}

RepeatStatement::RepeatStatement(StatementList* stms,Exp* exp):slist(stms),exp(exp){};
RepeatStatement::~RepeatStatement() {
    delete slist;
    delete exp;
}

BlockStatement::BlockStatement(StatementList* stms):slist(stms){}
BlockStatement::~BlockStatement() {
    delete slist;
}

//:::::::::STMIST
StatementList::StatementList(): stms() {}
void StatementList::add(Stm* s) {
    stms.push_back(s);
}
StatementList::~StatementList() {
    for (auto s: stms) {
        delete s;
    }
}
//::::::::::BODY

Body::Body(StatementList* s): slist(s) {}
Body::~Body() {
    delete slist;
}
//:::::::::::::SECTION
Section::~Section() {}

//::::::::::::::::::::::::CONSTS

ConstDec::ConstDec(string id, Exp* value):id(id),value(value){};
ConstDec::~ConstDec() {delete value;}

ConstDecList::ConstDecList()= default;
void::ConstDecList::add(ConstDec* constdec) {
    constdecs.push_back(constdec);
}
ConstDecList::~ConstDecList() {
    for (auto cd: constdecs) delete cd;
}

//::::::::::::::::::::::::TYPES

TypeDec::TypeDec(string name, string type):name(name),type(type){}
TypeDec::~TypeDec(){}

TypeDecList::TypeDecList()=default;
void TypeDecList::add(TypeDec* typedec) {typedecs.push_back(typedec);}
TypeDecList::~TypeDecList() {
    for (auto td: typedecs) delete td;
}

//::::::::::::::::::::::::VARS


VarDec::VarDec( list<string> vars,string type):vars(vars),type(type) {}
VarDec::~VarDec()= default;


VarDecList::VarDecList()=default;
void VarDecList::add(VarDec* v) {
    vardecs.push_back(v);
}
VarDecList::~VarDecList() {
    for (auto vd: vardecs) delete vd;
}

//::::::::::::::::::::::::SUBPROGRAMS

SubProgram::SubProgram(string fname, list<string> typs, list<list<string>> l_vars, string rtype,VarDecList* varls, Body* body):fname(fname),rtype(rtype),var_dec_list(varls),body(body) {
    list<list<string>>::iterator vrs;
    list<string>::iterator type;
    for (vrs = l_vars.begin(),type=typs.begin(); vrs != l_vars.end(),type != typs.end(); ++vrs,++type) {
        list<string>::iterator var = vrs->begin();
        while (var != vrs->end()) {
            types.push_back(*type);
            vars.push_back(*var);
            ++var;
        }
    }
}
SubProgram::~SubProgram() {
    delete body;
}
SubProgramList::SubProgramList()= default;
void SubProgramList::add(SubProgram *s) {
    sub_programs_list.push_back(s);
}
SubProgramList::~SubProgramList() {
    for (auto sp: sub_programs_list) delete sp;
}

Program::Program():body(NULL){};
void::Program::addSection(Section* s) {
    sections.push_back(s);
}
void::Program::addBody(Body* b) {
    body = b;
}

Program::~Program() {
    for (auto st:sections) delete st;
    if (body)delete body;
}


string Exp::binopToChar(BinaryOp op) {
    string  c;
    switch(op) {
        case PLUS_OP: c = "+"; break;
        case MINUS_OP: c = "-"; break;
        case MUL_OP: c = "*"; break;
        case DIV_OP: c = "/"; break;
        case LT_OP: c = "<"; break;
        case LE_OP: c = "<="; break;
        case EQ_OP: c = "=="; break;
        default: c = "$";
    }
    return c;
}