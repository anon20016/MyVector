#include <iostream>
#include "Vector.h"
using namespace std;

enum class SortedStrategy {
	Increase,
	Decrease
};


MyVector<int> sortedSquares(const MyVector<int>& vec, SortedStrategy strategy)
{
	int n = vec.size();
	MyVector<int> result(n);
	int neg = 0;
	int pos = -1;
	for (int i = 0; i < n && pos < 0; i++) {
		if (vec[i] >= 0) {
			pos = i;
			neg = i - 1;
		}
	}
	if (pos == -1) {
		pos = n;
		neg = n - 1;
	}
	for (int i = 0; i < n; i++) {
		if (pos >= n) {
			result[i] = vec[neg] * vec[neg];
			neg--;
		}
		else {
			if (neg < 0) {
				result[i] = vec[pos] * vec[pos];
				pos++;
			}
			else {
				switch (strategy)
				{
				case SortedStrategy::Increase:
					if (vec[pos] * vec[pos] < vec[neg] * vec[neg]) {
						result[i] = vec[pos] * vec[pos];
						pos++;
					}
					else {
						result[i] = vec[neg] * vec[neg];
						neg--;
					}
					break;
				case SortedStrategy::Decrease:
					if (vec[pos] * vec[pos] < vec[neg] * vec[neg]) {
						result[i] = vec[neg] * vec[neg];
						neg--;
					}
					else {
						result[i] = vec[pos] * vec[pos];
						pos++;
					}
					break;
				default:
					break;
				}
			}
		}
	}
	return result;
}


int main() {
	int n;
	cin >> n;
	MyVector<int> a;
	for (int i = 0; i < n; i++) {
		int c;
		cin >> c;
		a.pushBack(c);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - 1; j++) {
			if (a[j] > a[j + 1]) {
				swap(a[j], a[j + 1]);
			}
		}
	}

	MyVector<int> b = sortedSquares(a, SortedStrategy::Increase);

	for (int i = 0; i < n; i++) {
		cout << b[i] << ' ';
	}
}

