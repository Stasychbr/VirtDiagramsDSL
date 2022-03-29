#pragma once

#include "AlternBuilder.h"

class OptionBuilder
{
public:
	OptionBuilder();

	void setElement(ObservableWrapper* wrapper);
	QGraphicsWidget* build() const;

private:
	ObservableWrapper* m_wrapper;
};

