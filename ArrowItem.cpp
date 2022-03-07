#include "ArrowItem.h"

#include <QPainter>

ArrowItem::ArrowItem(const QSizeF& sizeHint, QGraphicsItem* parent)
	: SimpleLayoutItem(parent), m_sizeHint(sizeHint) {
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
}

void ArrowItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	const auto& boundRect = boundingRect();

	QPointF startPoint(boundRect.top(), boundRect.height() / 2.0);
	QPointF endPoint = startPoint + QPointF(boundRect.width(), 0.0);

	QPainterPath path(startPoint);
	path.lineTo(endPoint);

	const QPointF& midPoint = (startPoint + endPoint) / 2.0;
	path.moveTo(midPoint);

	QPointF bias(10.0, 10.0);
	path.lineTo(midPoint - bias);

	bias.ry() *= -1;

	path.moveTo(midPoint);
	path.lineTo(midPoint - bias);

	painter->drawPath(path);
}

QSizeF ArrowItem::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
	QSizeF sh;
	switch (which) {
		case Qt::MinimumSize:
			sh = QSizeF(20, 10);
			break;

		case Qt::PreferredSize:
			sh = m_sizeHint;
			break;

		case Qt::MaximumSize:
			sh = QSizeF();
			break;

		default:
			break;
	}
	return sh;
}
