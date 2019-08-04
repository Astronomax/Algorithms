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
 
struct axo {
    struct node {
        pair<int, char> par;
        vector<int> term;
        int link = -1;
        vector<int> edjes;
        node() { edjes.assign(26, -1); }
    };
    vector<node> g;
    vector<int> pos;
    vector<bool> used;
 
    int get_next(int v, char c) {
        if (g[v].edjes[c - 'a'] != -1)
            return g[v].edjes[c - 'a'];
        if (v == 0) //root
            return 0;
 
        return (g[v].edjes[c - 'a'] = get_next(get_link(v), c));
    }
 
    int get_link(int v) {
        if (g[v].par.first == 0 || v == 0)
            return (g[v].link = 0);
 
        if (g[v].link == -1 || g[v].term.empty())
            g[v].link = get_next(get_link(g[v].par.first), g[v].par.second);
 
        return g[v].link;
    }
 
    void push(pair<int, char> par){
        node dop; dop.par = par;
        g.push_back(dop);
    }
 
    void update(int v, char c, int j) {
        while (v != 0 && used[v] == 0) {
            used[v] = 1;
            for (auto i : g[v].term)
                pos[i] = j;
            v = get_link(v);
        }
    }
};
 
void solve(axo &norm, vector<string> &a, string &t){
    int n = a.size();
    norm.pos.assign(n, -1);
    norm.g.assign(1, {});
 
    int last = 1;
    for (int i = 0; i < n; i++) {
        int start = 0;
        for (auto j : a[i]) {
            if (norm.g[start].edjes[j - 'a'] != -1)
                start = norm.g[start].edjes[j - 'a'];
            else {
                norm.push({ start, j });
                norm.g[start].edjes[j - 'a'] = last;
                start = last;
                last++;
            }
        }
        norm.g[start].term.push_back(i);
    }
    norm.used.resize(norm.g.size());
 
    int start = 0;
    for (int j = 0; j < t.size(); j++){
        start = norm.get_next(start, t[j]);
        norm.update(start, t[j], j);
    }
}
 
signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    freopen("search6.in", "r", stdin);
    freopen("search6.out", "w", stdout);
    //freopen("input.txt", "r", stdin);
    int n; cin >> n;
 
    vector<string> a(n);
    for (auto &i : a)
        cin >> i;
 
    string t; cin >> t;
 
    axo norm;
    solve(norm, a, t);
 
    for (auto &i : a)
        reverse(all(i));
 
    reverse(all(t));
 
    axo rev;
    solve(rev, a, t);
 
    for (int i = 0; i < n; i++){
        if (norm.pos[i] == -1)
            cout << -1 << " " << -1 << endl;
        else
            cout << (norm.pos[i] - a[i].size()) + 1 << " " << t.size() - 1 - rev.pos[i] << endl;
    }
    return 0;
}
