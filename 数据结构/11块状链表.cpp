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

//4.11 块状链表
int n = 100010;
const int m = (int)sqrt(n);
struct dat {
	int s, a[2 * m + 5];
	dat* next;
};
dat* root = NULL;
void insert(int x, int pos) {
	if (root == NULL) {
		root = new(dat);
		root->s = 1;
		root->a[1] = x;
		return;
	}
	dat* k = root;
	while (pos > k->s && k->next != NULL) {
		pos -= k->s;
		k = k->next;
	}
	memmove(k->a + pos + 1, k->a + pos, sizeof(int) * (k->s - pos + 1));
	k->s++; k->a[pos] = x;
	if (k->s == 2 * m) {
		dat* t = new(data);
		t->next = k->next;
		k->next = t;
		memcpy(t->a + 1, k->a + m + 1, sizeof(int) * m);
		k->s = t->s = m;
	}
}
void del(int pos) {
	dat* k = root;
	while (pos > k->s && k->next != NULL) {
		pos -= k->s;
		k = k->next;
	}
	memmove(k->a + pos, k->a + pos + 1, sizeof(int) * (k->s - pos));
	k->s--;
}
int find(int pos) {
	dat* k = root;
	while (pos > k->s && k->next != NULL) {
		pos -= k->s;
		k = k->next;
	}
	return k->a[pos];
}
void destroy(dat* k) { //程序最后 destroy(root) 释放空间
	if (k->next != NULL)
		destroy(k->next);
	delete(k);
}