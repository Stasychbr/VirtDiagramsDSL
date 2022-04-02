template<class T>
ObservableWrapper* ObservableWrapper::wrap(T* object) {
	auto wrapper = new ObservableWrapper(object);
	connect(object, &T::geometryChanged,
			wrapper, &ObservableWrapper::geometryChanged);

	auto prevObserver = wrapperOf(object);
	delete prevObserver;

	auto graphicsItem = object->graphicsItem();
	graphicsItem->setData(DataKey, QVariant::fromValue(wrapper));

	return wrapper;
}

template<class T>
ObservableWrapper* ObservableWrapper::wrapperOf(T* object) {
	auto graphicsItem = object->graphicsItem();
	QVariant itemData = graphicsItem->data(ObservableWrapper::DataKey);
	return itemData.value<ObservableWrapper*>();
}

inline ObservableWrapper::ObservableWrapper(QGraphicsLayoutItem* item, QObject* parent)
	: QObject(parent), m_item(item) {}

inline QGraphicsLayoutItem* ObservableWrapper::layoutItem() const
{
	return m_item;
}
