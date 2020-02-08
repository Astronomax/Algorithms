#pragma GCC optimize("Ofast, no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("section-anchors")
#pragma GCC optimize("profile-values,profile-reorder-functions,tracer")
#pragma GCC optimize("vpt")
#pragma GCC optimize("rename-registers")
#pragma GCC optimize("move-loop-invariants")
#pragma GCC optimize("unswitch-loops")
#pragma GCC optimize("function-sections")
#pragma GCC optimize("data-sections")
#pragma GCC optimize("branch-target-load-optimize")
#pragma GCC optimize("branch-target-load-optimize2")
#pragma GCC optimize("btr-bb-exclusive")
 
 
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
 
typedef double C;
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
 
int n, m;
long long p;
 
class matrix
{
public:
    int r, c;
    int a[140][140];
 
    matrix() {
        for(int i = 0; i < 140; i++)
        for(int j = 0; j < 140; j++)
        a[i][j] = 0;
    }
 
    matrix(int r, int c) {
        this->r = r; this->c = c;
        for(int i = 0; i < 140; i++)
        for(int j = 0; j < 140; j++)
        a[i][j] = 0;
    }
};
 
ostream& operator<<(ostream& cout, matrix &matr)
{
    for (int i = 0; i < matr.r; i++) {
        for (int j = 0; j < matr.c; j++)
            cout << matr.a[i][j] << " ";
        cout << endl;
    }
    return cout;
}
istream& operator >> (istream& cin, matrix &matr)
{
    for (int i = 0; i < matr.r; i++)
        for (int j = 0; j < matr.c; j++)
            cin >> matr.a[i][j];
    return cin;
}
 
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
 
void pls (matrix &a, matrix &b, matrix &res) {
    res = matrix(a.r, a.c);
    for (int i = 0; i < a.r; i++)
        for (int j = 0; j < a.c; j++)
            res.a[i][j] = (a.a[i][j] % p + b.a[i][j] % p) % p;
}
 
void mns (matrix &a, matrix &b, matrix &res) {
    res = matrix(a.r, a.c);
    for (int i = 0; i < a.r; i++)
        for (int j = 0; j < a.c; j++)
            res.a[i][j] = (a.a[i][j] % p - b.a[i][j] % p + p) % p;
}
 
void stupid(matrix &a, matrix &b, matrix &res) {
    int r = a.r, c = b.c, n = a.c;
    res = matrix(r, c);
   
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            for (int q = 0; q < n; q++)
                res.a[i][j] = (res.a[i][j] + (long long)a.a[i][q] % p * (long long)b.a[q][j] % p) % p;
}
 
void mult (matrix &a, matrix &b, matrix &res) {
    if (!comp(a, b))
        res = a;
 
    bool flag = 0;
    int n = 1 << max(normSize(a), normSize(b));
    int r = a.r, c = b.c, r1 = a.r, c1 = a.c, r2 = b.r, c2 = b.c;
 
    if(n > 100){
        stupid(a, b, res);
        return;
    }
   
    if (a.r != n && a.c != n || b.r != n || b.c != n) {
        getNorm(a, n);
        getNorm(b, n);
        flag = 1;
    }
 
    if (n <= 1) {
        stupid(a, b, res);
        if (flag) {
            matrix temp(r, c);
            getFrame(0, r, 0, c, res, temp);
            res = temp;
 
            a.r = r1; a.c = c1;
         
            b.r = r2; b.c = c2;
        }
        return;
    }
 
    matrix a11, a12, a21, a22;
    split(a, a11, a12, a21, a22);
    matrix b11, b12, b21, b22;
    split(b, b11, b12, b21, b22);
 
    matrix p1, p2, p3, p4, p5, p6, p7;
 
    matrix temp1, temp2;
    pls(a11, a22, temp1); pls(b11, b22, temp2); mult(temp1, temp2, p1);
    pls(a21, a22, temp1); mult(temp1, b11, p2);
    mns(b12, b22, temp1); mult(a11, temp1, p3);
    mns(b21, b11, temp1); mult(a22, temp1, p4);
    pls(a11, a12, temp1);  mult(temp1, b22, p5);
    mns(a21, a11, temp1); pls(b11, b12, temp2);  mult(temp1, temp2, p6);
    mns(a12, a22, temp1); pls(b21, b22, temp2); mult(temp1, temp2, p7);
 
    matrix c11, c12, c21, c22;
    pls(p1, p4, temp1); mns(p7, p5, temp2); pls(temp1, temp2, c11);
    pls(p3, p5, c12);
    pls(p2, p4, c21);
    mns(p1, p2, temp1); pls(p3, p6, temp2); pls(temp1, temp2, c22);
 
    merge(res, c11, c12, c21, c22);
 
    if(flag) {
        matrix temp(r, c);
        getFrame(0, r, 0, c, res, temp);
        res = temp;
 
        a.r = r1; a.c = c1;
 
        b.r = r2; b.c = c2;
    }
}
 
matrix a, ans, res;
 
void binpow() {
    for (int i = 0; i < n; i++)
        res.a[i][i] = 1;
 
    while (m) {
        if (m & 1) {
            mult(a, res, ans);
            res = ans;
            --m;
        }
        else {
            mult(a, a, ans);
            a = ans;
            m >>= 1;
        }
    }
}
 
signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    freopen("mpow.in", "r", stdin);
    freopen("mpow.out", "w", stdout);
    //freopen("input.txt", "r", stdin);
 
    cin >> n >> m >> p;
 
    a = matrix(n, n);
    res = matrix(n, n);
    cin >> a;
 
    binpow();
    cout << res;
    return 0;
}
