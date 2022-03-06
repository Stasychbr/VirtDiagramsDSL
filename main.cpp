#include <antlr4-runtime.h>

#include "antlr/MetaGrammar/MetaGrammarParser.h"
#include "antlr/MetaGrammar/MetaGrammarLexer.h"

using namespace std;
using namespace antlr4;

int main(int argc, const char* argv[]) {
    std::ifstream stream;
    stream.open("rules.txt");
    
    ANTLRInputStream input(stream);
    MetaGrammarLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    MetaGrammarParser parser(&tokens);    
    auto tree = parser.rulelist();

    return 0;
}