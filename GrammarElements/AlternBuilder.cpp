#include "AlternBuilder.h"

#include <QGraphicsLinearLayout>

#include "Defines.h"
#include "SpacerItem.h"

#include "GraphicsConnections/StairConnection.h"

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

	outerLayout->addItem(innerLayout);

	for (auto itemWrapper : m_wrappers) {
		innerLayout->addItem(itemWrapper->layoutItem());
	}

	if (m_wrappers.size() > 1) {
		auto leftSpacer = new SpacerItem({ GuiMetrics::SpacerWidth, -1 });
		outerLayout->insertItem(0, leftSpacer);

		auto rightSpacer = new SpacerItem({ GuiMetrics::SpacerWidth, -1 });
		outerLayout->insertItem(-1, rightSpacer);

		for (auto itemWrapper : m_wrappers) {
			auto leftConn = new StairConnection(widgetWrapper, itemWrapper, leftSpacer);
			leftConn->setFirstJoint({ 0, GuiMetrics::ItemHalfHeight });
			leftConn->setSecondJoint({ 0, GuiMetrics::ItemHalfHeight });

			auto rightConn = new StairConnection(widgetWrapper, itemWrapper, rightSpacer);
			rightConn->setFirstJoint({ 1.0, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);
			rightConn->setSecondJoint({ 1.0, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);
		}
	}

	widget->setLayout(outerLayout);
	return widget;
}
