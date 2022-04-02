#include "GraphicsVisitor.h"

#include <QGraphicsLinearLayout>
#include <QGraphicsWidget>

#include "GrammarElements/TerminalItem.h"
#include "GrammarElements/NonTerminalItem.h"
#include "GrammarElements/ConcatenationItem.h"
#include "GrammarElements/AlternationItem.h"
#include "GrammarElements/OptionItem.h"
#include "GrammarElements/SingleRuleItem.h"
#include "GrammarElements/RepetitionItem.h"
#include "GrammarElements/RuleListItem.h"

#include "ObservableWrapper.h"

GraphicsVisitor::GraphicsVisitor()
{

}

antlrcpp::Any GraphicsVisitor::visitRuleList(MetaGrammarParser::RuleListContext* ctx)
{
	auto ruleListItem = new RuleListItem;

	for (auto rule : ctx->singleRule()) {
		auto wrapper = visitSingleRule(rule).as<ObservableWrapper*>();
		ruleListItem->addElement(wrapper);
	}

	return static_cast<QGraphicsWidget*>(ruleListItem);
}

antlrcpp::Any GraphicsVisitor::visitSingleRule(MetaGrammarParser::SingleRuleContext* ctx)
{
	const auto& name = QString::fromStdString(ctx->name->getText());

	auto wrapper = visitAlternation(ctx->alternation()).as<ObservableWrapper*>();
	auto singleRuleItem = new SingleRuleItem(wrapper, name);

	return ObservableWrapper::wrap(singleRuleItem);
}

antlrcpp::Any GraphicsVisitor::visitAlternation(MetaGrammarParser::AlternationContext* ctx)
{
	auto alternationItem = new AlternationItem;

	for (auto concat : traversal(ctx->concatenation())) {
		auto wrapper = visitConcatenation(concat).as<ObservableWrapper*>();
		alternationItem->addElement(wrapper);
	}

	return ObservableWrapper::wrap(alternationItem);
}

antlrcpp::Any GraphicsVisitor::visitConcatenation(MetaGrammarParser::ConcatenationContext* ctx)
{
	auto concatenationItem = new ConcatenationItem;

	for (auto element : traversal(ctx->element())) {
		auto wrapper = visitElement(element).as<ObservableWrapper*>();
		concatenationItem->addElement(wrapper);
	}

	concatenationItem->flush();
	return ObservableWrapper::wrap(concatenationItem);
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
	auto wrapper = visitAlternation(ctx->alternation()).as<ObservableWrapper*>();
	auto optionItem = new OptionItem(wrapper);

	return ObservableWrapper::wrap(optionItem);
}

antlrcpp::Any GraphicsVisitor::visitRepetition(MetaGrammarParser::RepetitionContext* ctx)
{
	const auto& alernVec = ctx->alternation();

	auto wrapper = visitAlternation(alernVec[0]).as<ObservableWrapper*>();
	auto repetitionItem = new RepetitionItem(wrapper);

	if (alernVec.size() == 2) {
		switchDirection();
		wrapper = visitAlternation(alernVec[1]).as<ObservableWrapper*>();
		switchDirection();

		repetitionItem->setRepeatThrough(wrapper);
	}

	return ObservableWrapper::wrap(repetitionItem);
}

void GraphicsVisitor::switchDirection()
{
	m_direction = m_direction == Forward ? Reverse : Forward;
}
