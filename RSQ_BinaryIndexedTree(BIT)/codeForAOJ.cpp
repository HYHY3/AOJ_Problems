#include <bits/stdc++.h>

using namespace std;

const unsigned int MaxDataSize = 100000;

int N, Q;
unsigned int BITInfo[MaxDataSize + 1];

void add(int index, int value) {
    while (index <= N) {
        BITInfo[index] += value;
        index += index&(-index);
    }
}

unsigned int getSum(int index) {
    unsigned int sum;

    sum = 0;
    while (index > 0) {
        sum += BITInfo[index];
        index -= index&(-index);
    }
    return sum;
}

int main() {
    unsigned int cmd, x, y;

    fill(BITInfo, BITInfo + MaxDataSize + 1, 0);
    cin >> N >> Q;
    for (int i = 0; i < Q; ++i) {
        cin >> cmd >> x >> y;
        if (cmd == 0) {
            add(x, y);
        }
        else if (cmd == 1) {
            cout << getSum(y) - getSum(x - 1) << endl;
        }
    }

    return 0;
}