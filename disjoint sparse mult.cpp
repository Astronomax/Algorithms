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
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <iterator>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <complex>
#include <chrono>
#include <random>
#include <numeric>
//#pragma comment(linker, "/STACK:16777216")

using namespace std;

typedef long double C;
typedef complex<C> P;

#define X real()
#define Y imag()
#define Size(X) (int)X.size()
//#define int long long
#define ui unsigned int
#define mp make_pair
#define timer fghge
#define y1 yjyjyju
#define all(X) (X).begin(), (X).end()
#define endl '\n'
mt19937_64 rnd(std::chrono::system_clock::now().time_since_epoch().count());

const int MAXN = 1e6 + 10, LOGN = 21, mod = 764854400;
long long dp[LOGN][MAXN];

signed main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	//freopen("input.txt", "r", stdin);

	int n; cin >> n;
	vector<long long> a(n);
	for (auto &i : a){
	    cin >> i;
	    i %= mod;
    }
	int len = 1;
	for (int i = 0; i < LOGN; i++) {
		if (len > n) break;	
		for (int center = len - 1; center < n; center += 2 * len) {
			long long p = 1;
			for (int j = 0; j < len && center - j >= 0; j++) {
				p = (p * a[center - j]) % mod;
				dp[i][center - j] = p;
			}
			p = 1;
			for (int j = 0; j < len && center + j + 1 < n; j++) {
				p = (p * a[center + j + 1]) % mod;
				dp[i][center + j + 1] = p;
			}
		}
		len <<= 1;
	}

	int q; cin >> q;
	for (int i = 0; i < q; i++) {
		int l, r; cin >> l >> r; l--; r--;
		if (l == r)
			cout << a[l] << endl;
		else {
			int lvl = 31 - __builtin_clz(l ^ r);
			cout << (dp[lvl][l] * dp[lvl][r]) % mod << endl;
		}
	}
	return 0;
}
