#include <bits/stdc++.h>

using namespace std;

string MapInfo;
stack<int> LeftSlopes, AreaInfo;
stack<pair<int, int> > AreasInfo;

void solve(int rightIndex) {
	int leftIndex, curAreas;

	leftIndex = LeftSlopes.top();
	LeftSlopes.pop();
	curAreas = rightIndex - leftIndex;

	while (true) {
		if (AreasInfo.empty() || AreasInfo.top().first < leftIndex) {
			AreasInfo.push({ leftIndex, curAreas });
			return;
		}
		curAreas += AreasInfo.top().second;
		AreasInfo.pop();
	}
}

int main() {
	int len, k, total, curArea;

	cin >> MapInfo;
	len = MapInfo.size();
	for (int i = 0; i < len; ++i) {
		if (MapInfo[i] == '_') { 
			continue;
		}

		if (MapInfo[i] == '\\') {
			LeftSlopes.push(i);
			continue;
		}

		if (LeftSlopes.empty()) {
			continue;
		}
		solve(i);
	}
	k = AreasInfo.size();
	total = 0;
	for (int i = 0; i < k; ++i) {
		curArea = AreasInfo.top().second;
		AreasInfo.pop();
		total += curArea;
		AreaInfo.push(curArea);
	}

	cout << total << endl << k;
	for (int i = 0; i < k; ++i) {
		cout << " " << AreaInfo.top();
		AreaInfo.pop();
	}
	cout << endl;

	return 0;
}