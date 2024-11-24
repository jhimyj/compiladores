#include <iostream>
#include <fstream>
#include <string>
#include "scanner.h"
#include "parser.h"
#include "visitor.h"
#include "imp_interpreter.hh"
#include "imp_type_checker.h"
#include "imp_type.hh"
#include "imp_codegen.h"
using namespace std;

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        cout << "Numero incorrecto de argumentos. Uso: " << argv[0] << " <archivo_de_entrada>" << endl;
        exit(1);
    }

    ifstream infile(argv[1]);
    if (!infile.is_open()) {
        cout << "No se pudo abrir el archivo: " << argv[1] << endl;
        exit(1);
    }

    string input;
    string line;
    while (getline(infile, line)) {
        input += line + '\n';
    }
    infile.close();

    Scanner scanner(input.c_str());
    string input_copy = input;
    Scanner scanner_test(input_copy.c_str());
    test_scanner(&scanner_test);
    cout << "Scanner exitoso" << endl;
    cout << endl;
    cout << "Iniciando parsing:" << endl;
    Parser parser(&scanner);
    try {

        Program* program = parser.parseProgram();
        cout << "Parsing exitoso" << endl << endl;
        // cout << "Iniciando Visitor:" << endl;
        // PrintVisitor printVisitor;
        // ImpInterpreter interpreter;
        // cout << endl;
        // cout << "IMPRIMIR:" << endl;
        // printVisitor.imprimir(program);
        // cout  << endl;
        // cout << endl << "Run program:" << endl;
        // interpreter.interpret(program);
        // cout << "End of program execution" << endl;
        ImpTypeChecker typeChecker;



        cout << "TypeChecker:" << endl;
        typeChecker.typecheck(program);
        cout << "TypeChecker exitoso" << endl;

        ImpCodeGen* codegen = new ImpCodeGen(&typeChecker);
        cout << endl << "Generar codigo:" << endl;
        string filename =  argv[1];
        codegen->codegen(program, filename + ".sm");
        cout << "End of program execution" << endl;
        delete program;
    } catch (const exception& e) {
        cout << "Error durante la ejecución: " << e.what() << endl;
        return 1;
    }

    return 0;
}