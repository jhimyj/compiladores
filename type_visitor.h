#ifndef TYPE_VISITOR
#define TYPE_VISITOR

#include "exp.h"
#include "imp_type.hh"
class NumberExp;
class BoolExp;
class UnaryExp;
class BinaryExp;
class IdentifierExp;
class FCallExp;
class AssignStatement;
class PrintStatement;
class IfStatement;
class WhileStatement ;
class ForStatement;
class FCallStatement ;
class RepeatStatement;
class BlockStatement;
class StatementList ;
class Body;
class ConstDec ;
class ConstDecList;
class TypeDec;
class TypeDecList;
class VarDec ;
class VarDecList;
class SubProgram;
class SubProgramList;
class Program;

class TypeVisitor {
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
    virtual ImpType visit(NumberExp* exp) = 0;
    virtual ImpType visit(BoolExp* exp) = 0;
    virtual ImpType visit(UnaryExp* exp) = 0;
    virtual ImpType visit(BinaryExp* exp) = 0;
    virtual ImpType visit(IdentifierExp* exp) = 0;
    virtual ImpType visit(FCallExp* exp) = 0;
};


#endif
