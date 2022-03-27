#pragma once

#include <QGraphicsObject>
#include <QGraphicsLayoutItem>

class SimpleLayoutItem : public QGraphicsObject, public QGraphicsLayoutItem
{
	Q_OBJECT
public:
	SimpleLayoutItem(QGraphicsItem* parent = nullptr);

	QRectF boundingRect() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

	void setGeometry(const QRectF& rect) override;

Q_SIGNALS:
	void geometryChanged();
};

