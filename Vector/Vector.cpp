#include "Vector.h"


template<typename T>
float MyVector<T>::loadFactor() {
	return (float)_size / _capacity;
}

template<typename T>
inline void MyVector<T>::erase(const size_t i)
{
	if (i >= _size)
		throw std::runtime_error("Vector subscript out of range");
	for (int j = i; j < _size - 1; j++) {
		_data[j] = _data[j + 1];
	}
	_size--;
}

template<typename T>
inline void MyVector<T>::erase(const size_t i, const size_t len)
{
	if (i + len - 1 >= _size)
		throw std::runtime_error("Vector subscript out of range");
	for (int j = i; j < _size - len; j++) {
		_data[j] = _data[j + len];
	}
	_size -= len;
}


template<typename T>
inline void MyVector<T>::CalcCapacity(const int num)
{
	while (_size + num >= _capacity) {
		switch (ResizeStrategy)
		{
		case ResizeStrategy::Additive:
			reserve(max(capacity(), capacity() + _delta));
			break;
		case ResizeStrategy::Multiplicative:
			reserve(max(capacity() * _coef, capacity() + 1));
			break;
		default:
			break;
		}
	}
	if (loadFactor() <= 0.25) {
		reserve(capacity() / 2);
	}
}


template<typename T>
inline void MyVector<T>::popBack()
{
	if (_size == 0)
		throw std::runtime_error("Vector subscript out of range");
	_size--;
}


template<typename T>
inline void MyVector<T>::resize(const size_t size)
{
	CalcCapacity(size - _size);
	for (int i = _size; i < size; i++) {
		_data[i] = 0;
	}
	_size = size;
}

template<typename T>
inline void MyVector<T>::clear()
{
	_size = 0;
}


template<typename T>
inline void MyVector<T>::insert(const size_t i, const MyVector& value)
{
	if (i >= _size)
		throw std::runtime_error("Vector subscript out of range");
	addcapacity(value.size());
	for (int j = _size + value.size(); j > i; j--) {
		_data[j] = _data[j - value.size()];
	}
	for (int j = 0; j < value.size(); j++) {
		_data[i + j] = value[j];
	}
	_size += value.size();
}

template<typename T>
inline long long int MyVector<T>::find(const T& value, bool isBegin) const
{
	if (isBegin) {
		for (int i = 0; i < _size; i++) {
			if (_data[i] == value) {
				return i;
			}
		}
	}
	else {
		for (int i = _size - 1; i >= 0; i--) {
			if (_data[i] == value) {
				return i;
			}
		}
	}
	return -1;
}


template<typename T>
inline void MyVector<T>::pushBack(const T& value)
{
	CalcCapacity(1);
	_data[_size++] = value;
}

template<typename T>
inline void MyVector<T>::insert(const size_t i, const T& value)
{
	if (i >= _size)
		throw std::runtime_error("Vector subscript out of range");
	CalcCapacity(1);
	for (int j = _size; j > i; j--) {
		_data[j] = _data[j - 1];
	}
	_data[i] = value;
	_size++;
}




template<typename T>
inline MyVector<T>& MyVector<T>::operator=(const MyVector<T>& copy)
{
	_size = copy.size;
	_capacity = copy.capacity;
	_data = new T[_capacity];
	for (int i = 0; i < _size; i++) {
		_data[i] = copy._data[i];
	}
}
