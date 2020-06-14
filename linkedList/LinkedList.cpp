#include "LinkedList.h"
#include <cassert>

LinkedList::Node::Node(const ValueType& value, Node* next)
{
	this->value = value;
	this->next = next;
}

LinkedList::Node::~Node()
{
	// ничего не удаляем, т.к. агрегация
}

void LinkedList::Node::insertNext(const ValueType& value)
{
	Node* newNode = new Node(value, this->next);
	this->next = newNode;
}

void LinkedList::Node::removeNext()
{
	Node* removeNode = this->next;
	Node* newNext = removeNode->next;
	delete removeNode;
	this->next = newNext;
}

LinkedList::LinkedList()
	: _head(nullptr), _size(0)
{

}

LinkedList::LinkedList(const LinkedList& copyList)
{
	this->_size = copyList._size;
	if (this->_size == 0) {
		this->_head = nullptr;
		return;
	}

	this->_head = new Node(copyList._head->value);

	Node* currentNode = this->_head;
	Node* currentCopyNode = copyList._head;

	while (currentCopyNode->next) {
		currentNode->next = new Node(currentCopyNode->next->value);
		currentCopyNode = currentCopyNode->next;
		currentNode = currentNode->next;
	}
}

LinkedList& LinkedList::operator=(const LinkedList& copyList)
{
	if (this == &copyList) {
		return *this;
	}
	LinkedList bufList(copyList);
	this->_size = bufList._size;
	this->_head = bufList._head;

	return *this;
}

LinkedList::LinkedList(LinkedList&& moveList) noexcept
{
	this->_size = moveList._size;
	this->_head = moveList._head;

	moveList._size = 0;
	moveList._head = nullptr;
}

LinkedList& LinkedList::operator=(LinkedList&& moveList) noexcept
{
	if (this == &moveList) {
		return *this;
	}
	forceNodeDelete(_head);
	this->_size = moveList._size;
	this->_head = moveList._head;

	moveList._size = 0;
	moveList._head = nullptr;

	return *this;
}

LinkedList::~LinkedList()
{
	forceNodeDelete(_head);
}

ValueType& LinkedList::operator[](const size_t pos) const
{
	return getNode(pos)->value;
}

LinkedList::Node* LinkedList::getNode(const size_t pos) const
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

void LinkedList::insert(const size_t pos, const ValueType& value)
{
	if (pos < 0) {
		assert(pos < 0);
	}
	else if (pos > this->_size) {
		assert(pos > this->_size);
	}

	if (pos == 0) {
		pushFront(value);
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

void LinkedList::insertAfterNode(Node* node, const ValueType& value)
{
	node->insertNext(value);
}

void LinkedList::pushBack(const ValueType& value)
{
	if (_size == 0) {
		pushFront(value);
		return;
	}
	insert(_size, value);
}

void LinkedList::pushFront(const ValueType& value)
{
	_head = new Node(value, _head);
	++_size;
}

void LinkedList::remove(const size_t pos)
{
	if (pos < this->_size) {
		if (pos == 0) {
			auto temp = this->_head;
			this->_head = this->_head->next;
			delete temp;
		}
		else {
			this->getNode(pos - 1)->removeNext();
		}
		_size--;
	}
}

void LinkedList::removeNextNode(Node* node)
{
	node->removeNext();
}

void LinkedList::removeFront()
{
	auto temp = this->_head;
	*this->_head = *this->_head->next;
	delete temp;
	_size--;
}

void LinkedList::removeBack()
{	
	getNode(_size - 2)->removeNext();
	_size--;
}

long long int LinkedList::findIndex(const ValueType& value) const
{
	Node* cur = this->_head;
	int c = 0;
	while (cur != nullptr && cur->value != value) {
		cur = cur->next;
		c++;
	}
	return c == _size ? -1 : c;
}

LinkedList::Node* LinkedList::findNode(const ValueType& value) const
{
	Node* cur = this->_head;
	while (cur != nullptr && cur->value != value) {
		cur = cur->next;
	}
	return cur;
}

void LinkedList::reverse()
{
	rec(this->_head);
}

LinkedList LinkedList::reverse() const
{
	LinkedList newlist(*this);
	newlist.reverse();
	return newlist;
}

LinkedList LinkedList::getReverseList() const
{
	LinkedList newlist(*this);
	newlist.reverse();
	return newlist;
}

size_t LinkedList::size() const
{
	return _size;
}

void LinkedList::rec(Node* cur)
{
	Node* nxt = cur->next;
	if (nxt != nullptr) {
		rec(nxt);
		nxt->next = cur;
	}
	else {
		this->_head->next = nullptr;
		this->_head = cur;
	}
}

void LinkedList::forceNodeDelete(Node* node)
{
	if (node == nullptr) {
		return;
	}

	Node* nextDeleteNode = node->next;
	delete node;
	forceNodeDelete(nextDeleteNode);
}






