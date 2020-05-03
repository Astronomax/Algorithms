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
#define int long long
#define mp make_pair
#define timer fghge
#define y1 yjyjyju
#define all(X) (X).begin(), (X).end()
#define endl '\n'
mt19937_64 rnd(std::chrono::system_clock::now().time_since_epoch().count());

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

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	int a, b, c; cin >> a >> b >> c;
	
	int g = gcd(a, b);

	if (c % g != 0) 
		cout << "Impossible";
	else {
		int x, y;
		extgcd(a, b, x, y);
		x *= c / g; y *= c / g;

		if (x > 0) {
			int k = x / (b / g);
			x -= k * (b / g);
			y += k * (a / g);
		}
		else if (x < 0) {
			int k = -(x / (b / g));
			x += k * (b / g);
			y -= k * (a / g);
			while (x < 0) {
				x += (b / g);
				y -= (a / g);
			}
		}
		cout << x << " " << y;
	}
	return 0;
}
