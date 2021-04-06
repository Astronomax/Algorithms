#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2")
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
class matrix;

template<typename T>
matrix<T> get_identity(int n) {
	matrix<T> res(n, n);
	for (int i = 0; i < n; i++)
		res[i][i] = 1;
	return res;
}

template<typename T>
matrix<T> addition_elementary(int n, int r1, int r2, T p) {
	matrix<T> res = get_identity<T>(n);
	res[r1][r2] = p;
	return res;
}

template<typename T>
matrix<T> swap_elementary(int n, int r1, int r2) {
	matrix<T> res = get_identity<T>(n);
	res[r1][r1] = 0;
	res[r2][r2] = 0;
	res[r1][r2] = 1;
	res[r2][r1] = 1;
	return res;
}

template<typename T>
matrix<T> mult_elementary(int n, int r, T p) {
	matrix<T> res = get_identity<T>(n);
	res[r][r] = p;
	return res;
}

template<typename T>
matrix<T> operator *(const matrix<T> &a, T b) {
	int n = a.get_n(), m = a.get_m();
	matrix<T> res = a;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			res[i][j] *= b;
	return res;
}

template<typename T>
matrix<T> operator *(const matrix<T> &a, const matrix<T> &b) {
	int na = a.get_n(), ma = a.get_m();
	int nb = b.get_n(), mb = b.get_m();
	if (ma != nb)
		throw std::invalid_argument("it is not possible to multiply matrices");
	matrix<T> res(na, mb);
	for (int i = 0; i < na; i++)
		for (int j = 0; j < mb; j++)
			for (int k = 0; k < ma; k++)
				res[i][j] += a[i][k] * b[k][j];
	return res;
}

template<typename T>
matrix<T> operator +(const matrix<T> &a, const matrix<T> &b) {
	int na = a.get_n(), ma = a.get_m();
	int nb = b.get_n(), mb = b.get_m();
	if (na != nb || ma != mb)
		throw std::invalid_argument("it is impossible to add matrices");
	matrix<T> res(na, ma);
	for (int i = 0; i < na; i++)
		for (int j = 0; j < ma; j++)
			res[i][j] = a[i][j] + b[i][j];
	return res;
}

template<typename T>
matrix<T> operator -(const matrix<T> &a, const matrix<T> &b) {
	int na = a.get_n(), ma = a.get_m();
	int nb = b.get_n(), mb = b.get_m();
	if (na != nb || ma != mb)
		throw std::invalid_argument("it is not possible to subtract matrices");
	matrix<T> res(na, ma);
	for (int i = 0; i < na; i++)
		for (int j = 0; j < ma; j++)
			res[i][j] = a[i][j] - b[i][j];
	return res;
}

template<typename T>
matrix<T> binpow(matrix<T> a, int p) {
	int n = a.get_n(), m = a.get_m();
	if (n != m)
		throw std::invalid_argument("it is not possible to pow a non-square matrix");
	matrix<T> res = get_identity<T>(n);
	while (p) {
		if (p & 1) {
			res *= a;
			--p;
		}
		else {
			a *= a;
			p >>= 1;
		}
	}
	return res;
}

template<typename T>
std::ostream& operator <<(std::ostream& out, const matrix<T> &mat) {
	for (int i = 0; i < mat.get_n(); i++) {
		for (int j = 0; j < mat.get_m(); j++)
			out << mat[i][j] << " ";
		out << '\n';
	}
	return out;
}

template<typename T>
std::istream& operator >>(std::istream& in, matrix<T> &mat) {
	for (int i = 0; i < mat.get_n(); i++)
		for (int j = 0; j < mat.get_m(); j++)
			in >> mat[i][j];
	return in;
}

template<typename T>
class matrix {
public:
	~matrix() {
		if (this->_data == nullptr)
			return;
		delete[] this->_data[0];
		delete[] this->_data;
	}

	matrix() {
		
	}

	matrix(int n, int m) : n(n), m(m) {
		T* temp = new T[n * m];
		std::fill(temp, temp + n * m, 0);
		this->_data = new T *[n];
		for (int i = 0; i < n; i++)
			this->_data[i] = &temp[i * m];
	}

	matrix(const matrix &another) : matrix(another.n, another.m) {
		memcpy(_data[0], another._data[0], sizeof(T) * n * m);
	}

