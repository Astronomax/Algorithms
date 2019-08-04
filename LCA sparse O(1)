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
 
struct node{
    bool used = 0;
    int d;
    vector<int> edjes;
};
vector<node> g;
vector<int> order;
 
void dfs(int start, int ctr){
    g[start].used = 1;
    g[start].d = ctr;
    order.push_back(start);
 
    for (auto i : g[start].edjes){
        if (g[i].used == 0){
            dfs(i, ctr + 1);
            order.push_back(start);
        }
    }
    order.push_back(start);
}
 
signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    //freopen("input.txt", "r", stdin);
    int n; cin >> n;
    g.resize(n);
    for (int i = 1; i < n; i++){
        int x; cin >> x; x--;
        g[x].edjes.push_back(i);
    }
    dfs(0, 0);
 
    vector<vector<int>> sparse(log2(order.size()) + 1, vector<int>(order.size()));
 
    sparse[0] = order;
    for (int i = 1; i < sparse.size(); i++){
        for (int j = 0; j < order.size() - (1 << i) + 1; j++){
            int a = sparse[i - 1][j], b = sparse[i - 1][j + (1 << (i - 1))];
            if (g[a].d > g[b].d)
                swap(a, b);
            sparse[i][j] = a;
        }
    }
    vector<int> ind(n, 1e18);
    for (int i = 0; i < order.size(); i++)
        ind[order[i]] = min(ind[order[i]], i);
   
    int m; cin >> m;
    while (m--){
        int a, b;  cin >> a >> b; a--; b--;
        int l = ind[a], r = ind[b];
 
        if (l > r)
            swap(l, r);
 
        int j = log2(r - l + 1);
 
        a = sparse[j][l], b = sparse[j][r - (1 << j) + 1];
        if (g[a].d > g[b].d)
            swap(a, b);
        cout << a + 1 << endl;
    }
    return 0;
}
