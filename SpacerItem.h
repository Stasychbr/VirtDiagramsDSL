#pragma once

#include "SimpleLayoutItem.h"

class SpacerItem : public SimpleLayoutItem
{
public:
	SpacerItem(const QSizeF& sizeHint, QGraphicsItem* parent = nullptr);

protected:
	QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint) const override;

private:
	QSizeF m_sizeHint;
};

