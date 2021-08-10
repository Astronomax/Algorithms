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

const int MAXM = 6e5 + 100, INF = 4e5;
int lazyadd[4 * MAXM], t[4 * MAXM], lazyeq[4 * MAXM];

void push(int k, int l, int r) {
	t[k] = min(t[k], lazyeq[k]) + lazyadd[k];

	if (l < r) {
		lazyeq[k * 2] = min(lazyeq[k * 2], lazyeq[k] - lazyadd[k * 2]);
		lazyeq[k * 2 + 1] = min(lazyeq[k * 2 + 1], lazyeq[k] - lazyadd[k * 2 + 1]);
		lazyadd[k * 2] += lazyadd[k];
		lazyadd[k * 2 + 1] += lazyadd[k];
	}
	lazyeq[k] = INF;
	lazyadd[k] = 0;
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
		lazyadd[k] += x;
		push(k, l, r);
		return;
	}
	int mid = (l + r) / 2;
	add(k * 2, l, mid, lq, rq, x);
	add(k * 2 + 1, mid + 1, r, lq, rq, x);
	update(k, l, r);
}

void equate_min(int k, int l, int r, int lq, int rq, int x) {
	push(k, l, r);
	if (rq < l) return;
	if (r < lq) return;
	if (lq <= l && r <= rq) {
	    lazyeq[k] = min(lazyeq[k], x - lazyadd[k]);
		push(k, l, r);
		return;
	}
	int mid = (l + r) / 2;
	equate_min(k * 2, l, mid, lq, rq, x);
	equate_min(k * 2 + 1, mid + 1, r, lq, rq, x);
	update(k, l, r);
}

int min(int k, int l, int r, int lq, int rq) {
	push(k, l, r);
	if (rq < l) return INF;
	if (r < lq) return INF;
	if (lq <= l && r <= rq)
		return t[k];
	int mid = (l + r) / 2;
	return min(min(k * 2, l, mid, lq, rq), min(k * 2 + 1, mid + 1, r, lq, rq));
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	fill(&t[0], &t[0] + 4 * MAXM, 0);
	fill(&lazyeq[0], &lazyeq[0] + 4 * MAXM, INF);

	return 0;
}
