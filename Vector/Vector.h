#include<stdexcept>
#include<stdlib.h>

#pragma once

using namespace std;

// стратегия изменения capacity
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

	// для умненьких — реализовать конструктор и оператор для перемещения

	size_t capacity() const;
	size_t size() const;
	
	float loadFactor();

	// доступ к элементу, 
	// должен работать за O(1)
	T& operator[](const size_t i);
	const T& operator[](const size_t i) const;

	// добавить в конец,
	// должен работать за amort(O(1))
	void pushBack(const T& value);
	// вставить,
	// должен работать за O(n)
	void insert(const size_t i, const T& value);	// версия для одного значения
	void insert(const size_t i, const MyVector& value);	// версия для вектора

	// удалить с конца,
	// должен работать за amort(O(1))
	void popBack();
	// удалить
	// должен работать за O(n)
	void erase(const size_t i);
	void erase(const size_t i, const size_t len);			// удалить len элементов начиная с i

	// найти элемент,
	// должен работать за O(n)
	// если isBegin == true, найти индекс первого элемента, равного value, иначе последнего
	// если искомого элемента нет, вернуть -1
	long long int find(const T& value, bool isBegin = true) const;

	// зарезервировать память (принудительно задать capacity)
	void reserve(const size_t capacity);

	// изменить размер
	// если новый размер больше текущего, то новые элементы забиваются дефолтными значениями
	// если меньше - обрезаем вектор
	void resize(const size_t size);

	// очистка вектора, без изменения capacity
	void clear();

	const T& Front() const;
private:
	// Изменения capacity, путём запроса на добавление num дополнительных элементов. При num = 0 идет п
	void CalcCapacity(const int num = 0);

	T* _data;
	size_t _size;
	size_t _capacity;
	ResizeStrategy resizestrategy;
	float _coef;
	int _delta;
};
