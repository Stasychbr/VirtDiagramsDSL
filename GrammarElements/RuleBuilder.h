#pragma once

#include <QGraphicsWidget>

#include "ObservableWrapper.h"

class RuleBuilder
{
public:
	RuleBuilder();

	void setElement(ObservableWrapper* wrapper);
	QGraphicsWidget* build() const;

private:
	ObservableWrapper* m_wrapper;
};

