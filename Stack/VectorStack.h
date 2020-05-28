#pragma once
#include "StackImplementation.h"
#include "/Users/anon2/OneDrive/Documents/MyVector/Vector/Vector.h"

// вариант с использованием ранее написанного вектора и множественного наследования
// если бы вектор не был реализован, то было бы наследование только от интерфейса
// множественное наследование можно заменить на композицию

template < typename T >
class VectorStack : public StackImplementation<T>, public MyVector<T>
{
public:
	VectorStack<T>()
		:MyVector<T>()
	{

	}

	void push(const T& value)
	{
		this->pushBack(value);
	}

	void pop()
	{
		this->popBack();
	}

	T& top()
	{
		return *(new T(this->Front()));
	}
	const T& top() const
	{
		return this->Front();
	}

	bool isEmpty() const
	{
		return this->size() == 0;
	}

	size_t Size() const
	{
		return this->size();
	}
};
