#include<bits/stdc++.h>

using namespace std;

bool judgePrimeNumber(const int &num) {
	int limit;

	if (num == 2) {
		return true;
	}

	if ((num & 1) == 0) {
		return false;
	}

	limit = sqrt(num) + 1;
	for (int i = 2; i < limit; ++i) {
		if (num%i == 0) {
			return false;
		}
	}
	return true;
}

int main() {
	int n, num, cnt;

	cnt = 0;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> num;
		if (!judgePrimeNumber(num)) {
			++cnt;
		}
	}
	cout << n - cnt << endl;

	return 0;
}