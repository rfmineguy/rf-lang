#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <fstream>
#include <vector>

class Parser {
    public:
        Parser(const std::string& lexFile);
        ~Parser();

    private:
        std::vector<std::string> SplitLine(const std::string& line);
        void CompileLine(const std::string& line, int lNum);

    private:
        std::fstream fs;
        int currentLine;
};

#endif
