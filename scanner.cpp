#include <iostream>
#include <cstring>
#include "token.h"
#include "scanner.h"
#include "unordered_set"

using namespace std;

Scanner::Scanner(const char* s):input(s),first(0), current(0) {
    isComment=false;
    typeComment=0;
}

bool is_white_space(char c) {
    return c == ' ' || c == '\n' || c == '\r' || c == '\t';
}

bool tolowerStringIsType(std::string &s) {
    static const std::unordered_set<std::string> validTypes = {"integer", "longint", "boolean"};
    const std::string original = s;
    for (char& c : s) {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    if (const auto it = validTypes.find(s); it != validTypes.end()) {
        s = *it;
        return true;
    }
    s = original;
    return false;
}


bool Scanner:: is_comment() {
    if(current < input.length()) {
        if(input[current] == '{') {
            current++;
            typeComment = 1;
            isComment = true;
            return isComment;
        }
        if(current+1 < input.length()) {
            if(input.substr(current,2)=="//") {
                current+=2;
                isComment = true;
                typeComment = 2;
                return isComment;
            }
            if(input.substr(current,2)=="(*") {
                current+=2;
                isComment = true;
                typeComment = 3;
                return isComment ;
            }
        }
    }
    isComment=false;
    return isComment;
}

Token* Scanner::nextToken() {
    Token* token;
    while (current < input.length() && (isComment||is_white_space(input[current])||is_comment())) {
       if(isComment) {
           if(typeComment==1 && input[current] == '}') {
               isComment=false;
               // current++;
               // is_comment();
               // continue;
           }
           else if(typeComment==2 && input[current] == '\n'){
               isComment=false;
               // current++;
               // is_comment();
               // continue;
           }
           else if(typeComment==3 && current+1 < input.length()) {
               if(input.substr(current,2)=="*)") {
                   isComment=false;
                    current+=1;
                   // is_comment();
                   // continue;
               }
           }
       }
        current++;
    }

    if (current >= input.length()) {
        if(isComment) return new Token(Token::ERR);
        return new Token(Token::END_P);
    }
    char c  = input[current];
    first = current;
    if (isdigit(c)) {
        current++;
        int cont = 0;
        while (current < input.length() && (isdigit(input[current])||(input[current]=='.' && ++cont<2))) {
            current++;
        }
        token = new Token(Token::NUM, input, first, current - first);
    }

    else if (isalpha(c)) {
        current++;
        while (current < input.length() && isalnum(input[current]))
            current++;
        string word = input.substr(first, current - first);
        if (word == "program") {
            token = new Token(Token::PROGRAM, word,0,word.length());
        }
        else if (word == "const") {
            token = new Token(Token::CONST, word,0,word.length());
        }
        else if (word == "type") {
            token = new Token(Token::TYPE, word,0,word.length());
        }
        else if (word == "var") {
            token = new Token(Token::VAR, word,0,word.length());
        }
        else if (word == "function") {
            token = new Token(Token::FUNCTION, word,0,word.length());
        }
        else if (word == "procedure") {
            token = new Token(Token::PROCEDURE, word,0,word.length());
        }
        else if (word == "begin") {
            token = new Token(Token::BEGIN, word,0,word.length());
        }
        else if (word == "end") {
            token = new Token(Token::END, word,0,word.length());
        }
        else if (word == "writeln") {
            token = new Token(Token::WRITELN, word,0,word.length());
        }
        else if (word == "if") {
            token = new Token(Token::IF, word,0,word.length());
        }
        else if (word == "then") {
            token = new Token(Token::THEN, word,0,word.length());
        }
        else if (word == "else") {
            token = new Token(Token::ELSE, word,0,word.length());
        }
        else if (word == "while") {
            token = new Token(Token::WHILE, word,0,word.length());
        }
        else if (word == "do") {
            token = new Token(Token::DO, word,0,word.length());
        }
        else if (word == "for") {
            token = new Token(Token::FOR, word,0,word.length());
        }
        else if (word == "to") {
            token = new Token(Token::TO, word,0,word.length());
        }
        else if (word == "downto") {
            token = new Token(Token::DOWNTO, word,0,word.length());
        }
        else if (word == "true") {
            token = new Token(Token::TRUE, word,0,word.length());
        }
        else if (word == "false") {
            token = new Token(Token::FALSE, word,0,word.length());
        }else if(word =="repeat") {
            token = new Token(Token::REPEAT, word,0,word.length());
        }else if (word=="until") {
            token = new Token(Token::UNTIL, word,0,word.length());
        }else if(tolowerStringIsType(word)) {
            token = new Token(Token::ID, word,0,word.length());
        }
        else {
            token = new Token(Token::ID, word, 0, word.length());
        }

    }
    else if (strchr("+-*/()=;,<:>.", c)) {
        switch(c) {
            case '+': token = new Token(Token::PLUS, c); break;
            case '-': token = new Token(Token::MINUS, c); break;
            case '*': token = new Token(Token::MUL, c); break;
            case '/': token = new Token(Token::DIV, c); break;
            case ',': token = new Token(Token::COMA, c); break;
            case '(': token = new Token(Token::PI, c); break;
            case ')': token = new Token(Token::PD, c); break;
            case '=':token = new Token(Token::EQ, c); break;
            case '.':token = new Token(Token::DOT, c); break;

            case ':':
                if (current + 1 < input.length() && input[current + 1] == '=') {
                    token = new Token(Token::ASSIGN, ":=", 0, 2);
                    current++;
                } else {
                    token = new Token(Token::COLON, c);
                }
                break;
            case '<':
                if (current + 1 < input.length() && input[current + 1] == '=') {
                    token = new Token(Token::LE, "<=", 0, 2);
                    current++;
                }else {
                    token = new Token(Token::LT, c);
                }
                break;
            case '>':
                if (current + 1 < input.length() && input[current + 1] == '=') {
                    token = new Token(Token::GE, ">=", 0, 2);
                    current++;
                }else {
                    token = new Token(Token::GT, c);
                }
            break;
            case ';': token = new Token(Token::PC, c); break;
            default:
                cout << "No debería llegar acá" << endl;
                token = new Token(Token::ERR, c);
        }
        current++;
    }
    else {
        token = new Token(Token::ERR, c);
        current++;
    }
    return token;
}

void Scanner::reset() {
    first = 0;
    current = 0;
}

Scanner::~Scanner() { }

void test_scanner(Scanner* scanner) {
    Token* current;
    cout << "Iniciando Scanner:" << endl<< endl;
    while ((current = scanner->nextToken())->type != Token::END_P) {
        if (current->type == Token::ERR) {
            cout << "Error en scanner - carácter inválido: " << current->text << endl;
            break;
        } else {
            cout << *current << endl;
        }
        delete current;
    }
    cout << "TOKEN(END_P)" << endl;
    delete current;
}