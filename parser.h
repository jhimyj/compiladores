#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"
#include "exp.h"

class Parser {
private:
    Scanner* scanner;
    Token *current, *previous;
    bool match(Token::Type ttype);
    bool check(Token::Type ttype);
    bool advance();
    bool isAtEnd();
    list<Stm*> parseStmList();
    Exp* parseCExp();
    Exp* parseExpression();
    Exp* parseTerm();
    Exp* parseUExp();
    Exp* parseFactor();
public:
    Parser(Scanner* scanner);
    Stm* parseStatement();
    StatementList* parseStatementList();
    Body* parseBody();
    ConstDec* parseConstDec();
    ConstDecList *parseConstDecList();
    TypeDec* parseTypeDec();
    TypeDecList* parseTypeDecList();
    VarDec* parseVarDec();
    VarDecList* parseVarDecList();
    SubProgram* parseSubProgDec();
    SubProgramList* parseSubProgDecList();
    Program* parseProgram();
};

#endif // PARSER_H