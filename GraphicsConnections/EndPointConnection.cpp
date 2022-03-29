#include "EndPointConnection.h"

EndPointConnection::EndPointConnection(ObservableWrapper* wrapper1,
									   ObservableWrapper* wrapper2,
									   QGraphicsItem* parent)
	: GraphicsConnection(wrapper1, wrapper2, parent) {}


void EndPointConnection::setRadius(qreal radius)
{
	m_radius = radius;
}

QPainterPath EndPointConnection::shape() const
{
	QPointF startPoint = mapJointPos(FirstJoint);
	QPointF endPoint = mapJointPos(SecondJoint);

	QPainterPath path(startPoint);
	path.lineTo(endPoint);

	path.addEllipse(endPoint, m_radius, m_radius);

	return path;
}
