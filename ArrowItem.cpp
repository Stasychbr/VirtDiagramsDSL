#include "ArrowItem.h"

#include <QPainter>

ArrowItem::ArrowItem(const QSizeF& sizeHint, QGraphicsItem* parent)
	: QGraphicsItem(parent), m_sizeHint(sizeHint) {
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	setGraphicsItem(this);
}

QRectF ArrowItem::boundingRect() const
{
	QSizeF geomSize = geometry().size();
	return QRectF(QPointF(), geomSize);
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

void ArrowItem::setGeometry(const QRectF& rect)
{
	prepareGeometryChange();
	QGraphicsLayoutItem::setGeometry(rect);
	setPos(rect.topLeft());
}

QSizeF ArrowItem::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
	return m_sizeHint;
}
