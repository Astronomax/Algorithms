#define _CRT_SECURE_NO_WARNINGS
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

template<typename T>
struct decart {
	struct node {
		T key;
		int y, s;
		node *l, *r;
		node(T _key) {
			key = _key;
			y = rnd();
			l = nullptr, r = nullptr;
			s = 1;
		}
	};

	node *root = nullptr;

	int get_size(node *v) {
		return ((v == nullptr) ? 0 : v->s);
	}

	void update(node *v) {
		if (v == nullptr)
			return;
		v->s = get_size(v->l) + get_size(v->r) + 1;
	}

	node *merge(node *a, node *b) {
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

	pair<node *, node *> split(node *v, T key) {
		if (v == nullptr)
			return{ nullptr, nullptr };
		if (v->key > key) {
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

	int lower_count(node *v, T key) {
		if (v == nullptr)
			return 0;

		int res = 0;
		if (v->key >= key) {
			res += get_size(v->r) + 1;
			res += lower_count(v->l, key);
		}
		else
			res += lower_count(v->r, key);
		return res;
	}

	int upper_count(node *v, T key) {
		if (v == nullptr)
			return 0;

		int res = 0;
		if (v->key > key) {
			res += get_size(v->r) + 1;
			res += upper_count(v->l, key);
		}
		else
			res += upper_count(v->r, key);
		return res;
	}

	void insert(T key) {
		node *add = new node(key);
		auto res = split(root, key);
		root = merge(merge(res.first, add), res.second);
	}
};

template<typename T>
struct fenv {
	vector<T> t;
	int n;
	fenv(int _n, T default_value) {
		n = _n;
		t.assign(n + 1, default_value);
	}

	void add(int k, const function<void(T*)> func) {
		k++;
		while (k <= n) {
			func(&t[k]);
			k += k & -k;
		}
	}

	void ans(int k, const function<void(T*)> func) {
		k++;
		while (k >= 1) {
			func(&t[k]);
			k -= k & -k;
		}
	}
};

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	int n; cin >> n;
	fenv<decart<int>> d(n, decart<int>());
	for (int i = 0; i < n; i++) {
		int a, b; cin >> a >> b; a--;
		int ans = 0;
		d.ans(a, [&ans, b](decart<int> *v) {
			ans += v->upper_count(v->root, b);
		});
		d.add(a, [b](decart<int> *v) {
			v->insert(b);
		});
		cout << ans << " ";
	}
	return 0;
}
