#include <bits/stdc++.h>

using namespace std;

vector<int>NextInfo;

void getNext(const string &p) {
	int len, i, j;

	len = p.size();
	NextInfo.resize(len + 1);
	fill(NextInfo.begin(), NextInfo.end(), 0);
	NextInfo[0] = -1;

	i = 0;
	j = -1;
	while (i < len) {
		if (j == -1 || p[i] == p[j]) {
			++i;
			++j;
			NextInfo[i] = j;
			if (p[i] == p[NextInfo[i]]) {
				NextInfo[i] = NextInfo[NextInfo[i]];
			}
		}
		else {
			j = NextInfo[j];
		}
	}
}

void solve(const string &t, const string &p) {
	int len1, len2, i, j;

	len1 = t.size();
	len2 = p.size();

	i = 0;
	j = 0;
	while (i < len1) {
		if (j == -1 || t[i] == p[j]) {
			++i;
			++j;
			if (j == len2) {
				cout << i - j << endl;
				//j = 0;
				j = NextInfo[j];
			}
			continue;
		}
		j = NextInfo[j];
	}
}

int main() {
	string t, p;

	cin >> t >> p;
	getNext(p);
	solve(t, p);

	return 0;
}