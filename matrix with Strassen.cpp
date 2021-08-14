#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#include <random>
#include <chrono>
using namespace std;

typedef long double C;
typedef complex<C> P;
#define X real()
#define Y imag()
#define endl '\n'
#define int long long
#define all(X) (X).begin(), (X).end()
#define rall(X) (X).rbegin(), (X).rend()
mt19937_64 rnd(chrono::system_clock::now().time_since_epoch().count());
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int lcm(int a, int b) { return a * b / gcd(a, b); }

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
	res[r1][r1] = res[r2][r2] = 0;
	res[r1][r2] = res[r2][r1] = 1;
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
		throw 1;
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
		throw 1;
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
		throw 1;
	matrix<T> res(na, ma);
	for (int i = 0; i < na; i++)
		for (int j = 0; j < ma; j++)
			res[i][j] = a[i][j] - b[i][j];
	return res;
}

template<typename T>
matrix<T> add_mod(const matrix<T> &a, const matrix<T> &b, int mod) {
	int na = a.get_n(), ma = a.get_m();
	int nb = b.get_n(), mb = b.get_m();
	if (na != nb || ma != mb)
		throw 1;
	matrix<T> res(na, ma);
	for (int i = 0; i < na; i++)
		for (int j = 0; j < ma; j++)
			res[i][j] = (a[i][j] % mod + b[i][j] % mod) % mod;
	return res;
}

template<typename T>
matrix<T> sub_mod(const matrix<T> &a, const matrix<T> &b, int mod) {
	int na = a.get_n(), ma = a.get_m();
	int nb = b.get_n(), mb = b.get_m();
	if (na != nb || ma != mb)
		throw 1;
	matrix<T> res(na, ma);
	for (int i = 0; i < na; i++)
		for (int j = 0; j < ma; j++)
			res[i][j] = (a[i][j] % mod - b[i][j] % mod + mod) % mod;
	return res;
}

template<typename T>
matrix<T> binpow(matrix<T> a, int p) {
	int n = a.get_n(), m = a.get_m();
	if (n != m)
		throw 1;
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

	matrix() = default;

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

	//matrix(matrix&& another) : matrix(another.n, another.m) {
	//	std::swap(_data, another._data);
	//}

	matrix& operator=(matrix another) {
		n = another.n;
		m = another.m;
		std::swap(_data, another._data);
		return *this;
	}

	//matrix& operator=(matrix&& another) {
	//	n = another.n;
	//	m = another.m;
	//	std::swap(_data, another._data);
	//	return *this;
	//}

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
			throw 1;

		for (int i = 0; i < na; i++)
			for (int j = 0; j < ma; j++)
				(*this)[i][j] += b[i][j];
	}

	void operator -=(const matrix &b) {
		int na = this->n, ma = this->m;
		int nb = b.get_n(), mb = b.get_m();
		if (na != nb || ma != mb)
			throw 1;

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
			throw 1;

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
			throw 1;

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
			throw 1;

		T determinator = det();
		if (!determinator)
			throw 1;

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
		int nb = r2 - r1 + 1, mb = c2 - c1 + 1;
		if (nb < 1 || mb < 1)
			throw 1;
		if (0 > r1 || r2 >= n || 0 > c1 || c2 >= m)
			throw 1;
		matrix<T> res(nb, mb);
		for (int i = 0; i < nb; i++)
			for (int j = 0; j < mb; j++)
				res[i][j] = (*this)[i + r1][j + c1];
		return res;
	}

	void insert(int r1, int r2, int c1, int c2, matrix m) {
		int nb = r2 - r1 + 1, mb = c2 - c1 + 1;
		if (nb != m.n || mb != m.m)
			throw 1;
		for (int i = 0; i < nb; i++)
			for (int j = 0; j < mb; j++)
				(*this)[r1 + i][c1 + j] = m[i][j];
	}

	void split(matrix &_11, matrix &_12, matrix &_21, matrix &_22) const {
		int mid_row = n >> 1, mid_col = m >> 1;
		_11 = crop(0, mid_row - 1, 0, mid_col - 1);
		_12 = crop(0, mid_row - 1, mid_col, m - 1);
		_21 = crop(mid_row, n - 1, 0, mid_col - 1);
		_22 = crop(mid_row, n - 1, mid_col, m - 1);
	}
