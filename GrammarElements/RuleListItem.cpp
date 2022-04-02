#include "RuleListItem.h"

RuleListItem::RuleListItem(QGraphicsItem* parent)
{
	m_layout = new QGraphicsLinearLayout;
	m_layout->setOrientation(Qt::Vertical);
	setLayout(m_layout);
}

void RuleListItem::addElement(ObservableWrapper* element) {
	auto layoutItem = element->layoutItem();
	layoutItem->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	m_layout->addItem(layoutItem);
}
