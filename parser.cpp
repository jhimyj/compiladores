#include <iostream>
#include <stdexcept>
#include "token.h"
#include "scanner.h"
#include "exp.h"
#include "parser.h"

using namespace std;

bool Parser::match(Token::Type ttype) {
    if (check(ttype)) {
        advance();
        return true;
    }
    return false;
}

bool Parser::check(Token::Type ttype) {
    if (isAtEnd()) return false;
    return current->type == ttype;
}

bool Parser::advance() {
    if (!isAtEnd()) {
        Token* temp = current;
        if (previous) delete previous;
        current = scanner->nextToken();
        previous = temp;
        if (check(Token::ERR)) {
            cout << "Error de análisis, carácter no reconocido: " << current->text << endl;
            exit(1);
        }
        return true;
    }
    return false;
}

bool Parser::isAtEnd() {
    return (current->type == Token::END_P);
}

Parser::Parser(Scanner* sc):scanner(sc) {
    previous = NULL;
    current = scanner->nextToken();
    if (current->type == Token::ERR) {
        cout << "Error en el primer token: " << current->text << endl;
        exit(1);
    }
}


Exp* Parser::parseFactor() {
    if (match(Token::TRUE)){
        return new BoolExp(1);
    } if (match(Token::FALSE)){
        return new BoolExp(0);
    }
    if (match(Token::NUM)) {
        return new NumberExp(stoi(previous->text));
    }
    if (match(Token::ID)) {
        string texto = previous->text;
        //Parse FCallExp
        if (match(Token::PI)){
            list<Exp*> args;
            if (!check(Token::PD)){
                args.push_back(parseCExp());
                while (match(Token::COMA)){
                    args.push_back(parseCExp());
                }
            }
            if (!match(Token::PD)){
                cout << "Falta paréntesis derecho" << endl;
                exit(0);
            }
            return new FCallExp(texto, args);
        }

        return new IdentifierExp(previous->text);

    }
    if (match(Token::PI)){
        Exp *e = parseCExp();
        if (!match(Token::PD)){
            cout << "Falta paréntesis derecho" << endl;
            exit(0);
        }
        return e;
    }
    cout << "Error: se esperaba un número o identificador." << endl;
    exit(0);
}

Exp* Parser::parseUExp() {
    if(match(Token::NOT)) {
        Exp* left = parseUExp();
        return new UnaryExp(left,NOT_OP);
    }
    if (match(Token::MINUS)) {
        Exp* left = parseFactor();
        return new UnaryExp(left,MINUS_OP);
    }
    return parseFactor();
}


Exp* Parser::parseTerm() {
    Exp* left = parseUExp();
    while (match(Token::MUL) || match(Token::DIV) || match(Token::MOD)||match(Token::AND)) {
        BinaryOp op;
        if (previous->type == Token::MUL){
            op = MUL_OP;
        }
        else if (previous->type == Token::DIV){
            op = DIV_OP;
        }
        else if (previous->type ==Token::MOD) {
            op = MOD_OP;
        }
        else if (previous->type == Token::AND) {
            op = AND_OP;
        }
        Exp* right = parseUExp();
        left = new BinaryExp(left, right, op);
    }
    return left;
}

Exp* Parser::parseExpression() {
    Exp* left = parseTerm();
    while (match(Token::PLUS) || match(Token::MINUS) || match(Token::OR)) {
        BinaryOp op;
        if (previous->type == Token::PLUS){
            op = PLUS_OP;
        }
        else if (previous->type == Token::MINUS){
            op = MINUS_OP;
        }
        else if (previous->type == Token::OR) {
            op = OR_OP;
        }
        Exp* right = parseTerm();
        left = new BinaryExp(left, right, op);
    }
    return left;
}

Exp* Parser::parseCExp(){
    Exp* left = parseExpression();
    if (match(Token::LT) || match(Token::LE) || match(Token::EQ) || match(Token::GT) || match(Token::GE)){
        BinaryOp op;
        if (previous->type == Token::LT){
            op = LT_OP;
        }
        else if (previous->type == Token::LE){
            op = LE_OP;
        }
        else if (previous->type == Token::EQ){
            op = EQ_OP;
        }
        else if (previous->type == Token::GT) {
            op = GT_OP;
        }
        else if (previous->type == Token::GE) {
            op = GE_OP;
        }
        Exp* right = parseExpression();
        left = new BinaryExp(left, right, op);
    }
    return left;
}


