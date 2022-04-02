#include "HookConnection.h"

HookConnection::HookConnection(ObservableWrapper* wrapper1,
							   ObservableWrapper* wrapper2,
							   QGraphicsItem* parent)
	: GraphicsConnection(wrapper1, wrapper2, parent)
{

}

void HookConnection::setHookLen(qreal len)
{
	prepareGeometryChange();
	m_hookLen = len;
}

void HookConnection::setHookDirection(HookDirection direction)
{
	prepareGeometryChange();
	m_direction = direction;
}

QPainterPath HookConnection::shape() const
{
	QPointF startPoint = mapJointPos(FirstJoint);
	QPointF endPoint = mapJointPos(SecondJoint);

	QPainterPath path(startPoint);

	QRectF bRect(startPoint, endPoint);

	qreal halfHeight = bRect.height() / 2.0;

	int hookSgn = m_direction == DirectionLeft ? 1 : -1;
	qreal hook = hookSgn * m_hookLen;

	int biasSgn = bRect.height() >= 0 ? 1 : -1;
	qreal absBias = std::min(m_hookLen, std::fabs(halfHeight));
	qreal bias = biasSgn * absBias;

	QPointF cp1 = startPoint - QPointF(hook, 0.0);
	QPointF aux1 = cp1 + QPointF(0.0, bias);

	QPointF cp2 = endPoint - QPointF(hook, 0.0);
	QPointF aux2 = cp2 - QPointF(0.0, bias);

	path.quadTo(cp1, aux1);
	path.lineTo(aux2);
	path.quadTo(cp2, endPoint);

	return path;
}
