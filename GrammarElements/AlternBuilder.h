#pragma once

#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>

#include "ObservableWrapper.h"

class AlternBuilder
{
public:
	AlternBuilder();

	void addElement(ObservableWrapper* wrapper);
	QGraphicsWidget* build() const;

private:
	QList<ObservableWrapper*> m_wrappers;
};
