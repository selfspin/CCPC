//2.2.0 头文件
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


//2.2.1 Dijkstra
int dis[maxn], g[maxn][maxn], n;
bool v[maxn];
void dijkstra() {
	for (int i = 1; i <= n; ++i)dis[i] = inf;
	dis[1] = 0;
	memset(v, 0, sizeof(v));
	for (int i = 1; i <= n; ++i) {
		int mark = -1, mindis = inf;
		for (int j = 1; j <= n; ++j) {
			if (!v[j] && dis[j] < mindis) {
				mindis = dis[j];
				mark = j;
			}
		}
		v[mark] = 1;
		for (int j = 1; j <= n; ++j)
			if (!v[j])
				dis[j] = min(dis[j], dis[mark] + g[mark][j]);
	}
}


//2.2.2 SPFA
int n, m, src;//图的点数，边数，源点
int head[maxn], ver[maxn], edge[maxn], nxt[maxn], d[maxn];
int tot;
queue<int> q;
bool v[maxn];
void spfa() {
	memset(d, 0x3f, sizeof(d));
	memset(v, 0, sizeof(v));
	d[src] = 0; v[src] = 1;
	q.push(src);
	while (q.size()) {
		int x = q.front(); q.pop();
		v[x] = 0;
		for (int i = head[x]; i; i = nxt[i]) {
			int y = ver[i], z = edge[i];
			if (d[y] > d[x] + z) {
				d[y] = d[x] + z;
				if (!v[y])
					q.push(y), v[y] = 1;
			}
		}
	}
}


//2.2.3 Floyd
int d[maxn][maxn], n, m;
void floyd() {
	memset(d, 0x3f, sizeof(d));
	for (int i = 1; i <= n; ++i)d[i][i] = 0;
	for (int i = 1; i <= m; ++i) {
		int x, y, z;
		cin >> x >> y >> z;
		d[x][y] = min(d[x][y], z);
	}
	for (int k = 1; k <= n; ++k)
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}


//2.2.4 DAG(有向无环图)上的最短/长路
int topo[maxn], cnt;
int d[maxn];
int n, m;
void topsort() {
	queue<int> q;
	for (int i = 1; i <= n; ++i)
		if (deg[i] == 0)q.push(i);
	while (q.size()) {
		int x = q.front(); q.pop();
		topo[++cnt] = x;
		for (int i = head[x]; i; i = nxt[i]) {
			int y = ver[i];
			if (--deg[y] == 0)q.push(y);
		}
	}
}
void dag_path(int n, int start) {
	topsort();
	memset(d, 0x3f, sizeof(d));//最长路就初始化负无穷，下面更新改成<
	d[start] = 0;
	for (int i = 1; i <= n; i++) {
		int x = topo[i];
		for (int j = head[x]; j; j = nxt[j]) {
			int y = ver[i], z = edge[i];
			if (d[y] > d[x] + z)
				d[y] = d[x] + z;
		}
	}
}


//2.2.6 欧拉回路
int stack[maxn], ans[maxn];//模拟系统栈，答案栈
bool vis[maxn];//记录边是否访问  边是成对存的:(2,3),(4,5)……
int n, m, top, t;
void euler() {
	stack[++top] = 1;
	while (top > 0) {
		int x = stack[top], i = head[x];
		while (i && vis[i])i = nxt[i];//找到尚未访问的边
		if (i) { //沿着这条边模拟递归过程，标记该边，并更新表头
			stack[++top] = ver[i];
			vis[i] = vis[i ^ 1] = true;
			head[x] = nxt[i];
		}
		else { //x相连的所有边均已访问，模拟回溯过程，并记录在答案栈中
			top--;
			ans[++t] = x;
		}
	}
}
