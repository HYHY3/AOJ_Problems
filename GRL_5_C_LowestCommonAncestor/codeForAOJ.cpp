#include <bits/stdc++.h>
using namespace std;

const int MaxDataSize = 100000;

int N, Q;
vector<int> TreeInfo[MaxDataSize];
vector<pair<int,int> > QueryInfo[MaxDataSize];
bool Visited[MaxDataSize];
int Parent[MaxDataSize];
int Answer[MaxDataSize];

void Init() {

    memset(Visited, false, sizeof(Visited));
    for (int i = 0; i < N; ++i) {
        Parent[i] = i;
    }
    fill(Answer, Answer + MaxDataSize, -1);
}

int findParent(int node) {
    if (node == Parent[node]) {
        return node;
    }
    return Parent[node] = findParent(Parent[node]);
}

void solveByTarjan(int curNode) {
    int size, nextNode;

    Visited[curNode] = true;
    size = TreeInfo[curNode].size();
    for (int i = 0; i < size; ++i) {
        nextNode = TreeInfo[curNode][i];
        if (Visited[nextNode]) {
            continue;
        }
        solveByTarjan(nextNode);
        //Parent[nextNode] = findParent(curNode);
        Parent[nextNode] = curNode;
    }

    size = QueryInfo[curNode].size();
    for (int i = 0; i < size; ++i) {
        nextNode = QueryInfo[curNode][i].first;
        if (Visited[nextNode]) {
            Answer[QueryInfo[curNode][i].second] = findParent(nextNode);
        }        
    }
}

int main() {
    int k, c, cmd, u, v, w;

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    Init();
    for (int i = 0; i < N; i++) {
        cin >> k;
        for (int j = 0; j < k; ++j) {
            cin >> c;
            TreeInfo[i].push_back(c);
            TreeInfo[c].push_back(i);
        }
    }
    cin >> Q;
    for (int id = 0; id < Q; id++) {
        cin >> cmd;
        if (cmd == 0) {
            cin >> v >> w;

        }
        else if (cmd == 1) {
            cin >> u;
        }
        QueryInfo[u].push_back({ v, id });
        QueryInfo[v].push_back({ u, id });
    }
    solveByTarjan(0);
    for (int i = 0; i < Q; i++) {
        cout << Answer[i] << endl;
    }

    return 0;
}