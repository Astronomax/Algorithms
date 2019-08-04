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
 
struct decart {
    struct node {
        int key, y, sum;
        node *pred;
        node *l, *r;
        node(int x) : l(nullptr), r(nullptr), pred(nullptr), key(x), sum(x), y(rand()) {}
    };
    node *root = nullptr;
 
    void update(node *v) {
        if (v == nullptr) return;
        v->sum = v->key + ((v->l == nullptr) ? 0 : v->l->sum) + ((v->r == nullptr) ? 0 : v->r->sum);
    }
 
    pair<node *, node *> split(int x, node *v) {
        if (v == nullptr)
            return { nullptr, nullptr };
 
        if (v->key <= x) {
            auto res = split(x, v->r);
            v->r = res.first;
            if (v->r != nullptr)
                v->r->pred = v;
            update(v);
            return { v, res.second };
        }
        else {
            auto res = split(x, v->l);
            v->l = res.second;
            if (v->l != nullptr)
                v->l->pred = v;
            update(v);
            return { res.first, v };
        }
    }
 
    node * merge(node *a, node *b) {
        if (a == nullptr || b == nullptr)
            return a == nullptr ? b : a;
 
        if (b->y > a->y) {
            b->l = merge(a, b->l);
            if (b->l != nullptr)
                b->l->pred = b;
            update(b);
            return b;
        }
        else {
            a->r = merge(a->r, b);
            if (a->r != nullptr)
                a->r->pred = a;
            update(a);
            return a;
        }
    }
 
    node* add(node *v, int x) {
        auto f = split(x - 1, v), s = split(x, f.second);
        node *u = new node(x);
        return merge(f.first, merge(u, s.second));
    }
 
    node* find(int x, node *v) {
        auto f = split(x - 1, v), s = split(x, f.second);
        return s.first;
    }
 
    node *lower_bound(int x, node *v) {
        return ((v->key >= x) ? v : ((v->r == nullptr) ? nullptr : lower_bound(x, v->r)));
    }
 
    node *upper_bound(int x, node *v) {
        return ((v->key > x) ? v : ((v->r == nullptr) ? nullptr : lower_bound(x, v->r)));
    }
 
    bool is_descend(node *v, node *parent) {
        return ((v->pred == nullptr) ? false : ((v->pred == parent) ? true : is_descend(v->pred, parent)));
    }
 
    int sum(int l, int r) {
        auto f = split(l - 1, root), s = split(r, f.second);
        int ans = ((s.first == nullptr) ? 0 : s.first->sum);
 
        root = merge(f.first, merge(s.first, s.second));
        return ans;
    }
};
const int mod = 1e9;
 
signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    //freopen("search5.in", "r", stdin);
    //freopen("search5.out", "w", stdout);
    //freopen("input.txt", "r", stdin);
 
    decart dec;
    int n; cin >> n;
    int y = 0;
    for (int i = 0; i < n; i++) {
        char t; cin >> t;
        if (t == '+') {
            int x; cin >> x;
            x = (x % mod + y % mod) % mod;
            dec.root = dec.add(dec.root, x);
            y = 0;
        }
        else {
            int ans = 0, l, r; cin >> l >> r;
            ans = dec.sum(l, r);
            cout << ans << endl;
            y = ans;
        }
    }
    return 0;
}
