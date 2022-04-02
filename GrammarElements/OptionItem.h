#pragma once

#include "AlternationItem.h"

class OptionItem : public AlternationItem
{
public:
	OptionItem(ObservableWrapper* element,
			   QGraphicsItem* parent = nullptr);
};

