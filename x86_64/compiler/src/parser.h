#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <fstream>
#include <vector>

struct Result {
    public:
        Result(bool wasError, const std::string& t, const std::string& m, int l, const std::string& s) 
            :wasError(wasError), type(t), message(m), line(l), source(s) {}
        
        void Print() {
            printf("ERROR: Line=%d, %s\n", line, source.c_str());
            printf("\t%s, %s\n", type.c_str(), message.c_str());
        }

    public:
        bool wasError;
        std::string type;
        std::string message;
        int line;
        std::string source;
};

class Parser {
    public:
        Parser(const std::string& lexFilePath, const std::string& sourceFilePath);
        ~Parser();

    private:
        std::vector<std::string> SplitLine(const std::string& line);
        Result CheckLineSyntax(const std::vector<std::string>& line, const std::string& sourceLine, int lNum);
        void ClassifyLine(Result& r);

    private:
        void PrintStrVec(const std::vector<std::string>& line);
        std::vector<std::string> ReadToLineVec(std::fstream& fs);
        std::string Trim(const std::string& line);

    private:
        std::fstream fs;
        int currentLineNum;
};

#endif
