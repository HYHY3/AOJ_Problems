#include <bits/stdc++.h>
using namespace std;

const int MaxDataSize = 100000;

int N, Q, EndPos;
vector<int> TreeInfo[MaxDataSize];
int Distance[4 * MaxDataSize];
int LeftInfo[MaxDataSize], RightInfo[MaxDataSize];
int ParentInfo[MaxDataSize];

void Init() {

    memset(TreeInfo, 0, sizeof(TreeInfo));
    memset(Distance, 0, sizeof(Distance));
    memset(LeftInfo, 0, sizeof(LeftInfo));
    memset(RightInfo, 0, sizeof(RightInfo));
    memset(ParentInfo, 0, sizeof(ParentInfo));

    EndPos = 1;
    while (EndPos < N) {
        EndPos *= 2;
    }
}

void createSegmentTreeByDFS(const int curNode, int &time) {
    int size;

    LeftInfo[curNode] = time++;
    size = TreeInfo[curNode].size();
    for (int i = 0; i < size; ++i) {
        ParentInfo[TreeInfo[curNode][i]] = curNode;
        createSegmentTreeByDFS(TreeInfo[curNode][i], time);
    }
    RightInfo[curNode] = time;
}

void update(int root, int left, int right, int s, int e, int w) {

    if (e <= left || s >= right) {
        return;
    }

    if (s <= left && right <= e) {
        Distance[root] += w;
        return;
    }

    int mid = (left + right) / 2;
    update(2 * root + 1, left, mid, s, e, w);
    update(2 * root + 2, mid, right, s, e, w);
}

int getSum(int k) {
    int sum;

    k += EndPos - 1;
    sum = Distance[k];
    while (k > 0) {
        k = (k - 1) / 2;
        sum += Distance[k];
    }

    return sum;
}

int main() {
    int k, c, cmd, v, w;

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
        }
    }
    k = 0;
    createSegmentTreeByDFS(0, k);
    cin >> Q;
    for (int i = 0; i < Q; ++i) {
        cin >> cmd;
        if (cmd == 0) {
            cin >> v >> w;
            // the range of update is from node v to its parent only. → GRL_5_D is Accepted
            update(0, 0, EndPos, LeftInfo[v], RightInfo[v], w);

            // the range of update is from node v to root. → GRL_5_E is Time Limit Exceeded
            /*while (v != 0) {
                update(0, 0, EndPos, LeftInfo[v], RightInfo[v], w);
                v = ParentInfo[v];
            }*/
        }
        else if (cmd == 1) {
            cin >> v;
            cout << getSum(LeftInfo[v]) << endl;
        }
    }

    return 0;
}