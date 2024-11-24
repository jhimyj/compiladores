#ifndef IMP_VALUE_VISITOR
#define IMP_VALUE_VISITOR

#include "exp.h"
#include "imp_value.hh"


class ImpValueVisitor {
public:
    virtual void visit(AssignStatement* stm) = 0;
    virtual void visit(PrintStatement* stm) = 0;
    virtual void visit(IfStatement* stm) = 0;
    virtual void visit(WhileStatement* stm) = 0;
    virtual void visit(ForStatement* stm) = 0;
    virtual void visit(FCallStatement* stm) = 0;
    virtual void visit(RepeatStatement* stm) = 0;
    virtual void visit(BlockStatement* stm) = 0;
    virtual void visit(StatementList* stm) = 0;
    virtual void visit(Body* b) = 0;
    virtual void visit(ConstDec* stm) = 0;
    virtual void visit(ConstDecList* stm) = 0;
    virtual void visit(TypeDec* stm) = 0;
    virtual void visit(TypeDecList* stm) = 0;
    virtual void visit(VarDec* stm) =0;
    virtual void visit(VarDecList* stm) =0;
    virtual void visit(SubProgram* stm) =0;
    virtual void visit(SubProgramList* stm) =0;
    virtual void visit(Program* p) = 0;
    virtual ImpValue visit(NumberExp* exp) = 0;
    virtual ImpValue visit(BoolExp* exp) = 0;
    virtual ImpValue visit(UnaryExp* exp) = 0;
    virtual ImpValue visit(BinaryExp* exp) = 0;
    virtual ImpValue visit(IdentifierExp* exp) = 0;
    virtual ImpValue visit(FCallExp* exp) = 0;
};


#endif
