#pragma once

#include "TextLayoutItem.h"

class TerminalItem : public TextLayoutItem
{
public:
	TerminalItem(const QString& text, QGraphicsItem* parent = nullptr);
};

