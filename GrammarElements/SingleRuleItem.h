#pragma once

#include <QGraphicsWidget>

#include "ObservableWrapper.h"

class SingleRuleItem : public QGraphicsWidget
{
public:
	SingleRuleItem(ObservableWrapper* element,
				   const QString& name,
				   QGraphicsItem* parent = nullptr);
};

