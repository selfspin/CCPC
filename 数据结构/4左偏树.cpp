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

//4.4 左偏树
struct leftist_tree {

	int l, r;
	int val, dis;

	leftist_tree() {  }
	leftist_tree(int x) :l(0), r(0), val(x), dis(0) {  }

}ltt[maxn];
int tot;
int merge(int x, int y) {
	if (!x || !y) return x + y;
	if (ltt[x].val < ltt[y].val) swap(x, y);//大根堆
	ltt[x].r = merge(ltt[x].r, y);
	if (ltt[ltt[x].l].dis < ltt[ltt[x].r].dis)
		swap(ltt[x].l, ltt[x].r);
	ltt[x].dis = ltt[ltt[x].r].dis + 1;
	return x;
}
int init(int x) {
	ltt[++tot] = leftist_tree(x);
	return tot;
}
int insert(int x, int y) {
	return merge(x, init(y));
}
int top(int x) {
	return ltt[x].val;
}
int pop(int x) {
	return merge(ltt[x].l, ltt[x].r);
}