#pragma once

#include <QGraphicsLayoutItem>

class ObservableWrapper : public QObject
{
	Q_OBJECT
public:
	template<class T>
	static ObservableWrapper* wrap(T* object);

	template<class T>
	static ObservableWrapper* wrapperOf(T* object);

	QGraphicsLayoutItem* layoutItem() const;

Q_SIGNALS:
	void geometryChanged();

private:
	static constexpr int DataKey = 0x1;

	ObservableWrapper(QGraphicsLayoutItem* item, QObject* parent = nullptr);

	QGraphicsLayoutItem* m_item;
};

#include "ObservableWrapper.tpp"
