#ifndef LEXER_H
#define LEXER_H
#include <fstream>
#include <vector>
#include <map>
#include <filesystem>

class Lexer {
    public:
        Lexer(std::filesystem::path filepath);
        ~Lexer();
        std::string GetLexFile() const;

    private:
        std::fstream fileStream;
        std::filesystem::path inputRFpath;
        std::string lexFile;
        std::string fullCode;
        std::vector<std::pair<std::string, std::string>> regvec;
        int lineNumber;
};

#endif
