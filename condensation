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
 
typedef long double C;
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
 
struct node {
    bool used = 0;
    int color;
    set<int> edjes;
};
 
void dfs(int start, vector<int> &order, vector<node> &g) {
    g[start].used = 1;
    for (auto i : g[start].edjes) {
        if (g[i].used == 0)
            dfs(i, order, g);
    }
    order.push_back(start);
}
 
void _dfs(int start, vector<node> &g, int color) {
    g[start].used = 1;
    g[start].color = color;
 
    for (auto i : g[start].edjes) {
        if (g[i].used == 0)
            _dfs(i, g, color);
    }
}
signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    //freopen("search5.in", "r", stdin);
    //freopen("search5.out", "w", stdout);
    //freopen("input.txt", "r", stdin);
 
    int n, m; cin >> n >> m;
    vector<int> order;
    vector<node> g(n), gt(n);
 
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b; a--; b--;
        if (a != b) {
            g[a].edjes.insert(b);
            gt[b].edjes.insert(a);
        }
    }
 
    for (int i = 0; i < n; i++)
        if (g[i].used == 0)
            dfs(i, order, g);
 
    reverse(all(order));
    int color = 0;
 
    for (int i = 0; i < n; i++) {
        int v = order[i];
        if (gt[v].used == 0) {
            _dfs(v, gt, color);
            color++;
        }
    }
 
    set<pair<int, int>> ans;
    for (int i = 0; i < n; i++)
        for (auto j : g[i].edjes)
            if (gt[i].color != gt[j].color)
                ans.insert({ gt[i].color, gt[j].color});
    cout << ans.size();
    return 0;
}
