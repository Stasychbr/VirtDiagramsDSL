#pragma once

#include "GraphicsConnection.h"

class EndPointConnection : public GraphicsConnection
{
public:
	EndPointConnection(ObservableWrapper* wrapper1,
					   ObservableWrapper* wrapper2,
					   QGraphicsItem* parent = nullptr);

	void setInnerRadius(qreal radius);
	void setOuterRadius(qreal radius);

	QPainterPath shape() const override;

	QPainterPath innerShape() const;
	QPainterPath outerShape() const;

	enum RenderType {
		StartPoint,
		EndPoint,
	};

	void setRenderType(RenderType type);

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
	qreal m_innerRadius = 0.0;
	qreal m_outerRadius = 0.0;
	RenderType m_renderType = StartPoint;
};

