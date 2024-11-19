#ifndef IMP_TYPE_VISITOR
#define IMP_TYPE_VISITOR

#include "exp.h"
#include "imp_type.hh"
class Program;



class ImpTypeVisitor {
public:
  virtual void visit(Program* p) = 0;
  virtual void visit(Body* b) = 0;
  virtual void visit(VarDecList* e) = 0;
  virtual void visit(VarDec* e) = 0;
  virtual void visit(FunDecList* e) = 0;
  virtual void visit(FunDec* e) = 0;
  virtual void visit(StatementList* e) = 0;
  virtual void visit(AssignStatement* e) = 0;
  virtual void visit(PrintStatement* e) = 0;
  virtual void visit(IfStatement* e) = 0;
  virtual void visit(WhileStatement* e) = 0;
  virtual void visit(ForDoStm* e) = 0;
  virtual void visit(ReturnStatement* e) = 0;
  virtual void visit(FCallStatement* s) = 0;

  virtual ImpType visit(BinaryExp* e) = 0;
  virtual ImpType visit(NumberExp* e) = 0;
  virtual ImpType visit(* e) = 0;
  virtual ImpType visit(IdExp* e) = 0;
  virtual ImpType visit(ParenthExp* e) = 0;
  virtual ImpType visit(CondExp* e) = 0;
  virtual ImpType visit(FCallExp* e) = 0;
};


#endif
