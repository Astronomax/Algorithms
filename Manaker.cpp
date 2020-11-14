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
#include <chrono>
#include <random>
#include <cassert>
 
//#pragma comment(linker, "/STACK:16777216")
 
using namespace std;
 
typedef double C;
typedef complex<C> P;
 
#define X real()
#define Y imag()
#define Size(X) (int)X.size()
#define ui unsigned int
#define int long long
#define mp make_pair
#define timer fghge
#define y1 yjyjyju
#define all(X) (X).begin(), (X).end()
#define endl '\n'
mt19937_64 rnd(std::chrono::system_clock::now().time_since_epoch().count());
 
const int MAXN = 100010;
int d1[MAXN], d2[MAXN];
 
signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	freopen("palindrome.in", "r", stdin);
	freopen("palindrome.out", "w", stdout);
 
	string s; cin >> s;
	int n = s.size();
 
	//считаем d1
	int L = -1, R = -1;
	for (int i = 0; i < n; i++) {
		if (i > R) {
			R = i; L = i;
			for (int l = i - 1, r = i + 1; l >= 0 && r < n; l--, r++, R++) 
				if (s[l] != s[r]) 
					break;
			d1[i] = R - i;
			L = i - d1[i];
		}
		else {
			int j = L + (R - i);
			d1[i] = d1[j];
 
			if (i + d1[i] >= R) {
				int d = (R + 1) - i;
				d1[i] = d;
 
				for (int l = i - d, r = i + d; l >= 0 && r < n; l--, r++, R++)
					if (s[l] != s[r])
						break;
				d1[i] = R - i;
				L = i - d1[i];
			}
		}
	}
 
	//считаем d2
	L = -1, R = -1;
	for (int i = 0; i < n; i++) {
		if (i > R) {
			for (int l = i - 1, r = i; l >= 0 && r < n; l--, r++, d2[i]++) 
				if (s[l] != s[r])
					break;
			if (d2[i] != 0) {
				L = i - d2[i];
				R = i + d2[i] - 1;
			}
		}
		else {
			int j = L + (R - i) + 1;
			d2[i] = d2[j];
 
			if (i + d2[i] - 1 >= R) {
				int d = (R + 1) - i;
				d2[i] = d + 1;
 
				for (int l = i - 1 - d, r = i + d; l >= 0 && r < n; l--, r++, R++)
					if (s[l] != s[r])
						break;
				d2[i] = R - i + 1;
				L = i - d2[i];
			}
		}
	}
	
	int ans = 0;
	for (int i = 0; i < n; i++) 
		d1[i] = min(d1[i], n - 1 - i);
	for (int i = 0; i < n; i++)
		d2[i] = min(d2[i], n - i);
	for (int i = 0; i < n; i++) 
		ans += d1[i] + d2[i];
 
	cout << ans;
	return 0;
}
