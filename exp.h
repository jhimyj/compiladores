#ifndef EXP_H
#define EXP_H
#include "imp_value.hh"
#include "imp_type.hh"
#include <string>
#include <unordered_map>
#include <list>
#include "visitor.h"
using namespace std;
enum BinaryOp { PLUS_OP, MINUS_OP, MUL_OP, DIV_OP,LT_OP, LE_OP, EQ_OP,GT_OP,GE_OP,NOT_OP,MOD_OP,AND_OP,OR_OP};

class Body;
class ImpValueVisitor;
class ImpTypeVisitor;
//::::::::::::::::::::::::EXp
class Exp {
public:
    // virtual int  accept(Visitor* visitor) = 0;
    // virtual ImpValue accept(ImpValueVisitor* v) = 0;
    virtual ImpType accept(ImpTypeVisitor* v) = 0;
    virtual ~Exp() = 0;
    static string binopToChar(BinaryOp op);
};

class NumberExp : public Exp {
public:
    int value;
    NumberExp(int v);
    // int accept(Visitor* visitor);
    // ImpValue accept(ImpValueVisitor* v);
    ImpType accept(ImpTypeVisitor* v) ;
    ~NumberExp();
};

class BoolExp : public Exp {
public:
    int value;
    BoolExp(bool v);
    // int accept(Visitor* visitor);
    // ImpValue accept(ImpValueVisitor* v);
    ImpType accept(ImpTypeVisitor* v) ;
    ~BoolExp();
};

class UnaryExp : public Exp {
public:
    Exp *exp;
    BinaryOp op;
    UnaryExp(Exp* exp, BinaryOp op);
    // int accept(Visitor* visitor);
    // ImpValue accept(ImpValueVisitor* v);
    ImpType accept(ImpTypeVisitor* v) ;
    ~UnaryExp();
};

class BinaryExp : public Exp {
public:
    Exp *left, *right;
    BinaryOp op;
    BinaryExp(Exp* l, Exp* r, BinaryOp op);
    // int accept(Visitor* visitor);
    // ImpValue accept(ImpValueVisitor* v);
    ImpType accept(ImpTypeVisitor* v) ;
    ~BinaryExp();
};

class IdentifierExp : public Exp {
public
    string name;
    IdentifierExp(const std::string& n);
    // int accept(Visitor* visitor);
    // ImpValue accept(ImpValueVisitor* v);
    ImpType accept(ImpTypeVisitor* v) ;
    ~IdentifierExp();
};


class FCallExp : public Exp {
public:
    std::string fname;
    list<Exp*> args;
    FCallExp(std::string fname, list<Exp*> args);
    // int accept(Visitor* visitor);
    // ImpValue accept(ImpValueVisitor* v);
    ImpType accept(ImpTypeVisitor* v) ;
    ~FCallExp();
};

//::::::::::::::::::::::::STM


class Stm {
public:
    //virtual int accept(Visitor* visitor) = 0;
    virtual ~Stm() = 0;
    //virtual void accept(ImpValueVisitor* v) = 0;
    virtual void accept(ImpTypeVisitor* v) = 0;
};

class AssignStatement : public Stm {
public:
    std::string id;
    Exp* rhs;
    AssignStatement(std::string id, Exp* e);
    // int accept(Visitor* visitor);
    // void accept(ImpValueVisitor* v);
    void accept(ImpTypeVisitor* v);
    ~AssignStatement();
};

class PrintStatement : public Stm {
public:
    Exp* e;
    PrintStatement(Exp* e);
    // int accept(Visitor* visitor);
    // void accept(ImpValueVisitor* v);
    void accept(ImpTypeVisitor* v);
    ~PrintStatement();
};


class IfStatement : public Stm {
public:
    Exp* condition;
    Stm* then_stm;
    Stm* els_stm;
    IfStatement(Exp* condition, Stm* then_stm, Stm* els_stm);
    // int accept(Visitor* visitor);
    // void accept(ImpValueVisitor* v);
    void accept(ImpTypeVisitor* v);
    ~IfStatement();
};
class WhileStatement : public Stm {
public:
    Exp* condition;
    Stm* stm;
    WhileStatement(Exp* condition, Stm* stm);
    // int accept(Visitor* visitor);
    // void accept(ImpValueVisitor* v);
    void accept(ImpTypeVisitor* v);
    ~WhileStatement();
};

class ForStatement : public Stm {
public:
    string type_for;
    string it_id;
    Exp* start;
    Exp* end;
    Stm* stm;
    ForStatement(string itid,Exp* start, Exp* end, Stm* stm, string type_for);
    // int accept(Visitor* visitor);
    // void accept(ImpValueVisitor* v);
    void accept(ImpTypeVisitor* v);
    ~ForStatement();
};

