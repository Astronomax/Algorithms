#define _USE_MATH_DEFINES
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
#include <unordered_map>
#include <iterator>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <stack>
#include <complex>
 
using namespace std;
 
typedef long double C;
typedef complex<C> P;
 
#define X real()
#define Y imag()
#define ll long long
#define MP make_pair
#define timer fghge
#define y1 yjyjyju
#define all(X) (X).begin(), (X).end()
 
const double EPS = 1e-9;
 
vector<int> a;
vector<int> t;
 
void build(int v, int l, int r)
{
    if (l == r)
        t[v] = a[l];
    else
    {
        int mid = (l + r) / 2;
        build(v * 2, l, mid);
        build(v * 2 + 1, mid + 1, r);
        t[v] = t[v * 2] + t[v * 2 + 1];
    }
}
 
int sum(int v, int l, int r, int tl, int tr)
{
    if (l > r)
        return 0;
    if (tl == l && tr == r)
        return t[v];
    else
    {
        int mid = (tl + tr) / 2;
        return sum(v * 2, l, min(mid, r), tl, mid) + sum(v * 2 + 1, max(l, mid + 1), r, mid + 1, tr);
    }
}

void update(long long v, long long l, long long r, long long i, long long x)
{
    if (l == r)
        t[v] = x;
    else
    {
        long long mid = (l + r) / 2;
        if (i <= mid)
            update(v * 2, l, mid, i, x);
        else
            update(v * 2 + 1, mid + 1, r, i, x);
        t[v] = t[v * 2] + t[v * 2 + 1];
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    //freopen("input.txt", "r", stdin);
    int n, q; cin >> n >> q;
    a.resize(n);
    for (auto &i : a)
        cin >> i;
    t.resize(4 * n);
    build(1, 0, n - 1);
    while (q--)
    {
        int l, r; cin >> l >> r;
        cout << sum(1, l, r, 0, n - 1) << endl;
    }
    return 0;
}
