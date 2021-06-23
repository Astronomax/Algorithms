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
 
void dfs(int start, int ctr){
    g[start].used = 1;
    g[start].d = ctr;
    for(auto i : g[start].edjes){
        if(g[i].used == 0)
            dfs(i, ctr + 1);
    }
}
 
signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
 
    int n; cin>>n;
    g.resize(n);
    vector<vector<int>> up(log2(n) + 1, vector<int> (n));
    up[0][0] = 0;
    for(int i = 1; i < n; i++){
        int x; cin>>x; x--;
        up[0][i] = x;
        g[x].edjes.push_back(i);
    }
 
    dfs(0, 0);
 
    for(int i = 1; i < up.size(); i++){
        for(int j = 0; j < n; j++){
            up[i][j] = up[i - 1][up[i - 1][j]];
        }
    }
 
    int m; cin>>m;
    while(m--){
        int a, b; cin>>a>>b; a--; b--;
        if(g[a].d < g[b].d)
            swap(a, b);
        int dif = g[a].d - g[b].d;
        for(int i = log2(n); i >= 0; i--){
            if((1 << i) <= dif){
                dif-=(1<<i);
                a = up[i][a];
            }
        }
 
        if(a == b){
            cout<<a + 1<<endl;
            continue;
        }
        int v = a;
        for(int i = log2(n); i >= 0; i--){
            if(up[i][a] != up[i][b]){
                a = up[i][a];
                b = up[i][b];
            }
        }
        cout<<up[0][a] + 1<<endl;
    }
    return 0;
}
