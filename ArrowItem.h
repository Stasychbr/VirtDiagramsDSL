#pragma once

#include "SimpleLayoutItem.h"

class ArrowItem : public SimpleLayoutItem
{
public:
	ArrowItem(const QSizeF& sizeHint, QGraphicsItem* parent = nullptr);

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

protected:
	QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint) const override;

private:
	QSizeF m_sizeHint;
};

