#include <bits/stdc++.h>

using namespace std;

const int INF = 100000000;

class Edge {
public:
	int u, v, w;

	Edge(int u, int v, int w) {
		this->u = u;
		this->v = v;
		this->w = (w == -1 ? INF : w);
	}
};

int N;
int Relations[100];
int Ranking[100];
vector<Edge> GraphInfo;

int findRoot(int num) {
	int ans;

	if (Relations[num] == num) {
		return num;
	}
	ans = findRoot(Relations[num]);
	Relations[num] = ans;
	return ans;
}

bool cmp(const Edge &e1, const Edge &e2) {
	return e1.w < e2.w;
}

void solve() {
	int cnt, ans, size, rootU, rootV;

	sort(GraphInfo.begin(), GraphInfo.end(), cmp);

	ans = 0;
	cnt = 0;
	size = GraphInfo.size();
	for (int i = 0; i < size; ++i) {
		rootU = findRoot(GraphInfo[i].u);
		rootV = findRoot(GraphInfo[i].v);
		if (rootU == rootV) {
			continue;
		}

		if (Ranking[rootU] > Ranking[rootV]) {
			Relations[rootV] = rootU;
		}
		else {
			Relations[rootU] = rootV;
			if (Ranking[rootU] == Ranking[rootV]) {
				++Ranking[rootU];
			}
		}
		ans += GraphInfo[i].w;
		++cnt;
		if (cnt == N - 1) {
			break;
		}
	}

	cout << ans << endl;
}

int main() {
	int w;

	for (int i = 0; i < 100; ++i) {
		Relations[i] = i;
		Ranking[i] = 1;
	}
	cin >> N;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> w;
			if (j > i) {
				GraphInfo.push_back(Edge(i, j, w));
			}
		}
	}
	solve();

	return 0;
}