Stm* Parser::parseStatement() {
    Stm* s = NULL;
    Exp* e = NULL;
    Stm* tb = NULL; //true case
    Stm* fb = NULL; //false case

    if (current == NULL) {
        cout << "Error: Token actual es NULL" << endl;
        exit(1);
    }

    if (match(Token::ID)) {
        string lex = previous->text;

        if (match(Token::PI)||check(Token::PC)){
            list<Exp*> args;
            if(!check(Token::PC)) {
                if (!check(Token::PD)){
                    args.push_back(parseCExp());
                    while (match(Token::COMA)){
                        args.push_back(parseCExp());
                    }
                }
                if (!match(Token::PD)){
                    cout << "Falta paréntesis derecho" << endl;
                    exit(0);
                }
            }
            return new FCallStatement(lex, args);
        }

        if (!match(Token::ASSIGN)) {
            cout << "Error: se esperaba un ':=' después del identificador." << endl;
            exit(1);
        }

        e = parseCExp();
        s = new AssignStatement(lex, e);

    } else if (match(Token::WRITELN)) {

        if (!match(Token::PI)) {
            cout << "Error: se esperaba un '(' después de 'print'." << endl;
            exit(1);
        }
        e = parseCExp();
        if (!match(Token::PD)) {
            cout << "Error: se esperaba un ')' después de la expresión." << endl;
            exit(1);
        }
        s = new PrintStatement(e);
    }
    else if (match(Token::IF)) {
        e = parseCExp();
        if (!match(Token::THEN)) {
            cout << "Error: se esperaba 'then' después de la expresión." << endl;
            cout<<current<<endl;
            cout<<current->text<<endl;
            exit(1);
        }

        tb = parseStatement();

        if (match(Token::ELSE)) {
            fb = parseStatement();
        }
        s = new IfStatement(e, tb, fb);

    }
    else if (match(Token::WHILE)) {
        e = parseCExp();
        if (!match(Token::DO)) {
            cout << "Error: se esperaba 'do' después de la expresión." << endl;
            exit(1);
        }
        tb = parseStatement();
        s = new WhileStatement(e, tb);

    }
    else if(match(Token::FOR)){
        if(!match(Token::ID)){
            cout << "Error: se esperaba 'id' después de 'for'." << endl;
            exit(1);
        }
        string lex = previous->text;
        if(!match(Token::ASSIGN)){
            cout << "Error: se esperaba ':=' después de 'for id '." << endl;
            exit(1);
        }
        Exp* start = parseCExp();

        if (!match(Token::TO)&& !match(Token::DOWNTO)) {
            cout << "Error: se esperaba 'to o downto' después de la expresión." << endl;
            exit(1);
        }
        string type_for = previous->text;
        Exp* end = parseCExp();
        if (!match(Token::DO)) {
            cout << "Error: se esperaba 'do' después de la expresión." << endl;
            exit(1);
        }
        tb = parseStatement();
        s = new ForStatement(lex,start, end, tb,type_for);
    }
    else if(match(Token::REPEAT)) {
        StatementList* stms = parseStatementList();
        if(!match(Token::UNTIL)) {
            cout << "Error: se esperaba 'until' despues de clarar los statements." << endl;
            exit(1);
        }
        e = parseCExp();
        s = new RepeatStatement(stms,e);
    }
    else if (match(Token::BEGIN)) {
        StatementList* stms = parseStatementList();
        if (!match(Token::END)) {
            cout << "Error: Se esperaba un 'end' pero se encontró: " << *current << endl;
            exit(1);
        }
        s = new BlockStatement(stms);
    }
    else {
        cout << "Error: Se esperaba un identificador o 'print', pero se encontró: " << *current << endl;
        exit(1);
    }
    return s;
}


list<Stm*> Parser::parseStmList() {
    list<Stm*> slist;
    slist.push_back(parseStatement());

    while(match(Token::PC)) {
        if(check(Token::END)) break;
        slist.push_back(parseStatement());
    }
    return slist;


    // list<Stm*> slist;
    // if(!check(Token::PC)) slist.push_back(parseStatement());
    // while(match(Token::PC)) {
    //     if(check(Token::END))break;
    //     if(check(Token::PC) ) break;
    //     slist.push_back(parseStatement());
    // }
    // return slist;

}


