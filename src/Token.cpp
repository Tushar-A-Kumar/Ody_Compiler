#include "Token.h"

Token::Token(TokenType type, std::string lexeme, int line)
{
    this->type = type;
    this->lexeme = lexeme;
    this->line = line;
}