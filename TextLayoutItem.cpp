#include "TextLayoutItem.h"

#include <QPainter>
#include <QPen>

TextLayoutItem::TextLayoutItem(const QString& text, QGraphicsItem* parent)
	: SimpleLayoutItem(parent), m_text(text) {

	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	updateTextSize();
}

void TextLayoutItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->drawText(boundingRect(), Qt::AlignCenter, m_text);
}

void TextLayoutItem::setTextAdjustment(const QSizeF& adj)
{
	m_textAdj = adj;
	updateGeometry();
}

void TextLayoutItem::setFont(const QFont& font)
{
	m_font = font;
	updateTextSize();
}

QSizeF TextLayoutItem::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
	QSizeF sh;

	switch (which) {
	case Qt::MinimumSize:
		sh = m_textSize;
		break;

	case Qt::PreferredSize:
	case Qt::MaximumSize:
		sh = m_textSize +  2 * m_textAdj;
		break;

	default:
		break;
	}

	return sh;
}

void TextLayoutItem::updateTextSize()
{
	QFontMetrics metrics(m_font);
	m_textSize = metrics.size(0, m_text);
	updateGeometry();
}
