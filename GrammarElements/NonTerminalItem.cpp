#include "NonTerminalItem.h"

#include "../Defines.h"
#include "../FrameGraphicsEffect.h"

NonTerminalItem::NonTerminalItem(const QString& text, QGraphicsItem* parent)
	: TextLayoutItem(text, parent)
{
	expandTo(QSizeF(-1, GuiMetrics::ItemHeight));
	growBy(QMarginsF(GuiMetrics::TextHorMargin, 0,
							 GuiMetrics::TextHorMargin, 0));
	setGraphicsEffect(new FrameGraphicsEffect);
}
