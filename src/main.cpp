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

class Token{
    TokenType type;
    optional<string> value;
};

vector<Token> tokenize(const string& str){
    for(char c : str){
        cout<< c << endl;
    }
};

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
    tokenize(contents);
//    cout<<contents<<endl;
    return EXIT_SUCCESS;
}
