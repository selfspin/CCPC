//2.5.0 头文件
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


//2.5.1 最大流Dinic算法
int n, m, s, t, tot, maxflow;
int head[maxn], nxt[maxn], ver[maxn], edge[maxn], d[maxn];
queue<int> q;
void add(int x, int y, int z) {
	ver[++tot] = y, edge[tot] = z, nxt[tot] = head[x], head[x] = tot;
	ver[++tot] = x, edge[tot] = 0, nxt[tot] = head[y], head[y] = tot;
}
bool bfs() {
	memset(d, 0, sizeof(d));
	while (q.size()) q.pop();
	q.push(s); d[s] = 1;
	while (q.size()) {
		int x = q.front(); q.pop();
		for (int i = head[x]; i; i = nxt[i]) {
			if (edge[i] && !d[ver[i]]) {
				q.push(ver[i]);
				d[ver[i]] = d[x] + 1;
				if (ver[i] == t) return 1;
			}
		}
	}
	return 0;
}
int dinic(int x, int flow) {
	if (x == t) return flow;
	int rest = flow, k;
	for (int i = head[x]; i && rest; i = nxt[i]) {
		if (edge[i] && d[ver[i]] == d[x] + 1) {
			k = dinic(ver[i], min(rest, edge[i]));
			if (!k) d[ver[i]] = 0;//剪枝
			edge[i] -= k;
			edge[i ^ 1] += k;
			rest -= k;
		}
	}
	return flow - rest;
}
int main() {
	cin >> n >> m;
	cin >> s >> t;
	tot = 1;
	for (int i = 1; i <= m; ++i) {
		int x, y, c; scanf_s("%d%d%d", &x, &y, &c);
		add(x, y, c);
	}
	int flow = 0;
	while (bfs())
		while (flow = dinic(s, inf))
			maxflow += flow;
}


//2.5.2 最小割
//待补


//2.5.3 无向图最小割Stoer-Wagner算法
//待补


//2.5.4 有上下界的网络流
//待补


//2.5.5 费用流
//最小费用最大流Edmonds-Karp算法
int cost[maxn];
int d[maxn], incf[maxn], pre[maxn], v[maxn];
int n, k, tot, s, t, maxflow, ans;
void add(int x, int y, int z, int c) {
	//正向边，初始容量z，单位费用c
	ver[++tot] = y, edge[tot] = z, cost[tot] = c;
	nxt[tot] = head[x], head[x] = tot;
	//反向边，初始容量0，单位费用-c
	ver[++tot] = x, edge[tot] = 0, cost[tot] = -c;
	nxt[tot] = head[y], head[y] = tot;
}
bool spfa() {
	queue<int> q;
	memset(d, 0x3f, sizeof(d));//INF
	memset(v, 0, sizeof(v));
	q.push(s); d[s] = 0; v[s] = 1;
	incf[s] = inf;
	while (q.size()) {
		int x = q.front(); v[x] = 0; q.pop();
		for (int i = head[x]; i; i = nxt[i]) {
			if (!edge[i]) continue;
			int y = ver[i];
			if (d[y] > d[x] + cost[i]) {
				d[y] = d[x] + cost[i];
				incf[y] = min(incf[x], edge[i]);
				pre[y] = i;
				if (!v[y]) v[y] = 1, q.push(y);
			}
		}
	}
	if (d[t] == 0x3f3f3f3f) return false;
	return true;
}
void update() {
	int x = t;
	while (x != s) {
		int i = pre[x];
		edge[i] -= incf[t];
		edge[i ^ 1] += incf[t];
		x = ver[i ^ 1];
	}
	maxflow += incf[t];
	ans += d[t] * incf[t];
}
int main() {
	cin >> n >> m;
	cin >> s >> t;
	tot = 1;
	for (int i = 1; i <= m; ++i) {
		int x, y, z, c; scanf_s("%d%d%d%d", &x, &y, &z, &c);
		add(x, y, z, c);
	}
	while (spfa()) update();
}