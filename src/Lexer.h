#pragma once

#include <string>
#include <vector>

#include "Token.h"

class Lexer {
private:
    std::string source;
    int current;
    int line;
    std::unordered_map<std::string,TokenType> mp = {
            {"fn",TokenType::FN},
            {"start",TokenType::START},
            {"output",TokenType::OUTPUT},
            {"input",TokenType::INPUT},
            {"var",TokenType::VARIABLE}
    };
    
    bool isAtEnd();
    bool isAlpha(char);
    bool isNum(char);
    bool isAlNum(char);
    bool match(char);

public:
    Lexer(std::string source);
    std::vector<Token> tokenize();
    char advance();
    char peek();
    Token scanString(char);
    Token scanSymbols(char);
    
};



