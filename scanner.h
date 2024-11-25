#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include "token.h"

class Scanner {
private:
    int typeComment;
    bool isComment;
    std::string input;
    int first, current;
public:
    Scanner(const char* in_s);
    Token* nextToken();
    void reset();
    bool is_comment();
    ~Scanner();
};

void test_scanner(Scanner* scanner);

#endif // SCANNER_H