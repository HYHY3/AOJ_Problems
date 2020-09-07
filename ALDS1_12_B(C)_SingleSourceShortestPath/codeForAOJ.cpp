#include <bits/stdc++.h>

using namespace std;

int N;
vector<vector<pair<int, int> > > GraphInfo;
int DistanceInfo[10000];
bool Visited[10000];

const int INF = 100000000;

void solve(int startId) {
	int curId, size, nextId;
	pair<int, int> curNode;
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > nodeList;

	memset(Visited, false, sizeof(Visited));
	fill(DistanceInfo, DistanceInfo + 10000, INF);

	DistanceInfo[startId] = 0;
	nodeList.push({ DistanceInfo[startId],startId });
	while (!nodeList.empty()) {
		curNode = nodeList.top();
		nodeList.pop();

		curId = curNode.second;
		if (Visited[curId]) {
			continue;
		}
		Visited[curId] = true;

		size = GraphInfo[curId].size();
		for (int i = 0; i < size; ++i) {
			nextId = GraphInfo[curId][i].first;
			DistanceInfo[nextId] = min(DistanceInfo[nextId], curNode.first + GraphInfo[curId][i].second);
			nodeList.push({ DistanceInfo[nextId],nextId });
		}
	}
}

int main() {
	int u, k, v, c;

	cin >> N;
	GraphInfo.resize(N);
	for (int i = 0; i < N; ++i) {
		cin >> u >> k;
		for (int j = 0; j < k; ++j) {
			cin >> v >> c;
			GraphInfo[u].push_back({ v,c });
		}
	}
	solve(0);

	for (int i = 0; i < N; ++i) {
		cout << i << " " << DistanceInfo[i] << endl;
	}

	return 0;
}