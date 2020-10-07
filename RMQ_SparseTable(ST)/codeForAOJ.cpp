#include <bits/stdc++.h>

using namespace std;

vector<int> DataInfo;
//the number of data <= 100000 and the number of query <= 100000(log2(100000) < 20)
unsigned int minData[100000][20];
unsigned int maxData[100000][20]; 

void update(int len) {
    int limit;

    for (int i = 0; i < len; ++i) {
        minData[i][0] = DataInfo[i];
    	maxData[i][0] = DataInfo[i];
    }

    limit = log(len) / log(2);
    for (int j = 1; j <= limit; ++j) {
        for (int i = 0; i + (1 << j) - 1 < len; ++i) {
            minData[i][j] = min(minData[i][j - 1], minData[i + (1 << (j - 1))][j - 1]);
        	maxData[i][j] = max(maxData[i][j - 1], maxData[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int main() {
    int n, q, cmd, x, y, k;

    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        DataInfo.push_back(INT_MAX);
    }
    update(n);
    for (int i = 0; i < q; ++i) {
        cin >> cmd >> x >> y;
        if (cmd == 0) {
            DataInfo[x] = y;
            update(n);
        }
        else if (cmd == 1) {
            k = log(y - x + 1) / log(2);
            cout << min(minData[x][k], minData[y - (1 << k) + 1][k]) << endl;
        	cout << max(maxData[x][k], maxData[y - (1 << k) + 1][k]) << endl;
        }
    }

    return 0;
}