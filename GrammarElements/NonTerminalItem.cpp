#include "NonTerminalItem.h"

#include "Defines.h"
#include "FrameGraphicsEffect.h"

NonTerminalItem::NonTerminalItem(const QString& text, QGraphicsItem* parent)
	: TextLayoutItem(parseText(text), parent)
{
	expandTo(QSizeF(-1, GuiMetrics::ItemHeight));
	growBy(QMarginsF(GuiMetrics::TextHorMargin, 0,
							 GuiMetrics::TextHorMargin, 0));
	setGraphicsEffect(new FrameGraphicsEffect);
}

QString NonTerminalItem::parseText(const QString& text)
{
	QString copy = text;
	return copy.replace("_", " ").simplified();
}
