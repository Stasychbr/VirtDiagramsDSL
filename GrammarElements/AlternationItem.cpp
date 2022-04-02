#include "AlternationItem.h"

#include <QGraphicsLinearLayout>

#include "Defines.h"
#include "SpacerItem.h"

#include "GraphicsConnections/StairConnection.h"

AlternationItem::AlternationItem(QGraphicsItem* parent)
	: QGraphicsWidget(parent)
{
	ObservableWrapper::wrap(this);

	m_forkLayout = new QGraphicsLinearLayout;
	m_forkLayout->setSpacing(0.0);
	m_forkLayout->setContentsMargins(0.0f, 0.0f, 0.0f, 0.0f);

	m_elementsLayout = new QGraphicsLinearLayout;
	m_elementsLayout->setSpacing(GuiMetrics::VerticalItemSpacing);
	m_elementsLayout->setOrientation(Qt::Vertical);

	m_forkLayout->addItem(m_elementsLayout);
	setLayout(m_forkLayout);
}

void AlternationItem::addElement(ObservableWrapper* element) {
	m_elementsLayout->addItem(element->layoutItem());
	addForkConn(element);

	if (m_elementsLayout->count() == 2) {
		addSideSpacers();
	}
}

void AlternationItem::addSideSpacers()
{
	auto leftSpacer = new SpacerItem({ GuiMetrics::SpacerWidth, -1 });
	m_forkLayout->insertItem(0, leftSpacer);
	leftSpacer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);

	auto rightSpacer = new SpacerItem({ GuiMetrics::SpacerWidth, -1 });
	m_forkLayout->insertItem(-1, rightSpacer);
	rightSpacer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
}

void AlternationItem::addForkConn(ObservableWrapper* element)
{
	auto selfWrapper = ObservableWrapper::wrapperOf(this);

	auto leftConn = new StairConnection(selfWrapper, element, this);
	leftConn->setFirstJoint({ 0, GuiMetrics::ItemHalfHeight });
	leftConn->setSecondJoint({ 0, GuiMetrics::ItemHalfHeight });

	auto rightConn = new StairConnection(selfWrapper, element, this);
	rightConn->setFirstJoint({ 1.0, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);
	rightConn->setSecondJoint({ 1.0, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);
}
