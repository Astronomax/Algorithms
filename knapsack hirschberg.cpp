//Байдак Иван Ефимович 06.04.1937 (05.04.1937) - 27.12.2021
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#include <unordered_map>
#include <random>
#include <chrono>
using namespace std;

#define X real()
#define Y imag()
#define endl '\n'
//#define int long long
#define all(X) (X).begin(), (X).end()
#define rall(X) (X).rbegin(), (X).rend()
mt19937_64 rnd(chrono::system_clock::now().time_since_epoch().count());
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int lcm(int a, int b) { return a * b / gcd(a, b); }

const int MAXW = 10100, MAXN = 110;
int l[MAXW], r[MAXW];
bool ans[MAXN];

void hirschberg(int w, int lq, int rq, vector<int> &v, vector<int> &c) {
	if (lq == rq)
		return;
	if (lq + 1 == rq) {
		if (v[lq] <= w)
			ans[lq] = 1;
	}
	else {
		int mid = (lq + rq) / 2;
		for (int i = 0; i <= w; i++)
			l[i] = 0;
		for (int i = lq; i < mid; i++)
			for (int j = w; j >= 0; j--)
				if (v[i] <= j)
					l[j] = max(l[j], l[j - v[i]] + c[i]);
		for (int i = 0; i <= w; i++)
			r[i] = 0;
		for (int i = mid; i < rq; i++)
			for (int j = w; j >= 0; j--)
				if (v[i] <= j)
					r[j] = max(r[j], r[j - v[i]] + c[i]);
		int j = 0;
		for (int i = 0; i <= w; i++)
			if (l[i] + r[w - i] > l[j] + r[w - j])
				j = i;
		hirschberg(j, lq, mid, v, c);
		hirschberg(w - j, mid, rq, v, c);
	}
}

signed main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	int n, w; cin >> n >> w;
	vector<int> v(n), c(n);
	for (auto &i : v)
		cin >> i;
	for (auto &i : c)
		cin >> i;
	hirschberg(w, 0, n, v, c);
	for (int i = 0; i < n; i++)
		if (ans[i])
			cout << i + 1 << endl;
	return 0;
}
