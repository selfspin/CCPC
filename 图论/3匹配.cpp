//2.3.0 头文件
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


//2.3.1 匈牙利算法(增广路)
//二分图染色法判定
int head[maxn], nxt[maxn], ver[maxn], edge[maxn];
int v[maxn];
int dfs(int x, int color) {
	v[x] = color;
	for (int i = head[x]; i; i = nxt[i]) {
		int y = ver[i];
		if (!v[y]) {
			if (!dfs(y, 3 - color))
				return 0;
		}
		else if (v[y] == color)
			return 0;
	}
	return 1;
}
int main() {
	for (int i = 1; i <= n; i++)
		if (v[i] == 0) dfs(i, 1);
}
//匈牙利算法
int visit[maxn], match[maxn];
int ans;
bool dfs(int x) {
	for (int i = head[x]; i; i = nxt[i]) {
		int y = ver[i];
		if (!visit[y]) {
			visit[y] = 1;
			if (!match[y] || dfs(match[y])) {
				match[y] = x;
				return true;
			}
		}
	}
	return false;
}
int main() {
	for (int i = 1; i <= n; i++) { //n是二分图其中任意一边的点
		memset(visit, 0, sizeof(visit));
		if (dfs(i)) ans++;
	}
}


//2.3.2 Hopcroft-Karp算法
//待补


//2.3.3 KM算法
//听说不如费用流，那就先不写了qwq


//2.3.4 一般图最大匹配
//在费用流处写