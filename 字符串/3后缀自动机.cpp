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

struct state {
	int len, link;
	map<char, int> next;

    bool is_clone;
    int first_pos;//字符串第一次出现的末尾位置，从0计数
    vector<int> inv_link;
};
state st[maxn << 1];
int sz, last;

void sam_init() {
	st[0].len = 0;
	st[0].link = -1;
	sz++;
	last = 0;
}

void sam_extend(char c) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    st[cur].is_clone = false;
    st[cur].first_pos = st[cur].len - 1;

    int p = last;
    while (p != -1 && !st[p].next.count(c)) {
        st[p].next[c] = cur;
        p = st[p].link;
    }

    if (p == -1) {
        st[cur].link = 0;
    }
    else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        }
        else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            st[clone].is_clone = true;
            st[clone].first_pos = st[q].first_pos;

            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}

void sam_build_inv_link() {
    for (int v = 1; v < sz; v++)
        st[st[v].link].inv_link.push_back(v);
}

int cnt[maxn << 1];//出现次数

void find_occurtimes(int x) {
    if (!st[x].is_clone) cnt[x] = 1;
    for (int i = 0; i < st[x].inv_link.size(); ++i) {
        find_occurtimes(st[x].inv_link[i]);
        cnt[x] += cnt[st[x].inv_link[i]];
    }
}

void output_all_occurences(int v, int P_len) { //输出状态v所有出现位置
    if (!st[v].is_clone) cout << st[v].first_pos - P_len + 1 << endl;
    for (int i = 0; i < st[v].inv_link.size(); ++i)
        output_all_occurences(st[v].inv_link[i], P_len);
}

int main() {
    sam_init();
    char c = getchar();
    while (c >= 'a' && c <= 'z') { sam_extend(c); c = getchar();  }

    sam_build_inv_link();
    find_occurtimes(0);
}