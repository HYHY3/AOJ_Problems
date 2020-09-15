#include <bits/stdc++.h>

using namespace std;

int N;
vector<pair<int, int> > MatrixInfo;
int DpCount[101][101];
const int INF = 100000000;

void solve() {
	int curEndPos, curCount;

	memset(DpCount, 0, sizeof(DpCount));

	for (int len = 2; len <= N; ++len) {
		for (int i = 1; i < N; ++i) {
			curEndPos = i + len - 1;
			if (curEndPos > N) {
				break;
			}
			DpCount[i][curEndPos] = INF;
			for (int k = i; k < curEndPos; ++k) {
				curCount = DpCount[i][k] + DpCount[k + 1][curEndPos];
				curCount += MatrixInfo[i - 1].first * MatrixInfo[k].first * MatrixInfo[curEndPos - 1].second;
				DpCount[i][curEndPos] = min(DpCount[i][curEndPos], curCount);
			}
		}
	}

	cout << DpCount[1][N] << endl;
}

int main() {
	int r, c;

	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> r >> c;
		MatrixInfo.push_back({ r,c });
	}
	solve();

	return 0;
}