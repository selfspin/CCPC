//1.3.0 头文件
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


//1.3.1 素数筛法
bool valid[maxn];
void getPrime(int n, int& tot, int ans[maxn]) {
	memset(valid, true, sizeof(valid));
	for (int i = 2; i <= n; i++) {
		if (valid[i]) {
			tot++;
			ans[tot] = i;
		}
		for (int j = 1; (j <= tot) && (i * ans[j] < n); ++j) {
			valid[i * ans[j]] = false;
			if (i % ans[j] == 0)break;
		}
	}
}


//1.3.2 素数判定
bool test(int n, int a, int d) {
	if (n == 2)return true;
	if (n == a)return true;
	if ((n & 1) == 0)return false;
	while (!(d & 1))  d >>= 1;
	int t = pow_mod(a, d, n);//ksm
	while ((d != n - 1) && (t != 1) && (t != n - 1)) {
		t = (ll)t * t % n;
		d <<= 1;
	}
	return (t == n - 1 || (d & 1) == 1);
}
bool isPrime(int n) {
	if (n < 2)return false;
	int a[] = { 2,3,61 }; //测试集，更广的测试范围需要更大的测试集     1 <= a <= n - 1
	for (int i = 0; i <= 2; ++i)
		if (!test(n, a[i], n - 1))return false;
	return true;
}


//1.3.3 质因数分解
void factor(int n, int a[maxn], int b[maxn]; int& tot) {
	int temp, i, now;
	temp = (int)((double)sqrt(n) + 1);
	tot = 0; now = n;
	for (int i = 2; i <= temp; ++i) {
		if (now % i == 0) {
			a[++tot] = i;//质因数值
			b[tot] = 0;//质因数指数
			while (now % i) {
				++b[tot];
				now /= i;
			}
		}
	}
	if (now != 1) {
		a[++tot] = now;
		b[tot] = 1;
	}
}


//1.3.4 欧拉函数计算
int minDiv[maxn], phi[maxn], sum[maxn];
void getPhi() {
	for (int i = 1; i < maxn; ++i) {
		minDiv[i] = i;
	}
	for (int i = 2; i * i < maxn; ++i) {
		if (minDiv[i] == i) {
			for (int j = i * i; j < max; j += i)
				minDiv[j] = i;
		}
	}
	phi[1] = 1;
	for (int i = 2; i < maxn; ++i) {
		phi[i] = phi[i / minDiv[i]];
		if ((i / minDiv[i]) % minDiv[i] == 0)
			phi[i] *= minDiv[i];
		else
			phi[i] *= minDiv[i] - 1;
	}
}