#pragma once

#include <QGraphicsLayoutItem>

class ObservableWrapper : public QObject
{
	Q_OBJECT
public:
	template<class T>
	static ObservableWrapper* wrap(T* object);

	QGraphicsLayoutItem* layoutItem() const;

Q_SIGNALS:
	void geometryChanged();

private:
	ObservableWrapper(QGraphicsLayoutItem* item, QObject* parent = nullptr);

	QGraphicsLayoutItem* m_item;
};

#include "ObservableWrapper.tpp"
