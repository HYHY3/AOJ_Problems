#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

const ll INF = 1e10;

class Edge {
public:
    int s, t, d;

    Edge(int s, int t, int d) {
        this->s = s;
        this->t = t;
        this->d = d;
    }
};

int V, E;
vector<Edge> GraphInfo;
ll Distance[1000];

void solve(int startId) {

    fill(Distance, Distance + 1000, INF);

    Distance[startId] = 0;
    for (int k = 1; k < V; ++k) {
        for (int i = 0; i < E; ++i) {
            if (Distance[GraphInfo[i].s] == INF) {
                continue;
            }
            Distance[GraphInfo[i].t] = min(Distance[GraphInfo[i].t], Distance[GraphInfo[i].s] + GraphInfo[i].d);
        }
    }

    for (int i = 0; i < E; ++i) {
        if (Distance[GraphInfo[i].s] == INF) {
            continue;
        }
        if (Distance[GraphInfo[i].t] > Distance[GraphInfo[i].s] + GraphInfo[i].d) {
            cout << "NEGATIVE CYCLE" << endl;
            return;
        }
    }

    for (int i = 0; i < V; ++i) {
        if (Distance[i] == INF) {
            cout << "INF" << endl;
        }
        else {
            cout << Distance[i] << endl;
        }
    }
}

int main() {
    int s, t, d, r;

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    GraphInfo.clear();
    cin >> V >> E >> r;
    for (int i = 0; i < E; ++i) {
        cin >> s >> t >> d;
        GraphInfo.push_back(Edge(s, t, d));
    }
    solve(r);

    return 0;
}