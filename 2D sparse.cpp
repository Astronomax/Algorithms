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
 
struct node {
    int maxx, minx, maxy, miny;
};
 
vector<vector<vector<vector<node>>>> sp(7, vector<vector<vector<node>>>(127, vector<vector<node>>(7, vector<node>(127))));
//node sp[7][127][7][127];
 
void merge(node &ans, node &a, node&b) {
    ans.maxx = min(a.maxx, b.maxx);
    ans.maxy = min(a.maxy, b.maxy);
    ans.minx = max(a.minx, b.minx);
    ans.miny = max(a.miny, b.miny);
}
const int mod = 1e9 + 7;
int next(int v, int A, int B) {
    int ans = ((A * v) % mod + B) % mod;
    return ans;
}
 
signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
     
    //freopen("input.txt", "r", stdin);
 
    int n, m; cin >> n >> m;
    vector<vector<node>> a(n, vector<node>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
            a[i][j].minx = min(x1, x2);
            a[i][j].maxx = max(x1, x2);
            a[i][j].miny = min(y1, y2);
            a[i][j].maxy = max(y1, y2);
        }
    }
 
    for (int q = 0; q < n; q++) {
        for (int j = 0; j < m; j++)
            sp[0][q][0][j] = a[q][j];
 
        for (int i = 1; i < 7; i++) {
            for (int j = 0; j < m; j++) {
                if (j + (1 << i) - 1 >= m) break;
                merge(sp[0][q][i][j], sp[0][q][i - 1][j], sp[0][q][i - 1][j + (1 << (i - 1))]);
            }
        }
    }
 
    for (int w = 1; w < 7; w++) {
        for (int q = 0; q < n; q++) {
            if (q + (1 << w) - 1 >= n) break;
            for (int i = 0; i < 7; i++) {
                for (int j = 0; j < m; j++) {
                    if (j + (1 << i) - 1 >= m) break;
                    merge(sp[w][q][i][j], sp[w - 1][q][i][j], sp[w - 1][q + (1 << (w - 1))][i][j]);
                }
            }
        }
    }
 
    int q, A, B, v0; cin >> q >> A >> B >> v0;
    vector<int> query;
    v0 = next(v0, A, B);
    query.push_back(v0);
    for (int i = 0; i < 3; i++) {
        v0 = next(v0, A, B);
        query.push_back(v0);
    }
 
    int sum = 0;
    for (int j = 0; j < q; j++) {
        query[0] %= n;
        query[1] %= m;
        query[2] %= n;
        query[3] %= m;
        int minr = min(query[0], query[2]);
        int maxr = max(query[0], query[2]);
        int minc = min(query[1], query[3]);
        int maxc = max(query[1], query[3]);
 
        int sr = log2(maxr - minr + 1), sc = log2(maxc - minc + 1);
 
        node ans, ans1, ans2;
        merge(ans1, sp[sr][minr][sc][minc], sp[sr][minr][sc][maxc - (1 << sc) + 1]);
        merge(ans2, sp[sr][maxr - (1 << sr) + 1][sc][minc], sp[sr][maxr - (1 << sr) + 1][sc][maxc - (1 << sc) + 1]);
        merge(ans, ans1, ans2);
 
        if (ans.maxx >= ans.minx && ans.maxy >= ans.miny)
            sum = (sum % mod + ((ans.maxx - ans.minx) % mod * (ans.maxy - ans.miny) % mod) % mod) % mod;
 
        for (int i = 0; i < 4; i++) {
            v0 = next(v0, A, B);
            query[i] = v0;
        }
    }
    cout << sum;
    return 0;
}
