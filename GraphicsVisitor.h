#pragma once

#include <QGraphicsLayoutItem>

#include "antlr/MetaGrammar/MetaGrammarBaseVisitor.h"

class GraphicsVisitor : public MetaGrammarBaseVisitor
{
public:
	GraphicsVisitor();

	antlrcpp::Any visitRuleList(MetaGrammarParser::RuleListContext* ctx) override;
	antlrcpp::Any visitSingleRule(MetaGrammarParser::SingleRuleContext* ctx) override;
	antlrcpp::Any visitConcatenation(MetaGrammarParser::ConcatenationContext* ctx) override;
	antlrcpp::Any visitTerminal(MetaGrammarParser::TerminalContext* ctx) override;
};

