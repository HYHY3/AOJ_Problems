#include<bits/stdc++.h>

using namespace std;

int getGCD(int a, int b) {
	int ans;

	if (b == 0) {
		return a;
	}
	ans = getGCD(b, a%b);
	return ans;
	//return getGCD(b, a%b);
}

int main() {
	int x, y;

	cin >> x >> y;
	cout << getGCD(x, y) << endl;

	return 0;
}