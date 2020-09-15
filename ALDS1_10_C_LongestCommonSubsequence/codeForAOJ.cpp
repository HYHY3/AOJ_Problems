#include <bits/stdc++.h>

using namespace std;

string X, Y;
int DpLen[1001][1001];

void solve() {
	int lenX, lenY;

	memset(DpLen, 0, sizeof(DpLen));
	lenX = X.size();
	lenY = Y.size();
	for (int i = 1; i <= lenX; ++i) {
		for (int j = 1; j <= lenY; ++j) {
			if (X[i - 1] == Y[j - 1]) {
				DpLen[i][j] = DpLen[i - 1][j - 1] + 1;
			}
			else {
				DpLen[i][j] = max(DpLen[i - 1][j], DpLen[i][j - 1]);
			}
		}
	}
	
	cout << DpLen[lenX][lenY] << endl;
}

int main() {
	int q;

	cin >> q;
	for (int i = 0; i < q; ++i) {
		cin >> X >> Y;
		solve();
	}

	return 0;
}