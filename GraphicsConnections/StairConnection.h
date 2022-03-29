#pragma once

#include "GraphicsConnection.h"

class StairConnection : public GraphicsConnection
{
public:
	StairConnection(ObservableWrapper* wrapper1,
					ObservableWrapper* wrapper2,
					QGraphicsItem* parent = nullptr);

	QPainterPath shape() const override;
};

