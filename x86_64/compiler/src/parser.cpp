#include "parser.h"
#include <sstream>

Parser::Parser(const std::string& lexFile)
:currentLine(0) {
    std::fstream fs(lexFile);
    if (!fs.is_open()) {
        printf("Could not open file %s", lexFile.c_str());
        return;
    }
    //lex file will always exist for this class
    std::string s;
    while (getline(fs, s)) {
        CompileLine(s, currentLine);
        currentLine++;
    }

    fs.close();
}

Parser::~Parser() {

}

std::vector<std::string> Parser::SplitLine(const std::string& line) {
    std::vector<std::string> words;
    std::stringstream ss(line);
    std::string s;
    while (getline(ss, s, ' ')) {
        words.push_back(s);
    }
    return words;
}

void Parser::CompileLine(const std::string& line, int lnum) {
    std::vector<std::string> words = SplitLine(line);
    if (words.size() == 0) {
    }
    else if (words[0] == "IF") {
        printf("Line %d is an %s\n", lnum, "if statement");
    }
    else if (words[0] == "FUNC") {
        printf("Line %d is a %s\n", lnum, "function declaration");
    }
    else if (words[0] == "WHILE") {
        printf("Line %d is a %s\n", lnum, "while loop");
    }
    else if (words[0] == "FOR") {
        printf("Line %d is a %s\n", lnum, "for loop");
    }
    else if (words[0] == "TYPE" && words[1] == "ID" && words[2] == "ASSIGN") {
        printf("Line %d is an %s\n", lnum, "assignment");
    }
}
