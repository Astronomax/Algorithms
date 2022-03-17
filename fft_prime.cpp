#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
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

const int mod = 786433;
int pw[mod];

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

int inv(int a) {
	int x, y;
	extgcd(a, mod, x, y);
	x = (x % mod + mod) % mod;
	return x;
}

void fft(int n, vector<int> &a, bool inverse) {
	if (n == 1) return;

	for (int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		for (; j >= bit; bit >>= 1)
			j -= bit;
		j += bit;
		if (i < j)
			swap(a[i], a[j]);
	}

	for (int i = 2; i <= n; i <<= 1) {
		for (int j = 0; j < n; j += i) {
			int w = 1, w0 = pw[(mod - 1) / i];
			if (inverse) w0 = inv(w0);
			for (int k = 0; k < (i >> 1); k++) {
				int f = add(a[j + k], prod(w, a[j + (i >> 1) + k]));
				int g = add(a[j + k], prod(-w, a[j + (i >> 1) + k]));
				a[j + k] = f;
				a[j + (i >> 1) + k] = g;
				w = prod(w, w0);
			}
		}
	}
	if(inverse)
		for (int i = 0; i < n; ++i)
			a[i] = prod(a[i], inv(n));
}

vector<int> mult(vector<int> a, vector<int> b) {
	int n = 1;
	while (n < max(a.size(), b.size()))
		n *= 2;
	n *= 2;
	vector<int> _a(all(a));
	vector<int> _b(all(b));
	_a.resize(n);
	_b.resize(n);
	fft(n, _a, false);
	fft(n, _b, false);
	for (int i = 0; i < n; i++)
		_a[i] = prod(_a[i], _b[i]);
	fft(n, _a, true);
	return _a;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	return 0;
}
