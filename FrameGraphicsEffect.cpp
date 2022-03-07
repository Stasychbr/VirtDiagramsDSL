#include "FrameGraphicsEffect.h"

#include <QPainter>

FrameGraphicsEffect::FrameGraphicsEffect(QObject* parent) : QGraphicsEffect(parent) {}

void FrameGraphicsEffect::draw(QPainter* painter)
{
	QRectF sourceRect = sourceBoundingRect();
	qreal penWidth = painter->pen().widthF();
	sourceRect.adjust(0, 0, -penWidth, -penWidth);
	painter->drawRect(sourceRect);

	drawSource(painter);
}
