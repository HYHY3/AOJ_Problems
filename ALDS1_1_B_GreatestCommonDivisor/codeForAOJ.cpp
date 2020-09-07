#include<iostream>

using namespace std;

int main() {
	int x, y, a;

	cin >> x >> y;

	do {
		a = x % y;
		x = y;
		y = a;
	} while (a != 0);

	cout << x << endl;

	return 0;
}