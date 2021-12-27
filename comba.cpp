#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#include <random>
#include <chrono>

using namespace std;

typedef long double C;
typedef complex<C> P;
#define X real()
#define Y imag()
#define endl '\n'
#define int long long
#define all(X) (X).begin(), (X).end()
#define rall(X) (X).rbegin(), (X).rend()
mt19937_64 rnd(chrono::system_clock::now().time_since_epoch().count());
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int lcm(int a, int b) { return a * b / gcd(a, b); }

const int mod = 998244353, MAXN = 510;
int dp[MAXN][MAXN], pw[MAXN];

template <typename T>
T add(T n) {
	int ans = n % mod;
	if (ans < 0) ans += mod;
	return ans;
}

template <typename T, typename... Args>
T add(T n, Args... rest) {
	int ans = (n + add(rest...)) % mod;
	if (ans < 0) ans += mod;
	return ans;
}

template <typename T>
T prod(T n) {
	return n % mod;
}

template <typename T, typename... Args>
T prod(T n, Args... rest) {
	return ((n % mod) * prod(rest...)) % mod;
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

int f[MAXN];

int c(int n, int k) {
	if (n < 0 || k < 0 || n - k < 0) return 0;
	return (f[n] * inv(f[n - k] * f[k], mod)) % mod;
}

int klimenko(int n, int k) {
	return c(n + k - 1, k - 1);
}

int kuznets(int n, int k, int d) {
	return klimenko(n - k * (d - 1) - d, d + 1);
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif
	f[0] = 1;
	for (int i = 1; i < MAXN; i++)
		f[i] = (f[i - 1] * i) % mod;
	return 0;
}
