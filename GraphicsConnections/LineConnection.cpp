#include "LineConnection.h"

LineConnection::LineConnection(ObservableWrapper* wrapper1,
							   ObservableWrapper* wrapper2,
							   QGraphicsItem* parent)
	: GraphicsConnection(wrapper1, wrapper2, parent) {}

QPainterPath LineConnection::shape() const
{
	QPointF startPoint = mapJointPos(FirstJoint);
	QPointF endPoint = mapJointPos(SecondJoint);

	QPainterPath path(startPoint);
	path.lineTo(endPoint);

	return path;
}
