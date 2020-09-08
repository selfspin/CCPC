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

//4.5 Trie
const int charset = 26, base = 'a', maxnode = 100000;
struct trie {
	int tot, root, child[maxnode][charset];//child[i][j]:以i为根的子树，字符j连向的节点(==0 则不存在)
	bool flag[maxnode];//节点i是不是单词结尾
	trie() {
		memset(child[1], 0, sizeof(child[1]));
		flag[1] = false;
		root = tot = 1;
	}
	void insert(const char* str) {
		int* cur = &root;
		for (const char* p = str; *p; ++p) {
			cur = &child[*cur][*p - base];
			if (*cur == 0) {
				*cur = ++tot;
				memset(child[tot], 0, sizeof(child[tot]));
				flag[tot] = false;
			}
		}
		flag[*cur] = true;
	}
	bool ask(const char* str) {
		int* cur = &root;
		for (const char* p = str; *p && *cur; ++p)
			cur = &child[*cur][*p - base];
		return *cur && flag[*cur];
	}
};