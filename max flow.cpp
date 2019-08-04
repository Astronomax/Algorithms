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
#include <windows.h>
 
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
 
int n, m, x;
 
vector<vector<int>> g, dop, f;
vector<bool> used;
vector<int> p;
 
void update(int s, int t, int d) {
    for (int i = t; i != s; i = p[i]) {
        int a = p[i], b = i;
        f[a][b] -= d;
        f[b][a] += d;
    }
}
 
int bfs(int s, int t) {
    for (auto &i : used)
        i = 0;
    for (auto &i : p)
        i = 0;
 
    used[s] = 1;
    queue<pair<int, int>> que;
    que.push({ s, 1e18 });
 
    while (!que.empty()) {
        int v = que.front().first, c = que.front().second;
        que.pop();
        if (v == t)
            return c;
        for (int i = 0; i < n; i++) {
            if (used[i] == 0 && dop[v][i] + f[v][i] > 0) {
                que.push({ i, min(c, dop[v][i] + f[v][i]) });
                p[i] = v;
                used[i] = 1;
            }
        }
    }
    return -1;
}
 
int potok(int s, int t) {
    int ans = 0;
    for (auto &i : f)
        for (auto &j : i)
            j = 0;
 
    while (true) {
        int d = bfs(s, t);
       
        if (d != -1) {
            ans += d;
            update(s, t, d);
        }
        else
            break;
    }
    return ans;
}
 
signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
 
    cin >> n >> m >> x;
    p.resize(n);
    used.resize(n);
    g.assign(n, vector<int>(n));
    dop.assign(n, vector<int>(n));
    f.assign(n, vector<int>(n));
 
    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c; a--; b--;
        g[a][b] = c;
    }
 
    double l = 0, r = 1e6 + 1;
    for (int i = 0; i < 500; i++) {
        double mid = (l + r) / 2;
       
        for (int j = 0; j < n; j++)
            for (int q = 0; q < n; q++)
                dop[j][q] = g[j][q] / mid;
 
        if(potok(0, n - 1) >= x)
            l = mid;
        else
            r = mid;
    }
 
    cout << fixed << setprecision(10) << l * double(x);
    return 0;
}
