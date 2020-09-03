//1.2.0 头文件
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


//1.2.1 欧几里得算法
int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}


//1.2.2 扩展欧几里得
//解x，y    ax + by = gcd(a, b);
int extend_gcd(int a, int b, int& x, int& y) {
	if (b == 0) {
		x = 1; y = 0;
		return a;
	}
	int r = extend_gcd(b, a % b, y, x);
	y -= x * (a / b);
	return r;
}


//1.2.3 单变元模线性方程
//求x    ax = b(mod n)
vector<ll> line_mod_equation(ll a, ll b, ll n) {
	ll x, y;
	ll d = extend_gcd(a, n, x, y);
	vector<ll> ans;
	ans.clear();
	if (b % d) {
		x %= n; x += n; x %= n;
		ans.push_back(x * (b / d) % (n / d));
		for (ll i = 1; i < d; ++i)
			ans.push_back((ans[0] + i * n / d) % n);
	}
	return ans;
}


//1.2.4 中国剩余定理
//求出 x = ai(mod mi) (0 <= i < n) 的解x    其中mi两两互质
int CRT(int a[], int m[], int n) {
	int M = 1;
	for (int i = 0; i < n; ++i)M *= m[i];
	int ret = 0;
	for (int i = 0; i < n; ++i) {
		int x, y;
		int tm = M / m[i];
		extend_gcd(tm, m[i], x, y);
		ret = (ret + tm * x * a[i]) % M;
	}
	return (ret + M) % M;
}