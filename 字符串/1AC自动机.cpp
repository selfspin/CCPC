//#pragma comment(linker,"/STACK:1024000000,1024000000") 
#include<algorithm>
#include<bitset>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<deque>
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
const ll mod = 1000007;
const int maxn = 1000010;
const int maxtot = 500010;

struct Aho {
	struct state {
		int next[26];
		int fail, cnt;
	}stateTable[maxtot];

	int size;

	queue<int> que;

	void init() {
		while (que.size()) que.pop();
		for (int i = 0; i < maxtot; ++i) {
			memset(stateTable[i].next, 0, sizeof(stateTable[i].next));
			stateTable[i].fail = stateTable[i].cnt = 0;
		}
		size = 1;
		stateTable[0].cnt = -1;
	}

	void insert(char* S) {
		int n = strlen(S);
		int now = 0;
		for (int i = 0; i < n; ++i) {
			char c = S[i];
			if (!stateTable[now].next[c - 'a'])
				stateTable[now].next[c - 'a'] = size++;
			now = stateTable[now].next[c - 'a'];
		}
		stateTable[now].cnt++;
	}

	void build() {
		stateTable[0].fail = -1;
		que.push(0);
		while (que.size()) {
			int u = que.front();
			que.pop();
			for (int i = 0; i < 26; ++i) {
				if (stateTable[u].next[i]) {
					if (u == 0) stateTable[stateTable[u].next[i]].fail = 0;
					else {
						int v = stateTable[u].fail;
						while (v != -1) {
							if (stateTable[v].next[i]) {
								stateTable[stateTable[u].next[i]].fail = stateTable[v].next[i];
								break;
							}
							v = stateTable[v].fail;
						}
						if (v == -1) stateTable[stateTable[u].next[i]].fail = 0;
					}
					que.push(stateTable[u].next[i]);
				}
			}
		}
	}

	int Get(int u) {
		int res = 0;
		while (stateTable[u].cnt != -1) {
			res += stateTable[u].cnt;
			stateTable[u].cnt = -1;
			u = stateTable[u].fail;
		}
		return res;
	}

	int match(char* S){
		int n = strlen(S);
		int res = 0, now = 0;
		for (int i = 0; i < n; ++i) {
			char c = S[i];
			if (stateTable[now].next[c - 'a'])
				now = stateTable[now].next[c - 'a'];
			else {
				int p = stateTable[now].fail;
				while (p != -1 && stateTable[p].next[c - 'a'] == 0)
					p = stateTable[p].fail;
				if (p == -1) now = 0;
				else now = stateTable[p].next[c - 'a'];
			}
			if (stateTable[now].cnt != -1)
				res += Get(now);
		}
		return res;
	}
}aho;

int t, n;
char s[maxn];

int main() {
	cin >> t;
	while (t--) {
		aho.init();
		scanf_s("%d", &n);
		for (int i = 0; i < n; ++i) {
			scanf_s("%s", s, maxn);
			aho.insert(s);
		}
		aho.build();
		scanf_s("%s", s, maxn);
		printf("%d\n", aho.match(s));
	}
}