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

const int MAXM = 1e5 + 100;
int sumt[4 * MAXM], mint[4 * MAXM], maxt[4 * MAXM];
int lazy[4 * MAXM];

void push(int k, int l, int r) {
	sumt[k] -= lazy[k] * (r - l + 1);
	maxt[k] -= lazy[k];
	mint[k] -= lazy[k];

	if (l < r) {
		lazy[k * 2] += lazy[k];
		lazy[k * 2 + 1] += lazy[k];
	}
	lazy[k] = 0;
}

void update(int k, int l, int r) {
	if (l < r) {
		sumt[k] = sumt[k * 2] + sumt[k * 2 + 1];
		mint[k] = min(mint[2 * k], mint[2 * k + 1]);
		maxt[k] = max(maxt[2 * k], maxt[2 * k + 1]);
	}
}

void mod(int k, int l, int r, int lq, int rq, int m) {
	push(k, l, r);
	if (rq < l || r < lq || maxt[k] < m) return;
	if (lq <= l && r <= rq && mint[k] / m == maxt[k] / m) {
		int d = mint[k] - mint[k] % m;
		lazy[k] += d;
		push(k, l, r);
		return;
	}
	int mid = (l + r) / 2;
	mod(k * 2, l, mid, lq, rq, m);
	mod(k * 2 + 1, mid + 1, r, lq, rq, m);
	update(k, l, r);
}

void eq(int k, int l, int r, int x, int y) {
	push(k, l, r);
	if (x < l || r < x) 
		return;
	if (l == r) {
		sumt[k] = y;
		mint[k] = y;
		maxt[k] = y;
		return;
	}
	int mid = (l + r) / 2;
	eq(k * 2, l, mid, x, y);
	eq(k * 2 + 1, mid + 1, r, x, y);
	update(k, l, r);
}

int sum(int k, int l, int r, int lq, int rq) {
	push(k, l, r);
	if (rq < l) return 0;
	if (r < lq) return 0;
	if (lq <= l && r <= rq)
		return sumt[k];
	int mid = (l + r) / 2;
	return sum(k * 2, l, mid, lq, rq) + sum(k * 2 + 1, mid + 1, r, lq, rq);
}

int min(int k, int l, int r, int lq, int rq) {
	push(k, l, r);
	if (rq < l) return LLONG_MAX;
	if (r < lq) return LLONG_MAX;
	if (lq <= l && r <= rq)
		return mint[k];
	int mid = (l + r) / 2;
	return min(min(k * 2, l, mid, lq, rq), min(k * 2 + 1, mid + 1, r, lq, rq));
}

int max(int k, int l, int r, int lq, int rq) {
	push(k, l, r);
	if (rq < l) return -LLONG_MAX;
	if (r < lq) return -LLONG_MAX;
	if (lq <= l && r <= rq)
		return maxt[k];
	int mid = (l + r) / 2;
	return max(max(k * 2, l, mid, lq, rq), max(k * 2 + 1, mid + 1, r, lq, rq));
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	int n, m; cin >> n >> m;
	vector<int> a(n);
	for (auto &i : a)
		cin >> i;
	for (int i = 0; i < n; i++) 
		eq(1, 0, n - 1, i, a[i]);
	
	for (int i = 0; i < m; i++) {
		int t; cin >> t;
		if (t == 1) {
			int l, r; cin >> l >> r;
			l--; r--;
			cout << sum(1, 0, n - 1, l, r) << endl;
		}
		else if (t == 2) {
			int l, r, m; cin >> l >> r >> m;
			l--; r--;
			mod(1, 0, n - 1, l, r, m);
		}
		else {
			int x, y; cin >> x >> y;
			x--;
			eq(1, 0, n - 1, x, y);
		}
	}
	return 0;
}
