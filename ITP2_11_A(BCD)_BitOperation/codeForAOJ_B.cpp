#include <bits/stdc++.h>

using namespace std;

int main() {
    unsigned int n, k, b, limit;
    bitset<32> bsNum;
    vector<int> posInfo;
    bool flag;

    posInfo.clear();
    cin >> n >> k;
    for (unsigned int i = 0; i < k; ++i) {
        cin >> b;
        posInfo.push_back(b);
    }

    limit = 1 << n;
    for (unsigned int num = 0; num < limit; ++num) {
        bsNum &= 0;
        bsNum |= num;
        flag = true;
        for (unsigned int pos = 0; pos < k; ++pos) {
            if (!bsNum.test(posInfo[pos])) {
                flag = false;
                break;
            }
        }
        if (!flag) {
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