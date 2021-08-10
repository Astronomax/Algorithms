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
	MAX
};

class op {
public:
	op_type t;
	int x;
};

const int MAXM = 6e5 + 100, INF = 4e5;
int t[4 * MAXM];
op lazy[4 * MAXM][3];
int size_[4 * MAXM];

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

	for (int i = 0; i < size_[k]; i++) {
		if (lazy[k][i].t == op_type::EQ)
			t[k] = lazy[k][i].x;
		else if (lazy[k][i].t == op_type::MIN)
			t[k] = min(t[k], lazy[k][i].x);
		else if (lazy[k][i].t == op_type::MAX)
			t[k] = max(t[k], lazy[k][i].x);
	}

	if (l < r) {
		for (int i = 0; i < size_[k]; i++) {
			propagation(lazy[k][i], 2 * k);
			propagation(lazy[k][i], 2 * k + 1);
		}
	}
	size_[k] = 0;
}

void update(int k, int l, int r) {
	if (l < r)
		t[k] = max(t[2 * k], t[2 * k + 1]);
}

void apply(int k, int l, int r, int lq, int rq, op x) {
	push(k, l, r);
	if (rq < l) return;
	if (r < lq) return;
	if (lq <= l && r <= rq) {
		propagation(x, k);
		push(k, l, r);
		return;
	}
	int mid = (l + r) / 2;
	apply(k * 2, l, mid, lq, rq, x);
	apply(k * 2 + 1, mid + 1, r, lq, rq, x);
	update(k, l, r);
}

int max(int k, int l, int r, int lq, int rq) {
	push(k, l, r);
	if (rq < l) return -INF;
	if (r < lq) return -INF;
	if (lq <= l && r <= rq)
		return t[k];
	int mid = (l + r) / 2;
	return max(max(k * 2, l, mid, lq, rq), max(k * 2 + 1, mid + 1, r, lq, rq));
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	apply(1, 0, 100, 0, 100, { op_type::MAX, 10 });
	cout << max(1, 0, 100, 5, 5);
	return 0;
}
