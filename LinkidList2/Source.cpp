#include<iostream>
#include "DoublyLinkedList.h"

using namespace std;

int main() {
	DoublyLinkedList list;
	list.pushBack(1);
	list.pushBack(2);
	list.pushBack(3);

	DoublyLinkedList a = list.getReverseList();

	for (int i = 0; i < a.size(); i++) {
		cout << a[i] << ' ';
	}

	return 0;
}