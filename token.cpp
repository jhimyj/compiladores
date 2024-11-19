#include <iostream>
#include "token.h"

using namespace std;

Token::Token(Type type):type(type) { text = ""; }

Token::Token(Type type, char c):type(type) { text = string(1, c); }

Token::Token(Type type, const string& source, int first, int last):type(type) {
    text = source.substr(first, last);
}

std::ostream& operator<<(std::ostream& outs, const Token& tok) {
    switch (tok.type) {
        case Token::PROGRAM: outs << "TOKEN(PROGRAM)"; break;
        case Token::CONST: outs << "TOKEN(CONST)"; break;
        case Token::TYPE: outs << "TOKEN(TYPE)"; break;
        case Token::VAR: outs << "TOKEN(VAR)"; break;
        case Token::FUNCTION: outs << "TOKEN(FUNCTION)"; break;
        case Token::PROCEDURE: outs << "TOKEN(PROCEDURE)"; break;
        case Token::BEGIN: outs << "TOKEN(BEGIN)"; break;
        case Token::END: outs << "TOKEN(END)"; break;
        case Token::WRITELN: outs << "TOKEN(WRITELN)"; break;
        case Token::IF: outs << "TOKEN(IF)"; break;
        case Token::ELSE: outs << "TOKEN(ELSE)"; break;
        case Token::THEN: outs << "TOKEN(THEN)"; break;
        case Token::WHILE: outs << "TOKEN(WHILE)"; break;
        case Token::DO: outs << "TOKEN(DO)"; break;
        case Token::FOR: outs << "TOKEN(FOR)"; break;
        case Token::TO: outs << "TOKEN(TO)"; break;
        case Token::DOWNTO: outs << "TOKEN(DOWNTO)"; break;
        case Token::NUM: outs << "TOKEN(NUM)"; break;
        case Token::TRUE: outs << "TOKEN(TRUE)"; break;
        case Token::FALSE: outs << "TOKEN(FALSE)"; break;
        case Token::DOT: outs << "TOKEN(DOT)"; break;
        case Token::ID: outs << "TOKEN(ID)"; break;
        case Token::PLUS: outs << "TOKEN(PLUS)"; break;
        case Token::MINUS: outs << "TOKEN(MINUS)"; break;
        case Token::MUL: outs << "TOKEN(MUL)"; break;
        case Token::DIV: outs << "TOKEN(DIV)"; break;
        case Token::ERR: outs << "TOKEN(ERR)"; break;
        case Token::PD: outs << "TOKEN(PD)"; break;
        case Token::PI: outs << "TOKEN(PI)"; break;
        case Token::ASSIGN: outs << "TOKEN(ASSIGN)"; break;
        case Token::PC: outs << "TOKEN(PC)"; break;
        case Token::LT: outs << "TOKEN(LT)"; break;
        case Token::LE: outs << "TOKEN(LE)"; break;
        case Token::EQ: outs << "TOKEN(EQ)"; break;
        case Token::COMA: outs << "TOKEN(COMA)"; break;
        case Token::COLON: outs << "TOKEN(COLON)"; break;
        case Token::END_P:outs<< "TOKEN(END_P)"; break;
        case Token::REPEAT:outs<< "TOKEN(REPEAT)"; break;
        case Token::UNTIL: outs<< "TOKEN(UNTIL)"; break;
        case Token::MOD: outs<< "TOKEN(MOD)"; break;
        case Token::AND: outs<< "TOKEN(AND)"; break;
        case Token::OR: outs<< "TOKEN(OR)"; break;
        case Token::NOT: outs<< "TOKEN(NOT)"; break;
        default: outs << "TOKEN(UNKNOWN)"; break;
    }
    return outs;
}


std::ostream& operator << ( std::ostream& outs, const Token* tok ) {
    return outs << *tok;
}