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

class binary_heap {
public:
	binary_heap(int n) {
		data_ = new int[n];
		capacity_ = n;
	}

	~binary_heap() {
		if (data_ != nullptr)
			delete[] data_;
	}

	bool empty() {
		return !size_;
	}

	int min_elem() {
		return data_[0];
	}

	void insert(int value) {
		++size_;
		data_[size_ - 1] = value;
		sift_up(size_ - 1);
	}

	void erase_min() {
		--size_;
		data_[0] = data_[size_];
		sift_down(0);
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
		if (l >= size_)
			return;
		int ind = l;
		if (r < size_ && data_[r] < data_[ind])
			ind = r;
		if (data_[v] > data_[ind]) {
			swap(data_[v], data_[ind]);
			sift_down(ind);
		}
	}
private:
	int *data_ = nullptr;
	int size_ = 0, capacity_ = 0;
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
