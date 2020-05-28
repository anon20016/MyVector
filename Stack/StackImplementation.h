#pragma once

// приходится тянуть ValueType во все места,
// наглядная демонстрация того, почему с шаблонами было бы легче.
// Ждем, когда дойдете до этого на МиСП.

// интерфейс для конкретных реализаций контейнера для стека

template < typename T >
class StackImplementation {
public:
	// добавление в хвост
	virtual void push(const T& value) = 0;
	// удаление с хвоста
	virtual void pop() = 0;
	// посмотреть элемент в хвосте
	virtual const T& top() const = 0;
	// посмотреть элемент в хвосте
	virtual T& top() = 0;
	// проверка на пустоту
	virtual bool isEmpty() const = 0;
	// размер 
	virtual size_t Size() const = 0;
	// виртуальный деструктор
	//virtual ~StackImplementation() {};
};
