#pragma once

#include <QPushButton>

class HighlightableButton : public QPushButton
{
	Q_OBJECT
	Q_PROPERTY(QColor color MEMBER m_color
			   WRITE setColor NOTIFY colorChanged)

public:
	HighlightableButton(const QColor& color, QWidget* parent = nullptr);

	void highlight(const QColor& color, int duration);

	void setColor(const QColor& color);

Q_SIGNALS:
	void colorChanged();

private Q_SLOTS:
	void onColorChanged();

private:
	QColor m_color;
};

