#include <bits/stdc++.h>

using namespace std;

const string QueryTypes[] = { "Change","Add" };
//DSL_2_D: 0,0
//DSL_2_E: 1,1
const unsigned int QueryTypeIndex = 1;
const unsigned int DataIndexStartedFrom = 1;

string RangeQueryType = QueryTypes[QueryTypeIndex];

const unsigned int MaxDataSize = 100000;

int N, Q, EndPos;
long long TreeInfo[4 * MaxDataSize];
long long LazyInfo[4 * MaxDataSize];
vector<long long> DataInfo;

void update(int root, int left, int right, int s, int t, long long x) {

    if (t <= left || s >= right) {
        return;
    }

    if (s <= left && right <= t) {
        if (RangeQueryType == QueryTypes[0]) {         // changing type
            TreeInfo[root] = x;
        }
        else if (RangeQueryType == QueryTypes[1]) {    // adding type
            LazyInfo[root] += x;
        }
        return;
    }

    int mid = (left + right) / 2;
    update(2 * root + 1, left, mid, s, t, x);
    update(2 * root + 2, mid, right, s, t, x);

    if (RangeQueryType == QueryTypes[1]) {    // adding type
        TreeInfo[root] = max(TreeInfo[2 * root + 1] + LazyInfo[2 * root + 1], TreeInfo[2 * root + 2] + LazyInfo[2 * root + 2]);
    }    
}

long long getValueByChange(int k) {

    k += EndPos - 1;

    long long curIndex = TreeInfo[k];
    while (k > 0) {
        k = (k - 1) / 2;
        curIndex = max(curIndex, TreeInfo[k]);
    }
    return curIndex;
}

long long getValueByAdd(int root, int left, int right, int s, int t) {

    if (t <= left || s >= right) {
        return 0;
    }

    if (s <= left && right <= t) {
        return TreeInfo[root] + LazyInfo[root];
    }

    int mid = (left + right) / 2;
    long long leftVal = getValueByAdd(2 * root + 1, left, mid, s, t);
    long long rightVal = getValueByAdd(2 * root + 2, mid, right, s, t);

    return max(leftVal, rightVal) + LazyInfo[root];
}

int main() {
    int cmd, s, t, index;
    long long x;

    fill(TreeInfo, TreeInfo + 4 + MaxDataSize, 0);
    fill(LazyInfo, LazyInfo + 4 + MaxDataSize, 0);
    if (RangeQueryType == QueryTypes[0]) {      // changing type
        DataInfo.push_back(INT_MAX);
        index = 1;
    }
    cin >> N >> Q;
    EndPos = 1;
    while (EndPos < N) {
        EndPos *= 2;
    }
    for (int i = 0; i < Q; ++i) {
        cin >> cmd;
        if (cmd == 0) {
            cin >> s >> t >> x;
            if (DataIndexStartedFrom == 1) {    // make data format looks like a0,a1,a2,...,an-1.
                --s;
                --t;
            }
            if (RangeQueryType == QueryTypes[0]) {         // changing type
                DataInfo.push_back(x);
                update(0, 0, EndPos, s, t + 1, index++);
            }
            else if (RangeQueryType == QueryTypes[1]) {    // adding type
                update(0, 0, EndPos, s, t + 1, x);
            }
        }
        else if (cmd == 1) {
            cin >> s;
            if (DataIndexStartedFrom == 1) {    // make data format looks like a0,a1,a2,...,an-1.
                --s;
            }
            if (RangeQueryType == QueryTypes[0]) {         // changing type
                cout << DataInfo[getValueByChange(s)] << endl;
            }
            else if (RangeQueryType == QueryTypes[1]) {    // adding type
                cout << getValueByAdd(0, 0, EndPos, s, s + 1) << endl;
            }            
        }
    }

    return 0;
}