	matrix& operator=(matrix another) {
		std::swap(_data, another._data);
		std::swap(this->n, another.n);
		std::swap(this->m, another.m);
		return *this;
	}

	T* operator[] (int index) const {
		return this->_data[index];
	}

	int get_n() const {
		return n;
	}

	int get_m() const {
		return m;
	}

	void operator *=(T b) {
		int n = this->n, m = this->m;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				(*this)[i][j] *= b;
	}

	void operator *=(const matrix &b) {
		(*this) = (*this) * b;
	}

	void operator +=(const matrix &b) {
		int na = this->n, ma = this->m;
		int nb = b.get_n(), mb = b.get_m();
		if (na != nb || ma != mb)
			throw std::invalid_argument("it is impossible to add matrices");

		for (int i = 0; i < na; i++)
			for (int j = 0; j < ma; j++)
				(*this)[i][j] += b[i][j];
	}

	void operator -=(const matrix &b) {
		int na = this->n, ma = this->m;
		int nb = b.get_n(), mb = b.get_m();
		if (na != nb || ma != mb)
			throw std::invalid_argument("it is not possible to subtract matrices");

		for (int i = 0; i < na; i++)
			for (int j = 0; j < ma; j++)
				(*this)[i][j] -= b[i][j];
	}

	bool operator ==(const matrix &b) const {
		int na = this->n, ma = this->m;
		int nb = b.get_n(), mb = b.get_m();
		if (na != nb || ma != mb)
			return 0;
		for (int i = 0; i < na; i++)
			for (int j = 0; j < ma; j++)
				if ((*this)[i][j] != b[i][j])
					return 0;
		return 1;
	}

	bool operator !=(const matrix &b) const {
		return !(*this == b);
	}

	int rank() const {
		int n = this->n, m = this->m;
		matrix<T> step_matrix = get_step_matrix();
		int j = 0, not_null_str_count = 0;

		for (int i = 0; i < n; i++) {
			for (j; j < m; j++)
				if (step_matrix[i][j] != 0)
					break;
			if (j == m)
				break;
			not_null_str_count++;
		}
		return not_null_str_count;
	}

	T det() const {
		int n = this->n, m = this->m;
		if (n != m)
			throw std::invalid_argument("it is not possible to find the determinant of a non-square matrix");

		matrix<T> step_matrix = *this;
		T res = 1;
		for (int col = 0, processed = 0; col < m; col++) {
			int not_null_row = -1;
			for (int row = processed; row < n; row++)
				if (step_matrix[row][col] != 0)
					not_null_row = row;

			if (not_null_row == -1)
				continue;

			for (int row = processed; row < n; row++) {
				if (row == not_null_row)
					continue;
				T k = step_matrix[row][col] / step_matrix[not_null_row][col];
				step_matrix = addition_elementary<T>(n, row, not_null_row, -k) * step_matrix;
			}
			if (processed != not_null_row)
				res *= -1;
			step_matrix = swap_elementary<T>(n, processed, not_null_row) * step_matrix;
			processed++;
		}
		for (int i = 0; i < n; i++)
			res *= step_matrix[i][i];
		return res;
	}

	T get_extension(int row, int col) const {
		T res = get_minor(row, col).det();
		if ((row + col) % 2 == 1)
			res *= -1;
		return res;
	}

	matrix transpose() const {
		int n = this->n, m = this->m;
		matrix res(m, n);
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				res[i][j] = (*this)[j][i];
		return res;
	}

	matrix get_minor(int row, int col) const {
		int n = this->n, m = this->m;
		if (0 > row || row >= n || 0 > col || col >= m)
			throw std::out_of_range("it is not possible to get minor of the matrix");

		matrix<T> res(n - 1, m - 1);
		for (int i = 0; i < n - 1; i++)
			for (int j = 0; j < m - 1; j++)
				res[i][j] = (*this)[i + (i >= row)][j + (j >= col)];
		return res;
	}

	matrix get_attached() const {
		int n = this->n, m = this->m;
		matrix<T> res(n, m);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				res[i][j] = get_extension(i, j);
		return res;
	}

	matrix get_opposite() const {
		int n = this->n, m = this->m;
		if (n != m)
			throw std::invalid_argument("it is not possible to find the opposite of a non-square matrix");

		T determinator = det();
		if (!determinator)
			throw std::invalid_argument("the determinator of the matrix is irreversible");

		return get_attached().transpose() * (1.0 / determinator);
	}

