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

//4.8 线段树
//单点修改
int cover[maxn];

struct SegmentTree {
	int l, r;
	int dat; //维护的区间信息，这里维护区间和
}t[maxn];

void build(int p, int l, int r) { //build(1, 1, n)
	t[p].l = l, t[p].r = r;
	if (l == r) {
		t[p].dat = cover[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	t[p].dat = t[p << 1].dat + t[p << 1 | 1].dat;
}

void change(int p, int x, int v) { //change(1, x, v)
	if (t[p].l == t[p].r) {
		t[p].dat = v;
		return;
	}
	int mid = (t[p].l + t[p].r) >> 1;
	if (x <= mid) change(p << 1, x, v);
	else change(p << 1 | 1, x, v);
	t[p].dat = t[p << 1].dat + t[p << 1 | 1].dat);
}

void ask(int p, int l, int r) { //ask(1, l, r)
	if (l <= t[p].l && r >= t[p].r) return t[p].dat;
	int mid = (t[p].l + t[p].r) >> 1;
	int val = 0;
	if (l <= mid) val += ask(p << 1, l, r));
	if (r > mid) val += ask(p << 1 | 1, l, r));
	return val;
}

//区间修改
int cover[maxn];

struct SegmentTree {
	int l, r;
	int dat; //维护的区间信息，这里维护区间和
	int add; //区间修改懒标记

	#define l(x) t[x].l
	#define r(x) t[x].r
	#define sum(x) t[x].dat
	#define add(x) t[x].add

}t[maxn];

void build(int p, int l, int r) {
	t[p].l = l, t[p].r = r;
	if (l == r) {
		t[p].dat = cover[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	t[p].dat = t[p << 1].dat + t[p << 1 | 1].dat;
}

void spread(int p) { //下传懒标记
	if (add(p)) {
		sum(p << 1) += add(p) * (r(p << 1) - l(p << 1) + 1);
		sum(p << 1 | 1) += add(p) * (r(p << 1 | 1) - l(p << 1 | 1) + 1);
		add(p << 1) += add(p);
		add(p << 1 | 1) += add(p);
		add(p) = 0;
	}
}

void change(int p, int l, int r, int d) { //区间修改
	if (l >= l(p) && r >= r(p)) {
		sum(p) += d * (r(p) - l(p) + 1);
		add(p) += d;
		return;
	}
	spread(p);
	int mid = (l(p) + r(p)) >> 1;
	if (l <= mid) change(p << 1, l, r, d);
	if (r > mid) change(p << 1 | 1, l, r, d);
	sum(p) = sum(p << 1) + sum(p << 1 | 1);
}

void ask(int p, int l, int r) { 
	if (l <= l(p) && r >= r(p)) return sum(p);
	spread(p);
	int mid = (l(p) + r(p)) >> 1;
	int val = 0;
	if (l <= mid) val += ask(p << 1, l, r));
	if (r > mid) val += ask(p << 1 | 1, l, r));
	return val;
}