#include "TerminalWidget.h"

#include <QPainter>
#include <QPen>

TerminalWidget::TerminalWidget(const QString& text, QGraphicsItem* parent)
	: QGraphicsWidget(parent), m_text(text) {
	updateMinSize();
}

void TerminalWidget::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	qreal penWidth = painter->pen().widthF();

	QRectF adjusted = m_textRect.adjusted(0, 0, -penWidth, -penWidth);
	painter->drawRect(adjusted);
	painter->drawText(adjusted, Qt::AlignCenter, m_text);
}

void TerminalWidget::setRectAdjustment(qreal dx, qreal dy)
{
	m_widthAdj = dx;
	m_heightAdj = dy;
}

bool TerminalWidget::event(QEvent* event)
{
	if (event->type() == QEvent::FontChange) {
		updateMinSize();
		QGraphicsWidget::event(event);
		return true;
	}

	return QGraphicsWidget::event(event);
}

void TerminalWidget::updateMinSize()
{
	QFontMetrics metrics(font());
	QSize textSize = metrics.size(0, m_text);

	m_textRect = QRectF(QPointF(), textSize);
	m_textRect.adjust(0, 0, 2 * m_widthAdj, 2 * m_heightAdj);

	setMinimumSize(m_textRect.size());
}
