#include <iostream>
#include "Stack.h"

using namespace std;
int main() {
	Stack<int> a(StackContainer::List);
	a.push(1);
	a.push(2);
	cout << a.top() << endl;
	a.pop();
	cout << a.top() << endl;
	a.pop();
	cout << a.size();
}