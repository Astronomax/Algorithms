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
 
using namespace std;
 
typedef long double C;
typedef complex<C> P;
 
#define X real()
#define Y imag()
#define ui unsigned int
#define int long long
#define MP make_pair
#define timer fghge
#define y1 yjyjyju
#define all(X) (X).begin(), (X).end()
#define endl "\n"
 
namespace geoma{
	struct vect{
		int x, y;
 
		double polar(){
			return atan2(-1.0 * y, x * 1.0) + ((atan2(-1.0 * y, x * 1.0) < 0) ? 2 * M_PI : 0);
		}
 
		bool operator!= (vect b){
			return x != b.x || y != b.y;
		}
 
		bool operator== (vect b){
			return x == b.x && y == b.y;
		}
 
		int operator* (vect b){
			return x * b.y - b.x * y;
		}
 
		int operator ^(vect b){
			return x * b.x + y * b.y;
		}
 
		vect operator- (vect b){
			return{ x - b.x, y - b.y };
		}
 
		vect operator+ (vect b){
			return{ x + b.x, y + b.y };
		}
 
		void operator -=(vect b){
			x -= b.x;
			y -= b.y;
		}
 
		void operator +=(vect b){
			x += b.x;
			y += b.y;
		}
	};
 
	double dist(vect a, vect b){
		return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	}
 
	double ang(vect a, vect b){
		return abs(atan2(a * b, a ^ b));
	}
 
	double plosh(vector<vect> a){
		int n = a.size();
		double ans = 0;
		for (int i = 0; i < n; i++){
			int next = i + 1; next %= n;
			ans += (a[i].x - a[next].x) * (a[i].y + a[next].y) / 2;
		}
		return abs(ans);
	}
 
	double perim(vector<vect> a){
		int n = a.size();
		double ans = 0;
		for (int i = 0; i < n; i++){
			int next = i + 1; next %= n;
			ans += dist(a[i], a[next]);
		}
		return abs(ans);
	}
 
	bool cmp(vect a, vect b){
		if (a * b > 0)
			return 1;
		else if (a * b < 0)
			return 0;
		else
			return dist(a, { 0, 0 }) < dist(b, { 0, 0 });
	}
 
	vector<vect> obol(vector<vect> a){
		int n = a.size(), start = -1;
		for (int i = 0; i < n; i++)
			if (start == -1 || a[i].y < a[start].y || (a[i].y == a[start].y && a[i].x < a[start].x))
				start = i;
		vect b = a[start];
		for (auto &i : a)
			i -= b;
 
		swap(a[start], a[n - 1]);
		a.pop_back();
		sort(all(a), cmp);
		a.push_back({ 0, 0 });
 
		vector<vect> ans;
		ans.push_back({ 0, 0 });
		ans.push_back(a[0]);
 
		for (int i = 1; i < n; i++){
			int last = ans.size() - 1;
			vect pred = ans[last] - ans[last - 1], next = a[i] - ans[last];
			while (ans.size() > 1 && pred * next <= 0){
				if (ans[last] == a[i])
					break;
				ans.pop_back();
				last--;
				if (ans.size() > 1){
					pred = ans[last] - ans[last - 1];
					next = a[i] - ans[last];
				}
			}
			if (ans[last] != a[i])
				ans.push_back(a[i]);
		}
 
		for (auto &i : ans)
			i += b;
 
		return ans;
	}
};
 
using namespace geoma;
 
signed main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	freopen("hull.in", "r", stdin);
	freopen("hull.out", "w", stdout);
	//freopen("input.txt", "r", stdin);
 
	int n; cin >> n;
	vector<vect> a(n);
	for (auto &i : a)
		cin >> i.x >> i.y;
 
	vector<vect> ans = obol(a);
	cout << ans.size() - 1 << endl;
	for (int i = 0; i < ans.size() - 1; i++)
		cout << ans[i].x << " " << ans[i].y << endl;
	return 0;
}
