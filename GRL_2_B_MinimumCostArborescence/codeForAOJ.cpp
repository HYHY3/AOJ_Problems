#include <bits/stdc++.h>
using namespace std;

const int MaxDataSize = 1000;
const int INF = 1e8;

class EdgeInfo {
public:
    int s, t, w;

    EdgeInfo() {
        this->s = 0;
        this->t = 0;
        this->w = INF;
    }

    EdgeInfo(int s, int t, int w) {
        this->s = s;
        this->t = t;
        this->w = w;
    }
};

int V, E;
EdgeInfo GraphInfo[MaxDataSize];
int InDegree[MaxDataSize];
int Previous[MaxDataSize];
int Visited[MaxDataSize], IdInfo[MaxDataSize];


bool solve(int root) {
    int ans, s, t, w, cycleCnt;

    ans = 0;
    while (true) {
        fill(InDegree, InDegree + MaxDataSize, INF);
        fill(Previous, Previous + MaxDataSize, root);

        // for each vertex, find the minimum indegree. 
        for (int i = 0; i < E; ++i) {
            s = GraphInfo[i].s;
            t = GraphInfo[i].t;
            w = GraphInfo[i].w;
            if (s != t && w < InDegree[t]) {   // except self cycle.
                InDegree[t] = w;
                Previous[t] = s;
            }
        }

        // // judge the graph whether it has unreachable vertex except root.
        // ※because this problem presented "G has arborescence(s) with the root r", this part can be commented out.
        /*for (int i = 0; i < V; ++i) {
            if (i == root) {
                continue;
            }
            if (InDegree[i] == INF) {    // if the graph has an unreachable vertex, it has no MST.
                return false;
            }
        }*/

        // judge the graph whether it has cycle.
        fill(Visited, Visited + MaxDataSize, -1);
        fill(IdInfo, IdInfo + MaxDataSize, -1);
        cycleCnt = 0;
        InDegree[root] = 0;
        for (int i = 0; i < V; ++i) {
            ans += InDegree[i];
            s = i;
            // if the vertex which is not root can not return back to the root. the graph has cycle.
            while (s != root && Visited[s] != i && IdInfo[s] == -1) {
                Visited[s] = i;
                s = Previous[s];    // return to the previous vertex.
            }
            // if current vertex is root or vertex set new Id, the starting vertex is not in cycle.
            if (s == root || IdInfo[s] != -1) {
                continue;
            }
            // for each vertex in cycle, set new Id to them.
            for (t = Previous[s]; t != s; t = Previous[t]) {
                IdInfo[t] = cycleCnt;
            }
            IdInfo[s] = cycleCnt++;
        }
        // if the graph has not any cycle, print the answer of MST.
        if (cycleCnt == 0) {
            break;
        }

        // for the rest vertices, set new Id to them.
        for (int i = 0; i < V; ++i) {
            if (IdInfo[i] == -1) {
                IdInfo[i] = cycleCnt++;
            }
        }

        // reset the edges information of the graph.
        for (int i = 0; i < E; ++i) {
            s = GraphInfo[i].s;
            t = GraphInfo[i].t;
            // for each edge, id of endpoints may have been changed.
            GraphInfo[i].s = IdInfo[s];
            GraphInfo[i].t = IdInfo[t];

            // if the endpoints of edge are different, reset the weight of the edge.
            // ※one is in cycle, however another is not.
            if (IdInfo[s] != IdInfo[t]) {
                GraphInfo[i].w -= InDegree[t];
            }
        }

        // reset the number of vertices and Id of root.
        V = cycleCnt;
        root = IdInfo[root];
    }

    cout << ans << endl;
    return true;
}

int main() {
    int r, s, t, w;

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> V >> E >> r;
    for (int i = 0; i < E; i++) {
        cin >> s >> t >> w;
        GraphInfo[i] = EdgeInfo(s, t, w);
    }
    solve(r);

    return 0;
}