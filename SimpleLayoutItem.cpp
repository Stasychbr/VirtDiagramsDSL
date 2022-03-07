#include "SimpleLayoutItem.h"

SimpleLayoutItem::SimpleLayoutItem(QGraphicsItem* parent)
	: QGraphicsItem(parent) {
	setGraphicsItem(this);
}


QRectF SimpleLayoutItem::boundingRect() const
{
	QSizeF geomSize = geometry().size();
	return QRectF(QPointF(), geomSize);
}

void SimpleLayoutItem::setGeometry(const QRectF& rect)
{
	prepareGeometryChange();
	QGraphicsLayoutItem::setGeometry(rect);
	setPos(rect.topLeft());
}
