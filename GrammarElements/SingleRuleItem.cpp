#include "SingleRuleItem.h"

#include <QGraphicsLinearLayout>

#include "Defines.h"
#include "SpacerItem.h"
#include "TextLayoutItem.h"

#include "../GraphicsConnections/EndPointConnection.h"

SingleRuleItem::SingleRuleItem(ObservableWrapper* element,
							   const QString& name,
							   QGraphicsItem* parent)
	: QGraphicsWidget(parent)
{
	using namespace GuiMetrics::EndPointMetrics;

	auto vertLayout = new QGraphicsLinearLayout;
	vertLayout->setOrientation(Qt::Vertical);

	auto nameItem = new	TextLayoutItem(name);
	vertLayout->addItem(nameItem);

	auto horLayout = new QGraphicsLinearLayout;
	horLayout->setSpacing(0.0);
	horLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);

	auto leftSpacer = new SpacerItem({ GuiMetrics::SpacerWidth, GuiMetrics::ItemHeight });
	horLayout->addItem(leftSpacer);

	auto leftWrapper = ObservableWrapper::wrap(leftSpacer);

	auto leftConn = new EndPointConnection(element, leftWrapper, this);
	leftConn->setFirstJoint({ 0.0, GuiMetrics::ItemHalfHeight });
	leftConn->setSecondJoint({ 1.0 - WidthFraction, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);

	leftConn->setRadius(Radius);

	horLayout->addItem(element->layoutItem());

	auto rightSpacer = new SpacerItem({ GuiMetrics::SpacerWidth, GuiMetrics::ItemHeight });
	horLayout->addItem(rightSpacer);

	auto rightWrapper = ObservableWrapper::wrap(rightSpacer);

	auto rightConn = new EndPointConnection(element, rightWrapper, this);
	rightConn->setFirstJoint({ 1.0, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);
	rightConn->setSecondJoint({ WidthFraction, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);

	rightConn->setRadius(Radius);

	vertLayout->addItem(horLayout);
	setLayout(vertLayout);
}
