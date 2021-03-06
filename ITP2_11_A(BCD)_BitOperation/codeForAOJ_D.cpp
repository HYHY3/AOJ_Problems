#include <bits/stdc++.h>

using namespace std;

int main() {
    unsigned int n, k, limit;
    bitset<32> bsNum;

    cin >> n >> k;

    limit = 1 << n;
    for (unsigned int num = 0; num < limit; ++num) {
        bsNum &= 0;
        bsNum |= num;
        if (bsNum.count() != k) {
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