	matrix get_step_matrix() const {
		int n = this->n, m = this->m;
		matrix<T> res = *this;
		for (int col = 0, processed = 0; col < m; col++) {
			int not_null_row = -1;
			for (int row = processed; row < n; row++)
				if (res[row][col] != 0)
					not_null_row = row;

			if (not_null_row == -1)
				continue;

			for (int row = processed; row < n; row++) {
				if (row == not_null_row)
					continue;
				T k = res[row][col] / res[not_null_row][col];
				res = addition_elementary<T>(n, row, not_null_row, -k) * res;
			}

			res = swap_elementary<T>(n, processed, not_null_row) * res;
			processed++;
		}
		return res;
	}

	matrix get_edged_identity() const {
		matrix<T> res(n, m);
		int r = rank();
		for (int i = 0; i < r; i++)
			res[i][i] = 1;
		return res;
	}

	matrix crop(int r1, int r2, int c1, int c2) const {
		int n = this->n, m = this->m;
		int nb = r2 - r1 + 1, mb = c2 - c1 + 1;
		if (nb < 1 || mb < 1)
			throw std::invalid_argument("it is not possible to crop the matrix");

		if (0 > r1 || r2 >= n || 0 > c1 || c2 >= m)
			throw std::out_of_range("it is not possible to crop the matrix");

		matrix<T> res(nb, mb);
		for (int i = 0; i < nb; i++)
			for (int j = 0; j < mb; j++)
				res[i][j] = (*this)[i + r1][j + c1];
		return res;
	}
private:
	T** _data = nullptr;
	int n = 0, m = 0;
};

const int MAXN = 250010, LOGN = 21, mod = 1e9 + 7;
matrix<int> dp[LOGN][MAXN];

matrix<int> mult_with_mod(const matrix<int> &a, const matrix<int> &b, int mod) {
	int na = a.get_n(), ma = a.get_m();
	int nb = b.get_n(), mb = b.get_m();
	if (ma != nb)
		throw std::invalid_argument("it is not possible to multiply matrices");
	matrix<int> res(na, mb);
	for (int i = 0; i < na; i++)
		for (int j = 0; j < mb; j++)
			for (int k = 0; k < ma; k++)
				res[i][j] = (res[i][j] + ((long long)a[i][k] * (long long)b[k][j]) % mod) % mod;
	return res;
}

signed main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	//freopen("input.txt", "r", stdin);

	int n; cin >> n;
	string s; cin >> s;
	vector<matrix<int>> a(n);
	for (int i = 0; i < n; i++) {
		switch (s[i]) {
		case 'm':
			a[i] = addition_elementary<int>(5, 1, 0, 1);
			break;
		case 'a':
			a[i] = addition_elementary<int>(5, 2, 1, 1);
			break;
		case 'r':
			a[i] = addition_elementary<int>(5, 3, 2, 1);
			break;
		case 's':
			a[i] = addition_elementary<int>(5, 4, 3, 1);
			break;
		default:
			a[i] = get_identity<int>(5);
			break;
		}
	}
	int len = 1;
	for (int i = 0; i < LOGN; i++) {
		if (len > n) break;	
		for (int center = len - 1; center < n; center += 2 * len) {
			matrix<int> p = get_identity<int>(5);
			for (int j = 0; j < len && center - j >= 0; j++) {
				p = mult_with_mod(p, a[center - j], mod);
				dp[i][center - j] = p;
			}
			p = get_identity<int>(5);
			for (int j = 0; j < len && center + j + 1 < n; j++) {
				p = mult_with_mod(a[center + j + 1], p, mod);
				dp[i][center + j + 1] = p;
			}
		}
		len <<= 1;
	}
	int q; cin >> q;
	for (int i = 0; i < q; i++) {
		int l, r; cin >> l >> r; l--; r--;
		matrix<int> ans(5, 1);
		ans[0][0] = 1;
		if (l == r)
			ans = mult_with_mod(a[l], ans, mod);
		else {
			int lvl = 31 - __builtin_clz(l ^ r);
			ans = mult_with_mod(mult_with_mod(dp[lvl][r], dp[lvl][l], mod), ans, mod);
		}
		cout << ans[4][0] << endl;
	}
	return 0;
}
