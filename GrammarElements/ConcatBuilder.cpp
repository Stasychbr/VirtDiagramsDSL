#include "ConcatBuilder.h"

#include <QGraphicsLinearLayout>

#include "SpacerItem.h"
#include "GraphicsConnection.h"
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

	auto leftConn = new GraphicsConnection(wrapper, m_wrappers.first(), widget);
	leftConn->setFirstJoint({ 0, GuiMetrics::ItemHalfHeight });
	leftConn->setSecondJoint({ 0, GuiMetrics::ItemHalfHeight });

	auto rightConn = new GraphicsConnection(m_wrappers.last(), wrapper, widget);
	rightConn->setFirstJoint({ 1.0, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);
	rightConn->setSecondJoint({ 1.0, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);

	auto spacer = new SpacerItem({ GuiMetrics::SpacerWidth, -1 });
	layout->addItem(spacer);

	for (int i = 0; i < m_wrappers.size(); i++) {
		layout->addItem(m_wrappers[i]->layoutItem());

		auto spacer = new SpacerItem({ GuiMetrics::SpacerWidth, -1 });
		layout->addItem(spacer);

		if (i > 0) {
			auto conn = new GraphicsConnection(m_wrappers[i - 1], m_wrappers[i], widget);
			conn->setFirstJoint({ 1.0, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);
			conn->setSecondJoint({ 0, GuiMetrics::ItemHalfHeight });
		}
	}

	widget->setLayout(layout);
	return widget;
}

void ConcatBuilder::addElement(ObservableWrapper* wrapper)
{
	m_wrappers.append(wrapper);
}
