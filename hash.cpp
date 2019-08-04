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
 
#define ll long long
 
using namespace std;
 
namespace hash_use
{
    ll H_MAX = 200005;
    const ll p = 239017;
    const ll mod = 1e9 + 7;
    vector<ll> pw(H_MAX);
 
    void init()
    {
        pw[0] = 1;
        for (ll i = 1; i < pw.size(); i++)
            pw[i] = (pw[i - 1] % mod * p % mod) % mod;
    }
 
    vector<ll> getHash(string s)
    {
        vector<ll> hash(s.size());
        hash[0] = s[0];
        for (ll i = 1; i < s.size(); i++)
            hash[i] = ((hash[i - 1] * p) % mod + s[i]) % mod;
 
        return hash;
    }
 
    ll getHashSeg(ll l, ll r, vector<ll> &hash)
    {
        ll hashSeg;
        if (l > 0)
            hashSeg = (hash[r] - (hash[l - 1] * pw[r - l + 1]) % mod + mod) % mod;
        else
            hashSeg = hash[r];
        return hashSeg;
    }
}
 
using namespace hash_use;
 
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
 
    //freopen("input.txt", "r", stdin);
   
    init();
    string t; cin >> t;
    auto h = getHash(t);
    ll T; cin >> T;
    while (T--)
    {
        string s; cin >> s;
        ll hashS = getHash(s)[s.size() - 1];
        bool is = 0;
        for (ll i = 0; i < t.size(); i++)
        {
            if (i + s.size() - 1 >= t.size())
                break;
            ll HashSeg = getHashSeg(i, i + s.size() - 1, h);
            if (hashS == HashSeg)
                is = 1;
        }
        if (is) cout << "YES" <<endl;
        else cout << "NO" << endl;
    }
    return 0;
}
