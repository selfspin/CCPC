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

//4.3 树状数组
int tree[maxn]; int n;
inline int lowbit(int x) {
	return x & -x;
}
void add(int x, int val) {
	for (; x <= n; x += lowbit(x))
		tree[x] += val;
}
int ask(int x) {
	int sum = 0;
	for (; x; x -= lowbit(x))
		sum += tree[x];
	return sum;
}