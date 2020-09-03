//1.1.0 头文件
#include<algorithm>
#include<bitset>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<fstream>
#include<iostream>
#include<map>
#include<queue>
#include<random>
#include<set>
#include<string>
#include<vector>
using namespace std;
typedef long long ll;
const int maxn = 1010;
const int inf = 0x3f3f3f3f;


//1.1.1 矩阵类
struct matrix {
	int n, m;//矩阵大小
	int a[maxn][maxn];//矩阵
	void clear() {
		n = m = 0;
		memset(a, 0, sizeof(a));
	}
	matrix operator +(const matrix& b) const {
		matrix tmp;
		tmp.n = n, tmp.m = m;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				tmp.a[i][j] = a[i][j] + b.a[i][j];
		return tmp;
	}
	matrix operator -(const matrix& b) const {
		matrix tmp;
		tmp.n = n, tmp.m = m;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				tmp.a[i][j] = a[i][j] - b.a[i][j];
		return tmp;
	}
	matrix operator *(const matrix& b) const {
		matrix tmp; tmp.clear();
		tmp.n = n, tmp.m = b.m;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < b.m; j++)
				for (int k = 0; k < m; k++)
					tmp.a[i][j] += a[i][k] * b.a[k][j];
		return tmp;
	}
};


//1.1.2 Guass 消元
//a      方程组对应的矩阵
//n      未知数个数
//l,ans  存储解，l[]表示是否为自由元
inline int solve(double a[][maxn], bool l[], double ans[], const int& n) {
	int res = 0, r = 0;//解空间维数res   正在进行的列数r
	for (int i = 0; i < n; i++)
		l[i] = false;
	for (int i = 0; i < n; ++i) {
		for (int j = r; j < n; ++j) {//找到一个第i列不为0的行，上移到第r行
			if (fabs(a[j][i]) > eps) {
				for (int k = i; k <= n; ++k)
					swap(a[j][k], a[r][k]);
				break;
			}
		}
		if (fabs(a[r][i]) < eps) {//这一列没有非0的数
			++res;
			continue;
		}
		for (int j = 0; j < n; ++j) {
			if (j != r && fabs(a[j][i]) > eps) {
				double tmp = a[j][i] / a[r][i];
				for (int k = i; k <= n; ++k)
					a[j][k] -= a[r][k] * tmp;
			}
		}
		l[i] = true; ++r;
	}
	for (int i = 0; i < n; ++i) {
		if (l[i])
			for (int j = 0; j < n; ++j)
				if (fabs(a[j][i]) > 0)
					ans[i] = a[j][n] / a[j][i];
	}
	return res;
}


//1.1.3 矩阵的逆
inline vector<double> operator *(vector<double> a, double b) {
	int n = a.size();
	vector<double> res(N, 0);
	for (int i = 0; i < n; ++i)
		res[i] = a[i] * b;
	return res;
}
inline vector<double> operator -(vector<double> a, vector<double> b) {
	int n = a.size();
	vector<double> res(N, 0);
	for (int i = 0; i < n; ++i)
		res[i] = a[i] - b[i];
	return res;
}
//A：原矩阵  C：A的逆矩阵  N：A的阶数
inline void inverse(vector<double> A[], vector<double> C[], int n) {
	for (int i = 0; i < n; ++i) {
		C[i] = vector<double>(n, 0);
		C[i][i] = 1;
	}
	for (int i = 0; i < n; ++i) {
		for (int j = i; j < n; ++j) {
			if (fabs(A[j][i]) > 0) {
				swap(A[i], A[j]);
				swap(C[i], C[j]);
				break;
			}
		}
		C[i] = C[i] * (1 / A[i][i]);
		A[i] = A[i] * (1 / A[i][i]);
		for (int j = 0; j < N; ++j) {
			if (j != i && fabs(A[j][i]) > 0) {
				C[j] = C[j] - C[i] * A[j][i];
				A[j] = A[j] - A[i] * A[j][i];
			}
		}
	}
}


//1.1.4 常系数线性齐次递推
//已知 f[x] = a[0]f[x - 1] + a[1]f[x - 2] + …… + a[n - 1]f[x - n] ，求f[t]
//a 常系数数组
//b 初值数组
//n 数组大小
//t 要解的项数
int solve(int a[], int b[], int n, int t) {
	matrix m, f, e;
	m.clear(), f.clear(), e.clear();
	m.n = m.m = n;
	e.n = e.m = n;
	f.n = n, f.m = 1;
	for (int i = 0; i < n - 1; ++i)
		m[i][i + 1] = 1;
	for (int i = 0; i < n; ++i) {
		m[n - 1][i] = a[i];
		e.a[i][i] = 1;
		f.a[i][0] = b[i];		
	}
	if (t < n)return f.a[t][0];
	for (t -= n - 1; t; t >>= 1) {
		if (t & 1)e = m * e;
		m = m * m;
	}
	f = e * f;
	return f.a[n - 1][0];
}