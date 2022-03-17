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

void fft(int n, vector<P> &a) {
	if (n == 1) return;

	for (int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		for (; j >= bit; bit >>= 1)
			j -= bit;
		j += bit;
		if (i < j)
			swap (a[i], a[j]);
	}

	for (int i = 2; i <= n; i <<= 1) {
		for (int j = 0; j < n; j += i) {
			P w = 1, w0 = polar((C)1, (C)2 * M_PI / i);
			for (int k = 0; k < (i >> 1); k++) {
				P f = a[j + k] + w * a[j + (i >> 1) + k];
				P g = a[j + k] - w * a[j + (i >> 1) + k];
				a[j + k] = f;
				a[j + (i >> 1) + k] = g;
				w *= w0;
			}
		}
	}
}

void inverse_fft(int n, vector<P> &a) {
if (n == 1) return;

	for (int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		for (; j >= bit; bit >>= 1)
			j -= bit;
		j += bit;
		if (i < j)
			swap (a[i], a[j]);
	}

	for (int i = 2; i <= n; i <<= 1) {
		for (int j = 0; j < n; j += i) {
			P w = 1, w0 = polar((C)1, -(C)2 * M_PI / i);
			for (int k = 0; k < (i >> 1); k++) {
				P f = a[j + k] + w * a[j + (i >> 1) + k];
				P g = a[j + k] - w * a[j + (i >> 1) + k];
				a[j + k] = f;
				a[j + (i >> 1) + k] = g;
				w *= w0;
			}
		}
	}
	for (int i = 0; i < n; ++i)
		a[i] /= n;
}

vector<int> mult(vector<int> a, vector<int> b) {
	int n = 1;
	while (n < max(a.size(), b.size()))
		n *= 2;
	n *= 2;
	vector<P> _a(all(a)), _b(all(b));
	_a.resize(n);
	_b.resize(n);
	fft(n, _a);
	fft(n, _b);
	for (int i = 0; i < n; i++)
		_a[i] *= _b[i];
	inverse_fft(n, _a);
	vector<int> res(n);
	for (int i = 0; i < n; i++)
		res[i] = _a[i].X + (C)0.5;
	return res;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	return 0;
}
