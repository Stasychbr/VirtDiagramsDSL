#pragma once

#include <QGraphicsLinearLayout>
#include <QGraphicsWidget>

#include "ObservableWrapper.h"
#include "GraphicsConnections/LineConnection.h"

class ConcatenationItem : public QGraphicsWidget
{
public:
	ConcatenationItem(QGraphicsItem* parent = nullptr);

	void addElement(ObservableWrapper* element);
	void flush();

private:
	ObservableWrapper* elementAt(int i) const;
	ObservableWrapper* firstElement() const;
	ObservableWrapper* lastElement() const;

	int elementCount() const;

	QGraphicsLinearLayout* m_layout;
};

