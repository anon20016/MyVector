#pragma once

#include "StackImplementation.h"
#include "/Users/anon2/OneDrive/Documents/MyVector/linkedList/LinkedList.h"


// вариант с использованием ранее написанного списка и множественного наследования
// если бы список не был реализован, то было бы наследование только от интерфейса
// множественное наследование можно заменить на композицию

template < typename T >
class ListStack : public StackImplementation<T>, public LinkedList
{
public:
	ListStack<T>()
		: LinkedList()
	{

	}

	void push(const T& value)
	{
		this->pushBack(value);
	}

	void pop()
	{
		this->removeBack();
	}

	T& top()
	{
		return *(new T(getNode(size() - 1)->value));
	}
	const T& top() const
	{
		return this->getNode(size() - 1)->value;
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

