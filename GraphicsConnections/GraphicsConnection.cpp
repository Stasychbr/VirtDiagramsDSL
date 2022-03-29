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
}

void GraphicsConnection::setFirstJoint(const QPointF& point,
									   Qt::SizeMode xSizeMode,
									   Qt::SizeMode ySizeMode)
{
	m_joints[FirstJoint].pos = point;
	m_joints[FirstJoint].sizeMode[Qt::XAxis] = xSizeMode;
	m_joints[FirstJoint].sizeMode[Qt::YAxis] = ySizeMode;

	updateJoints();
}

void GraphicsConnection::setSecondJoint(const QPointF& point,
										Qt::SizeMode xSizeMode,
										Qt::SizeMode ySizeMode)
{
	m_joints[SecondJoint].pos = point;
	m_joints[SecondJoint].sizeMode[Qt::XAxis] = xSizeMode;
	m_joints[SecondJoint].sizeMode[Qt::YAxis] = ySizeMode;

	updateJoints();
}

QRectF GraphicsConnection::boundingRect() const
{
	const auto& shapeRect = shape().boundingRect();
	qreal penWidth = QPen().widthF();
	return shapeRect.adjusted(0, 0, penWidth, penWidth);
}

void GraphicsConnection::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->setPen(QPen());
	painter->drawPath(shape());
}

void GraphicsConnection::updateJoints()
{
	update();
}

QPointF GraphicsConnection::mapJointPos(Joint joint) const
{
	auto item = m_joints[joint].item;

	QRectF bRect = item->boundingRect();
	QPointF pos = m_joints[joint].pos;

	if (m_joints[joint].sizeMode[Qt::XAxis] == Qt::RelativeSize) {
		pos.rx() *= bRect.width();
	}

	if (m_joints[joint].sizeMode[Qt::YAxis] == Qt::RelativeSize) {
		pos.ry() *= bRect.height();
	}

	return mapFromItem(item, pos);
}

