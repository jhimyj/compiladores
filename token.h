#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token {
public:
    enum Type {
        PROGRAM,CONST,TYPE,VAR,FUNCTION,PROCEDURE,BEGIN,END,WRITELN,IF,ELSE,THEN,WHILE,DO,FOR,TO,DOWNTO,REPEAT,UNTIL,NUM,TRUE,FALSE,DOT,ID,PLUS, MINUS, MUL, DIV,MOD, ERR, PD, PI,ASSIGN, PC,LT, LE, EQ,COMA,COLON,GT,GE,AND,OR,NOT,END_P,
    };

    Type type;
    std::string text;

    Token(Type type);
    Token(Type type, char c);
    Token(Type type, const std::string& source, int first, int last);

    friend std::ostream& operator<<(std::ostream& outs, const Token& tok);
    friend std::ostream& operator<<(std::ostream& outs, const Token* tok);
};

#endif // TOKEN_H