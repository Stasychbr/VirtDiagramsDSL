#include "AlternBuilder.h"

#include "Defines.h"
#include "SpacerItem.h"
#include "GraphicsConnection.h"

AlternBuilder::AlternBuilder() {
}

void AlternBuilder::addElement(ObservableWrapper* wrapper)
{
	m_wrappers.append(wrapper);
}

QGraphicsWidget* AlternBuilder::build() const
{
	auto widget = new QGraphicsWidget;
	auto widgetWrapper = ObservableWrapper::wrap(widget);

	auto outerLayout = new QGraphicsLinearLayout;
	outerLayout->setContentsMargins(0.0f, 0.0f, 0.0f, 0.0f);

	auto innerLayout = new QGraphicsLinearLayout;
	innerLayout->setSpacing(GuiMetrics::AlternSpacing);
	innerLayout->setOrientation(Qt::Vertical);

	auto leftSpacer = new SpacerItem({ GuiMetrics::SpacerWidth, -1 });
	outerLayout->addItem(leftSpacer);

	outerLayout->addItem(innerLayout);

	auto rightSpacer = new SpacerItem({ GuiMetrics::SpacerWidth, -1 });
	outerLayout->addItem(rightSpacer);


	for (auto itemWrapper : m_wrappers) {
		auto leftConn = new GraphicsConnection(widgetWrapper, itemWrapper, widget);
		leftConn->setFirstJoint({ 0, GuiMetrics::ItemHalfHeight });
		leftConn->setSecondJoint({ 0, GuiMetrics::ItemHalfHeight });

		innerLayout->addItem(itemWrapper->layoutItem());

		auto rightConn = new GraphicsConnection(widgetWrapper, itemWrapper, widget);
		rightConn->setFirstJoint({ 1.0, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);
		rightConn->setSecondJoint({ 1.0, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);
	}

	widget->setLayout(outerLayout);
	return widget;
}
