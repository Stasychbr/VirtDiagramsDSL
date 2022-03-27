#include "TerminalItem.h"

#include "Defines.h"
#include "FrameGraphicsEffect.h"

TerminalItem::TerminalItem(const QString& text, QGraphicsItem* parent)
	: TextLayoutItem(text, parent)
{
	expandTo(QSizeF(-1, GuiMetrics::ItemHeight));
	growBy(QMarginsF(GuiMetrics::TextHorMargin, 0,
							 GuiMetrics::TextHorMargin, 0));
	setGraphicsEffect(new FrameGraphicsEffect);
}
