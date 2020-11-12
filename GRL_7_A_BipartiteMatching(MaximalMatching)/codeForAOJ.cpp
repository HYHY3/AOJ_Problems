#include <bits/stdc++.h>
using namespace std;

const int MaxDataSize = 100;

int X, Y, E;
bool GraphInfo[MaxDataSize][MaxDataSize];
int MatchInfo[MaxDataSize];
bool Visited[MaxDataSize];

bool findMatch(const int x) {

    for (int y = 0; y < Y; ++y) {
        if (Visited[y] || !GraphInfo[x][y]) {
            continue;
        }
        Visited[y] = true;

        if (MatchInfo[y] == -1 || findMatch(MatchInfo[y])) {
            MatchInfo[y] = x;
            return true;
        }
    }

    return false;
}

void solve() {
    int cnt;

    fill(MatchInfo, MatchInfo + MaxDataSize, -1);

    cnt = 0;
    for (int x = 0; x < X; ++x) {
        memset(Visited, false, sizeof(Visited));
        if (findMatch(x)) {
            ++cnt;
        }
    }

    cout << cnt << endl;
}

int main() {
    int u, v;

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    memset(GraphInfo, false, sizeof(GraphInfo));
    cin >> X >> Y >> E;
    for (int i = 0; i < E; i++) {
        cin >> u >> v;
        GraphInfo[u][v] = true;
    }
    solve();

    return 0;
}