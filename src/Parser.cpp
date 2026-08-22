#include "Parser.h"
#include "Token.h"
#include <cstdlib>
#include <vector>
#include <iostream>

Parser::Parser(std::vector<Token> tokens){
    this->tokens = tokens;
    current = 0;
}

Token Parser::peek(){
    return tokens[current];
}

Token Parser::advance(){
    Token token = tokens[current];
    if(!isAtEnd())current++;
    return token;
}

bool Parser::isAtEnd(){
    return peek().type == TokenType::END_OF_FILE;
}

bool Parser::check(TokenType type){
    return peek().type == type;
}

bool Parser::match(TokenType type){
    if(!check(type))return false;

    advance();
    return true;
}

Token Parser::consume(TokenType type){
    if(peek().type == type){
        return advance();
    }
    std::cerr<<"Syntax error at line:"<<peek().line<<" "<<peek().lexeme<<"\n";
    return Token(TokenType::ERROR,"Unexpected Token",peek().line);
}

void Parser::parse(){
    while (!isAtEnd()) {
        function();
    }
}

void Parser::function()
{
    consume(TokenType::FN);
  
    if(check(TokenType::START)){ // cant take parameters 
        if(!startfound){
            startfound=true;
            consume(TokenType::START);
        }
        else{
            std::cerr<<"Error: More than one start function found";
            exit(1);
        }
        consume(TokenType::LEFT_PAREN);
    }
    else if(check(TokenType::IDENTIFIER)){   //funtion other than start , which can also take parameters
        consume(TokenType::IDENTIFIER); 
        consume(TokenType::LEFT_PAREN);
        if(check(TokenType::IDENTIFIER)){ // used to parse through parameters if any
            consume(TokenType::IDENTIFIER);
            while (check(TokenType::COMMA)) {
                consume(TokenType::COMMA);
                consume(TokenType::IDENTIFIER);
            }
        }
    }
    consume(TokenType::RIGHT_PAREN);
    block();
}

void Parser::block(){
    consume(TokenType::LEFT_BRACE);
    while(!check(TokenType::RIGHT_BRACE) && !isAtEnd()){
        if(check(TokenType::VARIABLE)){
            declaration();
        }
        else{
            //statement();
        }
    }
    consume(TokenType::RIGHT_BRACE);
}

void Parser::declaration(){
    consume(TokenType::VARIABLE);
    consume(TokenType::IDENTIFIER);
    if(check(TokenType::ASSIGN)){
        consume(TokenType::ASSIGN);
        expression();
    }
    consume(TokenType::SEMI_COLON);
}

void Parser::expression(){
    if(check(TokenType::NUMBER)){
        consume(TokenType::NUMBER);
    }
    else if (check(TokenType::STRING)) {
        consume(TokenType::STRING);
    }
    else if(check(TokenType::IDENTIFIER)){
        consume(TokenType::IDENTIFIER);
    }
    else{
        std::cerr<<"Error: Unexpected error at line "<<peek().line<<"\n";
        exit(1);
    }
}