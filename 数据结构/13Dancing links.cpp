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
#include<set>
#include<string>
#include<vector>
using namespace std;
typedef long long ll;
const int maxn = 7100;
const int maxm = 710;

int n, m;
int cnt;
int colnum[maxm];//每列有多少个元素

struct node {
	int up, down, left, right;
	int row, col;
}nodes[maxn];
#define u(id) nodes[id].up
#define d(id) nodes[id].down
#define l(id) nodes[id].left
#define r(id) nodes[id].right
#define rw(id) nodes[id].row
#define cl(id) nodes[id].col

void init(int x, int y) {
	for (int i = 1; i <= y; ++i)
		nodes[i] = node({ i, i, i - 1, i + 1, 0, i });
	r(y) = 0;
	nodes[0] = node{ 0,0,y,1,0,0 };
}
void insert(int row) {
	int a[510];
	int num = 0;
	for (int i = 1; i <= m; i++) {
		int x; scanf_s("%d", &x);
		if (x == 1)
			a[++num] = i;
	}
	for (int i = 1; i <= num; ++i) {
		int col = a[i];
		nodes[cnt + i] = node({ u(col),col,cnt + i - 1,cnt + i + 1 ,row,col });
		d(u(col)) = cnt + i;
		u(col) = cnt + i;
		++colnum[col];
	}
	l(cnt + 1) = cnt + num;
	r(cnt + num) = cnt + 1;
	cnt += num;
}

void remove_col(int c) { //删除这一列以及相交的所有行
	r(l(c)) = r(c);
	l(r(c)) = l(c);
	for (int i = d(c); i != c; i = d(i)) {
		for (int j = r(i); j != i; j = r(j)) {
			u(d(j)) = u(j);
			d(u(j)) = d(j);
			--colnum[cl(j)];
		}
	}
}
void resume_col(int c) { //恢复
	r(l(c)) = c;
	l(r(c)) = c;
	for (int i = u(c); i != c; i = u(i)) {
		for (int j = r(i); j != i; j = r(j)) {
			u(d(j)) = j;
			d(u(j)) = j;
			++colnum[cl(j)];
		}
	}
}

vector<int> ans;

bool dance() {
	if (r(0) == 0) return true;
	int now_col = r(0);
	for (int i = r(now_col); i != 0; i = r(i))
		if (colnum[i] < colnum[now_col]) now_col = i; //找到元素最少的列
	remove_col(now_col);
	for (int i = d(now_col); i != now_col; i = d(i)) {
		ans.push_back(rw(i));
		for (int j = r(i); j != i; j = r(j))
			remove_col(cl(j));
		if (dance()) {
			for (int j = l(i); j != i; j = l(j))
				resume_col(cl(j));
			return true;
		}
		ans.pop_back();
		for (int j = l(i); j != i; j = l(j))
			resume_col(cl(j));
	}
	resume_col(now_col);
	return false;
}

int main() {
	scanf_s("%d%d", &n, &m);
	cnt = m;
	init(n, m);
	for (int i = 1; i <= n; ++i) {
		insert(i);
	}
	ans.clear();
	if (dance()) {
		//cout << ans.size();
		for (int i = 0; i < ans.size(); ++i) {
			cout << ans[i];
			if (i != ans.size() - 1) cout << ' ';
			else cout << endl;
		}
	}
	else cout << "No Solution!" << endl;
}
