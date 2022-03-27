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

	auto ctrlPtsGenerator = [] (const QPointF& startPoint, const QPointF& endPoint) {
		QPointF cp2 = { startPoint.x(), endPoint.y() };
		QPointF cp1 = { endPoint.x(), startPoint.y() };
		return GraphicsConnection::PtsPair{ cp1, cp2 };
	};

	for (auto itemWrapper : m_wrappers) {
		auto leftConn = new GraphicsConnection(widgetWrapper, itemWrapper, widget);
		leftConn->setFirstJoint({ 0, GuiMetrics::ItemHalfHeight });
		leftConn->setSecondJoint({ 0, GuiMetrics::ItemHalfHeight });
		leftConn->setCtrlPtsGenerator(ctrlPtsGenerator);

		innerLayout->addItem(itemWrapper->layoutItem());

		auto rightConn = new GraphicsConnection(widgetWrapper, itemWrapper, widget);
		rightConn->setFirstJoint({ 1.0, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);
		rightConn->setSecondJoint({ 1.0, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);
		rightConn->setCtrlPtsGenerator(ctrlPtsGenerator);
	}

	widget->setLayout(outerLayout);
	return widget;
}
