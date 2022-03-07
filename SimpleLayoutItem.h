#pragma once

#include <QGraphicsItem>
#include <QGraphicsLayoutItem>

class SimpleLayoutItem : public QGraphicsItem, public QGraphicsLayoutItem
{
public:
	SimpleLayoutItem(QGraphicsItem* parent = nullptr);

	QRectF boundingRect() const override;
	void setGeometry(const QRectF& rect) override;
};

