#include "OptionItem.h"

#include "Defines.h"
#include "SpacerItem.h"

#include "GraphicsConnections/LineConnection.h"

OptionItem::OptionItem(ObservableWrapper* element, QGraphicsItem* parent)
	: AlternationItem(parent)
{
	auto spacer = new SpacerItem({ GuiMetrics::SpacerWidth, GuiMetrics::ItemHeight });
	auto spacerWrapper = ObservableWrapper::wrap(spacer);

	addElement(spacerWrapper);
	addElement(element);

	auto conn = new LineConnection(spacerWrapper, spacerWrapper, this);
	conn->setFirstJoint({ 0.0, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);
	conn->setSecondJoint({ 1.0, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);
}
