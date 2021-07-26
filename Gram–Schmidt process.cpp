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

long double prod(vector<long double> a, vector<long double> b) {
	long double res = 0;
	for (int i = 0; i < a.size(); i++)
		res += a[i] * b[i];
	return res;
}

long double len(vector<long double> a) {
	return sqrt(prod(a, a));
}

vector<long double> operator*(long double k, vector <long double> a) {
	for (auto &i : a)
		i *= k;
	return a;
}

void operator -=(vector<long double> &a, vector<long double> b) {
	for (int i = 0; i < a.size(); i++)
		a[i] -= b[i];
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif
	int n = 3;
	vector<vector<long double>> f(n);
	f[0] = { 2, 1, 0 };
	f[1] = { 0, 1, 0 };
	f[2] = { 0, 0, 1 };

	vector<vector<long double>> e(n);
	e[0] = 1.0 / len(f[0]) * f[0];
	for (int i = 1; i < n; i++) {
		e[i] = f[i];
		for (int j = 0; j < i; j++)
			e[i] -= prod(f[i], e[j]) * e[j];
		e[i] = 1.0 / len(e[i]) * e[i];
	}
	cout << fixed << setprecision(3);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << prod(e[i], e[j]) << " ";
		cout << endl;
	}
	cout << endl;

	for (auto &i : e) {
		for (auto &j : i)
			cout << j << " ";
		cout << endl;
	}
	return 0;
}
