#include <bits/stdc++.h>

using namespace std;

int K;
int QueenInfo[8];
bool Col[8], LeftDiagonal[15], RightDiagonal[15];

void show() {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			cout << (QueenInfo[i] == j ? 'Q' : '.');
		}
		cout << endl;
	}
}

void solve(int curRow) {
	int leftPos, rightPos;

	if (curRow == 8) {
		show();
		return;
	}

	if (QueenInfo[curRow] != -1) {
		solve(curRow + 1);
		return;
	}

	for (int j = 0; j < 8; ++j) {
		leftPos = curRow - j + 7;
		rightPos = curRow + j;
		if (Col[j] || LeftDiagonal[leftPos] || RightDiagonal[rightPos]) {
			continue;
		}

		QueenInfo[curRow] = j;
		Col[j] = true;
		LeftDiagonal[leftPos] = true;
		RightDiagonal[rightPos] = true;
		solve(curRow + 1);

		QueenInfo[curRow] = -1;
		Col[j] = false;
		LeftDiagonal[leftPos] = false;
		RightDiagonal[rightPos] = false;
	}
}

int main() {
	int r, c;

	fill(QueenInfo, QueenInfo + 8, -1);
	memset(Col, false, sizeof(Col));
	memset(LeftDiagonal, false, sizeof(LeftDiagonal));
	memset(RightDiagonal, false, sizeof(RightDiagonal));
	cin >> K;
	for (int i = 0; i < K; ++i) {
		cin >> r >> c;
		QueenInfo[r] = c;
		Col[c] = true;
		LeftDiagonal[r - c + 7] = true;
		RightDiagonal[r + c] = true;
	}
	solve(0);

	return 0;
}