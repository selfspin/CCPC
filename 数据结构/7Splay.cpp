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

//4.7 Spaly
struct splaytree {
	int cnt, root, type[maxn], fa[maxn];
	int childs[maxn][2], size[maxn];
	int stack[maxn], reversed[maxn];

	void clear() {
		root = 0;
		size[0] = 0;
		cnt = 1;
	}

	int malloc() {
		type[cnt] = 2;
		childs[cnt][0] = childs[cnt][1] = 0;
		size[cnt] = 1;
		reversed[cnt] = 0;
		return cnt++;
	}

	void update() {
		size[x] = size[childs[x][0]] + 1 + size[childs[x][1]];
	}

	void pass(int x) { //下传翻转懒标记
		if (reversed[x]) {
			swap(childs[x][0], childs[x][1]);
			type[childs[x][0]] = 0;
			reversed[childs[x][0]] ^= 1;
			type[childs[x][1]] = 1;
			reversed[childs[x][1]] ^= 1;
			reversed[x] = 0;
		}
	}

	void rotate(int x) {
		int t = type[x], y = fa[x], z = childs[x][1 - t];
		type[x] = type[y];
		fa[x] = fa[y];
		if (type[x] != 2) {
			childs[fa[x]][type[x]] = x;
		}
		type[y] = 1 - t;
		fa[y] = x;
		childs[x][1 - t] = y;
		if (z) {
			type[z] = t;
			fa[z] = y;
		}
		childs[y][t] = z;
		update(y); update(x);
	}

	void splay(int x) {
		int stackcnt = 0;
		stack[stackcnt++] = x;
		for (int i = x; type[i] != 2; i = fa[i]) {
			stack[stackcnt++] = fa[i];
		}
		for (int i = stackcnt - 1; i >= 0; --i) {
			pass(stack[i]);
		}
		while (type[x] != 2) {
			int y = fa[x];
			if (type[x] == type[y])
				rotate(y);
			else
				rotate(x);
			if (type[x] == 2) break;
			rotate(x);
		}
	}

	int find(int x, int rank) {
		while (1) {
			pass(x);
			if (size[childs[x][0]] + 1 == rank) break;
			if (rank <= size[childs[x][0]]) x = childs[x][0];
			else {
				rank -= size[childs[x][0]] + 1;
				x = childs[x][1];
			}
		}
		return x;
	}

	void split(int& x, int& y, int a) { //x初始为树根  分裂后x大小为a
		y = find(x, a + 1);
		splay(y);
		x = childs[y][0];
		type[x] = 2;
		childs[y][0] = 0;
		update(y);
	}
	void split3(int& x, int& y, int& z, int a, int b) {
		//x初始为树根  分裂后x为前a-1个，y为a到b，z为b之后的
		split(x, z, b);
		split(x, y, a - 1);
	}

	void merge(int& x, int y) {
		x = find(x, size[x]);
		splay(x);
		childs[x][1] = y;
		type[y] = 1;
		fa[y] = x;
		update(x);
	}
	void merge3(int& x, int y, int z) {
		merge(y, z);
		merge(x, y);
	}

	int getrank(int x) {
		splay(x);
		root = x;
		return size[x][0];
	}

	void reverse(int a, int b) {
		int x, y;
		split3(root, x, y, a, b);
		reversed[x] ^= 1;
		merge3(root, x, y);
	}
};