StatementList* Parser::parseStatementList() {
    StatementList* sl = new StatementList();
    sl->add(parseStatement());
    while(match(Token::PC)) {
        if(check(Token::ID)||check(Token::WRITELN)||check(Token::IF)||check(Token::WHILE)||check(Token::FOR)||check(Token::REPEAT)||check(Token::BEGIN))
            sl->add(parseStatement());
    }
    return sl;
}


Body* Parser::parseBody() {
    if(!match(Token::BEGIN)) {
        cout << "Error: Se esperaba un begin pero se encontró: " << *current << endl;
        exit(1);
    }
    StatementList* sl = parseStatementList();
    if(!match(Token::END)) {
        cout << "Error: Se esperaba un end pero se encontró: " << *current << endl;
        exit(1);
    }
    return new Body(sl);
}

ConstDec *Parser::parseConstDec() {
    ConstDec* cd = NULL;
    if(match(Token::ID)) {
        string id  =  previous->text;
        if(!match(Token::EQ)) {
            cout << "Error: se esperaba un '=' después de un identificador." << endl;
            exit(1);
        }
        Exp* exp = parseCExp();
        if(!match(Token::PC)) {
            cout << "Error: se esperaba un ';' después de definir una constante." << endl;
            exit(1);
        }
        cd = new ConstDec(id, exp);
    }
    return cd;
}


ConstDecList *Parser::parseConstDecList() {
    ConstDecList* cl = new ConstDecList();
    if(match(Token::CONST)) {
       ConstDec* aux= parseConstDec();
        if(aux==NULL) {
            cout << "Error: La sección 'const' debe tener al menos una declaración." << endl;
            exit(1);
        }
        while (aux != NULL) {
            cl->add(aux);
            aux = parseConstDec();
        }
    }
    return cl;

}

TypeDec* Parser::parseTypeDec() {
    TypeDec* td= NULL;
    if(match(Token::ID)) {
        string id  =  previous->text;
        if(!match(Token::EQ)) {
            cout << "Error: se esperaba un '=' después de un identificador." << endl;
            exit(1);
        }
        if( !match(Token::ID)) {//id de tipo
            cout << "Error: se esperaba un tipo después de un '='." << endl;
            exit(1);
        }
        string type =  previous->text;
        if(!match(Token::PC)) {
            cout << "Error: se esperaba un ';' después de definir una tipo." << endl;
            exit(1);
        }
        td = new TypeDec(id, type);
    }
    return td;
}

TypeDecList* Parser::parseTypeDecList() {
    TypeDecList* tl = new TypeDecList();
    if(match(Token::TYPE)) {
        TypeDec* aux= parseTypeDec();
        if(aux==NULL) {
            cout << "Error: La sección 'type' debe tener al menos una declaración." << endl;
            exit(1);
        }
        while (aux != NULL) {
            tl->add(aux);
            aux = parseTypeDec();
        }
    }
    return tl;
}


VarDec* Parser::parseVarDec() {
    VarDec* vd = NULL;
    if (match(Token::ID)) {
        list<string> ids;
        ids.push_back(previous->text);
        while (match(Token::COMA)) {
            if (!match(Token::ID)) {
                cout << "Error: se esperaba un identificador después de ','." << endl;
                exit(1);
            }
            ids.push_back(previous->text);
        }
        if (!match(Token::COLON)) {
            cout << "Error: se esperaba un ':' al final de los ids." << endl;
            exit(1);
        }
        if(!match(Token::ID)) {//id de tipo
            cout << "Error: se esperaba un tipo y se encontro" <<*current<< endl;
            exit(1);
        }
        string type = previous->text;
        if(!match(Token::PC)) {
            cout << "Error: se esperaba un ';' al final de la declaracion." << endl;
            exit(1);
        }
        vd = new VarDec(ids, type);
    }
    return vd;
}

VarDecList* Parser::parseVarDecList() {
        VarDecList* vdl = new VarDecList();
        if(match(Token::VAR)) {
            VarDec *aux = parseVarDec();
            if(aux==NULL) {
                cout << "Error: La sección 'var' debe tener al menos una declaración." << endl;
                exit(1);
            }
            while (aux != NULL) {
                vdl->add(aux);
                aux = parseVarDec();
            }
        }
        return vdl;
}




