#include "parser.h"
#include <sstream>
#include <algorithm>

Parser::Parser(const std::string& lexFilePath, const std::string& sourceFilePath)
:currentLineNum(1) {
    std::fstream lex_fs(lexFilePath);
    std::fstream source_fs(sourceFilePath);
    if (!source_fs.is_open()) {
        printf("Could not open file %s", lexFilePath.c_str());
        return;
    }
    if (!lex_fs.is_open()) {
        printf("Could not open file %s", sourceFilePath.c_str());
        return;
    }

    printf("\n\nPARSER\n");
    //lex file will always exist for this class
    std::vector<Result> errorResults;
    std::vector<std::string> lexLines = ReadToLineVec(lex_fs);
    std::vector<std::string> sourceLines = ReadToLineVec(source_fs);

    for (int i = 0; i < lexLines.size(); i++) {
        if (lexLines[i].empty()) {
            continue;
        }
        std::vector<std::string> words = SplitLine(lexLines[i]);
        Result r = CheckLineSyntax(words, sourceLines[i], currentLineNum);
        if (r.wasError) {
            errorResults.push_back(r);
        }
        currentLineNum++;
    }

    for (Result r : errorResults) {
        r.Print();
    }
    fs.close();
}

Parser::~Parser() {}

std::vector<std::string> Parser::ReadToLineVec(std::fstream& fs) {
    std::vector<std::string> lines;
    if (fs.is_open()) {
        std::string line;
        while(getline(fs, line)) {
            std::string trimmed = Trim(line);
            if (trimmed[0] == '/' && trimmed[1] == '/') {
                continue;
            }
            lines.push_back(trimmed);
        }
    }
    else {
        printf("File stream not open\n");
        return {};
    }
    return lines;
}

void Parser::PrintStrVec(const std::vector<std::string>& lines) {
    printf("[");
    for (int i = 0; i < lines.size(); i++) {
        printf("%d=%s", i, lines[i].c_str());
        if (i < lines.size() - 1)
            printf(", ");
    }
    printf("]\n");
}

//https://stackoverflow.com/questions/1798112/removing-leading-and-trailing-spaces-from-a-string
std::string Parser::Trim(const std::string& str)
{
    const auto strBegin = str.find_first_not_of(" \t");
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(" \t");
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
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

Result Parser::CheckLineSyntax(const std::vector<std::string>& words, const std::string& sourceLine, int lnum) {
    printf("Checking [%3d] : %s\n", lnum, sourceLine.c_str());
    //PrintStrVec(words);
    //printf("\n");
    if (words[0] == "FUNC") {
        if (words[1] != "ID")
            return Result(true, "Function decl", "Missing function name", lnum, sourceLine);

        if (words[2] != "OPEN_PAREN")
            return Result(true, "Function decl", "Missing open parenthesis", lnum, sourceLine);

        if (words[words.size() - 1] != "OPEN_BRACE")
            return Result(true, "Function decl", "Missing braces for scope", lnum, sourceLine);

        if (words[words.size() - 2] != "TYPE")
            return Result(true, "Function decl", "Missing return type", lnum, sourceLine);

        if (words[words.size() - 3] != "ARROW")
            return Result(true, "Function decl", "Missing arrow", lnum, sourceLine);

        if (words[words.size() - 4] != "CLOSE_PAREN")
            return Result(true, "Function decl", "Missing closing parenthesis", lnum, sourceLine);

        return Result(false, "Function decl", "No errors", lnum, sourceLine);
    }
    //VARIABLE DECLARATION
    else if (words[0] == "TYPE") {
        if (words[1] != "ID")
            return Result(true, "Var decl", "Missing name for variable", lnum, sourceLine);

        if (words[2] != "ASSIGN" && words[2] != "OPEN_PAREN")
            return Result(true, "Var decl", "Missing equals sign for variable assignment", lnum, sourceLine);

        return Result(false, "Var decl", "No errors", lnum, sourceLine);
    }
    else if (words[0] == "ID") {
        if (words[1] != "ASSIGN" || (words[1] != "PLUS" && words[2] != "PLUS") || (words[1] != "MINUS" && words[2] != "MINUS"))
            return Result(true, "Assignment", "Attempting to use id without assignment", lnum, sourceLine);
        
        return Result(false, "Assignment", "No errors", lnum, sourceLine);
    }
    return Result(false, "Unknown", "Feature encountered that's not implemented", lnum, sourceLine);
}
