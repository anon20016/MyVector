#include<stdexcept>
#include<stdlib.h>

#pragma once

// ��������� ��������� capacity
enum class ResizeStrategy {
	Additive,
	Multiplicative
};

template < typename T >
class MyVector
{
public:
	MyVector<T>(size_t size = 0, ResizeStrategy = ResizeStrategy::Multiplicative, float coef = 2.0, int delta = 10);

	MyVector(const MyVector<T>& copy);
	MyVector& operator=(const MyVector<T>& copy);
	~MyVector();

	// ��� ��������� � ����������� ����������� � �������� ��� �����������

	size_t capacity() const;
	size_t size() const;
	
	float loadFactor();

	// ������ � ��������, 
	// ������ �������� �� O(1)
	T& operator[](const size_t i);
	const T& operator[](const size_t i) const;

	// �������� � �����,
	// ������ �������� �� amort(O(1))
	void pushBack(const T& value);
	// ��������,
	// ������ �������� �� O(n)
	void insert(const size_t i, const T& value);	// ������ ��� ������ ��������
	void insert(const size_t i, const MyVector& value);	// ������ ��� �������

	// ������� � �����,
	// ������ �������� �� amort(O(1))
	void popBack();
	// �������
	// ������ �������� �� O(n)
	void erase(const size_t i);
	void erase(const size_t i, const size_t len);			// ������� len ��������� ������� � i

	// ����� �������,
	// ������ �������� �� O(n)
	// ���� isBegin == true, ����� ������ ������� ��������, ������� value, ����� ����������
	// ���� �������� �������� ���, ������� -1
	long long int find(const T& value, bool isBegin = true) const;

	// ��������������� ������ (������������� ������ capacity)
	void reserve(const size_t capacity);

	// �������� ������
	// ���� ����� ������ ������ ��������, �� ����� �������� ���������� ���������� ����������
	// ���� ������ - �������� ������
	void resize(const size_t size);

	// ������� �������, ��� ��������� capacity
	void clear();
private:
	// ��������� capacity, ���� ������� �� ���������� num �������������� ���������. ��� num = 0 ���� �
	void CalcCapacity(const int num = 0);

	void decreasecapacity();

	T* _data;
	size_t _size;
	size_t _capacity;
	ResizeStrategy resizestrategy;
	float _coef;
	int _delta;
};

template<typename T>
inline MyVector<T>::MyVector(size_t size, ResizeStrategy r, float coef, int delta)
{
	_coef = coef;
	_delta = delta;
	_capacity = 1;
	reserve(size);
	_size = size;
	resizestrategy = r;
	for (int i = 0; i < _size; i++) {
		_data[i] = 0;
	}
}

template<typename T>
inline T& MyVector<T>::operator[](const size_t i)
{
	if (i < _size) {
		return _data[i];
	}
	else {
		throw std::runtime_error("Vector subscript out of range");
	}
}

template<typename T>
inline void MyVector<T>::reserve(const size_t new_capacity)
{
	if (new_capacity > _capacity) {			
		T* ndata = new T[new_capacity];
		for (int i = 0; i < _size; i++) {
			ndata[i] = _data[i];
		}
		delete[] _data;
		_capacity = new_capacity;
		_data = ndata;
	}
}


template<typename T>
inline size_t MyVector<T>::capacity() const
{
	return _capacity;
}



template<typename T>
inline size_t MyVector<T>::size() const
{
	return _size;
}


template<typename T>
inline const T& MyVector<T>::operator[](const size_t i) const
{
	if (i <= _size) {
		return _data[i];
	}
	else {
		throw std::runtime_error("Vector subscript out of range");
	}
}
template<typename T>
inline MyVector<T>::MyVector(const MyVector<T>& copy)
{
	_size = copy._size;
	_capacity = copy._capacity;
	_data = new T[_capacity];
	for (int i = 0; i < _size; i++) {
		_data[i] = copy._data[i];
	}
}
template<typename T>
MyVector<T>::~MyVector()
{
	delete[] _data;
}



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
	CalcCapacity();
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
	decreasecapacity();
}


template<typename T>
inline void MyVector<T>::CalcCapacity(const int num)
{
	while (_size + num >= _capacity) {
		switch (resizestrategy)
		{
		case ResizeStrategy::Additive:
			reserve(_capacity + _delta);
			break;
		case ResizeStrategy::Multiplicative:
			// ��������� max, ��� ��� ���� coef ������ ����, �� ����� �� ���������� ������. 1 * 1.5 = 1
			if (_capacity * _coef == _capacity) {
				reserve(_capacity + 1);
			}
			else {
				reserve(_capacity * _coef);
			}
			break;
		default:
			break;
		}
	}
	
}

template<typename T>
inline void MyVector<T>::decreasecapacity()
{
	while (loadFactor() <= 1 / (_coef * _coef)) {
		int new_capacity = _capacity / _coef;
		T* ndata = new T[new_capacity];
		for (int i = 0; i < _size; i++) {
			ndata[i] = _data[i];
		}
		delete[] _data;
		_capacity = new_capacity;
		_data = ndata;
	}
}





template<typename T>
inline void MyVector<T>::popBack()
{
	if (_size == 0)
		throw std::runtime_error("Vector subscript out of range");
	_size--;
	decreasecapacity();
}


template<typename T>
inline void MyVector<T>::resize(const size_t size)
{
	// ����� ���� �������������, ����� ������ �� ���������� � CalcCapacity, ����� ���������� ������ �� ��� ��������
	CalcCapacity(size - _size);
	for (int i = _size; i < size; i++) {
		_data[i] = 0;
	}
	_size = size;
	CalcCapacity();
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

