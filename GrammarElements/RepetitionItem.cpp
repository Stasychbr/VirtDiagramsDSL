#include "RepetitionItem.h"

#include "AlternationItem.h"
#include "SpacerItem.h"
#include "Defines.h"

RepetitionItem::RepetitionItem(ObservableWrapper* element,
							   QGraphicsItem* parent)
	: QGraphicsWidget(parent)
{
	auto wrapper = ObservableWrapper::wrap(this);

	m_layout = new QGraphicsLinearLayout;
	m_layout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
	m_layout->setSpacing(GuiMetrics::VerticalItemSpacing);
	m_layout->setOrientation(Qt::Vertical);

	m_layout->addItem(element->layoutItem());

	auto spacer = new SpacerItem({ GuiMetrics::SpacerWidth, GuiMetrics::ItemHeight });
	auto spacerWrapper = ObservableWrapper::wrap(spacer);

	m_layout->addItem(spacer);

	m_lineConn= new LineConnection(spacerWrapper, spacerWrapper, this);
	m_lineConn->setFirstJoint({ 0.0, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);
	m_lineConn->setSecondJoint({ 1.0, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);

	m_leftHookConn = new HookConnection(element, spacerWrapper, this);
	m_leftHookConn->setFirstJoint({ 0.0, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);
	m_leftHookConn->setSecondJoint({ 0.0, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);

	m_leftHookConn->setHookLen(GuiMetrics::SpacerWidth / 2.0);
	m_leftHookConn->setHookDirection(HookConnection::DirectionLeft);

	m_rightHookConn = new HookConnection(element, spacerWrapper, this);
	m_rightHookConn->setFirstJoint({ 1.0, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);
	m_rightHookConn->setSecondJoint({ 1.0, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);

	m_rightHookConn->setHookLen(GuiMetrics::SpacerWidth / 2.0);
	m_rightHookConn->setHookDirection(HookConnection::DirectionRight);

	setLayout(m_layout);
}

void RepetitionItem::setRepeatThrough(ObservableWrapper* element)
{
	auto spacer = m_layout->itemAt(m_layout->count() - 1);
	m_layout->removeItem(spacer);

	m_layout->addItem(element->layoutItem());

	m_leftHookConn->resetSecondWrapper(element);
	m_rightHookConn->resetSecondWrapper(element);

	delete spacer;
	delete m_lineConn;
}
