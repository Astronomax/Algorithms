#include <bits/stdc++.h>
#include <random>
#include <chrono>

//#pragma comment(linker, "/STACK:16777216")

using namespace std;

typedef long double C;
typedef complex<C> P;

#define X real()
#define Y imag()

#define ui unsigned int
#define int long long
#define mp make_pair
#define timer fghge
#define y1 yjyjyju
#define have(X, a) (X.find(a) != X.end())
#define Size(X) (int)X.size()
#define all(X) (X).begin(), (X).end()
#define endl '\n'
mt19937_64 rnd(std::chrono::system_clock::now().time_since_epoch().count());

class matrix
{
public:
	int r, c;
	vector<vector<int>> a;

	matrix() {

	}

	matrix(int r, int c) {
		this->r = r; this->c = c;
		a.assign(r, vector<int>(c));
	}
};

bool comp(matrix &a, matrix &b) {
	return a.c == b.r;
}

int normSize(matrix &a) {
	return ceil(log2((double)max(a.r, a.c)));
}

void getNorm(matrix &a, int n) {
	matrix norm = matrix(n, n);

	for (int i = 0; i < a.r; i++)
		for (int j = 0; j < a.c; j++)
			norm.a[i][j] = a.a[i][j];
	a = norm;
}

void getFrame(int r1, int r2, int c1, int c2, matrix &a, matrix &b) {
	int r = r2 - r1, c = c2 - c1;
	b = matrix(r, c);
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			b.a[i][j] = a.a[r1 + i][c1 + j];
}

void insert(int r1, int r2, int c1, int c2, matrix &a, matrix &b) {
	int r = r2 - r1, c = c2 - c1;
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			a.a[r1 + i][c1 + j] = b.a[i][j];
}

void split(matrix &a, matrix &_11, matrix &_12, matrix &_21, matrix &_22) {
	int n = a.r >> 1;
	_11 = matrix(n, n);
	_12 = matrix(n, n);
	_21 = matrix(n, n);
	_22 = matrix(n, n);

	getFrame(0, n, 0, n, a, _11);
	getFrame(0, n, n, 2 * n, a, _12);
	getFrame(n, 2 * n, 0, n, a, _21);
	getFrame(n, 2 * n, n, 2 * n, a, _22);
}

void merge(matrix &a, matrix &_11, matrix &_12, matrix &_21, matrix &_22) {
	int n = _11.r;
	a = matrix(n << 1, n << 1);

	insert(0, n, 0, n, a, _11);
	insert(0, n, n, 2 * n, a, _12);
	insert(n, 2 * n, 0, n, a, _21);
	insert(n, 2 * n, n, 2 * n, a, _22);
}

matrix operator+ (matrix &a, matrix &b) {
	matrix res(a.r, a.c);
	for (int i = 0; i < a.r; i++)
		for (int j = 0; j < a.c; j++)
			res.a[i][j] = a.a[i][j] + b.a[i][j];
	return res;
}

matrix operator- (matrix &a, matrix &b) {
	matrix res(a.r, a.c);
	for (int i = 0; i < a.r; i++)
		for (int j = 0; j < a.c; j++)
			res.a[i][j] = a.a[i][j] - b.a[i][j];
	return res;
}

matrix stupid(matrix &a, matrix &b) {
	int r = a.r, c = b.c, n = a.c;
	matrix res = matrix(r, c);
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			for (int q = 0; q < n; q++)
				res.a[i][j] += a.a[i][q] * b.a[q][j];
	return res;
}

matrix operator* (matrix &a, matrix &b) {
	if (!comp(a, b))
		return a;

	bool flag = 0;
	int n = 1 << max(normSize(a), normSize(b));
	int r = a.r, c = b.c;

	if (a.r != n && a.c != n || b.r != n || b.c != n) {
		getNorm(a, n);
		getNorm(b, n);
		flag = 1;
	}

	if (n <= 1)
		return stupid(a, b);

	matrix res;

	matrix a11, a12, a21, a22;
	split(a, a11, a12, a21, a22);
	matrix b11, b12, b21, b22;
	split(b, b11, b12, b21, b22);

	auto p1 = (a11 + a22) * (b11 + b22);
	auto p2 = (a21 + a22) * b11;
	auto p3 = a11 * (b12 - b22);
	auto p4 = a22 * (b21 - b11);
	auto p5 = (a11 + a12) * b22;
	auto p6 = (a21 - a11) * (b11 + b12);
	auto p7 = (a12 - a22) * (b21 + b22);

	auto c11 = (p1 + p4) + (p7 - p5);
	auto c12 = p3 + p5;
	auto c21 = p2 + p4;
	auto c22 = (p1 - p2) + (p3 + p6);

	merge(res, c11, c12, c21, c22);
	
	if (flag) {
		matrix temp(r, c);
		getFrame(0, r, 0, c, res, temp);
		res = temp;
	}

	return res;
}

void operator*= (matrix &a, matrix &b) {
	a = a * b;
}

ostream& operator<<(ostream& cout, matrix &matr)
{
	for (auto &i : matr.a) {
		for (auto &j : i)
			cout << j << " ";
		cout << endl;
	}
	return cout;
}
istream& operator >> (istream& cin, matrix &matr)
{
	for (auto &i : matr.a)
		for (auto &j : i)
			cin >> j;
	return cin;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	//freopen("input.txt", "r", stdin);
	//freopen("input.txt", "w", stdout);

	int r1, c1, r2, c2; cin >> r1 >> c1 >> r2 >> c2;
	matrix a(r1, c1), b(r2, c2);
	cin >> a >> b;
	cout << a * b;
	return 0;
}
