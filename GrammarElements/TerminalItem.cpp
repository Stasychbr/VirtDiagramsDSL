#include "TerminalItem.h"

#include "../Defines.h"
#include "../FrameGraphicsEffect.h"

TerminalItem::TerminalItem(const QString& text, QGraphicsItem* parent)
	: TextLayoutItem(text, parent)
{
	expandTo(QSizeF(-1, GuiMetrics::ItemHeight));
	growBy(QMarginsF(GuiMetrics::TextHorMargin, 0,
							 GuiMetrics::TextHorMargin, 0));

	auto frameEffect = new FrameGraphicsEffect;
	frameEffect->setXRoundRadius(GuiMetrics::NonTerminalRoundRad, Qt::AbsoluteSize);
	frameEffect->setYRoundRadius(1.0, Qt::RelativeSize);
	setGraphicsEffect(frameEffect);
}
