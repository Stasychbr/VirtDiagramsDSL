#pragma once

#include "GraphicsConnection.h"

class HookConnection : public GraphicsConnection
{
public:
	HookConnection(ObservableWrapper* wrapper1,
				   ObservableWrapper* wrapper2,
				   QGraphicsItem* parent = nullptr);

	enum HookDirection {
		DirectionLeft,
		DirectionRight,
	};

	void setHookLen(qreal len);
	void setHookDirection(HookDirection direction);

	QPainterPath shape() const override;

private:
	qreal m_hookLen = 0.0;
	HookDirection m_direction = DirectionLeft;
};

