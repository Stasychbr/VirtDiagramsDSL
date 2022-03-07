#pragma once

#include <QGraphicsEffect>

class FrameGraphicsEffect : public QGraphicsEffect
{
public:
	FrameGraphicsEffect(QObject* parent = nullptr);

	void setXRoundRadius(qreal xRadius, Qt::SizeMode mode = Qt::AbsoluteSize);
	void setYRoundRadius(qreal yRadius, Qt::SizeMode mode = Qt::AbsoluteSize);

protected:
	void draw(QPainter* painter) override;

private:
	qreal m_xRoundRadius = 0.0;
	qreal m_yRoundRadius = 0.0;
	Qt::SizeMode m_xRoundMode = Qt::AbsoluteSize;
	Qt::SizeMode m_yRoundMode = Qt::AbsoluteSize;
};

