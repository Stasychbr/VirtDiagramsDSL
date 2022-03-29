#include "StairConnection.h"

StairConnection::StairConnection(ObservableWrapper* wrapper1,
								 ObservableWrapper* wrapper2,
								 QGraphicsItem* parent)
	: GraphicsConnection(wrapper1, wrapper2, parent) {}

QPainterPath StairConnection::shape() const
{
	QPointF startPoint = mapJointPos(FirstJoint);
	QPointF endPoint = mapJointPos(SecondJoint);

	QPainterPath path(startPoint);

	QRectF bRect(startPoint, endPoint);

	qreal halfWidth = bRect.width() / 2.0;
	qreal halfHeight = bRect.height() / 2.0;

	int biasSgn = bRect.height() >= 0 ? 1 : -1;
	qreal absBias = std::min(std::fabs(halfWidth), std::fabs(halfHeight));
	qreal bias = biasSgn * absBias;

	QPointF cp1 = startPoint + QPointF(halfWidth, 0.0);
	QPointF aux1 = cp1 + QPointF(0.0, bias);

	QPointF cp2 = endPoint - QPointF(halfWidth, 0.0);
	QPointF aux2 = cp2 - QPointF(0.0, bias);

	path.quadTo(cp1, aux1);
	path.lineTo(aux2);
	path.quadTo(cp2, endPoint);

	return path;
}
