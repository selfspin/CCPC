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


//2.1.2 割边和割点
//割边判定
int dfn[maxn], low[maxn];
bool bridge[maxn * 2]; int n, m, num;
void tarjan(int x, int in_edge) {
	dfn[x] = low[x] = ++num;
	for (int i = head[x]; i; i = nxt[i]) {
		int y = ver[i];
		if (!dfn[y]) {
			tarjan(y, i);
			low[x] = min(low[x], low[y]);
			if (low[y] > dfn[x])
				bridge[i] = bridge[i ^ 1] = true;
		}
		else if (i != (in_edge ^ 1))
			low[x] = min(low[x], dfn[y]);
	}
}
int main() {
	for (int i = 1; i <= n; ++i)
		if (!dfn[i])tarjan(i, 0);//可能有多个连通块
}
//割点判定
int dfn[maxn], low[maxn];
bool cut[maxn]; int n, m, root, num;
void tarjan(int x) {
	dfn[x] = low[x] = ++num;
	int flag = 0;
	for (int i = head[x]; i; i = nxt[i]) {
		int y = ver[i];
		if (!dfn[y]) {
			tarjan(y);
			low[x] = min(low[x], low[y]);
			if (low[y] >= dfn[x]) {
				flag++;
				if (x != root || flag > 1)cut[x] = true;
			}
		}
		else low[x] = min(low[x], dfn[y]);
	}
}
int main() {
	for (int i = 1; i <= n; ++i)
		if (!dfn[i])root = i, tarjan(i);//可能有多个连通块
}


//2.1.3 双连通分量
//边双连通分量
int c[maxn], dcc;//c[x]表示点x所属边双连通分量的编号
void dfs(int x) {
	c[x] = dcc;
	for (int i = head[x]; i; i = nxt[i]) {
		int y = ver[i];
		if (c[y] || bridge[i])continue; //dfs不走桥
		dfs(y);
	}
}
int hc[maxn], vc[maxn * 2], nc[maxn * 2], tc;
void add_c(int x, int y) {
	vc[++tc] = y, nc[tc] = x, hc[x] = tc;
}
int main() {
	for (int i = 1; i <= n; ++i)
		if (!dfn[i]) tarjan(i, 0);
	for (int i = 1; i <= n; ++i) //先求出所有的桥再搜出所有的边双
		if (!c[i]) ++dcc, dfs(i);
	//缩点
	tc = 1;
	for (int i = 2; i <= tot; ++i) { 
		int x = ver[i ^ 1], y = ver[i];
		if (c[x] == c[y])continue;
		add_c(c[x], c[y]);
	}
}
//点双连通分量
int dfn[maxn], low[maxn], stack[maxn], top;
bool cut[maxn]; int n, m, root, num, cnt;
vector<int> dcc[maxn];
void tarjan(int x) {
	dfn[x] = low[x] = ++num;
	stack[++top] = x;
	if (x == root && head[x] == 0) {
		dcc[++cnt].push_back(x);
		return;
	}
	int flag = 0;
	for (int i = head[x]; i; i = nxt[i]) {
		int y = ver[i];
		if (!dfn[y]) {
			tarjan(y);
			low[x] = min(low[x], low[y]);
			if (low[y] >= dfn[x]) {
				flag++;
				if (x != root || flag > 1)cut[x] = true;
				cnt++;
				int z;
				do {
					z = stack[top--];
					dcc[cnt].push_back(z);
				} while (z != y);
				dcc[cnt].push_back(x);
			}
		}
		else low[x] = min(low[x], dfn[y]);
	}
}
int new_id[maxn]; 
int hc[maxn], vc[maxn * 2], nc[maxn * 2], tc;
void add_c(int x, int y) {
	vc[++tc] = y, nc[tc] = x, hc[x] = tc;
}
int main() {
	for (int i = 1; i <= n; ++i)
		if (!dfn[i])root = i, tarjan(i);
	//缩点
	num = cnt;
	for (int i = 1; i <= n; ++i) //给每个割点一个新编号
		if (cut[i]) new_id[i] = ++num;
	//建新图，从每个v-DCC到它包含的所有割点连边
	tc = 1; 
	for (int i = 1; i <= cnt; ++i) {
		for (int j = 0; j < dcc[i].size(); ++j) {
			int x = dcc[i][j];
			if (cut[x]) {
				add_c(i, new_id[x]);
				add_c(new_id[x], i);
			}
			else c[x] = i; //除割点外，其他点仅属于一个v-DCC
		}
	}
}


//2.1.4 极大强连通分量
int dfn[maxn], low[maxn];
int stack[maxn], ins[maxn], c[maxn];//c[i]:i所在强连通分量编号
vector<int> scc[maxn];//强连通分量中的所有点
int n, m, num, top, cnt;
void tarjan(int x) {
	dfn[x] = low[x] = ++num;
	stack[++top] = x, ins[x] = 1;
	for (int i = head[x]; i; i = nxt[i]) {
		int y = ver[i];
		if (!dfn[y]) {
			tarjan(y);
			low[x] = min(low[x], low[y]);
		}
		else if (ins[y])
			low[x] = min(low[x], dfn[y]);
	}
	if (dfn[x] == low[x]) {
		cnt++; int y;
		do {
			y = stack[top--]; ins[y] = 0;
			c[y] = cnt; scc[cnt].push_back(y);
		} while (x != y);
	}
}
int hc[maxn], vc[maxn * 2], nc[maxn * 2], tc;
void add_c(int x, int y) {
	vc[++tc] = y, nc[tc] = x, hc[x] = tc;
}
int main() {
	for (int i = 1; i <= n; ++i)
		if (!dfn[i]) tarjan(i); //多个连通块
	//缩点
	for (int x = 1; x <= n; ++x) {
		for (int i = head[x]; i; i = nxt[i]) {
			int y = ver[i];
			if (c[x] == c[y]) continue;
			add_c(c[x], c[y]);
		}
	}
}


//2.1.5 拓扑排序
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


//2.1.6 2-SAT
int vis[maxn];
int c[maxn];//存每个变量所在强联通分量序号
int opp[maxn];//存每个变量取值的另一值
int val[maxn];//存每个变量的取值
bool two_sat() {
	for (int i = 1; i <= 2 * n; ++i)
		if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= n; ++i) {
		int j = i + n;
		if (c[i] == c[j])return false;
		opp[i] = i + n;
		opp[i + n] = i;
	}
	for (int i = 1; i <= 2 * n; ++i)//tarjan算法得到的SCC编号本来就满足缩点后的有向无环图中自底向上的拓扑序
		val[i] = c[i] > c[opp[i]];
}
int main() {
	int i, p, j, q;
	while (~scanf_s("%d%d%d%d", &i, &p, &j, &q)) { //若i赋值p，则j赋值q   p,q属于{0,1}  有N个变量
		add(i + p * n, j + q * n);
		add(j + (1 - q) * n, i + (1 - p) * n);
	}
	two_sat();
}