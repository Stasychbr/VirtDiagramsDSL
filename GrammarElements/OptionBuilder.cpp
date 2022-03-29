#include "OptionBuilder.h"

#include "Defines.h"
#include "SpacerItem.h"

#include "GraphicsConnections/LineConnection.h"

OptionBuilder::OptionBuilder()
{
}

void OptionBuilder::setElement(ObservableWrapper* wrapper)
{
	m_wrapper = wrapper;
}

QGraphicsWidget* OptionBuilder::build() const
{
	AlternBuilder builder;

	auto spacer = new SpacerItem({ GuiMetrics::SpacerWidth, GuiMetrics::ItemHeight });
	auto spacerWrapper = ObservableWrapper::wrap(spacer);

	builder.addElement(spacerWrapper);
	builder.addElement(m_wrapper);

	auto widget = builder.build();
	auto wrapper = ObservableWrapper::wrap(widget);

	auto conn = new LineConnection(wrapper, wrapper, widget);
	conn->setFirstJoint({ 0.0, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);
	conn->setSecondJoint({ 1.0, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);

	return widget;
}
