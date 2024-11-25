#ifndef IMP_CODEGEN_H
#define IMP_CODEGEN_H

#include "visitor.h"
#include "imp_type_checker.h"
class VarEntry {
public:
    int dir;
    bool is_global;
};

class ImpCodeGen : public Visitor {
public:
    ImpCodeGen(ImpTypeChecker*);
    void codegen(Program*, string outfname);
    int visit(NumberExp* exp) ;
    int visit(BoolExp* exp) ;
    int visit(UnaryExp* exp) ;
    int visit(BinaryExp* exp);
    int visit(IdentifierExp* exp);
    int visit(FCallExp* exp);
    void visit(AssignStatement* stm);
    void visit(PrintStatement* stm);
    void visit(IfStatement* stm);
    void visit(WhileStatement* stm);
    void visit(ForStatement* stm);
    void visit(FCallStatement* stm);
    void visit(RepeatStatement* stm);
    void visit(BlockStatement* stm);
    void visit(StatementList* stm);
    void visit(Body* b) ;
    void visit(ConstDec* stm);
    void visit(ConstDecList* stm);
    void visit(TypeDec* stm);
    void visit(TypeDecList* stm);
    void visit(VarDec* stm);
    void visit(VarDecList* stm);
    void visit(SubProgram* stm);
    void visit(SubProgramList* stm);
    void visit(Program* p);

private:
    ImpTypeChecker* analysis;
    std::ostringstream code;
    string nolabel;
    int current_label;
    Environment<VarEntry> direcciones;
    int current_dir;
    int max_stack, mem_locals, mem_globals;
    bool process_global;
    int num_params; // nuevo
    void codegen(string label, string instr);
    void codegen(string label, string instr, int arg);
    void codegen(string label, string instr, string jmplabel);
    string next_label();
    string get_flabel(string fname);
};



#endif //IMP_CODEGEN_H
