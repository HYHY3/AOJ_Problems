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

double getDotProductOf2Vectors(const Point &pA, const Point &pB, const Point &pC, const Point &pD) {
    double x1, y1, x2, y2;

    x1 = pB.x - pA.x;
    y1 = pB.y - pA.y;
    x2 = pD.x - pC.x;
    y2 = pD.y - pC.y;

    return x1*x2 + y1*y2;
}

double getCrossProductOf2Vectors(const Point &pA, const Point &pB, const Point &pC, const Point &pD) {
    double x1, y1, x2, y2;

    x1 = pB.x - pA.x;
    y1 = pB.y - pA.y;
    x2 = pD.x - pC.x;
    y2 = pD.y - pC.y;

    return x1*y2 - x2*y1;
}

bool isOnALine(const  Point &p0, const Point &p1, const Point &p2, const Point &p3) {
    double crossProduct;

    crossProduct = getCrossProductOf2Vectors(p1, p2, p1, p3);
    if (fabs(crossProduct) < EXP) {  // crossProduct = 0?
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

double getDistanceOfPointToLine(const Point &pa, const Point &pb, const Point &pc) {
    double dotProduct, len;

    dotProduct = getDotProductOf2Vectors(pa, pb, pa, pc);
    if (dotProduct < 0) {
        return sqrt(pow(pc.y - pa.y, 2) + pow(pc.x - pa.x, 2));
    }

    dotProduct = getDotProductOf2Vectors(pb, pa, pb, pc);
    if (dotProduct < 0) {
        return sqrt(pow(pc.y - pb.y, 2) + pow(pc.x - pb.x, 2));
    }

    len = sqrt(pow(pa.y - pb.y, 2) + pow(pa.x - pb.x, 2));
    return fabs(getCrossProductOf2Vectors(pa, pb, pa, pc)) / len;
}

double solve(const Point &p0, const Point &p1, const Point &p2, const Point &p3) {
    double crossProduct, dist1, dist2;

    crossProduct = getCrossProductOf2Vectors(p0, p1, p2, p3);
    if (fabs(crossProduct) < EXP) {
        // s1 and s2 are parallel.
        if (isOnALine(p0, p1, p2, p3)) {
            // s1 and s2 are on a line.
            if (p0.x == p1.x && p1.x == p2.x) { // on a Y line.
                if ((p0.y <= p2.y && p1.y >= p2.y) || (p2.y <= p0.y && p3.y >= p0.y)) {
                    return 0;
                }
            }
            else if ((p0.x <= p2.x && p1.x >= p2.x) || (p2.x <= p0.x && p3.x >= p0.x)) { // not on a Y line.
                return 0;
            }
            dist1 = sqrt(pow(p2.y - p1.y, 2) + pow(p2.x - p1.x, 2));
            dist2 = sqrt(pow(p3.y - p0.y, 2) + pow(p3.x - p0.x, 2));
            return min(dist1, dist2);
        }
    }

    // not parallel.
    if (isIntersection(p0, p1, p2, p3)) {
        return 0;
    }

    // not parallel and not intersection.
    dist1 = getDistanceOfPointToLine(p0, p1, p2);
    dist1 = min(dist1, getDistanceOfPointToLine(p0, p1, p3));
    dist2 = getDistanceOfPointToLine(p2, p3, p0);
    dist2 = min(dist2, getDistanceOfPointToLine(p2, p3, p1));
    //cout << "dist1:" << dist1 << ", dist2:" << dist2 << endl;
    return min(dist1, dist2);
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
        sortPosition(p0, p1); // p0 <= p1
        sortPosition(p2, p3); // p2 <= p3
        cout << fixed << setprecision(10) << solve(p0, p1, p2, p3) << endl;
    }

    return 0;
}