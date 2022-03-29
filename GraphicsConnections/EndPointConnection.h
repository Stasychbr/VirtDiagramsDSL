#pragma once

#include "GraphicsConnection.h"

class EndPointConnection : public GraphicsConnection
{
public:
	EndPointConnection(ObservableWrapper* wrapper1,
					   ObservableWrapper* wrapper2,
					   QGraphicsItem* parent = nullptr);

	void setRadius(qreal radius);
	QPainterPath shape() const override;

private:
	qreal m_radius = 0.0;
};

