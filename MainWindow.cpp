#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QGraphicsWidget>
#include <QGraphicsScene>

#include <antlr4-runtime.h>

#include "antlr/MetaGrammar/MetaGrammarParser.h"
#include "antlr/MetaGrammar/MetaGrammarLexer.h"

#include "GraphicsVisitor.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	auto scene = new QGraphicsScene(this);
	ui->graphicsView->setScene(scene);

	std::ifstream stream;
	stream.open("rules.txt");

	antlr4::ANTLRInputStream input(stream);
	MetaGrammarLexer lexer(&input);
	antlr4::CommonTokenStream tokens(&lexer);
	MetaGrammarParser parser(&tokens);

	GraphicsVisitor visitor;
	auto rulesList = parser.ruleList();
	auto widget = visitor.visit(rulesList).as<QGraphicsWidget*>();
	scene->addItem(widget);
	widget->setMaximumSize(200, 200);
}

MainWindow::~MainWindow()
{
	delete ui;
}
