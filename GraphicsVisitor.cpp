#include "GraphicsVisitor.h"

#include <QGraphicsLinearLayout>
#include <QGraphicsAnchorLayout>
#include <QGraphicsWidget>

#include "GrammarElements/TerminalItem.h"
#include "GrammarElements/NonTerminalItem.h"
#include "GrammarElements/ConcatBuilder.h"
#include "GrammarElements/AlternBuilder.h"
#include "GrammarElements/OptionBuilder.h"
#include "GrammarElements/RuleBuilder.h"

#include "ObservableWrapper.h"

GraphicsVisitor::GraphicsVisitor()
{

}

antlrcpp::Any GraphicsVisitor::visitRuleList(MetaGrammarParser::RuleListContext* ctx)
{
	auto form = new QGraphicsWidget;

	auto layout = new QGraphicsAnchorLayout;
	const auto& ruleVector = ctx->singleRule();

	QGraphicsLayoutItem* currItem = nullptr;
	for (int i = 0; i < ruleVector.size(); i++) {
		auto rule = ruleVector[i];

		QString ruleName = QString::fromStdString(rule->name->getText());
		auto label = new TextLayoutItem(ruleName);

		if (i == 0) {
			layout->addCornerAnchors(label, Qt::TopLeftCorner, layout, Qt::TopLeftCorner);

		} else {
			layout->addCornerAnchors(currItem, Qt::BottomLeftCorner, label, Qt::TopLeftCorner);
		}

		currItem = visitSingleRule(rule).as<ObservableWrapper*>()->layoutItem();
		layout->addCornerAnchors(label, Qt::BottomLeftCorner, currItem, Qt::TopLeftCorner);
	}

	form->setLayout(layout);
	layout->activate();
	return form;
}

antlrcpp::Any GraphicsVisitor::visitSingleRule(MetaGrammarParser::SingleRuleContext* ctx)
{
	RuleBuilder builder;

	auto wrapper = visitAlternation(ctx->alternation()).as<ObservableWrapper*>();
	builder.setElement(wrapper);

	return ObservableWrapper::wrap(builder.build());
}

antlrcpp::Any GraphicsVisitor::visitAlternation(MetaGrammarParser::AlternationContext* ctx)
{
	AlternBuilder builder;

	for (auto element : ctx->concatenation()) {
		auto wrapper = visitConcatenation(element).as<ObservableWrapper*>();
		builder.addElement(wrapper);
	}

	return ObservableWrapper::wrap(builder.build());
}

antlrcpp::Any GraphicsVisitor::visitConcatenation(MetaGrammarParser::ConcatenationContext* ctx)
{
	ConcatBuilder builder;

	for (auto element : ctx->element()) {
		auto wrapper = visitElement(element).as<ObservableWrapper*>();
		builder.addElement(wrapper);
	}

	return ObservableWrapper::wrap(builder.build());
}

antlrcpp::Any GraphicsVisitor::visitTerminal(MetaGrammarParser::TerminalContext* ctx)
{
	const auto& text = QString::fromStdString(ctx->getText());
	auto item = new TerminalItem(text);
	return ObservableWrapper::wrap(item);
}

antlrcpp::Any GraphicsVisitor::visitNonTerminal(MetaGrammarParser::NonTerminalContext* ctx)
{
	const auto& text = QString::fromStdString(ctx->getText());
	auto item = new NonTerminalItem(text);
	return ObservableWrapper::wrap(item);
}

antlrcpp::Any GraphicsVisitor::visitGroup(MetaGrammarParser::GroupContext* ctx)
{
	return visit(ctx->alternation());
}

antlrcpp::Any GraphicsVisitor::visitOption(MetaGrammarParser::OptionContext* ctx)
{
	OptionBuilder builder;

	auto wrapper = visitAlternation(ctx->alternation()).as<ObservableWrapper*>();
	builder.setElement(wrapper);

	return ObservableWrapper::wrap(builder.build());
}
