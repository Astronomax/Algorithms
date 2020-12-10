#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
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
 
using namespace std;
 
typedef double C;
typedef complex<C> P;
 
#define X real()
#define Y imag()
#define ui unsigned int
#define int long long
#define MP make_pair
#define timer fghge
#define y1 yjyjyju
#define all(X) (X).begin(), (X).end()
#define endl "\n"
 
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

