//感谢 不分解的AgOH 大佬！  此代码转自他的Github,做了一些更改
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
//const int maxn = 100010;
const int inf = 0x3f3f3f3f;

//4.12 树链剖分
const int maxn = 1e5 + 5;
const int maxm = maxn * 2;

int tot, head[maxn], ver[maxm], nxt[maxm], edge[maxm];

inline void add(int u, int v) {
    ver[++tot] = v, nxt[tot] = head[u], head[u] = tot;
    ver[++tot] = u, nxt[tot] = head[v], head[v] = tot;
}
int v[maxn];//点权
int fa[maxn], dep[maxn], siz[maxn], son[maxn]; //父节点  深度  大小  重儿子
void dfs1(int u, int f) { //搜索节点大小、深度、父节点、重儿子
    fa[u] = f;
    dep[u] = dep[f] + 1;
    siz[u] = 1;
    int maxsize = -1;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = ver[i];
        if (v == f) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > maxsize) {
            maxsize = siz[v];
            son[u] = v;
        }
    }
}
int tim, dfn[maxn], top[maxn], w[maxn];//时间戳  重链头  dfs序
void dfs2(int u, int t) { //划分重链，找出dfs序
    dfn[u] = ++tim;
    top[u] = t;
    w[tim] = v[u];
    if (!son[u]) return;
    dfs2(son[u], t);
    for (int i = head[u]; i; i = nxt[i]) {
        int v = ver[i];
        if (v == fa[u] || v == son[u])
            continue;
        dfs2(v, v);
    }
}

struct node { //建立在dfs序上的线段树
    int l, r, f, val;  //区间[l,r]  懒标记  维护的权值和
} sgt[maxn * 4];
inline int ls(int k) { return k << 1; }
inline int rs(int k) { return k << 1 | 1; }
inline void update(int k) { sgt[k].val = sgt[ls(k)].val + sgt[rs(k)].val; }

inline void pushdown(int k) { //下传懒标记
    sgt[ls(k)].f += sgt[k].f;
    sgt[rs(k)].f += sgt[k].f;
    sgt[ls(k)].val += (sgt[ls(k)].r - sgt[ls(k)].l + 1) * sgt[k].f;
    sgt[rs(k)].val += (sgt[rs(k)].r - sgt[rs(k)].l + 1) * sgt[k].f;
    sgt[k].f = 0;
}
void build(int k, int l, int r) {
    sgt[k].l = l, sgt[k].r = r;
    if (l == r) {
        sgt[k].val = w[l];
        return;
    }
    int m = (l + r) >> 1;
    build(ls(k), l, m);
    build(rs(k), m + 1, r);
    update(k);
}
void modify(int k, int x, int y, int z) { //区间[x,y]加上z
    int l = sgt[k].l, r = sgt[k].r;
    if (x <= l && y >= r) {
        sgt[k].f += z;
        sgt[k].val += (r - l + 1) * z;
        return;
    }
    if (sgt[k].f) pushdown(k);
    int m = (l + r) >> 1;
    if (x <= m) modify(ls(k), x, y, z);
    if (y > m)  modify(rs(k), x, y, z);
    update(k);
}
int query(int k, int x, int y) {  //查询区间[x,y]
    int l = sgt[k].l, r = sgt[k].r;
    if (x <= l && y >= r) return sgt[k].val;
    if (sgt[k].f) pushdown(k);
    int sum = 0, m = (l + r) >> 1;
    if (x <= m) sum += query(ls(k), x, y);
    if (y > m)  sum += query(rs(k), x, y);
    return sum;
}

void mchain(int x, int y, int z) { //x到y的链上所有节点加z
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        modify(dfn[top[x]], dfn[x], z);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    modify(dfn[x], dfn[y], z);
}
int qchain(int x, int y) { //查询x到y的链上节点权值和
    int ret = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        ret += query(dfn[top[x]], dfn[x]);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    ret += query(dfn[x], dfn[y]);
    return ret;
}
inline void mson(int x, int z) { //x为根的子树上所有节点加z
    modify(dfn[x], dfn[x] + siz[x] - 1, z);
}
inline int qson(int x) { //查询x为根的子树上所有节点权值和
    return query(dfn[x], dfn[x] + siz[x] - 1);
}