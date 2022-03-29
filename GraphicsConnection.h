#pragma once

#include <QGraphicsObject>

#include <functional>
#include <array>

#include "ObservableWrapper.h"

class GraphicsConnection : public QGraphicsObject
{
	Q_OBJECT
public:
	GraphicsConnection(ObservableWrapper* wrapper1,
					   ObservableWrapper* wrapper2,
					   QGraphicsItem* parent = nullptr);

	void setFirstJoint(const QPointF& point,
					   Qt::SizeMode xSizeMode = Qt::AbsoluteSize,
					   Qt::SizeMode ySizeMode = Qt::AbsoluteSize);

	void setSecondJoint(const QPointF& point,
						Qt::SizeMode xSizeMode = Qt::AbsoluteSize,
						Qt::SizeMode ySizeMode = Qt::AbsoluteSize);

	QRectF boundingRect() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
	QPainterPath shape() const override;

private Q_SLOTS:
	void updateJoints();

private:
	enum Joint {
		FirstJoint,
		SecondJoint,
	};

	QPointF mapJointPos(Joint joint) const;

	struct JointInfo {
		QPointF pos;
		Qt::SizeMode sizeMode[2];
		QGraphicsItem* item;
	};

	JointInfo m_joints[2];
};

