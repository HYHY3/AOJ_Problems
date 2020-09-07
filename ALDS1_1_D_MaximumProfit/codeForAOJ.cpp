#include <bits/stdc++.h>

using namespace std;

vector<int> PriceInfo;

void solve(int n) {
	int minR, maxProfit;

	minR = PriceInfo[0];
	maxProfit = -1000000000;
	for (int i = 1; i < n; ++i) {
		maxProfit = max(maxProfit, PriceInfo[i] - minR);
		minR = min(minR, PriceInfo[i]);
	}

	cout << maxProfit << endl;
}

int main() {
	int n, r;

	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> r;
		PriceInfo.push_back(r);
	}
	solve(n);

	return 0;
}