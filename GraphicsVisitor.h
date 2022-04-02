#pragma once

#include <QGraphicsLayoutItem>

#include "antlr/MetaGrammar/MetaGrammarBaseVisitor.h"

class GraphicsVisitor : public MetaGrammarBaseVisitor
{
public:
	GraphicsVisitor();

	antlrcpp::Any visitRuleList(MetaGrammarParser::RuleListContext* ctx) override;
	antlrcpp::Any visitSingleRule(MetaGrammarParser::SingleRuleContext* ctx) override;
	antlrcpp::Any visitAlternation(MetaGrammarParser::AlternationContext* ctx) override;
	antlrcpp::Any visitConcatenation(MetaGrammarParser::ConcatenationContext* ctx) override;
	antlrcpp::Any visitTerminal(MetaGrammarParser::TerminalContext* ctx) override;
	antlrcpp::Any visitNonTerminal(MetaGrammarParser::NonTerminalContext* ctx) override;
	antlrcpp::Any visitGroup(MetaGrammarParser::GroupContext* ctx) override;
	antlrcpp::Any visitOption(MetaGrammarParser::OptionContext* ctx) override;
	antlrcpp::Any visitRepetition(MetaGrammarParser::RepetitionContext* ctx) override;

private:
	enum Direction {
		Forward,
		Reverse,
	};

	void switchDirection();

	template<class T>
	std::vector<T> traversal(const std::vector<T> vec) const {
		std::vector<T> traversal = vec;
		if (m_direction == Reverse) {
			std::reverse(traversal.begin(), traversal.end());
		}
		return traversal;
	}

	Direction m_direction = Forward;
};

