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

//4.2 并查集
struct DisjointSet {
	vector<int> father, rank;

	DisjointSet(int n) :father(n), rank(n) {
		for (int i = 0; i < n; ++i) {
			father[i] = i;
			rank[i] = 1;
		}
	}

	int find(int v) {
		return father[v] = father[v] == v ? v : find(father[v]);
	}

	void merge(int x, int y) {
		int a = find(x), b = find(y);
		if (rank[a] < rank[b]) {
			father[a] = b;
			rank[b] += rank[a];
		}
		else {
			father[b] = a;
			rank[a] += rank[b];
		}
	}
};