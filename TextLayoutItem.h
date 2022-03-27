#pragma once

#include "SimpleLayoutItem.h"

#include <QFont>

class TextLayoutItem : public SimpleLayoutItem
{
public:
	TextLayoutItem(const QString& text, QGraphicsItem* parent = nullptr);

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

	void expandTo(const QSizeF& size);
	void growBy(const QMarginsF& margins);
	void setFont(const QFont& font);

protected:
	QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const override;

private:
	void updateTextSize();

	QString m_text;
	QFont m_font;
	QSizeF m_sizeHint;
};
