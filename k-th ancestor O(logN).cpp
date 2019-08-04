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
#include <iterator>
#include <fstream>
#include <iomanip>
 
using namespace std;
 
//#define X real()
//#define Y imag()
#define MP make_pair
#define timer fghge
#define y1 yjyjyju
#define all(X) (X).begin(), (X).end()
#define int long long
 
struct node {
    bool used = 0;
    vector<int> edjes;
};
 
signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    //freopen("input.txt", "r", stdin);
    int n; cin >> n;
    vector<node> g(n);
    vector<vector<int>> dp(ceil(log2(n)) + 1, vector<int>(n));
    int start = 1;
    vector<int> p;
    while (start <= n) {
        p.push_back(start);
        start *= 2;
    }
 
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        g[u].edjes.push_back(v);
        dp[0][v] = u;
    }
    for (int i = 0; i < dp.size(); i++)
        dp[i][0] = -1;
 
    for (int i = 1; i < dp.size(); i++) {
        for (int j = 1; j < n; j++) {
            if (dp[i - 1][j] != - 1)
                dp[i][j] = dp[i - 1][dp[i - 1][j]];
            else
                dp[i][j] = -1;
        }
    }
 
    int t; cin >> t;
    while (t--) {
        int v, k; cin >> v >> k; v--;
        int ans = v;
        for (int i = p.size() - 1; i >= 0; i--) {
            if (p[i] <= k) {
                ans = dp[i][ans];
                k -= p[i];
                if (k == 0)
                    break;
            }
            if (ans == -1)
                break;
        }
        cout << ans + (ans != -1) << endl;
    }
    return 0;
}
