#pragma once

#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>

#include "ObservableWrapper.h"

class AlternationItem : public QGraphicsWidget
{
public:
	AlternationItem(QGraphicsItem* parent = nullptr);

	void addElement(ObservableWrapper* element);

private:
	void addSideSpacers();
	void addForkConn(ObservableWrapper* element);

	QGraphicsLinearLayout* m_elementsLayout;
	QGraphicsLinearLayout* m_forkLayout;
};

