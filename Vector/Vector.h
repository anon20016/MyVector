#pragma once
#include<stdexcept>

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
	void CalcCapacity(const int num = 0);
	int min(int x, int y);
	int max(int x, int y);

	T* _data;
	size_t _size;
	size_t _capacity;
	float _coef;
	int _delta;
};

template<typename T>
inline MyVector<T>::MyVector(size_t size, ResizeStrategy, float coef, int delta)
{
	_coef = coef;
	_delta = delta;

	_capacity = 1;
	reserve(max(_capacity, size));
	_size = size;

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
	if (new_capacity == capacity())
		return;
	if (new_capacity < capacity()) {
		_size = min(_size, new_capacity);
	}
	T* ndata = new T[new_capacity];
	for (int i = 0; i < _size; i++) {
		ndata[i] = _data[i];
	}
	delete[] _data;
	_capacity = new_capacity;
	_data = ndata;
}


template<typename T>
inline MyVector<T>::~MyVector()
{
	delete[] _data;
}
template<typename T>
inline size_t MyVector<T>::capacity() const
{
	return _capacity;
}


template<typename T>
inline int MyVector<T>::min(int x, int y)
{
	if (x < y)
		return x;
	return y;
}

template<typename T>
inline int MyVector<T>::max(int x, int y)
{
	if (x > y)
		return x;
	return y;
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