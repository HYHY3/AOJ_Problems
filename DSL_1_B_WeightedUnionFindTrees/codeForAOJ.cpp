#include <bits/stdc++.h>

using namespace std;

vector<int> Parent, Weight;

int findRoot(int num) {
    int curParent;

    if (Parent[num] == num) {
        return num;
    }
    curParent = findRoot(Parent[num]);
    Weight[num] += Weight[Parent[num]];
    return Parent[num] = curParent;
}

void unite(int x, int y, int z) {
    int rootX, rootY;

    rootX = findRoot(x);
    rootY = findRoot(y);
    if (rootX == rootY) {
        return;
    }
    Parent[rootX] = rootY;
    Weight[rootX] = Weight[y] + z - Weight[x];
}

int main() {
    int n, q, cmd, x, y, z;

    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        Parent.push_back(i);
        Weight.push_back(0);
    }
    for (int i = 0; i < q; ++i) {
        cin >> cmd >> x >> y;
        if (cmd == 0) {
            cin >> z;
            unite(x, y, z);
        }
        else if (cmd == 1) {
            cout << (findRoot(x) == findRoot(y) ? to_string(Weight[x] - Weight[y]) : "?") << endl;
        }
    }

    return 0;
}