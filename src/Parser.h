#pragma once //makes it so even if the file is included multiple times its only processed once 

#include "Token.h"
#include <vector>
class Parser{
    private:
        std::vector<Token> tokens;
        int current;
        bool startfound=false;

        Token peek();
        Token advance();

        bool isAtEnd();
        bool check(TokenType type);
        bool match(TokenType type);
        Token consume(TokenType type);

        void function();
        void block();
        
        void declaration();
        void expression();
        void multi_div();
        void term();
        
        void statement();
        void parse_keyword();
        public:
            Parser(std::vector<Token> tokens);
            void parse();
};