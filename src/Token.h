#pragma once

#include <string>
#include <unordered_map>

enum class TokenType {
    FN,
    START,
    OUTPUT,
    INPUT,

    IDENTIFIER,
    VARIABLE,
    STRING,
    NUMBER,

    LEFT_PAREN,
    RIGHT_PAREN,

    LEFT_BRACE,
    RIGHT_BRACE,

    SEMI_COLON,
    COMMA,

    ASSIGN,
    COMPARE,
    ADD,
    SUB,
    MUL,
    DIV,
    GREATER,
    LESSER,
    GREATER_OR_EQ,
    LESSER_OR_EQ,
    NOT,
    NOT_EQ,

    INCREMENT,
    DECREMENT,

    AND,
    OR,

    ERROR,
    END_OF_FILE
};

class Token {

public:
    TokenType type;
    std::string lexeme;
    int line;
  

    Token(TokenType type, std::string lexeme, int line);
};
