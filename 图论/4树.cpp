//2.4.0 头文件
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


//2.4.1 LCA
int d[maxn], dist[maxn], f[maxn][20];//f[i][j]：点i的第2^j辈祖先
int ver[maxn], head[maxn], nxt[maxn], edge[maxn];
int n;
int t = int(log(n) / log(2)) + 1;//放在主函数里
queue<int> q;
void bfs() { //预处理
	q.push(1); d[1] = 1;
	while (q.size()) {
		int x = q.front(); q.pop();
		for (int i = head[x]; i; i = nxt[i]) {
			int y = ver[i];
			if (d[y]) continue;
			d[y] = d[x] + 1;
			dist[y] = dist[x] + edge[i];
			f[y][0] = x;
			for (int j = 1; j < t; j++) //上界按照题意更改
				f[y][j] = f[f[y][j - 1]][j - 1];
			q.push(y);
		}
	}
}
int lca(int x, int y) {
	if (d[x] > d[y])swap(x, y);
	for (int i = t; i >= 0; i--)
		if (d[f[y][i]] >= d[x]) y = f[y][i];
	if (x == y) return x;
	for (int i = t; i >= 0; i--)
		if (f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
	return f[x][0];
}


//2.4.2 Kruskal
struct rec { 
	int x, y, z;
	friend bool operator <(const rec& a, const rec& b) {
		return a.z < b.z;
	}
}edge[maxn]; int used[maxn];
int fa[maxn], n, m, ans;
int get(int x) {
	if (x == fa[x])return x;
	return fa[x] = get(fa[x]);
}
void kruskal() {
	sort(edge + 1, edge + m + 1);
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= m; i++) {
		int x = get(edge[i].x);
		int y = get(edge[i].y);
		if (x == y)continue;
		fa[x] = y; used[i] = 1;
		ans += edge[i].z;
	}
}


//2.4.3 Prim
int a[maxn][maxn], d[maxn], n, m, ans;
bool v[maxn];
void prim() {
	memset(d, 0x3f, sizeof(d));
	memset(v, 0, sizeof(v));
	d[1] = 0;
	for (int i = 1; i < n; i++) {
		int x = 0;
		for (int j = 1; j <= n; j++)
			if (!v[j] && (x == 0 || d[j] < d[x])) x = j;
		v[x] = 1;
		for (int y = 1; y <= n; y++)
			if (!v[y]) d[y] = min(d[y], a[x][y]);
	}
	for (int i = 2; i <= n; i++) ans += d[i];
}


//2.4.4 树的直径
//dp
void dp(int x) {
	v[x] = 1;
	for (int i = head[i]; i; i = nxt[i]) {
		int y = ver[i];
		if (v[y]) continue;
		dp(y);
		ans = max(ans, d[x] + d[y] + edge[i]);
		d[x] = max(d[x], d[y] + edge[i]);
	}
}
int find_diameter() {
	ans = 0;
	dp(1);
	return ans;
}
//2次dfs
int v = 0, ans = 0;
int dist[maxn];
void dfs(int fa, int x, int d) {
	dist[x] = d;
	if (d > ans) ans = d, v = x;
	for (int i = head[x]; i; i = nxt[i]) {
		int y = ver[x];
		if (y != fa) dfs(x, y, d + edge[i]);
	}
}
int find_diameter() {	
	dfs(-1, 1, 0);
	dfs(-1, v, 0);
	return ans;
}