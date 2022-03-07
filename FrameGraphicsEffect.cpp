#include "FrameGraphicsEffect.h"

#include <QPainter>

FrameGraphicsEffect::FrameGraphicsEffect(QObject* parent) : QGraphicsEffect(parent) {}

void FrameGraphicsEffect::setXRoundRadius(qreal xRadius, Qt::SizeMode mode)
{
	m_xRoundRadius = xRadius;
	m_xRoundMode = mode;
}

void FrameGraphicsEffect::setYRoundRadius(qreal yRadius, Qt::SizeMode mode)
{
	m_yRoundRadius = yRadius;
	m_yRoundMode = mode;
}

void FrameGraphicsEffect::draw(QPainter* painter)
{
	QRectF sourceRect = sourceBoundingRect();

	qreal penWidth = painter->pen().widthF();
	sourceRect.adjust(0, 0, -penWidth, -penWidth);

	qreal xRoundRadius = m_xRoundRadius;
	if (m_xRoundMode == Qt::RelativeSize) {
		xRoundRadius *= sourceRect.width() / 2.0;
	}

	qreal yRoundRadius = m_yRoundRadius;
	if (m_yRoundMode == Qt::RelativeSize) {
		yRoundRadius *= sourceRect.height() / 2.0;
	}

	painter->drawRoundedRect(sourceRect, xRoundRadius,
							 yRoundRadius, Qt::AbsoluteSize);

	drawSource(painter);
}
