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

const int MAXM = 3e5 + 100;
int sumt[4 * MAXM], maxt[4 * MAXM], smaxt[4 * MAXM], cntmaxt[4 * MAXM];
int lazy[4 * MAXM];

void push(int k, int l, int r) {
	int d = maxt[k] - lazy[k];
	if (d > 0) {
		sumt[k] -= d * cntmaxt[k];
		maxt[k] -= d;
	}

	if (l < r) {
		lazy[k * 2] = min(lazy[k * 2], lazy[k]);
		lazy[k * 2 + 1] = min(lazy[k * 2 + 1], lazy[k]);
	}
	lazy[k] = LLONG_MAX;
}

void update(int k, int l, int r) {
	if (l < r) {
		sumt[k] = sumt[k * 2] + sumt[k * 2 + 1];
		set<int> order;
		order.insert(smaxt[2 * k]);
		order.insert(maxt[2 * k]);
		order.insert(smaxt[2 * k + 1]);
		order.insert(maxt[2 * k + 1]);
		
		auto it = order.rbegin();
		maxt[k] = *(it++);
		smaxt[k] = *it;

		int a = k * 2, b = k * 2 + 1;
		if (maxt[a] < maxt[b]) swap(a, b);
		cntmaxt[k] = cntmaxt[a];
		if (maxt[a] == maxt[b])
			cntmaxt[k] += cntmaxt[b];
	}
}

void min_eq(int k, int l, int r, int lq, int rq, int x) {
	push(k, l, r);
	if (rq < l || r < lq || maxt[k] <= x) return;
	if (lq <= l && r <= rq && smaxt[k] < x && x < maxt[k]) {
		lazy[k] = min(lazy[k], x);
		push(k, l, r);
		return;
	}
	int mid = (l + r) / 2;
	min_eq(k * 2, l, mid, lq, rq, x);
	min_eq(k * 2 + 1, mid + 1, r, lq, rq, x);
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

void build(int k, int l, int r, vector<int> &a) {
	if (l == r) {
		sumt[k] = a[l];
		smaxt[k] = LLONG_MIN;
		maxt[k] = a[l];
		cntmaxt[k] = 1;
		return;
	}
	int mid = (l + r) / 2;
	build(k * 2, l, mid, a);
	build(k * 2 + 1, mid + 1, r, a);
	update(k, l, r);
}

int max(int k, int l, int r, int lq, int rq) {
	push(k, l, r);
	if (rq < l) return LLONG_MIN;
	if (r < lq) return LLONG_MIN;
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
	fill(&lazy[0], &lazy[0] + 4 * MAXM, LLONG_MAX);

	int n; cin >> n;
	vector<int> a(n);
	for (auto &i : a)
		cin >> i;
	build(1, 0, n - 1, a);
	
	int m; cin >> m;
	for (int i = 0; i < m; i++) {
		int t; cin >> t;
		if (t == 1) {
			int l, r, x; cin >> l >> r >> x;
			l--; r--;
			min_eq(1, 0, n - 1, l, r, x);
		}
		else {
			int l, r; cin >> l >> r;
			l--; r--;
			cout << sum(1, 0, n - 1, l, r) << endl;
		}
	}
	return 0;
}
