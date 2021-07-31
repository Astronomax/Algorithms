#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#include <random>
#include <chrono>
using namespace std;

typedef long double C;
typedef complex<C> P;
#define X real()
#define Y imag()
#define endl '\n'
#define int long long
#define all(X) (X).begin(), (X).end()
#define rall(X) (X).rbegin(), (X).rend()
mt19937_64 rnd(chrono::system_clock::now().time_since_epoch().count());
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int lcm(int a, int b) { return a * b / gcd(a, b); }

const int MAXM = 1e6 + 100;
int t[4 * MAXM], lazy[4 * MAXM];

void push(int k, int l, int r) {
	t[k] += lazy[k];
	if (l < r) {
		lazy[k * 2] += lazy[k];
		lazy[k * 2 + 1] += lazy[k];
	}
	lazy[k] = 0;
}

void update(int k, int l, int r) {
	if (l < r)
		t[k] = min(t[2 * k], t[2 * k + 1]);
}

void add(int k, int l, int r, int lq, int rq, int x) {
	push(k, l, r);
	if (rq < l) return;
	if (r < lq) return;
	if (lq <= l && r <= rq) {
		lazy[k] += x;
		push(k, l, r);
		return;
	}
	int mid = (l + r) / 2;
	add(k * 2, l, mid, lq, rq, x);
	add(k * 2 + 1, mid + 1, r, lq, rq, x);
	update(k, l, r);
}

int min(int k, int l, int r, int lq, int rq) {
	push(k, l, r);
	if (rq < l) return LLONG_MAX;
	if (r < lq) return LLONG_MAX;
	if (lq <= l && r <= rq)
		return t[k];
	int mid = (l + r) / 2;
	return min(min(k * 2, l, mid, lq, rq), min(k * 2 + 1, mid + 1, r, lq, rq));
}

struct interval {
	int l, r, w;
};

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	int n, m; cin >> n >> m;
	vector<interval> order(n);
	for (auto &i : order)
		cin >> i.l >> i.r >> i.w;
	for (auto &i : order) {
		/*i.l--;*/ i.r--;
	}
	sort(all(order), [](interval a, interval b) {return a.w < b.w; });

	int ans = LLONG_MAX, j = 0;

	for (int i = 0; i < n; i++) {
		while (j < n && min(1, 0, m - 1, 1, m - 1) == 0) {
			add(1, 0, m - 1, order[j].l, order[j].r, 1);
			j++;
		}
		if (min(1, 0, m - 1, 1, m - 1) > 0)
			ans = min(ans, order[j - 1].w - order[i].w);
		add(1, 0, m - 1, order[i].l, order[i].r, -1);
	}
	cout << ans;
	return 0;
}
