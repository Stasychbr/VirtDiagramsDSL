#pragma once

#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>

#include "ObservableWrapper.h"
#include "GraphicsConnections/HookConnection.h"
#include "GraphicsConnections/LineConnection.h"

class RepetitionItem : public QGraphicsWidget
{
public:
	RepetitionItem(ObservableWrapper* element,
				   QGraphicsItem* parent = nullptr);

	void setRepeatThrough(ObservableWrapper* element);

private:
	QGraphicsLinearLayout* m_layout;
	HookConnection* m_leftHookConn;
	HookConnection* m_rightHookConn;
	LineConnection* m_lineConn;
};

