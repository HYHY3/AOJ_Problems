#include <bits/stdc++.h>

using namespace std;

const int MaxDataSize = 100000;

int Cnt, Q;
int TreeInfo[4 * MaxDataSize];

int getAnswer(int root, int left, int right, int qStart, int qEnd) {
    int mid, leftMin, rightMin;

    if (qEnd <= left || right <= qStart) {
        return INT_MAX;
    }

    if (qStart <= left && right <= qEnd) {
        return TreeInfo[root];
    }

    mid = (left + right) / 2;
    leftMin = getAnswer(2 * root + 1, left, mid, qStart, qEnd);
    rightMin = getAnswer(2 * root + 2, mid, right, qStart, qEnd);

    return min(leftMin, rightMin);
}

void modify(int index, int value) {

    index += Cnt - 1;
    TreeInfo[index] = value;

    while (index > 0) {
        index = (index - 1) / 2;
        TreeInfo[index] = min(TreeInfo[2 * index + 1], TreeInfo[2 * index + 2]);
    }
}

int main() {
    int n, cmd, x, y;

    cin >> n >> Q;
    Cnt = 1;
    while (Cnt < n) {
        Cnt *= 2;
    }
    fill(TreeInfo, TreeInfo + 2 * Cnt - 1, INT_MAX);
    for (int i = 0; i < Q; ++i) {
        cin >> cmd >> x >> y;
        if (cmd == 0) {
            modify(x, y);
        }
        else if (cmd == 1) {
            cout << getAnswer(0, 0, Cnt, x, y + 1) << endl;
        }
    }

    return 0;
}