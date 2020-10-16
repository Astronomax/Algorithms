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
#define size fgfgfb
#define MP make_pair
#define timer fghge
#define y1 yjyjyju
#define all(X) (X).begin(), (X).end()
#define int long long
 
vector<int> link, size;
 
int find(int x) {
    if (link[x] == x)
        return x;
    else
        return link[x] = find(link[x]);
}
 
bool same(int a, int b) {
    return find(a) == find(b);
}
 
void unite(int a, int b) {
    if (!same(a, b)) {
        a = find(a);
        b = find(b);
        if (size[a] < size[b])
            swap(a, b);
        link[b] = a;
        size[a] += size[b];
    }
}
signed main()
{
    int n; cin >> n;
    link.resize(n);
    size.resize(n);
    for (int i = 0; i < n; i++) link[i] = i;
    for (int i = 0; i < n; i++) size[i] = 1;
    return 0;
}
