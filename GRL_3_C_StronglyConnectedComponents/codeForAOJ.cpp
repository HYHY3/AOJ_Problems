#include <bits/stdc++.h>

using namespace std;

const int MaxVertexCount = 10000;

int V, E, Q, SCCID;
vector<vector<int> > GraphInfo, RGraphInfo;
bool Visited[MaxVertexCount];
stack<int> NodeList;
int SCCInfo[MaxVertexCount];

void Init() {

    fill(SCCInfo, SCCInfo + MaxVertexCount, -1);
    SCCID = 1;
}

void dfsSearch(int curId) {
    int size, nextId;

    Visited[curId] = true;

    size = GraphInfo[curId].size();
    for (int i = 0; i < size; ++i) {
        nextId = GraphInfo[curId][i];
        if (Visited[nextId]) {
            continue;
        }
        dfsSearch(nextId);
    }
    NodeList.push(curId);
}

void dfsRSearch(int curId) {
    int size, nextId;

    Visited[curId] = true;
    SCCInfo[curId] = SCCID;

    size = RGraphInfo[curId].size();
    for (int i = 0; i < size; ++i) {
        nextId = RGraphInfo[curId][i];
        if (Visited[nextId]) {
            continue;
        }
        dfsRSearch(nextId);
    }
}

void solve() {
    int curId;

    memset(Visited, false, sizeof(Visited));
    for (int i = 0; i < V; ++i) {
        if (Visited[i]) {
            continue;
        }
        dfsSearch(i);
    }

    memset(Visited, false, sizeof(Visited));
    while (!NodeList.empty()) {
        curId = NodeList.top();
        NodeList.pop();
        
        if (Visited[curId]) {
            continue;
        }
        dfsRSearch(curId);
        ++SCCID;
    }
    
}

int main() {
    int s, t, u, v;

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> V >> E;
    GraphInfo.resize(V);
    RGraphInfo.resize(V);
    for (int i = 0; i < E; ++i) {
        cin >> s >> t;
        GraphInfo[s].push_back(t);
        RGraphInfo[t].push_back(s);
    }
    Init();
    solve();
    cin >> Q;
    for (int i = 0; i < Q; ++i) {
        cin >> u >> v;
        //cout << "u=" << u << ", SCC=" << SCCInfo[u] << endl;
        //cout << "v=" << v << ", SCC=" << SCCInfo[v] << endl;
        cout << (SCCInfo[u] == SCCInfo[v] ? "1" : "0") << endl;
    }

    return 0;
}