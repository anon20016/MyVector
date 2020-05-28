#include<stdexcept>
#include<stdlib.h>

#pragma once

using namespace std;

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

	const T& Front() const;
private:
	// ��������� capacity, ���� ������� �� ���������� num �������������� ���������. ��� num = 0 ���� �
	void CalcCapacity(const int num = 0);

	T* _data;
	size_t _size;
	size_t _capacity;
	ResizeStrategy resizestrategy;
	float _coef;
	int _delta;
};
