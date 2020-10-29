#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int V;
int GraphInfo[100][100];
bool Visited[100];
int Distance[100];

void solve(int startId) {
    int curId, minDist, ans;

    memset(Visited, false, sizeof(Visited));
    fill(Distance, Distance + 100, INF);

    for (int i = 0; i < V; ++i) {
        Distance[i] = GraphInfo[startId][i];
    }

    Visited[startId] = true;
    ans = 0;
    for (int k = 1; k < V; ++k) {
        minDist = INF;
        for (int i = 0; i < V; ++i) {
            if (Visited[i]) {
                continue;
            }
            if (Distance[i] < minDist) {
                minDist = Distance[i];
                curId = i;
            }
        }

        Visited[curId] = true;
        ans += minDist;

        for (int i = 0; i < V; ++i) {
            if (Visited[i]) {
                continue;
            }
            Distance[i] = min(Distance[i], GraphInfo[curId][i]);
        }
    }

    cout << ans << endl;
}

int main() {
    int num;

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> V;
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            cin >> num;
            if (num == -1) {
                num = INF;
            }
            GraphInfo[i][j] = num;
        }
    }
    solve(0);

    return 0;
}