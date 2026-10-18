#include <fstream>
#include <iostream>
#include "Lexer.h"
#include "Parser.h"

int main(int argc , char* argv[]){
    if(argc<2){
        std::cerr<<"Usage: "<<argv[0]<<"<filename>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if(!file.is_open()){
        std::cerr<<"Error: Couldn't open the file\n";
        return 1;
    }

    std::string s ,line;
    while(std::getline(file,line)){
        s+=line;
        s+="\n";
    }
    // std::cout<<s;

    Lexer lexer(s);
    auto tokens = lexer.tokenize();

    // for(auto t : tokens){
    //     std::cout<<t.lexeme<<" "<<t.line<<"\n";
    // }

    Parser parser(tokens);
    parser.parse();
    return 0;
}