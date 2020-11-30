#include <bits/stdc++.h>
using namespace std;

const double EXP = 1e-12;
const double INF = 1e12;
const int MaxDataSize = 100;

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

double LimitOfX[2], LimitOfY[2];
Point PointsInfo[MaxDataSize];


double getCrossProductOf2Vectors(const Point &pA, const Point &pB, const Point &pC, const Point &pD) {
    double x1, y1, x2, y2;

    x1 = pB.x - pA.x;
    y1 = pB.y - pA.y;
    x2 = pD.x - pC.x;
    y2 = pD.y - pC.y;

    return x1*y2 - x2*y1;
}

bool isOnSegment(const Point &target, const Point &start, const Point &end) {
    double crossProduct, xValue, yValue;

    crossProduct = getCrossProductOf2Vectors(target, start, target, end);
    if (fabs(crossProduct) > EXP) {
        // not on a line.
        return false;
    }

    // on a line.
    xValue = (target.x - start.x) * (target.x - end.x);
    yValue = (target.y - start.y) * (target.y - end.y);
    if (xValue <= 0 && yValue <= 0) {
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

int solve(const int &n, const Point &target) {
    int start, end, cnt;
    Point endPoint(LimitOfX[0] - 10, target.y);

    if (target.x < LimitOfX[0] || target.x > LimitOfX[1] ||
        target.y < LimitOfY[0] || target.y > LimitOfY[1]) {
        return 0;
    }

    cnt = 0;
    start = 0;
    end = 1;
    for (int i = 0; i < n; ++i) {
        if (isOnSegment(target, PointsInfo[start], PointsInfo[end])) {
            return 1;
        }

        if (PointsInfo[start].y == PointsInfo[end].y) {
            start = (start + 1) % n;
            end = (end + 1) % n;
            continue;
        }

        if (isOnSegment(PointsInfo[start], target, endPoint)) {
            if (PointsInfo[start].y > PointsInfo[end].y) {
                ++cnt;
            }
        }
        else if (isOnSegment(PointsInfo[end], target, endPoint)) {
            if (PointsInfo[end].y > PointsInfo[start].y) {
                ++cnt;
            }
        }
        else if (isIntersection(target, endPoint, PointsInfo[start], PointsInfo[end])) {
            ++cnt;
        }
        start = (start + 1) % n;
        end = (end + 1) % n;
    }

    if ((cnt&1) == 1) {
        return 2;
    }
    return 0;
}

int main() {
    int n, q;
    double x, y;
    Point target;

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    LimitOfX[0] = LimitOfY[0] = INF;  // min
    LimitOfX[1] = LimitOfY[1] = -INF; // max
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        LimitOfX[0] = min(LimitOfX[0], x);
        LimitOfX[1] = max(LimitOfX[1], x);
        LimitOfY[0] = min(LimitOfY[0], y);
        LimitOfY[1] = max(LimitOfY[1], y);
        PointsInfo[i] = Point(x, y);
    }
    cin >> q;
    for (int i = 0; i < q; ++i) {
        cin >> target.x >> target.y;
        cout << solve(n, target) << endl;
    }

    return 0;
}