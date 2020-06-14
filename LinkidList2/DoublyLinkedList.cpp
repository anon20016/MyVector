#include "DoublyLinkedList.h"
#include <cassert>

DoublyLinkedList::Node::Node(const ValueType& value, Node* next, Node* prev)
{
	this->value = value;
	this->next = next;
	this->prev = prev;
}

DoublyLinkedList::Node::~Node()
{
	// ничего не удаляем, т.к. агрегация
}

void DoublyLinkedList::Node::insertNext(const ValueType& value)
{
	Node* newNode = new Node(value, this->next, this);
	this->next->prev = newNode;
	this->next = newNode;
}

void DoublyLinkedList::Node::removeNext()
{
	Node* removeNode = this->next;
	this->next = removeNode->next;
	if (removeNode->next != nullptr) {
		removeNode->next->prev = this;
	}
	delete removeNode;
}

DoublyLinkedList::DoublyLinkedList()
	: _head(nullptr), _size(0), _tail(nullptr)
{

}

DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& copyList)
{
	this->_size = copyList._size;
	if (this->_size == 0) {
		this->_head = nullptr;
		this->_tail = nullptr;
		return;
	}

	this->_head = new Node(copyList._head->value);
	this->_tail = nullptr;

	Node* currentNode = this->_head;
	Node* currentCopyNode = copyList._head;

	while (currentCopyNode->next) {
		currentNode->next = new Node(currentCopyNode->next->value);
		currentNode->next->prev = currentNode;
		currentCopyNode = currentCopyNode->next;
		currentNode = currentNode->next;		
	}
	this->_tail = currentNode;

}

DoublyLinkedList& DoublyLinkedList::operator=(const DoublyLinkedList& copyList)
{
	if (this == &copyList) {
		return *this;
	}
	DoublyLinkedList bufList(copyList);
	this->_size = bufList._size;
	this->_head = bufList._head;
	this->_tail = bufList._tail;


	return *this;
}

DoublyLinkedList::DoublyLinkedList(DoublyLinkedList&& moveList) noexcept
{
	this->_size = moveList._size;
	this->_head = moveList._head;
	this->_tail = moveList._tail;

	moveList._size = 0;
	moveList._head = nullptr;
	moveList._head = nullptr;
}

DoublyLinkedList& DoublyLinkedList::operator=(DoublyLinkedList&& moveList) noexcept
{
	if (this == &moveList) {
		return *this;
	}
	forceNodeDelete(_head);
	this->_size = moveList._size;
	this->_head = moveList._head;
	this->_tail = moveList._tail;


	moveList._size = 0;
	moveList._head = nullptr;

	return *this;
}

DoublyLinkedList::~DoublyLinkedList()
{
	forceNodeDelete(_head);
}

ValueType& DoublyLinkedList::operator[](const size_t pos) const
{
	return getNode(pos)->value;
}

DoublyLinkedList::Node* DoublyLinkedList::getNode(const size_t pos) const
{
	if (pos < 0) {
		assert(pos < 0);
	}
	else if (pos >= this->_size) {
		assert(pos >= this->_size);
	}

	Node* bufNode = this->_head;
	for (int i = 0; i < pos; ++i) {
		bufNode = bufNode->next;
	}

	return bufNode;
}

void DoublyLinkedList::insert(const size_t pos, const ValueType& value)
{
	if (pos < 0) {
		assert(pos < 0);
	}
	else if (pos > this->_size) {
		assert(pos > this->_size);
	}

	if (pos == 0) {
		pushFront(value);
		return;
	}
	else {
		Node* bufNode = this->_head;
		for (size_t i = 0; i < pos - 1; ++i) {
			bufNode = bufNode->next;
		}
		bufNode->insertNext(value);
		++_size;
	}
}

void DoublyLinkedList::insertAfterNode(Node* node, const ValueType& value)
{
	node->insertNext(value);
}

void DoublyLinkedList::pushBack(const ValueType& value)
{
	if (_size == 0) {
		pushFront(value);
		return;
	}
	Node* node = this->_tail;
	this->_tail->insertNext(value);
	this->_tail->next->prev = node;
	this->_tail = node->next;
	_size++;
}

void DoublyLinkedList::pushFront(const ValueType& value)
{	
	_head = _tail = new Node(value, _head, nullptr);
	++_size;
}

void DoublyLinkedList::remove(const size_t pos)
{
	if (pos < this->_size) {
		if (pos == 0) {
			removeFront();
		}
		if (pos == _size - 1) {
			removeBack();
		}
		this->getNode(pos - 1)->removeNext();
		_size--;

	}
}

void DoublyLinkedList::removeNextNode(Node* node)
{
	node->removeNext();
}

void DoublyLinkedList::removeFront()
{
	this->_head->next->prev = nullptr;
	Node* h = this->_head;
	this->_head = this->_head->next;
	delete h;
	_size--;
}

void DoublyLinkedList::removeBack()
{
	this->_tail->prev->next = nullptr;
	Node* t = this->_tail;
	*this->_tail = *this->_tail->prev;
	delete t;
	_size--;
	return;
}

long long int DoublyLinkedList::findIndex(const ValueType& value) const
{
	Node* cur = this->_head;
	int c = 0;
	while (cur != nullptr && cur->value != value) {
		cur = cur->next;
		c++;
	}
	return c == _size ? -1 : c;
}

DoublyLinkedList::Node* DoublyLinkedList::findNode(const ValueType& value) const
{
	Node* cur = this->_head;
	while (cur != nullptr && cur->value != value) {
		cur = cur->next;
	}
	return cur;
}

void DoublyLinkedList::reverse()
{
	Node* cur = _tail;
	Node* tail = _tail;
	while (cur->prev != nullptr) {
		auto pr = cur->prev;
		cur->prev = cur->next;
		cur->next = pr;
		cur = cur->next;
	}
	cur->next = nullptr;
	this->_head = tail;
	this->_tail = cur;
}

DoublyLinkedList DoublyLinkedList::reverse() const
{
	DoublyLinkedList newlist(*this);
	newlist.reverse();
	return newlist;
}

DoublyLinkedList DoublyLinkedList::getReverseList() const
{
	DoublyLinkedList newlist(*this);
	newlist.reverse();
	return newlist;
}

size_t DoublyLinkedList::size() const
{
	return _size;
}

void DoublyLinkedList::forceNodeDelete(Node* node)
{
	if (node == nullptr) {
		return;
	}

	Node* nextDeleteNode = node->next;
	delete node;
	forceNodeDelete(nextDeleteNode);
}