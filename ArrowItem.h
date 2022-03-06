#pragma once

#include <QGraphicsLayoutItem>
#include <QGraphicsItem>

class ArrowItem : public QGraphicsItem, public QGraphicsLayoutItem
{
public:
	ArrowItem(const QSizeF& sizeHint, QGraphicsItem* parent = nullptr);

	QRectF boundingRect() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

	void setGeometry(const QRectF& rect) override;

protected:
	QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint) const override;

private:
	QSizeF m_sizeHint;
};

