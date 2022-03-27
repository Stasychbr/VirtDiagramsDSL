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

void TextLayoutItem::expandTo(const QSizeF& size)
{
	m_sizeHint = m_sizeHint.expandedTo(size);
	updateGeometry();
}

void TextLayoutItem::growBy(const QMarginsF& margins)
{
	m_sizeHint = m_sizeHint.grownBy(margins);
	updateGeometry();
}

void TextLayoutItem::setFont(const QFont& font)
{
	m_font = font;
	updateTextSize();
}

QSizeF TextLayoutItem::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
	return m_sizeHint;
}

void TextLayoutItem::updateTextSize()
{
	QFontMetrics metrics(m_font);
	expandTo(metrics.size(0, m_text));
}
