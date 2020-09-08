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

//4.6 fhqTreap
struct node {
	int l, r;
	int val, key;
	int size;
}fhq[maxn];
int cnt, root;
mt19937 rnd(233);
inline int newnode(int val) {
	fhq[++cnt].val = val;
	fhq[cnt].l = fhq[cnt].r = 0;
	fhq[cnt].key = rnd();
	fhq[cnt].size = 1;
	return cnt;
}
inline int update(int x) {
	fhq[x].size = fhq[fhq[x].l].size + fhq[fhq[x].r].size + 1;
}
void split(int now, int val, int& x, int& y) { 
	//按值分裂，左树全部小于等于给定的值，右树全部大于给定的值
	if (!now) x = y = 0;
	else {
		if (fhq[now].val <= val) {
			x = now;
			split(fhq[now].r, val, fhq[now].r, y);
		}
		else {
			y = now;
			split(fhq[now].l, val, x, fhq[now].l);
		}
		update(now);
	}
}
int merge(int x, int y) { //树x中值全比树y中值小
	if (!x || !y) return x + y;
	if (fhq[x].key > fhq[y].key) { //任意不等号都行,这里取大根堆
		fhq[x].r = merge(fhq[x].r, y);
		update(x); return x;
	}
	else {
		fhq[y].l = merge(x, fhq[y].l);
		update(y); return y;
	}
}
int x, y, z;
inline void ins(int val) {
	split(root, val, x, y);
	root = merge(merge(x, newnode(val)), y);
}
inline void del(int val) {
	split(root, val, x, z);
	split(x, val - 1, x, y);
	y = merge(fhq[y].l, fhq[y].r);//只删除一个val
	root = merge(merge(x, y), z);
}
inline int getrank(int val) {
	split(root, val - 1, x, y);
	int rank = fhq[x].size + 1;
	root = merge(x, y);
	return rank;
}
inline int getnum(int rank) {
	int now = root;
	while (now) {
		if (fhq[fhq[now].l].size + 1 == rank) break;
		else if (fhq[fhq[now].l].size >= rank)
			now = fhq[now].l;
		else {
			rank -= fhq[fhq[now].l].size + 1;
			now = fhq[now].r;
		}
	}
	return fhq[now].val;
}
inline int pre(int val) { //前驱
	split(root, val - 1, x, y);
	int now = x;
	while (fhq[now].r)
		now = fhq[now].r;
	int pre = fhq[now].val;
	root = merge(x, y);
	return pre;
}
inline void nxt(int val) { //后继
	split(root, val, x, y);
	int now = y;
	while (fhq[now].l)
		now = fhq[now].l;
	int nxt = fhq[now].val;
	root = merge(x, y);
	return nxt;
}


//文艺平衡树  维护区间翻转操作
struct Node{
	int l, r;
	int val, key;
	int size;
	bool reverse;//懒标记
}fhq[maxn];
int cnt, root;
mt19937 rnd(233);
inline int newnode(int val) {
	fhq[++cnt].val = val;
	fhq[cnt].key = rnd();
	fhq[cnt].size = 1;
	return cnt;
}
inline void update(int now) {
	fhq[now].size = fhq[fhq[now].l].size + fhq[fhq[now].r].size + 1;
}
inline void pushdown(int now) {
	swap(fhq[now].l, fhq[now].r);
	fhq[fhq[now].l].reverse ^= 1;
	fhq[fhq[now].r].reverse ^= 1;
	fhq[now].reverse = false;
}
void split(int now, int siz, int& x, int& y) {
	if (!now) x = y = 0;
	else {
		if (fhq[now].reverse) pushdown(now);
		if (fhq[fhq[now].l].size < siz)	{
			x = now;
			split(fhq[now].r, siz - fhq[fhq[now].l].size - 1, fhq[now].r, y);
		}
		else {
			y = now;
			split(fhq[now].l, siz, x, fhq[now].l);
		}
		update(now);
	}
}
int merge(int x, int y) {
	if (!x || !y) return x + y;
	if (fhq[x].key < fhq[y].key) {
		if (fhq[x].reverse) pushdown(x);
		fhq[x].r = merge(fhq[x].r, y);
		update(x);
		return x;
	}
	else {
		if (fhq[y].reverse) pushdown(y);
		fhq[y].l = merge(x, fhq[y].l);
		update(y);
		return y;
	}
}
void reverse(int l, int r) {
	int x, y, z;
	split(root, l - 1, x, y);
	split(y, r - l + 1, y, z);
	fhq[y].reverse ^= 1;
	root = merge(merge(x, y), z);
}
void ldr(int now) { //中序遍历输出
	if (!now) return;
	if (fhq[now].reverse) pushdown(now);
	ldr(fhq[now].l);
	print(fhq[now].val);
	ldr(fhq[now].r);
}