class FCallStatement : public Stm {
public:
    std::string fname;
    list<Exp*> args;
    FCallStatement(std::string fname, list<Exp*> args);
    // int accept(Visitor* visitor);
    // void accept(ImpValueVisitor* v);
    void accept(ImpTypeVisitor* v);
    ~FCallStatement();
};


class  RepeatStatement : public Stm {
public:
    StatementList* slist;
    Exp* exp;
    RepeatStatement(StatementList* stms,Exp* exp);
    // int accept(Visitor* visitor);
    // void accept(ImpValueVisitor* v);
    void accept(ImpTypeVisitor* v);
    ~RepeatStatement();
};

class  BlockStatement : public Stm {
public:
    StatementList* slist;
    BlockStatement(StatementList* stms);
    // int accept(Visitor* visitor);
    // void accept(ImpValueVisitor* v);
    void accept(ImpTypeVisitor* v);
    ~BlockStatement();
};


//::::::::::::::::::::::::STML
class StatementList {
public:
    list<Stm*> stms;
    StatementList();
    void add(Stm* stm);
    // int accept(Visitor* visitor);
    // void accept(ImpValueVisitor* v);
    void accept(ImpTypeVisitor* v);
    ~StatementList();
};

//::::::::::BODY
class Body{
public:
    StatementList* slist;
    Body(StatementList* stms);
    // int accept(Visitor* visitor);
    // void accept(ImpValueVisitor* v);
    void accept(ImpTypeVisitor* v);
    ~Body();
};

//::::::::::::::::::::: SECTION
class Section {
public:
    // virtual void  accept(Visitor* visitor) = 0;
    virtual ~Section() = 0;
    // virtual void accept(ImpValueVisitor* v) = 0;
    virtual void accept(ImpTypeVisitor* v) = 0;
};
//::::::::::::::::::::::::CONSTS

class ConstDec {
public:
    string type;
    string id;
    Exp* value;
    ConstDec(string id, Exp* value);
    // int accept(Visitor* visitor);
    // void accept(ImpValueVisitor* v);
    void accept(ImpTypeVisitor* v);
    ~ConstDec();
};

class ConstDecList : public Section{
public:
    list<ConstDec*> constdecs;
    ConstDecList();
    void add(ConstDec* constdec);
    // int accept(Visitor* visitor);
    // void accept(ImpValueVisitor* v);
    void accept(ImpTypeVisitor* v);
    ~ConstDecList();
};

//::::::::::::::::::::::::TYPES

class TypeDec {
public:
    string name;
    string type;
    TypeDec(string name, string type);
    // int accept(Visitor* visitor);
    // void accept(ImpValueVisitor* v);
    void accept(ImpTypeVisitor* v);
    ~TypeDec();
};

class TypeDecList : public Section{
public:
    list<TypeDec*> typedecs;
    TypeDecList();
    void add(TypeDec* typedec);
    // int accept(Visitor* visitor);
    // void accept(ImpValueVisitor* v);
    void accept(ImpTypeVisitor* v);
    ~TypeDecList();
};
//::::::::::::::::::::::::VARS
class VarDec {
public:
    list<string> vars;
    string type;
    VarDec(list<string> vars,string type);
    // int accept(Visitor* visitor);
    // void accept(ImpValueVisitor* v);
    void accept(ImpTypeVisitor* v);
    ~VarDec();
};

class VarDecList: public Section{
public:
    list<VarDec*> vardecs;
    VarDecList();
    void add(VarDec* vardec);
    // int accept(Visitor* visitor);
    // void accept(ImpValueVisitor* v);
    void accept(ImpTypeVisitor* v);
    ~VarDecList();
};


//::::::::::::::::::::::::SUBPROGRAMS

class SubProgram {
public:
    string fname, rtype;
    list<list<string>> vars;
    list<string> types;
    VarDecList* var_dec_list;
    Body* body;
    SubProgram(string fname, list<string> types, list<list<string>> vars, string rtype,VarDecList* varls, Body* body);
    // int accept(Visitor* v);
    // void accept(ImpValueVisitor* v);
    void accept(ImpTypeVisitor* v);
    ~SubProgram();
};


class SubProgramList: public Section{
public:
    list<SubProgram*> sub_programs_list;
    SubProgramList();
    void add(SubProgram* s);
    // int accept(Visitor* v);
    // void accept(ImpValueVisitor* v);
    void accept(ImpTypeVisitor* v);
    ~SubProgramList();
};


//PROGRAM

class Program {
public:
    list<Section*>sections;
    Body* body;
    Program();
    void addSection(Section* section);
    void addBody(Body*body);
    // int accept(Visitor* v);
    // void accept(ImpValueVisitor* v);
    void accept(ImpTypeVisitor* v);
    ~Program();
};


#endif // EXP_H