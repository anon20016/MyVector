#pragma once

#include "Stack.h"
#include "ListStack.h"
#include "VectorStack.h"
#include "StackImplementation.h"

#include <stdexcept>

// Уровень абстракции
// клиентский код подключает именно этот хедер

// тип значений в стеке

// на основе какого контейнера работает стек
enum class StackContainer {
	Vector = 0,
	List,
	// можно дополнять другими контейнерами
};

// декларация класса с реализацией
template < typename T >
class StackImplementation;

template < typename T >
class Stack
{
public:
	// Большая пятерка
	Stack(StackContainer container = StackContainer::Vector);
	// элементы массива последовательно подкладываются в стек
	Stack(const T* valueArray, const size_t arraySize, 
		  StackContainer container = StackContainer::Vector);


	// Здесь как обычно
	// Stack(Stack&& moveStack) noexcept;
	// Stack& operator=(Stack&& moveStack) noexcept;

	~Stack();

	// добавление в хвост
	void push(const T& value);
	// удаление с хвоста
	void pop();
	// посмотреть элемент в хвосте
	T& top();
	const T& top() const;
	// проверка на пустоту
	bool isEmpty() const;
	// размер 
	size_t size() const;
private:
	// указатель на имплементацию (уровень реализации)
	StackImplementation<T>* _pimpl = nullptr;
	// тип контейнера, наверняка понадобится
	StackContainer _containerType;
};

template<typename T>
inline Stack<T>::Stack(StackContainer container)
{
	switch (container)
	{
	case StackContainer::Vector:
		_pimpl = new VectorStack<T>;
		break;
	case StackContainer::List:
		_pimpl = new ListStack<T>;

		break;
	default:
		break;
	}
}

template<typename T>
Stack<T>::Stack(const T* valueArray, const size_t arraySize, StackContainer container)
{
	switch (container)
	{
	case StackContainer::Vector:
		_pimpl = new VectorStack<T>;
		for (int i = 0; i < arraySize; i++) {
			_pimpl->push(valueArray[i]);
		}
		break;
	case StackContainer::List:
		_pimpl = new ListStack<T>;
		for (int i = 0; i < arraySize; i++) {
			_pimpl->push(valueArray[i]);
		}
		break;
	default:
		break;
	}
}




template<typename T>
inline Stack<T>::~Stack()
{
}

template<typename T>
inline void Stack<T>::push(const T& value)
{
	_pimpl->push(value);
}

template<typename T>
inline void Stack<T>::pop()
{
	_pimpl->pop();
}

template<typename T>
inline T& Stack<T>::top()
{
	return _pimpl->top();
}

template<typename T>
inline const T& Stack<T>::top() const
{
	return _pimpl->top();
}

template<typename T>
inline bool Stack<T>::isEmpty() const
{
	return _pimpl->isEmpty();
}

template<typename T>
inline size_t Stack<T>::size() const
{
	return _pimpl->Size();
}

