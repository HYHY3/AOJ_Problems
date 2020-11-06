#include <bits/stdc++.h>

using namespace std;

const int MaxVertexCount = 10000;

int V;
vector<vector<pair<int, int> > > GraphInfo;
bool Visited[MaxVertexCount];
int Distance[MaxVertexCount];
int HeightOfTree[MaxVertexCount];

void searchByBFS(int curId) {
    int size, nextId;
    pair<int, int> nodeInfo;
    priority_queue<pair<int, int> > nodeList;

    memset(Visited, false, sizeof(Visited));
    fill(Distance, Distance + MaxVertexCount, 0);

    Distance[curId] = 0;
    nodeList.push({ 0,curId });
    while (!nodeList.empty()) {
        nodeInfo = nodeList.top();
        nodeList.pop();

        curId = nodeInfo.second;
        if (Visited[curId]) {
            continue;
        }
        Visited[curId] = true;

        size = GraphInfo[curId].size();
        for (int i = 0; i < size; ++i) {
            nextId = GraphInfo[curId][i].first;
            if (Visited[nextId]) {
                continue;
            }
            Distance[nextId] = max(Distance[nextId], Distance[curId] + GraphInfo[curId][i].second);
            nodeList.push({ Distance[nextId] ,nextId });
        }
    }
}

void solve() {
    int startId, endId;

    fill(HeightOfTree, HeightOfTree + MaxVertexCount, 0);

    searchByBFS(0);
    startId = max_element(Distance, Distance + MaxVertexCount) - Distance;
    //cout << "No.1=" << startId << endl;

    searchByBFS(startId);
    endId = max_element(Distance, Distance + MaxVertexCount) - Distance;
    //cout << "No.2=" << endId << endl;
    for (int i = 0; i < V; ++i) {
        HeightOfTree[i] = max(HeightOfTree[i], Distance[i]);
    }

    searchByBFS(endId);
    for (int i = 0; i < V; ++i) {
        HeightOfTree[i] = max(HeightOfTree[i], Distance[i]);
    }

    for (int i = 0; i < V; ++i) {
        cout << HeightOfTree[i] << endl;
    }
}

int main() {
    int s, t, w;

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> V;
    GraphInfo.resize(V);
    for (int i = 1; i < V; ++i) {
        cin >> s >> t >> w;
        GraphInfo[s].push_back({ t,w });
        GraphInfo[t].push_back({ s,w });
    }
    solve();

    return 0;
}