#include <bits/stdc++.h>

using namespace std;

const int N = 3;
const int MaxLength = N*N;
const int Dx[] = { 0,1,0,-1 };
const int Dy[] = { 1,0,-1,0 };

int Steps;
int PuzzleInfo[MaxLength];

int getHeuristic() {
	int hcost, curPos;

	hcost = 0;
	for (int i = 0; i < MaxLength; ++i) {
		curPos = PuzzleInfo[i] - 1;
		if (curPos == MaxLength - 1 || curPos == i) {
			continue;
		}
		hcost += abs(i / N - curPos / N) + abs(i % N - curPos % N);
	}

	return hcost;
}

bool check(int curDepth, int preDir, int spaceX, int spaceY) {
	int curCost, nextX, nextY, curSpaceIndex, nextSpaceIndex;

	curCost = getHeuristic();
	if (curCost == 0) {
		return true;
	}
	if (curCost + curDepth > Steps) {
		return false;
	}
	
	for (int i = 0; i < 4; ++i) {
		if (abs(i - preDir) == 2) {
			continue;
		}
		nextX = spaceX + Dx[i];
		nextY = spaceY + Dy[i];
		if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= N) {
			continue;
		}
		curSpaceIndex = spaceX*N + spaceY;
		nextSpaceIndex = nextX*N + nextY;
		swap(PuzzleInfo[curSpaceIndex], PuzzleInfo[nextSpaceIndex]);
		if (check(curDepth + 1, i, nextX, nextY)) {
			return true;
		}
		swap(PuzzleInfo[curSpaceIndex], PuzzleInfo[nextSpaceIndex]);
	}
	return false;
}

void solve(int &spaceIndex) {
	
	Steps = 0;
	while (true) {
		if (check(0, 10, spaceIndex / N, spaceIndex % N)) {
			break;
		}
		++Steps;
	}
	cout << Steps << endl;
}

int main() {
	int num, spaceIndex;

	for (int i = 0; i < MaxLength; ++i) {
		cin >> num;
		if (num == 0) {
			spaceIndex = i;
			num = MaxLength;
		}
		PuzzleInfo[i] = num;
	}
	solve(spaceIndex);

	return 0;
}