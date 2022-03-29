#include "ConcatBuilder.h"

#include <QGraphicsLinearLayout>

#include "SpacerItem.h"
#include "GraphicsConnections/LineConnection.h"
#include "Defines.h"

ConcatBuilder::ConcatBuilder()
{
}

QGraphicsWidget* ConcatBuilder::build() const
{
	auto widget = new QGraphicsWidget;
	auto wrapper = ObservableWrapper::wrap(widget);

	auto layout = new QGraphicsLinearLayout;
	layout->setSpacing(0.0);
	layout->setContentsMargins(0.0, 0.0, 0.0, 0.0);

	auto leftConn = new LineConnection(wrapper, m_wrappers.first(), widget);
	leftConn->setFirstJoint({ 0, GuiMetrics::ItemHalfHeight });
	leftConn->setSecondJoint({ 0, GuiMetrics::ItemHalfHeight });

	auto rightConn = new LineConnection(m_wrappers.last(), wrapper, widget);
	rightConn->setFirstJoint({ 1.0, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);
	rightConn->setSecondJoint({ 1.0, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);

	auto leftSpacer = new SpacerItem({ 0, GuiMetrics::ItemHeight });
	layout->addItem(leftSpacer);

	for (int i = 0; i < m_wrappers.size() - 1; i++) {
		layout->addItem(m_wrappers[i]->layoutItem());

		auto spacer = new SpacerItem({ GuiMetrics::SpacerWidth, GuiMetrics::ItemHeight });
		layout->addItem(spacer);

		auto conn = new LineConnection(m_wrappers[i], m_wrappers[i + 1], widget);
		conn->setFirstJoint({ 1.0, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);
		conn->setSecondJoint({ 0, GuiMetrics::ItemHalfHeight });
	}

	layout->addItem(m_wrappers.last()->layoutItem());

	auto rightSpacer = new SpacerItem({ 0, GuiMetrics::ItemHeight });
	layout->addItem(rightSpacer);

	widget->setLayout(layout);
	return widget;
}

void ConcatBuilder::addElement(ObservableWrapper* wrapper)
{
	m_wrappers.append(wrapper);
}
