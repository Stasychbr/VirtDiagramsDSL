#include "ConcatenationItem.h"

#include <QGraphicsLinearLayout>

#include "SpacerItem.h"
#include "Defines.h"

ConcatenationItem::ConcatenationItem(QGraphicsItem* parent)
	: QGraphicsWidget(parent)
{
	ObservableWrapper::wrap(this);

	m_layout = new QGraphicsLinearLayout;
	m_layout->setSpacing(0.0);
	m_layout->setContentsMargins(0.0, 0.0, 0.0, 0.0);

	setLayout(m_layout);
}

void ConcatenationItem::addElement(ObservableWrapper* element)
{
	if (elementCount() == 0) {
		m_layout->addItem(element->layoutItem());
		return;
	}

	auto lastWrapper = lastElement();

	auto conn = new LineConnection(lastWrapper, element, this);
	conn->setFirstJoint({ 1.0, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);
	conn->setSecondJoint({ 0.0, GuiMetrics::ItemHalfHeight });

	auto spacer = new SpacerItem({ GuiMetrics::SpacerWidth, GuiMetrics::ItemHeight });
	m_layout->addItem(spacer);
	m_layout->addItem(element->layoutItem());
}

void ConcatenationItem::flush()
{
	auto firstWrapper = firstElement();
	auto selfWrapper = ObservableWrapper::wrapperOf(this);

	auto leftConn = new LineConnection(selfWrapper, firstWrapper, this);
	leftConn->setFirstJoint({ 0, GuiMetrics::ItemHalfHeight });
	leftConn->setSecondJoint({ 0, GuiMetrics::ItemHalfHeight });

	auto lastWrapper = lastElement();

	auto rightConn = new LineConnection(lastWrapper, selfWrapper, this);
	rightConn->setFirstJoint({ 1.0, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);
	rightConn->setSecondJoint({ 1.0, GuiMetrics::ItemHalfHeight }, Qt::RelativeSize);

	auto leftSpacer = new SpacerItem({ 0, GuiMetrics::ItemHeight });
	m_layout->insertItem(0, leftSpacer);

	auto rightSpacer = new SpacerItem({ 0, GuiMetrics::ItemHeight });
	m_layout->insertItem(-1, rightSpacer);
}

ObservableWrapper* ConcatenationItem::firstElement() const
{
	return elementAt(0);
}

ObservableWrapper* ConcatenationItem::lastElement() const
{
	return elementAt(elementCount() - 1);
}

ObservableWrapper* ConcatenationItem::elementAt(int i) const
{
	auto element = m_layout->itemAt(2 * i);
	return ObservableWrapper::wrapperOf(element);
}

int ConcatenationItem::elementCount() const
{
	return (m_layout->count() + 1) / 2;
}
