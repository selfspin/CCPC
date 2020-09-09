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
const int maxn = 100010;
const int inf = 0x3f3f3f3f;

//4.9 ST表
int f[maxn][20], cover[maxn];
int n;

void ST_prework() {
	for (int i = 1; i <= n; ++i) f[i][0] = cover[i];
	int t = log(n) / log(2) + 1;
	for (int j = 1; j < t; ++j)
		for (int i = 1; i <= n - (1 << j) + 1; ++i)
			f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
}

int ST_query(int l, int r) {
	int k = log(r - l + 1) / log(2);
	return max(f[l][k], f[r - (1 << k) + 1][k]);
}