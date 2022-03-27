#include "SimpleLayoutItem.h"

SimpleLayoutItem::SimpleLayoutItem(QGraphicsItem* parent)
	: QGraphicsObject(parent) {
	setGraphicsItem(this);
}


QRectF SimpleLayoutItem::boundingRect() const
{
	QSizeF geomSize = geometry().size();
	return QRectF(QPointF(), geomSize);
}

void SimpleLayoutItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	Q_UNUSED(painter);
	Q_UNUSED(option);
	Q_UNUSED(widget);
}

void SimpleLayoutItem::setGeometry(const QRectF& rect)
{
	prepareGeometryChange();
	QGraphicsLayoutItem::setGeometry(rect);
	setPos(rect.topLeft());

	Q_EMIT geometryChanged();
}
