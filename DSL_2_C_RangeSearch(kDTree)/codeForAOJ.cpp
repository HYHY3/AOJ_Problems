#include <bits/stdc++.h>

using namespace std;

class Point {
public:
    int x, y;
    int id;

    Point() {
        ;
    }

    Point(int x, int y, int id) {
        this->x = x;
        this->y = y;
        this->id = id;
    }
};

class Node {
public:

    Point point;
    Node *left;
    Node *right;

    Node(Node *left, Node *right, Point p) {
        this->left = left;
        this->right = right;
        this->point = p;
    }
};

int N, Q;
vector<Point> PointInfo;
vector<int> Result;

bool compByX(const Point &p1, const Point &p2) {
    return p1.x < p2.x;
}

bool compByY(const Point &p1, const Point &p2) {
    return p1.y < p2.y;
}

Node *buildkDTree(int l, int r, int depth) {
    if (l >= r) {
        return NULL;
    }

    if (depth % 2 == 1) {    // sort by x axis, when current level is odd number.
        sort(PointInfo.begin() + l, PointInfo.begin() + r, compByX);
    }
    else {    // sort by y axis, when current level is even number.
        sort(PointInfo.begin() + l, PointInfo.begin() + r, compByY);
    }

    int mid = (l + r) / 2;
    Node *pLeft = buildkDTree(l, mid, depth + 1);
    Node *pRight = buildkDTree(mid + 1, r, depth + 1);
    Node *pRoot = new Node(pLeft, pRight, PointInfo[mid]);

    return pRoot;
    //return new Node(buildkDTree(l, mid, depth + 1), buildkDTree(mid + 1, r, depth + 1), PointInfo[mid]);
}

void findRange(Node *pNode, const int &sx, const int &tx, const int &sy, const int &ty, int depth) {
    if (pNode == NULL) {
        return;
    }

    Point &p = pNode->point;
    if (sx <= p.x && p.x <= tx && sy <= p.y && p.y <= ty) {
        Result.push_back(p.id);
    }

    if (depth % 2 == 1) {    // search by x axis, when current level is odd number.
        if (sx <= p.x) {
            findRange(pNode->left, sx, tx, sy, ty, depth + 1);
        }
        if (p.x <= tx) {
            findRange(pNode->right, sx, tx, sy, ty, depth + 1);
        }
    }
    else {     // search by y axis, when current level is even number.
        if (sy <= p.y) {
            findRange(pNode->left, sx, tx, sy, ty, depth + 1);
        }
        if (p.y <= ty) {
            findRange(pNode->right, sx, tx, sy, ty, depth + 1);
        }
    }
}

int main() {
    int x, y, sx, tx, sy, ty, size;
    Node *pRoot = NULL;

    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> x >> y;
        PointInfo.push_back(Point(x, y, i));
    }
    pRoot = buildkDTree(0, N, 0);
    cin >> Q;
    for (int i = 0; i < Q; ++i) {
        cin >> sx >> tx >> sy >> ty;
        Result.clear();
        findRange(pRoot, sx, tx, sy, ty, 0);
        sort(Result.begin(), Result.end());   // output by less point id.
        size = Result.size();
        for (int i = 0; i < size; ++i) {
#if true
            cout << Result[i] << "\n";
#else
            cout << Result[i] << endl;    // Time Limited.
#endif
        }
        cout << endl;
    }

    return 0;
}