#include <iostream>
#include <iomanip>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include <algorithm>

#define VERSION "0.0.1"

enum ExitCode {
    ARG_ERROR = 0,
    HELP_REQ = 1
};

void handleArgs(int argc, char* argv[]);
void usage(const char* problem);
void testing();

int main(int argc, char* argv[]) {
    handleArgs(argc, argv);
}

void handleArgs(int argc, char* argv[]) {
    bool shouldLex = false;
    bool shouldCompile = false;
    if (argc == 1) {
        std::cout << "Insufficient arguments supplied\n";
        std::cout << "Try ./rfc -h\n";
        return;
    }
    if (strcmp(argv[1], "-h") == 0) {
        usage("Requested help page");
        return;
    }
    if (strcmp(argv[1], "-v") == 0) {
        usage("Requested version");
        std::cout << "\tVersion : " << VERSION << std::endl;
        return;
    }

    if (strcmp(argv[1], "-c") == 0 && argc == 3) {
        Lexer l(argv[2]);
        Parser p(l.GetLexFile(), argv[2]);
    }
}

void usage(const char* problem) {
    std::cerr << problem << std::endl;
    std::cout << "Usage of rfc\n";
    std::cout << std::setw(20) << std::left << "-c <filename>" << std::setw(40) << " : Specify a valid rf-lang file to compile\n";
    std::cout << std::setw(20) << std::left << "-v" << std::setw(40) << " : Get the version of the compiler" << std::endl;
}
