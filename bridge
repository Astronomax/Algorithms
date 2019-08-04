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
    int color, tin, tout;
    vector<int> edjes;
};
int t = 0;
 
set<pair<int, int>> bridges;
 
void dfs(int start, vector<node> &g, vector<int> &g_min, int p) {
    g[start].used = 1;
    g[start].tin = g_min[start] = ++t;
 
    for (auto i : g[start].edjes) {
        if (i == p) continue;
 
        if (g[i].used == 1)
            g_min[start] = min(g_min[start], g[i].tin);
        else {
            dfs(i, g, g_min, start);
            g_min[start] = min(g_min[start], g_min[i]);
            if (g_min[i] > g[start].tin) {
                bridges.insert({ start, i });
                bridges.insert({ i, start });
            }
        }
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
    vector<node> g(n), gt(n);
    vector<int> g_min(n);
    vector<pair<int, int>> edjes(m);
 
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b; a--; b--;
        g[a].edjes.push_back(b);
        g[b].edjes.push_back(a);
        edjes[i] = { a, b };
    }
 
    for (int i = 0; i < n; i++)
        if (g[i].used == 0)
            dfs(i, g, g_min, -1);
    cout << bridges.size() / 2 << endl;
    for (int i = 0; i < m; i++)
        if (bridges.find(edjes[i]) != bridges.end())
            cout << i + 1 << endl;
    return 0;
}
