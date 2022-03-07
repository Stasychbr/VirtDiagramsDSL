#pragma once

#include <QGraphicsEffect>

class FrameGraphicsEffect : public QGraphicsEffect
{
public:
	FrameGraphicsEffect(QObject* parent = nullptr);

protected:
	void draw(QPainter* painter) override;
};

