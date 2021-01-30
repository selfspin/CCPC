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
const int maxn = 10010;

const int N = 1000010;

char s[N];
int n, sa[N], rk[N];
//sa[i]:���к�׺������iС�ĺ�׺�ı��
//rk[i]:��ʾ��׺i��������
int oldrk[N << 1], id[N], px[N], cnt[N];
//px[i] = rk[id[i]]������������������Խ� px��

bool cmp(int x, int y, int w) {
    return oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w];
}

//���� �������� ��������

int main() {
    int i, m = 300, p, w;

    scanf_s("%s", s + 1, N);
    n = strlen(s + 1);
    for (i = 1; i <= n; ++i) ++cnt[rk[i] = s[i]];
    for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
    for (i = n; i >= 1; --i) sa[cnt[rk[i]]--] = i;

    for (w = 1; w < n; w <<= 1, m = p) {  // m=p �����Ż���������ֵ��
        for (p = 0, i = n; i > n - w; --i) id[++p] = i;
        for (i = 1; i <= n; ++i)
            if (sa[i] > w) id[++p] = sa[i] - w;
        memset(cnt, 0, sizeof(cnt));
        for (i = 1; i <= n; ++i) ++cnt[px[i] = rk[id[i]]];
        for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
        for (i = n; i >= 1; --i) sa[cnt[px[i]]--] = id[i];
        memcpy(oldrk, rk, sizeof(rk));
        for (p = 0, i = 1; i <= n; ++i)
            rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? p : ++p;
    }

    for (i = 1; i <= n; ++i) printf("%d ", sa[i]);

    return 0;
}