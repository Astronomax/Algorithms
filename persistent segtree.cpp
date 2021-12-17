#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#include <unordered_map>
#include <random>
#include <chrono>
using namespace std;

#define X real()
#define Y imag()
#define endl '\n'
#define all(X) (X).begin(), (X).end()
#define rall(X) (X).rbegin(), (X).rend()
mt19937_64 rnd(chrono::system_clock::now().time_since_epoch().count());
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int lcm(int a, int b) { return a * b / gcd(a, b); }

struct node {
	node *l, *r;
	int sum = 0, lazy = 0;

	node(int lb, int rb) {
		if (lb + 1 < rb) {
			int mid = (lb + rb) / 2;
			l = new node(lb, mid);
			r = new node(mid, rb);
		}
	}

	void push(int lb, int rb) {
		sum += lazy * (rb - lb);
		if (lb + 1 < rb) {
			l->lazy += lazy;
			r->lazy += lazy;
		}
		lazy = 0;
	}

	void update(int lb, int rb) {
		if (lb + 1 < rb)
			sum = l->sum + r->sum;
	}

	node *add(int lb, int rb, int lq, int rq, int x) {
		push(lb, rb);
		if (lq >= rb || lb >= rq)
			return this;
		node *v = new node(*this);
		if (lq <= lb && rb <= rq) {
			v->lazy += x;
			v->push(lb, rb);
		}
		else {
			int mid = (lb + rb) / 2;
			v->l = v->l->add(lb, mid, lq, rq, x);
			v->r = v->r->add(mid, rb, lq, rq, x);
			v->update(lb, rb);
		}
		return v;
	}
};

int get_kth(int lb, int rb, node* l, node* r, int k) {
	int mid = (lb + rb) / 2;
	l->push(lb, rb); r->push(lb, rb);
	if (lb + 1 == rb)
		return lb;
	else if (r->l->sum - l->l->sum >= k)
		return get_kth(lb, mid, l->l, r->l, k);
	else return get_kth(mid, rb, l->r, r->r, k - (r->l->sum - l->l->sum));
}

const int mod = 1e9, MAXN = 450100;
node *pf[MAXN];
int a[MAXN], coords[MAXN];

signed main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	int n, l, m;
	cin >> n >> a[0] >> l >> m;
	for (int i = 1; i < n; i++)
		a[i] = ((long long)a[i - 1] * l + m) % mod;
	memcpy(coords, a, sizeof(int) * n);
	sort(coords, coords + n);

	for (int i = 0; i < n; i++)
		a[i] = lower_bound(coords, coords + n, a[i]) - coords;

	pf[0] = new node(0, n);
	for (int i = 0; i < n; i++)
		pf[i + 1] = pf[i]->add(0, n, a[i], a[i] + 1, 1);

	long long ans = 0;
	int b; cin >> b;
	for (int i = 0; i < b; i++) {
		int g, x, lx, mx, y, ly, my, k, lk, mk;
		cin >> g >> x >> lx >> mx >> y >> ly >> my >> k >> lk >> mk;
		int lq = min(x, y) - 1, rq = max(x, y) - 1;

		for (int j = 0; j < g; j++) {
			ans += coords[get_kth(0, n, pf[lq], pf[rq + 1], k)];
			x = ((long long)lq * lx + mx) % n;
			y = ((long long)rq * ly + my) % n;
			lq = min(x, y); rq = max(x, y);
			k = ((long long)(k - 1) * lk + mk) % (rq - lq + 1) + 1;
		}
	}
	cout << ans;
	return 0;
}
