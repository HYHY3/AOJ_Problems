#include <bits/stdc++.h>

using namespace std;

const unsigned int MaxDataSize = 100000;

unsigned int Cnt, Q;
unsigned int TreeInfo[4 * MaxDataSize];

unsigned int getSum(unsigned int root, unsigned int left, unsigned int right, unsigned int qStart, unsigned int qEnd) {
    unsigned int mid, leftSum, rightSum;

    if (qEnd <= left || right <= qStart) {
        return 0;
    }

    if (qStart <= left && right <= qEnd) {
        return TreeInfo[root];
    }

    mid = (left + right) / 2;
    leftSum = getSum(2 * root + 1, left, mid, qStart, qEnd);
    rightSum = getSum(2 * root + 2, mid, right, qStart, qEnd);

    return leftSum + rightSum;
}

void modify(unsigned int index, unsigned int value) {

     index += Cnt - 1;
    TreeInfo[index] += value;

    while (index > 0) {
        index = (index - 1) / 2;
        TreeInfo[index] = TreeInfo[2 * index + 1] + TreeInfo[2 * index + 2];
    }
}

int main() {
    unsigned int n, cmd, x, y;

    cin >> n >> Q;
    Cnt = 1;
    while (Cnt < n) {
        Cnt *= 2;
    }
    fill(TreeInfo, TreeInfo + 2 * Cnt - 1, 0);
    for (unsigned int i = 0; i < Q; ++i) {
        cin >> cmd >> x >> y;
        if (cmd == 0) {
            modify(x - 1, y);
        }
        else if (cmd == 1) {
            cout << getSum(0, 0, Cnt, x - 1, y) << endl;
        }
    }

    return 0;
}