private:
	T** _data = nullptr;
	int n = 0, m = 0;
};

template<typename T>
matrix<T> merge(const matrix<T> &_11, const matrix<T> &_12, const matrix<T> &_21, const matrix<T> &_22) {
	if(_11.get_n() != _12.get_n() || _21.get_n() != _22.get_n() || _11.get_m() != _21.get_m() || _12.get_m() != _22.get_m())
		throw 1;
	int nb = _11.get_n() + _21.get_n(), mb = _11.get_m() + _12.get_m();
	matrix<T> res(nb, mb);
	res.insert(0, _11.get_n() - 1, 0, _11.get_m() - 1, _11);
	res.insert(0, _12.get_n() - 1, _11.get_m(), mb - 1, _12);
	res.insert(_11.get_n(), nb - 1, 0, _21.get_m() - 1, _21);
	res.insert(_12.get_n(), nb - 1, _21.get_m(), mb - 1, _22);
	return res;
}

template<typename T>
matrix<T> mult_(const matrix<T> &a, const matrix<T> &b, int mod) {
	if (a.get_n() == 1) {
		matrix<T> res(1, 1);
		res[0][0] = (a[0][0] * b[0][0]) % mod;
		return res;
	}
	else {
		matrix<T> a11, a12, a21, a22;
		a.split(a11, a12, a21, a22);

		matrix<T> b11, b12, b21, b22;
		b.split(b11, b12, b21, b22);

		matrix<T> p1 = mult_(add_mod(a11, a22, mod), add_mod(b11, b22, mod), mod);
		matrix<T> p2 = mult_(add_mod(a21, a22, mod), b11, mod);
		matrix<T> p3 = mult_(a11, sub_mod(b12, b22, mod), mod);
		matrix<T> p4 = mult_(a22, sub_mod(b21, b11, mod), mod);
		matrix<T> p5 = mult_(add_mod(a11, a12, mod), b22, mod);
		matrix<T> p6 = mult_(sub_mod(a21, a11, mod), add_mod(b11, b12, mod), mod);
		matrix<T> p7 = mult_(sub_mod(a12, a22, mod), add_mod(b21, b22, mod), mod);

		matrix<T> c11 = add_mod(add_mod(p1, p4, mod), sub_mod(p7, p5, mod), mod);
		matrix<T> c12 = add_mod(p3, p5, mod);
		matrix<T> c21 = add_mod(p2, p4, mod);
		matrix<T> c22 = add_mod(sub_mod(p1, p2, mod), add_mod(p3, p6, mod), mod);

		return merge(c11, c12, c21, c22);
	}
}

template<typename T>
matrix<T> mult(const matrix<T> &a, const matrix<T> &b, int mod) {
	int na = a.get_n(), ma = a.get_m();
	int nb = b.get_n(), mb = b.get_m();
	if (ma != nb)
		throw 1;
	int n = (1 << (int)ceil(max(log2(max(a.get_n(), a.get_m())), log2(max(b.get_n(), b.get_m())))));
	matrix<T> normal_a(n, n), normal_b(n, n);
	normal_a.insert(0, a.get_n() - 1, 0, a.get_m() - 1, a);
	normal_b.insert(0, b.get_n() - 1, 0, b.get_m() - 1, b);
	return mult_(normal_a, normal_b, mod).crop(0, na - 1, 0, mb - 1);
}

template<typename T>
matrix<T> binpow_mod(matrix<T> a, int p, int mod) {
	int n = a.get_n(), m = a.get_m();
	if (n != m)
		throw 1;
	matrix<T> res = get_identity<T>(n);
	while (p) {
		if (p & 1) {
			res = mult(res, a, mod);
			--p;
		}
		else {
			a = mult(a, a, mod);
			p >>= 1;
		}
	}
	return res;
}

signed main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	//freopen("input.txt", "r", stdin);


	return 0;
}
