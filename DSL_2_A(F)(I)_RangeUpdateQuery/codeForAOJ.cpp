#include <bits/stdc++.h>

using namespace std;

const string RangeTypes[] = { "Point", "Segment" };
const string QueryTypes[] = { "CalculateSum","FindMin" };

//DSL_2_A: 0,1,0
//DSL_2_F: 1,1,0
//DSL_2_I: 1,0,0
const unsigned int RangeTypeIndex = 1;
const unsigned int QueryTypeIndex = 0;
const unsigned int DataIndexStartedFrom = 0;

string RangeType = RangeTypes[RangeTypeIndex];
string RangeQueryType = QueryTypes[QueryTypeIndex];

const unsigned int MaxDataSize = 100000;

struct Node {
    long long lazy;
    long long sum, minValue;
};

int N, Q, EndPos;
Node TreeInfo[4 * MaxDataSize];

void pushUp(int root) {

    if (RangeQueryType == QueryTypes[0]) {         // get Sum
        TreeInfo[root].sum = TreeInfo[2 * root + 1].sum + TreeInfo[2 * root + 2].sum;
    }
    else if (RangeQueryType == QueryTypes[1]) {    // get Min
        TreeInfo[root].minValue = min(TreeInfo[2 * root + 1].minValue, TreeInfo[2 * root + 2].minValue);
    }
}

void pushDown(int root, int left, int right, int mid) {
    long long diff;

    diff = TreeInfo[root].lazy;
    if (diff == INT_MAX) {
        return;
    }

    TreeInfo[2 * root + 1].lazy = diff;
    TreeInfo[2 * root + 2].lazy = diff;
    if (RangeQueryType == QueryTypes[0]) {                // get Sum
        TreeInfo[2 * root + 1].sum = diff*(mid - left);
        TreeInfo[2 * root + 2].sum = diff*(right - mid);
    }
    else if (RangeQueryType == QueryTypes[1]) {           // get Min
        TreeInfo[2 * root + 1].minValue = diff;
        TreeInfo[2 * root + 2].minValue = diff;
    }
    TreeInfo[root].lazy = INT_MAX;
}

void update(int root, int left, int right, int s, int t, long long diff) {

    if (t <= left || s >= right) {
        return;
    }

    if (s <= left && right <= t) {
        TreeInfo[root].lazy = diff;
        if (RangeQueryType == QueryTypes[0]) {           // get Sum
            TreeInfo[root].sum = diff*(right - left);
        }
        else if (RangeQueryType == QueryTypes[1]) {      // get Min
            TreeInfo[root].minValue = diff;
        }
        return;
    }

    int mid = (left + right) / 2;
    pushDown(root, left, right, mid);
    update(2 * root + 1, left, mid, s, t, diff);
    update(2 * root + 2, mid, right, s, t, diff);

    pushUp(root);
}

long long getSum(int root, int left, int right, int s, int t) {

    if (t <= left || s >= right) {
        return 0;
    }

    if (s <= left && right <= t) {
        return TreeInfo[root].sum;
    }

    int mid = (left + right) / 2;
    pushDown(root, left, right, mid);
    long long sumL = getSum(2 * root + 1, left, mid, s, t);
    long long sumR = getSum(2 * root + 2, mid, right, s, t);

    return sumL + sumR;
}

long long getMinValue(int root, int left, int right, int s, int t) {

    if (t <= left || s >= right) {
        return INT_MAX;
    }

    if (s <= left && right <= t) {
        return TreeInfo[root].minValue;
    }

    int mid = (left + right) / 2;
    pushDown(root, left, right, mid);
    long long leftVal = getMinValue(2 * root + 1, left, mid, s, t);
    long long rightVal = getMinValue(2 * root + 2, mid, right, s, t);

    return min(leftVal, rightVal);
}

int main() {
    int cmd, s, t;
    int x;

    for (int i = 0; i < MaxDataSize * 4; ++i) {
        TreeInfo[i].lazy = INT_MAX;
        TreeInfo[i].sum = 0;
        TreeInfo[i].minValue = INT_MAX;
    }
    cin >> N >> Q;
    EndPos = 1;
    while (EndPos < N) {
        EndPos *= 2;
    }
    for (int i = 0; i < Q; ++i) {
        cin >> cmd >> s >> t;
        if (DataIndexStartedFrom == 1) {             // make data format looks like a0,a1,a2,...,an-1.
            --s;
            --t;
        }
        if (cmd == 0) {
            if (RangeType == RangeTypes[0]) {        // change A[s] to t.
                if (DataIndexStartedFrom == 1) {
                    ++t;
                }
                update(0, 0, EndPos, s, s + 1, t);
            }
            else if (RangeType == RangeTypes[1]) {   // change A[s]...A[t] to x.
                cin >> x;
                update(0, 0, EndPos, s, t + 1, x);
            }
        }
        else if (cmd == 1) {
            if (RangeQueryType == QueryTypes[0]) {                  // get Sum
                cout << getSum(0, 0, EndPos, s, t + 1) << endl;
            }
            else if (RangeQueryType == QueryTypes[1]) {             // get Min
                cout << getMinValue(0, 0, EndPos, s, t + 1) << endl;
            }
        }
    }

    return 0;
}