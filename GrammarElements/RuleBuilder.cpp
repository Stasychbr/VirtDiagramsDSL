#include "RuleBuilder.h"

#include <QGraphicsLinearLayout>

#include "Defines.h"
#include "SpacerItem.h"

#include "GraphicsConnections/EndPointConnection.h"

RuleBuilder::RuleBuilder()
{
}

void RuleBuilder::setElement(ObservableWrapper* wrapper)
{
	m_wrapper = wrapper;
}

QGraphicsWidget* RuleBuilder::build() const
{
	using namespace GuiMetrics::EndPointMetrics;

	auto widget = new QGraphicsWidget;

	auto layout = new QGraphicsLinearLayout;
	layout->setContentsMargins(0.0, 0.0, 0.0, 0.0);

	auto leftSpacer = new SpacerItem({ GuiMetrics::SpacerWidth, GuiMetrics::ItemHeight });
	layout->addItem(leftSpacer);

	auto leftWrapper = ObservableWrapper::wrap(leftSpacer);

	auto leftConn = new EndPointConnection(m_wrapper, leftWrapper, widget);
	leftConn->setFirstJoint({ 0.0, GuiMetrics::ItemHalfHeight });
	leftConn->setSecondJoint({ 1.0 - WidthFraction, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);

	leftConn->setRadius(Radius);

	layout->addItem(m_wrapper->layoutItem());

	auto rightSpacer = new SpacerItem({ GuiMetrics::SpacerWidth, GuiMetrics::ItemHeight });
	layout->addItem(rightSpacer);

	auto rightWrapper = ObservableWrapper::wrap(rightSpacer);

	auto rightConn = new EndPointConnection(m_wrapper, rightWrapper, widget);
	rightConn->setFirstJoint({ 1.0, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);
	rightConn->setSecondJoint({ WidthFraction, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);

	rightConn->setRadius(Radius);

	widget->setLayout(layout);
	return widget;
}
