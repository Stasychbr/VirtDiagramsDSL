#include "GraphicsVisitor.h"

#include <QGraphicsLinearLayout>
#include <QGraphicsAnchorLayout>
#include <QGraphicsWidget>

#include "TextLayoutItem.h"
#include "ArrowItem.h"
#include "FrameGraphicsEffect.h"

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

		currItem = visitSingleRule(rule).as<QGraphicsLayoutItem*>();
		layout->addCornerAnchors(label, Qt::BottomLeftCorner, currItem, Qt::TopLeftCorner);
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

	auto widget = new TextLayoutItem(text);
	widget->setTextAdjustment(QSizeF(15, 10));
	widget->setGraphicsEffect(new FrameGraphicsEffect);

	return static_cast<QGraphicsLayoutItem*>(widget);
}
