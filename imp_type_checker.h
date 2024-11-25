#ifndef IMP_TYPE_CHECKER_H
#define IMP_TYPE_CHECKER_H
#include "exp.h"
#include "type_visitor.h"
#include "environment.hh"

using namespace std;

class FEntry {
public:
    string fname;
    ImpType ftype;
    int mem_locals, max_stack;
};

class ImpTypeChecker :public TypeVisitor{
public:
    ImpTypeChecker();
    Environment<FEntry> ftable;
    FEntry fentryConst;
    FEntry fentrybody;
private:
    Environment<string> tipos;
    Environment<ImpType> env;
    bool has_main;
    ImpType booltype;
    ImpType inttype;
    ImpType longinttype;
    ImpType voidtype;
    ImpType consttype;
    ImpType maintype;

    vector<string> fnames;
    int sp{}, max_sp{};
    int dir{}, max_dir{};
    void sp_decr(int n);
    void sp_incr(int n);

public:
    void typecheck(Program*);

    void visit(AssignStatement* stm);
    void visit(PrintStatement* stm);
    void visit(IfStatement* stm);
    void visit(WhileStatement* stm);
    void visit(ForStatement* stm);
    void visit(FCallStatement* stm);
    void visit(RepeatStatement* stm);
    void visit(BlockStatement* stm);
    void visit(StatementList* stm);
    void visit(Body* b);
    void visit(ConstDec* stm);
    void visit(ConstDecList* stm);
    void visit(TypeDec* stm);
    void visit(TypeDecList* stm);
    void visit(VarDec* stm);
    void visit(VarDecList* stm);
    void visit(SubProgram* stm);
    void visit(SubProgramList* stm);
    void visit(Program* p);//
    ImpType visit(NumberExp* exp);
    ImpType visit(BoolExp* exp);
    ImpType visit(UnaryExp* exp);
    ImpType visit(BinaryExp* exp);
    ImpType visit(IdentifierExp* exp);
    ImpType visit(FCallExp* exp);
private:
    void add_fundec(SubProgram* fd);
    void add_contsdec(list<Section*> conts);
    ImpType process_fcall(FCallExp*);
};



#endif //IMP_TYPE_CHECKER_H
