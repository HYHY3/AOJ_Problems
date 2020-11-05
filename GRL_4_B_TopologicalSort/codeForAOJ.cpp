#include <bits/stdc++.h>

using namespace std;

const int MaxVertexCount = 10000;

int V, E;
vector<vector<int> > GraphInfo;
int Indegree[MaxVertexCount];

void solve() {
    int curId, size, nextId;
    queue<int> nodeList;

    for (int i = 0; i < V; ++i) {
        if (Indegree[i] == 0) {
            nodeList.push(i);
        }
    }

    while (!nodeList.empty()) {
        curId = nodeList.front();
        nodeList.pop();
        cout << curId << endl;

        size = GraphInfo[curId].size();
        for (int i = 0; i < size; ++i) {
            nextId = GraphInfo[curId][i];
            --Indegree[nextId];
            if (Indegree[nextId] == 0) {
                nodeList.push(nextId);
            }
        }
    }
}

int main() {
    int s, t;

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    fill(Indegree, Indegree + MaxVertexCount, 0);
    cin >> V >> E;
    GraphInfo.resize(V);
    for (int i = 0; i < E; ++i) {
        cin >> s >> t;
        GraphInfo[s].push_back(t);
        ++Indegree[t];
    }
    solve();

    return 0;
}