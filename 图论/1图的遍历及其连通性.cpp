//2.1.0 头文件
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


//2.1.1 邻接表存图
int head[maxn], nxt[maxn], ver[maxn], edge[maxn];
int tot;
void add(int x, int y, int z) {
	ver[++tot] = y; edge[tot] = z;
	nxt[tot] = head[x]; head[x] = tot;
}
void visit() {
	for (int i = head[x]; i; i = nxt[i]) {
		int y = ver[i], z = edge[i];
		//……
	}
}


//2.1.2 割点和桥
