#pragma once

#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>

#include "ObservableWrapper.h"

class ConcatBuilder
{
public:
	ConcatBuilder();

	void addElement(ObservableWrapper* element);
	QGraphicsWidget* build() const;

private:
	QList<ObservableWrapper*> m_wrappers;
};

