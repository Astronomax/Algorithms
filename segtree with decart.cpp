#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("profile-values,profile-reorder-functions,tracer")
#pragma GCC optimize("branch-target-load-optimize")

#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <string>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <iterator>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <complex>
#include <chrono>
#include <random>

//#pragma comment(linker, "/STACK:16777216")

using namespace std;

typedef long double C;
typedef complex<C> P;

#define X real()
#define Y imag()
#define Size(X) (int)X.size()
#define ui unsigned int
#define mp make_pair
#define timer fghge
#define y1 yjyjyju
#define all(X) (X).begin(), (X).end()
#define endl '\n'
mt19937_64 rnd(std::chrono::system_clock::now().time_since_epoch().count());

struct decart {
	struct tree {
		int x, y, s;
		tree *l, *r;
		tree(int key) {
			x = key; y = rnd();
			l = nullptr, r = nullptr;
			s = 1;
		}
	};

	tree *root = nullptr;

	int get_size(tree *v) {
		return ((v == nullptr) ? 0 : v->s);
	}

	inline void update(tree *v) {
		if (v == nullptr)
			return;
		v->s = get_size(v->l) + get_size(v->r) + 1;
	}

	tree *merge(tree *a, tree *b) {
		if (a == 0 || b == 0)
			return ((a == 0) ? b : a);

		if (a->y > b->y) {
			a->r = merge(a->r, b);
			update(a);
			return a;
		}
		else {
			b->l = merge(a, b->l);
			update(b);
			return b;
		}
	}

	pair<tree *, tree *> split(tree *v, int key) {
		if (v == nullptr)
			return{ nullptr, nullptr };
		if (v->x > key) {
			auto res = split(v->l, key);
			v->l = res.second;
			update(v);
			return{ res.first, v };
		}
		else {
			auto res = split(v->r, key);
			v->r = res.first;
			update(v);
			return{ v, res.second };
		}
	}

	int ans(tree *v, int x) {
		if (v == nullptr)
			return 0;
		if (v->x > x)
			return ans(v->l, x) + get_size(v->r) + 1;
		else return ans(v->r, x);
	}

	tree* insert(tree* v, tree* x) {
		if (v == nullptr)
			return x;

		if (v->y < x->y) {
			auto res = split(v, x->x);
			x->l = res.first;
			x->r = res.second;
			update(x);
			return x;
		}
		else {
			if (v->x < x->x)
				v->r = insert(v->r, x);
			else v->l = insert(v->l, x);
			++v->s;
			return v;
		}
	}
};

struct node {
	int lb, rb;
	node *l, *r;
	decart *order;

	node(int lq, int rq) {
		lb = lq; rb = rq;
		order = new decart();

		if (lb + 1 < rb) {
			int t = (lb + rb) / 2;
			l = new node(lb, t);
			r = new node(t, rb);
		}
	}

	void add(int t, int x) {
		if (t < lb || t >= rb)
			return;
		order->root = order->insert(order->root, new decart::tree(x));
		if (lb + 1 < rb) {
			l->add(t, x);
			r->add(t, x);
		}
	}

	int ans(int lq, int rq, int x) {
		if (lq >= rb || rq < lb)
			return 0;
		if (lq <= lb && rb - 1 <= rq)
			return order->ans(order->root, x);
		else return l->ans(lq, rq, x) + r->ans(lq, rq, x);
	}
};

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	int n; cin >> n;
	node *d = new node(0, n);
	for (int i = 0; i < n; i++) {
		int a, b; cin >> a >> b; a--;
		cout << d->ans(0, a, b) << " ";
		d->add(a, b);
	}
	//cout << endl << (double)clock() / CLOCKS_PER_SEC;
	return 0;
}
