#pragma once

#include <QGraphicsWidget>

class TerminalWidget : public QGraphicsWidget
{
public:
	TerminalWidget(const QString& text, QGraphicsItem* parent = nullptr);

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
	bool event(QEvent* event) override;

	void setRectAdjustment(qreal dx, qreal dy);

private:
	void updateMinSize();

	QString m_text;

	qreal m_widthAdj = 15.0;
	qreal m_heightAdj = 15.0;
};
