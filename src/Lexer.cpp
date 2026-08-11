#include "Lexer.h"
#include "Token.h"
#include <iostream>

Lexer::Lexer(std::string source)
{
    this->source = source;
    current = 0;
    line = 1;
}

char Lexer::advance(){
    return source[current++];
}

bool Lexer::isAtEnd(){
    return current>=source.size();
}

bool Lexer::isAlpha(char c){
    return ((c>='a' && c<='z')||(c>='A'&&c<='Z')||(c=='_'));
}

bool Lexer::isNum(char c){
    return (c>='0' && c<='9');
}

bool Lexer::isAlNum(char c){
    return isAlpha(c) || isNum(c);
}

bool Lexer::match(char c){
    if(peek()==c){
        advance();
        return true;
    }
    return false;
}

char Lexer::peek(){
    if(isAtEnd())return '\0';
    return source[current];
}

Token Lexer::scanString(){
    std::string s="";
    while(!isAtEnd() && peek()!='"'){
        s+=advance();
    }
    if(isAtEnd()){
        return Token(TokenType::ERROR,"Unterminated String",line);
    }
    advance();   // moves past second "
    return Token(TokenType::STRING,s,line);
}

Token Lexer::scanSymbols(char c){
    switch (c) {
            case '"':return (scanString()); //Tokenize strings
                   
            case '(':return(Token(TokenType::LEFT_PAREN,"(",line));
                    
            case ')':return(Token(TokenType::RIGHT_PAREN,")",line));
                    
            case ';':return (Token(TokenType::SEMI_COLON,";",line));
                    
            case '{':return (Token(TokenType::LEFT_BRACE,"{",line));
                    
            case '}':return(Token(TokenType::RIGHT_BRACE,"}",line));

            case '*':return(Token(TokenType::MUL,"*",line));

            case '/':return(Token(TokenType::DIV,"/",line));

            case '+':{  if(match('+')){
                            return(Token(TokenType::INCREMENT,"++",line));}
                        else return(Token(TokenType::ADD,"+",line));
                    }
            case '-':{  if(match('-')){
                            return(Token(TokenType::DECREMENT,"--",line));}
                        else return(Token(TokenType::SUB,"-",line));
                    }
            case '=':{  if(match('=')){
                            return(Token(TokenType::COMPARE,"==",line));}
                        else return(Token(TokenType::ASSIGN,"=",line));
                      }
            case '>':{  if(match('=')){
                            return(Token(TokenType::GREATER_OR_EQ,">=",line));}
                        else return(Token(TokenType::GREATER,">",line));
                        }
            case '<':{  if(match('=')){
                            return(Token(TokenType::LESSER_OR_EQ,"<=",line));}
                        else return(Token(TokenType::LESSER,"<",line));
                    }
            case '!':{  if(match('=')){
                            return(Token(TokenType::NOT_EQ,"!=",line));}
                        else return(Token(TokenType::NOT,"!",line));
                    }
            case '&':{  if(match('&')){
                            return(Token(TokenType::AND,"&&",line));}
                        else return(Token(TokenType::ERROR,"&",line));
                    }
            case '|':{  if(match('|')){            
                            return(Token(TokenType::OR,"||",line));}
                        else return(Token(TokenType::ERROR,"|",line));
                    }
            default:std::cout<<"Unexpected Character:"<<c<<" in line:"<<line<<"\n";
         }
    return Token(TokenType::ERROR,"",line);
}


std::vector<Token> Lexer::tokenize()
{
    std::vector<Token> tokens;
    while(!isAtEnd()){
        char c = advance();
        if(isAlpha(c)){ //Tokenize Keywords and identifiers
            std::string s ;
            s+=c;
            char t = peek();
            while(!isAtEnd() && isAlNum(t)){
                t = advance();
                s+=t;
                t = peek();
            };
            if (mp.count(s)){
                tokens.push_back(Token(mp[s],s,line));
            }
            else tokens.push_back(Token(TokenType::IDENTIFIER,s,line));
        }
        else if(isNum(c)){      //Tokenize Numbers 
            std::string s ;
            s+=c;
            char t = peek();
            while(!isAtEnd() && isNum(t)){
                t=advance();
                s+=t;
                t=peek();
            }
            tokens.push_back(Token(TokenType::NUMBER,s,line));
        }
        else{   //Tokenize symbols and strings 
            if(c==' ' || c=='\r' || c=='\t')continue;
            
            if(c=='\n'){
                line++;
                continue;
            }
            if(c=='/'){
                if (peek()=='/'){
                    while(!isAtEnd() && peek()!='\n')advance();
                    continue;
                }
            }
            tokens.push_back(scanSymbols(c));
        }
    }
    tokens.push_back(Token(TokenType::END_OF_FILE,"EOF",line));
    return tokens;
}