SubProgram* Parser::parseSubProgDec() {
    SubProgram* sp = NULL;
    if (match(Token::FUNCTION)||match(Token::PROCEDURE)) {
        string tsp = previous->text;
        Body* body = NULL;
        VarDecList* vdl = NULL;
        if (!match(Token::ID)) {
            cout << "Error: se esperaba un nombre de función." << endl;
            exit(1);
        }
        string fname = previous->text;
        list<list<string>> vars;
        list<string> types;
        bool ingreso = false;
        if (match(Token::PI)) {
            ingreso = true;
            // if (!match(Token::PI)) {
            //     cout << "Error: se esperaba un '(' después del nombre de la función." << endl;
            //     exit(1);
            // }
            if (!check(Token::PD)) {
                if (!check(Token::ID)) {
                    cout << "Error: se esperaba un identificador después del '('." << endl;
                    exit(1);
                }
                vars.emplace_back();
                do {
                    if(!match(Token::ID)) {
                        cout << "Error: se esperaba un identificador después de ','." << endl;
                        exit(1);
                    }
                    vars.back().emplace_back(previous->text);
                    if(match(Token::COLON)) {
                        if(!match(Token::ID)) {//id de tipo
                            cout << "Error: se esperaba un tipo después de ':'." << endl;
                            exit(1);
                        }
                        types.emplace_back(previous->text);
                        if(!match(Token::PC)) break;
                        vars.emplace_back();
                    }

                }while(match(Token::COMA));

            }
            if (!match(Token::PD)) {
                cout << "Error: se esperaba un ')' después de la lista de argumentos." << endl;
                exit(1);
            }
        }
        string rtype = "void";
        if(tsp=="function") {
            if(!match(Token::COLON)) {
                if(ingreso) cout << "Error: se esperaba un ':' después de ')'." << endl;
                else cout << "Error: se esperaba un ':' o un '(' después de un identificador."<<endl;
                exit(1);
            }
            if(!match(Token::ID)) {//id de tipo
                cout << "Error: se esperaba un tipo después de ':'." << endl;
                exit(1);
            }
            rtype = previous->text;
        }
        if(!match(Token::PC)) {
            if (tsp=="function") cout << "Error: se esperaba un ';' después de un tipo." << endl;
            else if(ingreso) cout << "Error: se esperaba un ';' después de ')'." << endl;
            else cout << "Error: se esperaba un '(' o un ';' después de un identificador." << endl;
            exit(1);
        }
        vdl = parseVarDecList();
        body = parseBody();
        if(!match(Token::PC)) {
            cout << "Error: se esperaba un ';' después de definir un subprogrma." << endl;
            exit(1);
        }
        sp = new SubProgram(fname, types, vars, rtype,vdl, body);

    }
    return sp;
}

SubProgramList* Parser::parseSubProgDecList() {
    SubProgramList* fdl = new SubProgramList();
    SubProgram *aux = parseSubProgDec();
    while (aux != NULL) {
        fdl->add(aux);
        aux = parseSubProgDec();
    }
    return fdl;
}

Program* Parser::parseProgram() {
    if(!match(Token::PROGRAM)) {
        cout << "Error: se esperaba un programa." << endl;
        exit(1);
    }
    if (!match(Token::ID)) {
        cout << "Error: se esperaba un identificador de programa." << endl;
        exit(1);
    }
    if (!match(Token::PC)) {
        cout << "Error: se esperaba un ';' de programa." << endl;
        exit(1);
    }
    Program *p = new Program();
    Section* s = NULL;
    while (check(Token::CONST) || check(Token::TYPE) || check(Token::VAR) || check(Token::FUNCTION)||check(Token::PROCEDURE)) {
        if (check(Token::CONST)) {
            s = parseConstDecList();
            p->addSection(s);
            p->consts.push_back(s);
        }
        else if (check(Token::TYPE)) {
            p->addSection(parseTypeDecList());
        }
        else if (check(Token::VAR)) {
            s = parseVarDecList();
            p->addSection(s);
            p->vars.push_back(s);
        }
        else if (check(Token::PROCEDURE)|| check(Token::FUNCTION)) {
            s = parseSubProgDecList();
            p->addSection(s);
            p->programs.push_back(s);
        }
    }
    p->addBody( parseBody());
    if (!match(Token::DOT)) {
        cout << "Error: se esperaba un '.' la final del programa." << endl;
    }
    return p;
}












