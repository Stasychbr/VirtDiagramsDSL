#pragma once

#include "TextLayoutItem.h"

class NonTerminalItem : public TextLayoutItem
{
public:
	NonTerminalItem(const QString& text, QGraphicsItem* parent = nullptr);
};

