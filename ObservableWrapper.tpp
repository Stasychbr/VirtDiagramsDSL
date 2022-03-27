template<class T>
ObservableWrapper* ObservableWrapper::wrap(T* item) {
	auto wrapper = new ObservableWrapper(item);
	connect(item, &T::geometryChanged, wrapper, &ObservableWrapper::geometryChanged);
	return wrapper;
}

inline ObservableWrapper::ObservableWrapper(QGraphicsLayoutItem* item, QObject* parent)
	: QObject(parent), m_item(item) {}

inline QGraphicsLayoutItem* ObservableWrapper::layoutItem() const
{
	return m_item;
}
