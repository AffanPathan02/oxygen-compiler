#include<iostream>
#include<fstream>
#include<sstream>
#include <optional>
#include <vector>

using namespace std;

enum class TokenType {
    _return,
    int_lit,
    semi
};

struct Token{
    TokenType type;
    optional<string> value{};
};

vector<Token> tokenize(const string& str){
    std::vector<Token> tokens;

    std::string buf;
    for (int i = 0; i < str.length(); i++)
    {
        char c = str.at(i);
        if (std::isalpha(c))
        {
            buf.push_back(c);
            i++;
            while (std::isalnum(str.at(i)))
            {
                buf.push_back(str.at(i));
                i++;
            }
            i--;
            if (buf == "return")
            {
                tokens.push_back({.type = TokenType::_return});
                buf.clear();
                continue;
            } else
            {
                std::cerr << "You messed up!" << std::endl;
                exit(EXIT_FAILURE);
            }
        } else if (std::isdigit(c))
        {
            buf.push_back(c);
            i++;
            while (std::isdigit(str.at(i)))
            {
                buf.push_back(str.at(i));
                i++;
            }
            i--;
            tokens.push_back({.type = TokenType::int_lit, .value = buf});
            buf.clear();
        } else if (c == ';')
        {
            tokens.push_back({.type = TokenType::semi});
        } else if (std::isspace(c))
        {
            continue;
        } else
        {
            std::cerr << "You messed up!" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    return tokens;
};

string tokens_to_asm(const vector<Token>& tokens){
    stringstream output;
    output<< "global _start\n_start:\n ";
    for (int i = 0; i < tokens.size(); i++) {
        const Token& token = tokens.at(i);
        if(token.type == TokenType::_return){
            if(i+1 <tokens.size() && tokens.at(i+1).type==TokenType::int_lit){
                if(i+2 < tokens.size() && tokens.at(i+2).type == TokenType::semi){
                    output << "    mov rax, 60\n";
                    output << "    mov rdi, " << tokens.at(i + 1).value.value() << "\n";
                    output << "    syscall";
                }
            }
        }
    }
    return output.str();
}

int main(int argc, char* argv[]){
    if (argc != 2){
        cerr << "Incorrect Usage. Correct Usage .."<<endl;
        cerr <<"oxy <input.ox>"<<endl;
        return EXIT_FAILURE;
    }

    string contents;
    {
        stringstream contents_stream;
        fstream input(argv[1] ,ios::in);
        contents_stream << input.rdbuf();
        contents=contents_stream.str();
    }
    std::vector<Token> tokens = tokenize(contents);

    {
        fstream file("out.asm",ios::out);
        file<<tokens_to_asm(tokens);
    }


    system("nasm -felf64 out.asm");
    system("ld -o out out.o");

//    cout<<contents<<endl;
    return EXIT_SUCCESS;
}
