#include <bits/stdc++.h>

using namespace std;

int main() {
    unsigned int n, k, b, limit;
    bitset<32> bsNum, bsTarget;

    cin >> n >> k;
    for (unsigned int i = 0; i < k; ++i) {
        cin >> b;
        bsTarget.set(b, 1);
    }

    limit = 1 << n;
    for (unsigned int num = 0; num < limit; ++num) {
        bsNum &= 0;
        bsNum |= num;
        if ((bsNum | bsTarget) != bsTarget) {
            continue;
        }
        cout << num << ":";
        for (unsigned int pos = 0; pos < n; ++pos) {
            if (!bsNum.test(pos)) {
                continue;
            }
            cout << " " << pos;
        }
        cout << endl;
    }

    return 0;
}