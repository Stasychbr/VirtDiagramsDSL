#include "SpacerItem.h"

#include <QPainter>
#include <QWidget>

SpacerItem::SpacerItem(const QSizeF& sizeHint, QGraphicsItem* parent)
	: SimpleLayoutItem(parent), m_sizeHint(sizeHint) {
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

//void ArrowItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
//{
//	const auto& boundRect = boundingRect();

//	QPointF startPoint(boundRect.top(), boundRect.height() / 2.0);
//	QPointF endPoint = startPoint + QPointF(boundRect.width(), 0.0);

//	QPainterPath path(startPoint);
//	path.lineTo(endPoint);

//	const QPointF& midPoint = (startPoint + endPoint) / 2.0;
//	path.moveTo(midPoint);

//	float biasLen = (endPoint.x() - startPoint.x()) / 12.0;
//	QPointF biasVec(biasLen, biasLen);
//	path.lineTo(midPoint - biasVec);

//	biasVec.ry() *= -1;

//	path.moveTo(midPoint);
//	path.lineTo(midPoint - biasVec);

//	painter->drawPath(path);
//}

QSizeF SpacerItem::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
	QSizeF sh;
	switch (which) {
		case Qt::MinimumSize:
		case Qt::PreferredSize:
			sh = m_sizeHint;
			break;

		case Qt::MaximumSize:
			sh = QSizeF(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
			break;

		default:
			break;
	}
	return sh;
}
