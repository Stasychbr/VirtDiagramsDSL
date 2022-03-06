#include "GraphicsVisitor.h"

#include <QGraphicsLinearLayout>

#include "TerminalWidget.h"

GraphicsVisitor::GraphicsVisitor()
{

}

antlrcpp::Any GraphicsVisitor::visitRuleList(MetaGrammarParser::RuleListContext* ctx)
{
	auto form = new QGraphicsWidget;

	auto layout = new QGraphicsLinearLayout;
	layout->setOrientation(Qt::Vertical);

	for (auto rule : ctx->singleRule()) {
		auto item = visitSingleRule(rule).as<QGraphicsLayoutItem*>();
		layout->addItem(item);
	}

	form->setLayout(layout);
	return form;
}

antlrcpp::Any GraphicsVisitor::visitSingleRule(MetaGrammarParser::SingleRuleContext* ctx)
{
	return visitAlternation(ctx->alternation());
}

antlrcpp::Any GraphicsVisitor::visitConcatenation(MetaGrammarParser::ConcatenationContext* ctx)
{
	auto layout = new QGraphicsLinearLayout;

	for (auto element : ctx->element()) {
		auto item = visitElement(element).as<QGraphicsLayoutItem*>();
		layout->addItem(item);
	}

	return static_cast<QGraphicsLayoutItem*>(layout);
}

antlrcpp::Any GraphicsVisitor::visitTerminal(MetaGrammarParser::TerminalContext* ctx)
{
	const auto& text = QString::fromStdString(ctx->getText());
	auto widget = new TerminalWidget(text);
	return static_cast<QGraphicsLayoutItem*>(widget);
}
