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
#include <numeric>

using namespace std;

typedef long double C;
typedef complex<C> P;

#define X real()
#define Y imag()
#define Size(X) (int)X.size()
#define int long long
#define ui unsigned int
#define mp make_pair
#define timer fghge
#define y1 yjyjyju
#define all(X) (X).begin(), (X).end()
#define endl '\n'

const int mod = 998244353;

int gcd(int a, int b) {
	if (b == 0)
		return a;
	else
		return gcd(b, a % b);
}

void extgcd(int a, int b, int &x, int &y) {
	if (b == 0) {
		x = 1; y = 0;
		return;
	}
	else {
		extgcd(b, a % b, x, y);
		int temp = y;
		y = x - (a / b) * y;
		x = temp;
	}
}

int inv(int a, int mod) {
	int x, y;
	extgcd(a, mod, x, y);
	x = (x % mod + mod) % mod;
	return x;
}

const int MAXN = 500005;
int f[MAXN];

int c(int n, int k) {
	return (f[n] * inv(f[n - k] * f[k], mod)) % mod;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);

	f[0] = 1;
	for (int i = 1; i < MAXN; i++)
		f[i] = (f[i - 1] * i) % mod;

	int n, k; cin >> n >> k;
	int ans = 0;
	for (int i = 1; i <= n; i++) 
		if(k - 1 <= n / i - 1)
			ans = (ans + c(n / i - 1, k - 1)) % mod;
	cout << ans;
	return 0;
}
