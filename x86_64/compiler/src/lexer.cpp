#include "lexer.h"
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
#include <algorithm>
#include <regex>

Lexer::Lexer(std::filesystem::path filepath)
:lineNumber(0), lexFile("N/A"), inputRFpath(filepath) {
    fileStream.open(filepath);
    if (fileStream.fail()) {
        std::cout << "Failed to open file\n";
    }
    printf("Parent path: %s\n", filepath.parent_path().c_str());
    
    std::string s;
    while (getline(fileStream, s)) {
        s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
        if (s[0] == '/' && s[1] == '/')
            continue;
        fullCode.append(s + '\n');
    }
    
    printf("\033[33m%s\n", fullCode.c_str());
    printf("\033[39m\n");

    std::vector<std::pair<std::string, std::string>> vec;
    vec.push_back(std::make_pair("byte|word|dword|qword|void",   "TYPE "));
    vec.push_back(std::make_pair("\"([^\"]*)\"","SLITERAL "));
    vec.push_back(std::make_pair("fun",          "FUNC "));
    vec.push_back(std::make_pair("ret",          "RET "));
    vec.push_back(std::make_pair("for",          "FOR "));
    vec.push_back(std::make_pair("while",        "WHILE "));
    vec.push_back(std::make_pair("(or|\\|\\|)",  "OR "));
    vec.push_back(std::make_pair("(and|\\&\\&)", "AND "));
    vec.push_back(std::make_pair("if",           "IF "));
    vec.push_back(std::make_pair("0b[0-1]+",     "BLITERAL "));
    vec.push_back(std::make_pair("0x[0-9]+",     "HLITERAL "));
    vec.push_back(std::make_pair("[0-9]+",       "DLITERAL "));
    vec.push_back(std::make_pair("[a-z]+",       "ID "));
    vec.push_back(std::make_pair(",",            "COMMA "));
    vec.push_back(std::make_pair("\\(",          "OPEN_PAREN "));
    vec.push_back(std::make_pair("\\)",          "CLOSE_PAREN "));
    vec.push_back(std::make_pair("\\[",          "OPEN_BRACKET "));
    vec.push_back(std::make_pair("\\]",          "CLOSE_BRACKET "));
    vec.push_back(std::make_pair("\\{",          "OPEN_BRACE "));
    vec.push_back(std::make_pair("\\}",          "CLOSE_BRACE "));
    vec.push_back(std::make_pair("->",           "ARROW "));
    vec.push_back(std::make_pair(";",            "SEMI "));
    vec.push_back(std::make_pair("<=",           "LESSTHAN_EQ "));
    vec.push_back(std::make_pair("<",            "LESSTHAN "));
    vec.push_back(std::make_pair("=>",           "GREATERTHAN_EQ "));
    vec.push_back(std::make_pair(">",            "GREATERTHAN "));
    vec.push_back(std::make_pair("==",           "TEST_EQ "));
    vec.push_back(std::make_pair("=",            "ASSIGN "));
    vec.push_back(std::make_pair("\\+",          "PLUS "));
    vec.push_back(std::make_pair("\\-",          "MINUS "));
    vec.push_back(std::make_pair("\\*",          "MUL "));
    vec.push_back(std::make_pair("\\/",          "DIV "));
    
    for (auto& pair : vec) {
        try {
            fullCode = std::regex_replace(fullCode, std::regex(pair.first), pair.second.c_str());
        } catch (std::regex_error e) {
            printf("\033[31mERROR: Regex Error in [%s]\n", pair.first.c_str());
            printf("%s", e.what());
            printf("\033[39m\n");
        }
    }
    printf("%s\n", fullCode.c_str());
    printf("Lexed source code written to %s/%s\n", filepath.parent_path().c_str(), "main.lex");
    fileStream.close();
    std::filesystem::path lexPath = filepath.replace_extension("lex");
    fileStream.open(lexPath, std::ios::out);
    if (!fileStream.is_open()) {
        printf("Couldn't open %s\n", lexPath.c_str());
    } 
    fileStream.write(fullCode.c_str(), fullCode.size());
    fileStream.close();

    lexFile = lexPath.string();
}

Lexer::~Lexer() {

}

std::string Lexer::GetLexFile() const {
    return lexFile;
}
