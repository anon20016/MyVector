#include<iostream>
#include "LinkedList.h"

using namespace std;

int main() {
	LinkedList list;
	list.pushBack(1);
	list.pushBack(2);
	list.pushBack(3);

	list.removeFront();

	for (int i = 0; i < list.size(); i++) {
		cout << list[i] << ' ';
	}

	return 0;
}