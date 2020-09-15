#include <bits/stdc++.h>

using namespace std;

class Point {
public:
	double x, y;
};

void kochCurve(int n, Point p1, Point p2) {
	Point s, t, u;

	if (n == 0) {
		return;
	}
	
	s.x = (p2.x + 2 * p1.x) / 3.0;
	s.y = (p2.y + 2 * p1.y) / 3.0;
	t.x = (p1.x + 2 * p2.x) / 3.0;
	t.y = (p1.y + 2 * p2.y) / 3.0;

	u.x = (t.x - s.x)*0.5 - (t.y - s.y)*sqrt(3)*0.5 + s.x;
	u.y = (t.x - s.x)*sqrt(3)*0.5 + (t.y - s.y)*0.5 + s.y;

	kochCurve(n - 1, p1, s);
	cout << fixed << setprecision(6) << s.x << " " << s.y << endl;

	kochCurve(n - 1, s, u);
	cout << fixed << setprecision(6) << u.x << " " << u.y << endl;

	kochCurve(n - 1, u, t);
	cout << fixed << setprecision(6) << t.x << " " << t.y << endl;

	kochCurve(n - 1, t, p2);
}

int main() {
	int n;
	Point p1, p2;

	p1.x = 0;
	p1.y = 0;
	p2.x = 100;
	p2.y = 0;

	cin >> n;
	cout << fixed << setprecision(6) << p1.x << " " << p1.y << endl;
	kochCurve(n, p1, p2);
	cout << fixed << setprecision(6) << p2.x << " " << p2.y << endl;

	return 0;
}