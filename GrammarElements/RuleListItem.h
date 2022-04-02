#pragma once

#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>

#include "ObservableWrapper.h"

class RuleListItem : public QGraphicsWidget
{
public:
	RuleListItem(QGraphicsItem* parent = nullptr);

	void addElement(ObservableWrapper* element);

private:
	QGraphicsLinearLayout* m_layout;
};

