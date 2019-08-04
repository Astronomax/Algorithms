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
 
namespace hash_use {
    int p = 239017;
    pair<int, int> mod = { 1e9 + 7, 1e9 + 13 };
    const int HMAX = 1e5 + 5;
    vector<pair<int, int>> pw(HMAX);
    void init() {
        pw[0] = { 1, 1 };
        for (int i = 1; i < HMAX; i++)
            pw[i] = { (pw[i - 1].first * p) % mod.first, (pw[i - 1].second * p) % mod.second };
    }
 
    void getHash(string &s, vector<pair<int, int>> &hash) {
        hash.resize(s.size());
        hash[0] = { s[0], s[0] };
 
        for (int i = 1; i < s.size(); i++)
            hash[i] = { ((hash[i - 1].first * p) % mod.first + s[i]) % mod.first, ((hash[i - 1].second * p) % mod.second + s[i]) % mod.second };
    }
 
    pair<int, int> getHashSeg(vector<pair<int, int>> &hash, int l, int r) {
        pair<int, int> hashSeg;
        if (l > 0)
            hashSeg = { (hash[r].first - (hash[l - 1].first * pw[r - l + 1].first) % mod.first + mod.first) % mod.first, (hash[r].second - (hash[l - 1].second * pw[r - l + 1].second) % mod.second + mod.second) % mod.second };
        else
            hashSeg = hash[r];
        return hashSeg;
    }
}
using namespace hash_use;
 
signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    //freopen("input.txt", "r", stdin);
    
    return 0;
}
