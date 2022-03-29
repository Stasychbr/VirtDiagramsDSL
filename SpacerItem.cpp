#include "SpacerItem.h"

#include <QPainter>
#include <QWidget>

SpacerItem::SpacerItem(const QSizeF& sizeHint, QGraphicsItem* parent)
	: SimpleLayoutItem(parent), m_sizeHint(sizeHint) {
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

QSizeF SpacerItem::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
	QSizeF sh;
	switch (which) {
		case Qt::MinimumSize:
		case Qt::PreferredSize:
			sh = m_sizeHint;
			break;

		case Qt::MaximumSize:
			sh = QSizeF(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
			break;

		default:
			break;
	}
	return sh;
}
