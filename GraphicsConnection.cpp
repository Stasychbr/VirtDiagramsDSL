#include "GraphicsConnection.h"

#include <QPainter>

GraphicsConnection::GraphicsConnection(ObservableWrapper* wrapper1,
									   ObservableWrapper* wrapper2,
									   QGraphicsItem* parent)
	: QGraphicsObject(parent)
{
	connect(wrapper1, &ObservableWrapper::geometryChanged,
			this, &GraphicsConnection::updateJoints);
	connect(wrapper2, &ObservableWrapper::geometryChanged,
			this, &GraphicsConnection::updateJoints);

	m_joints[0].item = wrapper1->layoutItem()->graphicsItem();
	m_joints[1].item = wrapper2->layoutItem()->graphicsItem();

	m_generator = [] (const QPointF& startPoint, const QPointF& endPoint) {
		return PtsPair{ startPoint, endPoint };
	};
}

void GraphicsConnection::setFirstJoint(const QPointF& point,
									   Qt::SizeMode xSizeMode,
									   Qt::SizeMode ySizeMode)
{
	m_joints[0].pos = point;
	m_joints[0].xSizeMode = xSizeMode;
	m_joints[0].ySizeMode = ySizeMode;

	updateJoints();
}

void GraphicsConnection::setSecondJoint(const QPointF& point,
										Qt::SizeMode xSizeMode,
										Qt::SizeMode ySizeMode)
{
	m_joints[1].pos = point;
	m_joints[1].xSizeMode = xSizeMode;
	m_joints[1].ySizeMode = ySizeMode;

	updateJoints();
}

void GraphicsConnection::setCtrlPtsGenerator(const PtsGenerator& generator)
{
	m_generator = generator;
}

QRectF GraphicsConnection::boundingRect() const
{
	return shape().boundingRect();
}

void GraphicsConnection::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->drawPath(shape());
}

QPainterPath GraphicsConnection::shape() const
{
	QPointF startPoint = jointPos(0);
	QPointF endPoint = jointPos(1);

	const auto& controlPoints = m_generator(startPoint, endPoint);

	QPainterPath path(startPoint);
	path.cubicTo(controlPoints[0], controlPoints[1], endPoint);
	return path;
}

void GraphicsConnection::updateJoints()
{
	update();
}

QPointF GraphicsConnection::jointPos(int i) const
{
	auto item = m_joints[i].item;

	QRectF bRect = item->boundingRect();
	QPointF pos = m_joints[i].pos;

	if (m_joints[i].xSizeMode == Qt::RelativeSize) {
		pos.rx() *= bRect.width();
	}

	if (m_joints[i].ySizeMode == Qt::RelativeSize) {
		pos.ry() *= bRect.height();
	}

	return mapFromItem(item, pos);
}

