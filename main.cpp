#include <QApplication>

#include <antlr4-runtime.h>

#include "antlr/MetaGrammar/MetaGrammarParser.h"
#include "antlr/MetaGrammar/MetaGrammarLexer.h"

#include "MainWindow.h"

int main(int argc, char* argv[]) {
    std::ifstream stream;
    stream.open("rules.txt");
    
	antlr4::ANTLRInputStream input(stream);
	MetaGrammarLexer lexer(&input);
	antlr4::CommonTokenStream tokens(&lexer);
	MetaGrammarParser parser(&tokens);
    auto tree = parser.rulelist();

	QApplication app(argc, argv);
	MainWindow w;
	w.show();

	return app.exec();
}
