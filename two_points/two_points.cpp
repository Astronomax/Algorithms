#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#include <unordered_map>
#include <random>
#include <chrono>
using namespace std;

#define X real()
#define Y imag()
#define endl '\n'
typedef long double C;
typedef complex<C> P;
typedef long double ld;
#define int long long
#define all(X) (X).begin(), (X).end()
#define rall(X) (X).rbegin(), (X).rend()
mt19937_64 rnd(chrono::system_clock::now().time_since_epoch().count());
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int lcm(int a, int b) { return a * b / gcd(a, b); }

int two_points(int l, int r, vector<pair<int, int>> &p) {
	if (l + 1 == r)
		return LLONG_MAX;
	else {
		int mid = (l + r) / 2, x_mid = p[mid].first;
		int ans = min(two_points(l, mid, p), two_points(mid, r, p));
		int h = sqrt(ans);

		vector<pair<int, int>> sorted_y(r - l);
		merge(p.begin() + l, p.begin() + mid,
			p.begin() + mid, p.begin() + r,
			sorted_y.begin(),
			[](pair<int, int> a, pair<int, int> b) {
			return a.second > b.second;
		});

		for (int i = 0; i < r - l; i++)
			p[l + i] = sorted_y[i];

		vector<pair<int, int>> order;
		for (int i = l; i < r; i++)
			if (abs(p[i].first - x_mid) <= h)
				order.push_back(p[i]);

		for (int i = 0; i < order.size(); i++)
			for (int k = i + 1; k < order.size() && order[i].second - order[k].second <= h; k++)
				ans = min(ans, (int)pow(order[i].first - order[k].first, 2) + (int)pow(order[i].second - order[k].second, 2));
		return ans;
	}
}

signed main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	return 0;
}
