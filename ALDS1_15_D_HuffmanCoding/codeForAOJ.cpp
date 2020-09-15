#include <bits/stdc++.h>

using namespace std;

string Target;
int CountOfChar[26];

int solve() {
	int a, b, ans;
	priority_queue<int> nodelist;

	for (int i = 0; i < 26; ++i) {
		if (CountOfChar[i] == 0) {
			continue;
		}
		nodelist.push(CountOfChar[i]);
	}

	if (nodelist.size() == 1) {
		return -1 * nodelist.top();
	}

	ans = 0;
	while (nodelist.size() > 1) {
		a = nodelist.top();
		nodelist.pop();
		b = nodelist.top();
		nodelist.pop();

		ans += a + b;
		nodelist.push(a + b);
	}
	return -ans;
}

int main() {
	int len;

	memset(CountOfChar, 0, sizeof(CountOfChar));
	cin >> Target;

	len = Target.size();
	for (int i = 0; i < len; ++i) {
		--CountOfChar[Target[i] - 'a'];
	}
	cout << solve() << endl;

	return 0;
}