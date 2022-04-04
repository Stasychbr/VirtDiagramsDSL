#include "EndPointConnection.h"

#include <QPainter>

EndPointConnection::EndPointConnection(ObservableWrapper* wrapper1,
									   ObservableWrapper* wrapper2,
									   QGraphicsItem* parent)
	: GraphicsConnection(wrapper1, wrapper2, parent) {}

void EndPointConnection::setInnerRadius(qreal radius)
{
	prepareGeometryChange();
	m_innerRadius = radius;
}

void EndPointConnection::setOuterRadius(qreal radius)
{
	prepareGeometryChange();
	m_outerRadius = radius;
}

QPainterPath EndPointConnection::shape() const
{
	QPainterPath shape = outerShape();
	shape.addPath(innerShape());
	return shape;
}

QPainterPath EndPointConnection::innerShape() const
{
	QPointF endPoint = mapJointPos(SecondJoint);

	QPainterPath path;
	path.addEllipse(endPoint, m_innerRadius, m_innerRadius);
	return path;
}

QPainterPath EndPointConnection::outerShape() const
{
	QPointF startPoint = mapJointPos(FirstJoint);
	QPointF endPoint = mapJointPos(SecondJoint);

	QPainterPath path;

	if (m_renderType == EndPoint) {
		path.addEllipse(endPoint, m_outerRadius, m_outerRadius);

		QVector2D bias(endPoint - startPoint);
		qreal len = bias.length();
		qreal t = 1 - m_outerRadius / len;
		endPoint = startPoint + t * bias.toPointF();
	}

	path.moveTo(startPoint);
	path.lineTo(endPoint);

	return path;
}

void EndPointConnection::setRenderType(RenderType type)
{
	prepareGeometryChange();
	m_renderType = type;
}

void EndPointConnection::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->drawPath(outerShape());
	painter->setBrush(Qt::black);
	painter->drawPath(innerShape());
}
