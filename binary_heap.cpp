#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <complex>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <functional>
#include <algorithm>
#include <stack>
#include <numeric>
#include <set>

#define all(X) (X).begin(), (X).end()
//#define int long long
#define m_p make_pair
#define endl '\n'
using namespace std;

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

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	return 0;
}
