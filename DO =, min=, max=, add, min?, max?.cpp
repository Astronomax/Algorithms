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
//#define int long long
#define all(X) (X).begin(), (X).end()
#define rall(X) (X).rbegin(), (X).rend()
mt19937_64 rnd(chrono::system_clock::now().time_since_epoch().count());
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int lcm(int a, int b) { return a * b / gcd(a, b); }

enum class op_type {
	EQ,
	MIN,
	MAX,
	ADD
};

class op {
public:
	op_type t;
	int x;
};

const int MAXM = 6e5 + 100, INF = 4e5;
int mint[4 * MAXM], maxt[4 * MAXM], size_[4 * MAXM], lazyadd[4 * MAXM];
op lazy[4 * MAXM][3];

void add_op(op x, int k) {
	lazy[k][size_[k]] = x;
	++size_[k];
}

void propagation(op i, int to) {
	if (size_[to] == 0)
		add_op(i, to);
	else {
		if (i.t == op_type::EQ) {
			size_[to] = 0;
			add_op(i, to);
		}
		else if (i.t == op_type::MIN) {
			if (lazy[to][size_[to] - 1].t == op_type::EQ)
				add_op(i, to);
			else if (lazy[to][size_[to] - 1].t == op_type::MIN)
				lazy[to][size_[to] - 1].x = min(lazy[to][size_[to] - 1].x, i.x);
			else if (lazy[to][size_[to] - 1].t == op_type::MAX) {
				if (lazy[to][size_[to] - 1].x <= i.x) {
					if (size_[to] == 1)
						add_op(i, to);
					else if (lazy[to][size_[to] - 2].t == op_type::MIN)
						lazy[to][size_[to] - 2].x = min(lazy[to][size_[to] - 2].x, i.x);
					else if (lazy[to][size_[to] - 2].t == op_type::EQ)
						add_op(i, to);
				}
				else {
					size_[to] = 0;
					add_op({ op_type::EQ, i.x }, to);
				}
			}
		}
		else if (i.t == op_type::MAX) {
			if (lazy[to][size_[to] - 1].t == op_type::EQ)
				add_op(i, to);
			else if (lazy[to][size_[to] - 1].t == op_type::MAX)
				lazy[to][size_[to] - 1].x = max(lazy[to][size_[to] - 1].x, i.x);
			else if (lazy[to][size_[to] - 1].t == op_type::MIN) {
				if (lazy[to][size_[to] - 1].x >= i.x) {
					if (size_[to] == 1)
						add_op(i, to);
					else if (lazy[to][size_[to] - 2].t == op_type::MAX)
						lazy[to][size_[to] - 2].x = max(lazy[to][size_[to] - 2].x, i.x);
					else if (lazy[to][size_[to] - 2].t == op_type::EQ)
						add_op(i, to);
				}
				else {
					size_[to] = 0;
					add_op({ op_type::EQ, i.x }, to);
				}
			}
		}
	}
}

void push(int k, int l, int r) {
	assert(size_[k] <= 3);
	mint[k] += lazyadd[k]; //чекать переполнение
	maxt[k] += lazyadd[k]; //чекать переполнение

	for (int i = 0; i < size_[k]; i++) {
		if (lazy[k][i].t == op_type::EQ)
			maxt[k] = lazy[k][i].x + lazyadd[k];
		else if (lazy[k][i].t == op_type::MIN)
			maxt[k] = min(maxt[k], lazy[k][i].x + lazyadd[k]);
		else if (lazy[k][i].t == op_type::MAX)
			maxt[k] = max(maxt[k], lazy[k][i].x + lazyadd[k]);

		if (lazy[k][i].t == op_type::EQ)
			mint[k] = lazy[k][i].x + lazyadd[k];
		else if (lazy[k][i].t == op_type::MIN)
			mint[k] = min(mint[k], lazy[k][i].x + lazyadd[k]);
		else if (lazy[k][i].t == op_type::MAX)
			mint[k] = max(mint[k], lazy[k][i].x + lazyadd[k]);
	}

	if (l < r) {
		for (int i = 0; i < size_[k]; i++) {
			auto p1 = lazy[k][i];
			p1.x -= lazyadd[k * 2];
			propagation(p1, 2 * k);

			auto p2 = lazy[k][i];
			p2.x -= lazyadd[k * 2 + 1];
			propagation(p2, 2 * k + 1);
		}
		lazyadd[k * 2] += lazyadd[k]; //чекать переполнение
		lazyadd[k * 2 + 1] += lazyadd[k]; //чекать переполнение
	}
	lazyadd[k] = 0;
	size_[k] = 0;
}

void update(int k, int l, int r) {
	if (l < r) {
		mint[k] = min(mint[2 * k], mint[2 * k + 1]);
		maxt[k] = max(maxt[2 * k], maxt[2 * k + 1]);
	}
}

void apply(int k, int l, int r, int lq, int rq, op x) {
	push(k, l, r);
	if (rq < l) return;
	if (r < lq) return;
	if (lq <= l && r <= rq) {
		if (x.t == op_type::ADD)
			lazyadd[k] += x.x; //чекать переполнение
		else
			propagation(x, k);
		push(k, l, r);
		return;
	}
	int mid = (l + r) / 2;
	apply(k * 2, l, mid, lq, rq, x);
	apply(k * 2 + 1, mid + 1, r, lq, rq, x);
	update(k, l, r);
}

int min(int k, int l, int r, int lq, int rq) {
	push(k, l, r);
	if (rq < l) return INF;
	if (r < lq) return INF;
	if (lq <= l && r <= rq)
		return mint[k];
	int mid = (l + r) / 2;
	return min(min(k * 2, l, mid, lq, rq), min(k * 2 + 1, mid + 1, r, lq, rq));
}

int max(int k, int l, int r, int lq, int rq) {
	push(k, l, r);
	if (rq < l) return -INF;
	if (r < lq) return -INF;
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

	return 0;
}
