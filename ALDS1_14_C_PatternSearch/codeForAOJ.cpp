#include <bits/stdc++.h>

using namespace std;

const int BaseRow = 9999991;
const int BaseCol = 9999973;
const unsigned long long  M = 1000000007;
const int MaxLength = 1001;

int H, W, R, C;
unsigned long long TargetHashCode[MaxLength][MaxLength], TargetHashCodeTemp[MaxLength][MaxLength];
string Target[MaxLength], Pattern[MaxLength];

void calculateHashCode(unsigned long long &finalPatternHashCode) {
	unsigned long long  key, acc;

	finalPatternHashCode = 0;
	for (int i = 0; i < R; ++i) {
		key = 0;
		for (int j = 0; j < C; ++j) {
			key = (key * BaseCol % M + Pattern[i][j]) % M;
		}
		finalPatternHashCode = (finalPatternHashCode * BaseRow % M + key) % M;
	}

	acc = 1;
	for (int i = 0; i < C; ++i) {
		acc = acc * BaseCol % M;
	}
	for (int i = 0; i < H; ++i) {
		key = 0;
		for (int j = 0; j < W; ++j) {
			key = (key * BaseCol % M + Target[i][j]) % M;
			if (j >= C) {
				key = (key - Target[i][j - C] * acc % M + M) % M;
			}
			TargetHashCode[i][j] = key;
			TargetHashCodeTemp[i][j] = key;
		}
	}

	acc = 1;
	for (int i = 0; i < R; ++i) {
		acc = acc * BaseRow % M;
	}
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			if (i != 0) {
				TargetHashCode[i][j] = (TargetHashCode[i][j] + TargetHashCode[i - 1][j] * BaseRow % M) % M;
			}
			if (i >= R) {
				TargetHashCode[i][j] = (TargetHashCode[i][j] - TargetHashCodeTemp[i - R][j] * acc % M + M) % M;
			}
		}
	}
}

int main() {
	unsigned long long finalPatternHashCode;

	cin >> H >> W;
	for (int i = 0; i < H; ++i) {
		cin >> Target[i];
	}
	cin >> R >> C;
	for (int i = 0; i < R; ++i) {
		cin >> Pattern[i];
	}

	calculateHashCode(finalPatternHashCode);
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			if (TargetHashCode[i][j] == finalPatternHashCode) {
				cout << i - R + 1 << " " << j - C + 1 << endl;
			}
		}
	}

	return 0;
}