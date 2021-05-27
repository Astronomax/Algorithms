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
#define Size(X) (int)X.size()
//#define int long long
#define ui unsigned int
#define mp make_pair
#define timer fghge
#define y1 yjyjyju
#define all(X) (X).begin(), (X).end()
#define endl '\n'
mt19937_64 rnd(std::chrono::system_clock::now().time_since_epoch().count());

template<typename T>
class binary_heap {
public:
	bool empty() const {
		return !data_.size();
	}

	T min_element() const {
		return data_[0];
	}

	void insert(T value) {
		data_.push_back(value);
		sift_up(data_.size() - 1);
	}

	T erase_min() {
		T res = data_[0];
		data_[0] = data_.back();
		data_.pop_back();
		sift_down(0);
		return res;
	}

private:
	void sift_up(int v) {
		int p = v / 2;
		if (data_[v] < data_[p]) {
			swap(data_[v], data_[p]);
			sift_up(p);
		}
	}
	void sift_down(int v) {
		int l = 2 * v, r = 2 * v + 1;
		if (l >= data_.size())
			return;
		int ind = l;
		if (r < data_.size() && data_[r] < data_[ind])
			ind = r;
		if (data_[ind] < data_[v]) {
			swap(data_[v], data_[ind]);
			sift_down(ind);
		}
	}
private:
	vector<int> data_;
};

signed main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	//freopen("input.txt", "r", stdin);

	int n; cin >> n;
	binary_heap a(n);
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		a.insert(x);
	}
	while (!a.empty()) {
		cout << a.min_elem() << endl;
		a.erase_min();
	}
	return 0;
}
