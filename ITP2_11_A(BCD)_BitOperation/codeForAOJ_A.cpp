#include <bits/stdc++.h>

using namespace std;

int main() {
    unsigned int n, limit;
    bitset<32> bsNum;

    cin >> n;

    limit = 1 << n;
    for (unsigned int num = 0; num < limit; ++num) {
        bsNum &= 0;
        bsNum |= num;
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