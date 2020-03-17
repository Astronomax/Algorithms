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

//#pragma comment(linker, "/STACK:16777216")

using namespace std;

typedef long double C;
typedef complex<C> P;

#define X real()
#define Y imag()
#define Size(X) (int)X.size()
#define ui unsigned int
#define mp make_pair
#define timer fghge
#define y1 yjyjyju
#define all(X) (X).begin(), (X).end()
#define endl '\n'
mt19937_64 rnd(std::chrono::system_clock::now().time_since_epoch().count());

struct point {
	double x, y;
};

double operator *(point a, point b) {
	return a.x * b.y - a.y * b.x;
}

struct vect {
	double x, y;
	vect(point a, point b) {
		x = b.x - a.x;
		y = b.y - a.y;
	}
};

struct line {
	double a, b, c;

	line(point fir, point sec) {
		a = sec.y - fir.y;
		b = fir.x - sec.x;
		c = (fir * sec);
	}

	line(vect v, point p) {
		a = v.y;
		b = -v.x;
		c = -(a * p.x + b * p.y);
	}
};

double operator *(line a, line b) {
	return a.a * b.b - a.b * b.a;
}

point mid(point a, point b) {
	return{ (a.x + b.x) / 2, (a.y + b.y) / 2 };
}

bool intersec(line _1, line _2, point ans) {
	if ((_1 * _2) == 0)
		return 0;

	double x = (_2.c * _1.b - _1.c * _2.b) / (_1.a * _2.b - _2.a * _1.b), y = (_1.c * _2.a - _2.c * _1.a) / (_1.a * _2.b - _2.a * _1.b);
	ans = { x, y };
	return 1;
}

int dist(point a, point b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
 
	int n; cin >> n;
	vector<point> a(n);
	for (int i = 0; i < n; i++) 
		cin >> a[i].x >> a[i].y;
	
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (j == i) continue;
			for (int q = 0; q < 5; q++) {
				if (q == i || q == j) continue;

				point mid1 = mid(a[i], a[j]), mid2 = mid(a[j], a[q]);
				vect v1(a[i], a[j]), v2(a[j], a[q]);
				line l1(v1, mid1), l2(v2, mid2);

				point o;  
				if (!intersec(l1, l2, o))
					continue;
				double r = dist(a[i], o);
				vector<int> ans1, ans2;
				for (int w = 0; w < n; w++) {
					if (dist(a[w], o) == r) ans1.push_back(w);
					else ans2.push_back(w);
				}


			}
		}
	}
	return 0;
}
