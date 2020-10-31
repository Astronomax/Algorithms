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
#define hash HASH
#define int long long
#define Size(X) (int)X.size()
#define ui unsigned int
#define mp make_pair
#define timer fghge
#define y1 yjyjyju
#define all(X) (X).begin(), (X).end()
#define endl '\n'
mt19937_64 rnd(std::chrono::system_clock::now().time_since_epoch().count());

typedef pair<double, double> complex_t;

int norm(complex_t a) {
	return a.first * a.first + a.second * a.second;
}

complex_t conj(complex_t a) {
	return { a.first, -a.second };
}

complex_t operator+ (complex_t a, complex_t b) {
	return { a.first + b.first, a.second + b.second };
}

complex_t operator- (complex_t a, complex_t b) {
	return { a.first - b.first, a.second - b.second };
}

complex_t operator* (complex_t a, complex_t b) {
	return { a.first * b.first - a.second * b.second,  a.second * b.first + a.first * b.second };
}

complex_t operator/ (complex_t a, complex_t b) {
	auto res = a * conj(b);
	return { res.first / (b.first * b.first + b.second * b.second), res.second / (b.first * b.first + b.second * b.second) };
}

complex_t operator% (complex_t a, complex_t b) {
	auto res = a / b;
	res.first = floor(res.first + 0.5);
	res.second = floor(res.second + 0.5);
	return a - b * res;
}

bool operator== (complex_t a, complex_t b) {
	return ((a.first == b.first) && (a.second == b.second));
}

complex_t gcd(complex_t a, complex_t b) {
	if (norm(a) < norm(b))
		swap(a, b);
	if (b == mp(0, 0))
		return a;
	else return gcd(b, a % b);
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	complex_t a, b;
	cin >> a.first >> a.second >> b.first >> b.second;
	auto res = gcd(a, b);
	cout << res.first << " " << res.second;
	return 0;
}
