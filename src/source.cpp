#include <iostream>
#include "Lexer.h"

int main(){
    std::string s;
    getline(std::cin,s);
    Lexer lexer(s);
    auto tokens = lexer.tokenize();

    for(auto i:tokens){
        std::cout<<i.lexeme<<" "<<"\n";
    }
}