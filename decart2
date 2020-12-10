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
//#define int long long
#define mp make_pair
#define timer fghge
#define y1 yjyjyju
#define all(X) (X).begin(), (X).end()
#define endl '\n'
mt19937_64 rnd(std::chrono::system_clock::now().time_since_epoch().count());

const int mod = 1e9;

template<typename T>
struct decart {
	struct node {
		T key;
		int y, s;
		node *l, *r, *pred;
		node(T _key) {
			key = _key;
			y = rnd();
			l = nullptr;
			r = nullptr;
			pred = nullptr;
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
			if(a->r != nullptr)
				a->r->pred = a;
			update(a);
			return a;
		}
		else {
			b->l = merge(a, b->l);
			if(b->l != nullptr)
				b->l->pred = b;
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
			if (v->l != nullptr)
				v->l->pred = v;
			update(v);
			return{ res.first, v };
		}
		else {
			auto res = split(v->r, key);
			v->r = res.first;
			if(v->r != nullptr)
				v->r->pred = v;
			update(v);
			return{ v, res.second };
		}
	}

	pair<node *, node *> split_k(node *v, int k) {
		if (v == nullptr)
			return{ nullptr, nullptr };
		if (get_size(v->l) + 1 <= k) {
			auto res = split_k(v->r, k - (get_size(v->l) + 1));
			v->r = res.first;
			if(v->r != nullptr)
				v->r->pred = v;
			update(v);
			return{ v, res.second };
		}
		else {
			auto res = split_k(v->l, k);
			v->l = res.second;
			if(v->l != nullptr)
				v->l->pred = v;
			update(v);
			return{ res.first, v };
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

	bool find(node *v, T key) {
		if (v == nullptr)
			return 0;
		if (v->key == key)
			return 1;
		if (v->key > key)
			return find(v->l, key);
		else return find(v->r, key);
	}

	int index_of(T key) {
		if (!find(root, key))
			return -1;
		return lower_count(root, key);
	}

	node* get_by_index(int index) {
		auto spl1 = split_k(root, index);
		auto spl2 = split_k(spl1.second, 1);
		node* result = spl2.first;
		root = merge(spl1.first, merge(spl2.first, spl2.second));
		return result;
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

	class iterator : public std::iterator<std::input_iterator_tag, T, long, const T*, T>                     
	{
	private:
		node* num;
		int index;
	public:
		explicit iterator(node* _num, long _index) : num(_num), index(_index) {}
		iterator& operator++() { 
			node* last = num;
			if (num->r != nullptr) {
				num = num->r;
				while (num->l != nullptr)
					num = num->l;
				index++;
				return *this;
			}
			else {
				auto last = num;
				num = num->pred;
				while (num != nullptr && num->l != last) {
					last = num;
					num = num->pred;
				}
				if (num == nullptr) 
					index = -1;
				else index++;
				return *this;
			}
			num = num->r;
			while (num->l != nullptr)
				num = num->l;
			if (num == nullptr)
				index = -1;
			else index++;
			return *this; 
		}
		iterator operator++(int) { 
			iterator retval = *this; 
			++(*this); 
			return retval; 
		}
		bool operator==(iterator other) const { 
			return index == other.index; 
		}
		bool operator!=(iterator other) const { 
			return !(*this == other); 
		}
		T operator*() const { 
			return num->key; 
		}
	};
	iterator begin() { 
		node *cur = root;
		while (cur->l != nullptr)
			cur = cur->l;
		return iterator(cur, 0); 
	}
	iterator end() { 
		return iterator(nullptr, -1); 
	}
};

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	decart<int> d;
	int n, m; cin >> n >> m;
	for (int i = 0; i < n; i++) {
		d.insert(i + 1);
	for (int i = 0; i < m; i++) {
		int l, r; cin >> l >> r;
		l--; r--;
		int len = r - l + 1;
		auto spl1 = d.split_k(d.root, l);
		auto spl2 = d.split_k(spl1.second, len);
		d.root = d.merge(d.merge(spl2.first, spl1.first), spl2.second);
	}
	for (auto it : d)
		cout << it << " ";
	return 0;
}
