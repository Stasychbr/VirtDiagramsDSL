#include "GraphicsVisitor.h"

#include <QGraphicsLinearLayout>

#include "TerminalWidget.h"
#include "ArrowItem.h"

GraphicsVisitor::GraphicsVisitor()
{

}

antlrcpp::Any GraphicsVisitor::visitRuleList(MetaGrammarParser::RuleListContext* ctx)
{
	auto form = new QGraphicsWidget;

	auto layout = new QGraphicsLinearLayout;
	layout->setOrientation(Qt::Vertical);

	for (auto rule : ctx->singleRule()) {
		const std::string& ruleName = rule->name->getText();

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

antlrcpp::Any GraphicsVisitor::visitAlternation(MetaGrammarParser::AlternationContext* ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any GraphicsVisitor::visitConcatenation(MetaGrammarParser::ConcatenationContext* ctx)
{
	auto layout = new QGraphicsLinearLayout;
	layout->setSpacing(0.0);

	QSizeF arrowSize = { 100, 20 };
	auto addArrow = [layout, &arrowSize] () {
		auto arrow = new ArrowItem(arrowSize);
		layout->addItem(arrow);
		layout->setAlignment(arrow, Qt::AlignVCenter);
	};

	addArrow();

	for (auto element : ctx->element()) {
		auto item = visitElement(element).as<QGraphicsLayoutItem*>();
		layout->addItem(item);
		addArrow();
	}

	return static_cast<QGraphicsLayoutItem*>(layout);
}

antlrcpp::Any GraphicsVisitor::visitTerminal(MetaGrammarParser::TerminalContext* ctx)
{
	const auto& text = QString::fromStdString(ctx->getText());
	auto widget = new TerminalWidget(text);
	return static_cast<QGraphicsLayoutItem*>(widget);
}
