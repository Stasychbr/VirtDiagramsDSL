#pragma once

#include "GraphicsConnection.h"

class LineConnection : public GraphicsConnection
{
public:
	LineConnection(ObservableWrapper* wrapper1,
				   ObservableWrapper* wrapper2,
				   QGraphicsItem* parent = nullptr);

	QPainterPath shape() const override;
};

