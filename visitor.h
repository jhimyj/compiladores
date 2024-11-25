#ifndef VISITOR_H
#define VISITOR_H
#include "exp.h"

#include <list>

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


class Visitor {
public:
    virtual ~Visitor() = default;

    virtual int visit(NumberExp* exp) = 0;
    virtual int visit(BoolExp* exp) = 0;
    virtual int visit(UnaryExp* exp) = 0;
    virtual int visit(BinaryExp* exp) = 0;
    virtual int visit(IdentifierExp* exp) = 0;
    virtual int visit(FCallExp* exp) = 0;
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
};

// class PrintVisitor : public Visitor {
// public:
//     void imprimir(Program* program);
//     int visit(IFExp* exp) override;
//     int visit(BinaryExp* exp) override;
//     int visit(NumberExp* exp) override;
//     int visit(BoolExp* exp) override;
//     int visit(IdentifierExp* exp) override;
//     int visit(FCallExp* exp) override;
//     void visit(AssignStatement* stm) override;
//     void visit(PrintStatement* stm) override;
//     void visit(IfStatement* stm) override;
//     void visit(WhileStatement* stm) override;
//     void visit(ForStatement* stm) override;
//     void visit(VarDec* stm) override;
//     void visit(VarDecList* stm) override;
//     void visit(StatementList* stm) override;
//     void visit(Body* b) override;
//     void visit(Program* p) override;
//     void visit(FunDec* f) override;
//     void visit(FunDecList* f) override;
//     void visit(ReturnStatement* r) override;
//     void visit(FCallStatement* exp) override;

// private:
//     int indentLevel = 0;
//     void increaseIndent() { indentLevel++; }
//     void decreaseIndent() { indentLevel--; }
//     void printIndent();
// };




#endif // VISITOR_H