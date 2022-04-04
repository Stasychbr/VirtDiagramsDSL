#include "HighlightableButton.h"

#include <QVariant>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

static QVariant colorInterpolator(const QColor& start,
								  const QColor& end,
								  qreal progress)
{
	auto linearInterp = [=] (qreal a, qreal b) {
		return a + (b - a) * progress;
	};

	qreal redF = linearInterp(start.redF(), end.redF());
	qreal greenF = linearInterp(start.greenF(), end.greenF());
	qreal blueF = linearInterp(start.blueF(), end.blueF());
	qreal alphaF = linearInterp(start.alphaF(), end.alphaF());

	return QColor::fromRgbF(redF, greenF, blueF, alphaF);
}

HighlightableButton::HighlightableButton(QWidget* parent)
	: QPushButton(parent) {
	qRegisterAnimationInterpolator<QColor>(colorInterpolator);

	setFixedWidth(20);
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

	connect(this, &HighlightableButton::colorChanged,
			this, &HighlightableButton::onColorChanged);

	setColor(QColor(211, 211, 211));
}

void HighlightableButton::highlight(const QColor& color, int duration)
{
	QColor startColor = m_color;
	qreal halfDuration = duration / 2.0;

	auto forward = new QPropertyAnimation(this, "color");
	forward->setDuration(halfDuration);

	forward->setStartValue(startColor);
	forward->setEndValue(color);

	auto backward = new QPropertyAnimation(this, "color");
	backward->setDuration(halfDuration);

	backward->setStartValue(color);
	backward->setEndValue(startColor);

	auto group = new QSequentialAnimationGroup;
	group->addAnimation(forward);
	group->addAnimation(backward);

	group->start(QAbstractAnimation::DeleteWhenStopped);
}

void HighlightableButton::setColor(const QColor& color)
{
	m_color = color;
	Q_EMIT colorChanged();
}

void HighlightableButton::onColorChanged()
{
	QString colorName = m_color.name(QColor::HexArgb);
   QString qss = QString("background-color: %1;").arg(colorName);
   setStyleSheet(qss);
}
