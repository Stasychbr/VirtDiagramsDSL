#include "TerminalItem.h"

#include "Defines.h"
#include "FrameGraphicsEffect.h"

#include <QRegularExpression>

TerminalItem::TerminalItem(const QString& text, QGraphicsItem* parent)
	: TextLayoutItem(parseText(text), parent)
{
	expandTo(QSizeF(-1, GuiMetrics::ItemHeight));
	growBy(QMarginsF(GuiMetrics::TextHorMargin, 0,
							 GuiMetrics::TextHorMargin, 0));

	auto frameEffect = new FrameGraphicsEffect;
	frameEffect->setXRoundRadius(GuiMetrics::NonTerminalRoundRad, Qt::AbsoluteSize);
	frameEffect->setYRoundRadius(1.0, Qt::RelativeSize);
	setGraphicsEffect(frameEffect);
}

QString TerminalItem::parseText(const QString& text)
{
	if (!text.startsWith('"')) {
		return text;
	}

	QRegularExpression escapeRegex("\\\\(.)");
	QString copy = text;
	copy.replace(escapeRegex, "\\1"); //replacing extra escape characters

	QRegularExpression nonSpaceRegex("\\S");
	QString cut = copy.mid(1, copy.size() - 2);
	if (cut.contains(nonSpaceRegex)) { //check for possibility replace boundary quotes
		copy = cut;
	}
	return copy;
}
