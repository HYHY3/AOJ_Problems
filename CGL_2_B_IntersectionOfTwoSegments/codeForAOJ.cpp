#include <bits/stdc++.h>
using namespace std;

const double EXP = 1e-12;

class Point {
public:
    double x, y;

    Point() {
        this->x = 0;
        this->y = 0;
    }

    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }
};


double getCrossProductOf2Vectors(const Point &pA, const Point &pB, const Point &pC, const Point &pD) {
    double x1, y1, x2, y2;

    x1 = pB.x - pA.x;
    y1 = pB.y - pA.y;
    x2 = pD.x - pC.x;
    y2 = pD.y - pC.y;

    return x1*y2 - x2*y1;
}

void sortPosition(Point &a, Point &b) {
    double tmp;

    if (a.x < b.x) {
        return;
    }
    else if (a.x == b.x) {
        if (a.y > b.y) {
            tmp = a.y;
            a.y = b.y;
            b.y = tmp;
        }
    }
    else if (a.x > b.x) {
        tmp = a.x;
        a.x = b.x;
        b.x = tmp;
        tmp = a.y;
        a.y = b.y;
        b.y = tmp;
    }
}

bool isOnALine(Point &p0, Point &p1, Point &p2, Point &p3) {
    double crossProduct;

    sortPosition(p0, p1);
    sortPosition(p2, p3);

    crossProduct = getCrossProductOf2Vectors(p1, p2, p1, p3);
    if (fabs(crossProduct) < EXP) {
        return true;
    }
    return false;
}

bool isIntersection(const Point &p0, const Point &p1, const Point &p2, const Point &p3) {
    double crossProduct1, crossProduct2;

    crossProduct1 = getCrossProductOf2Vectors(p0, p1, p0, p2);
    crossProduct2 = getCrossProductOf2Vectors(p0, p1, p0, p3);
    if (crossProduct1*crossProduct2 > 0) {
        return false;
    }

    crossProduct1 = getCrossProductOf2Vectors(p2, p3, p2, p0);
    crossProduct2 = getCrossProductOf2Vectors(p2, p3, p2, p1);
    if (crossProduct1*crossProduct2 > 0) {
        return false;
    }

    return true;
}

bool solve(Point &p0, Point &p1, Point &p2, Point &p3) {
    double crossProduct;

    crossProduct = getCrossProductOf2Vectors(p0, p1, p2, p3);
    if (fabs(crossProduct) < EXP) {
        if (!isOnALine(p0, p1, p2, p3)) {
            return false;
        }
        // on a line.
        if (p0.x == p1.x && p1.x == p2.x) {
            if ((p0.y <= p2.y && p1.y >= p2.y) || (p2.y <= p0.y && p3.y >= p0.y)) {
                return true;
            }
        }
        else if ((p0.x <= p2.x && p1.x >= p2.x) || (p2.x <= p0.x && p3.x >= p0.x)) {
            return true;
        }
        return false;
    }

    if (isIntersection(p0, p1, p2, p3)) {
        return true;
    }
    return false;
}

int main() {
    int q;
    Point p0, p1, p2, p3;

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> p0.x >> p0.y >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;
        cout << (solve(p0, p1, p2, p3) ? "1" : "0") << endl;
    }

    return 0;
}