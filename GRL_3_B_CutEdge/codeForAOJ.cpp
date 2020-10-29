#include <bits/stdc++.h>

using namespace std;

int V, E;
vector<vector<int> > GraphInfo;
bool Visited[100000];
int Parent[100000], Depth[100000], Low[100000];
set<pair<int, int> > CutVertex;

void solve(int curId, int depth) {
    int size, nextId;

    Visited[curId] = true;
    Depth[curId] = Low[curId] = depth;

    size = GraphInfo[curId].size();
    for (int i = 0; i < size; ++i) {
        nextId = GraphInfo[curId][i];

        if (!Visited[nextId]) {
            Parent[nextId] = curId;
            solve(nextId, depth + 1);
            Low[curId] = min(Low[curId], Low[nextId]);
            if (Low[nextId] > Depth[curId]) {
                if (curId < nextId) {
                    CutVertex.insert({ curId, nextId });
                }
                else {
                    CutVertex.insert({ nextId, curId });
                }
            }
        }
        else if (Parent[curId] != nextId) {
            Low[curId] = min(Low[curId], Depth[nextId]);
        }
    }
}

void Init() {

    memset(Visited, false, sizeof(Visited));
    fill(Parent, Parent + 100000, 0);
    fill(Depth, Depth + 100000, 0);
    fill(Low, Low + 100000, 0);
    CutVertex.clear();
}

int main() {
    int s, t;

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> V >> E;
    GraphInfo.resize(V);
    for (int i = 0; i < E; ++i) {
        cin >> s >> t;
        GraphInfo[s].push_back(t);
        GraphInfo[t].push_back(s);
    }
    Init();
    Parent[0] = V;
    solve(0, 0);
    for (set<pair<int, int> >::iterator it = CutVertex.begin(); it != CutVertex.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }

    return 0;
}