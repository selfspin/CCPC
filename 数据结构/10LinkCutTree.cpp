//感谢 不分解的AgOH 大佬！  此代码转自他的Github,做了一些更改
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

//4.10 Link Cut Tree
struct Node {
    int fa, ch[2], val, res;   //res是异或结果
    bool tag;                  //翻转懒标记
}spl[maxn];
#define ls(x) (spl[x].ch[0])
#define rs(x) (spl[x].ch[1])
#define fa(x) (spl[x].fa)
#define ident(x,f) (rs(f) == x)                  //查询x是f的哪个儿子
#define connect(x,f,s) spl[fa(x) = f].ch[s] = x  //x作为f的s儿子
#define update(x) spl[x].res = spl[ls(x)].res ^ spl[rs(x)].res ^ spl[x].val //更新异或和
#define ntroot(x) (ls(fa(x)) == x || rs(fa(x)) == x)  //判断结点是否为Splay的根

inline void pushdw(int x) {         //懒标记下传
    if (!spl[x].tag) return;
    swap(ls(x), rs(x));
    if (ls(x)) spl[ls(x)].tag ^= 1;
    if (rs(x)) spl[rs(x)].tag ^= 1;
    spl[x].tag = 0;
}
void pushall(int x) {               //头递归，从上到下下传所有懒标记
    if (ntroot(x)) pushall(fa(x));
    pushdw(x);
}

inline void rotate(int x) {         //Splay基操
    int f = fa(x), ff = fa(f), k = ident(x, f);
    connect(spl[x].ch[k ^ 1], f, k);
    fa(x) = ff;
    if (ntroot(f)) spl[ff].ch[ident(f, ff)] = x; //不能忘记判断，关系到虚实边
    connect(f, x, k ^ 1);
    update(f), update(x);
}
inline void splay(int x) {          //Splay基操，都是伸展到根结点
    pushall(x);                     //要先把上面的懒标记全都下传
    while (ntroot(x)) {
        int f = fa(x), ff = fa(f);
        if (ntroot(f)) ident(f, ff) ^ ident(x, f) ? rotate(x) : rotate(f);
        rotate(x);
    }
}
inline void access(int x) {         //从x到原树根结点拉一条实链
    for (int y = 0; x; x = fa(y = x))  {      //y为上一个Splay的根
       splay(x);                    //伸展到当前Splay的根
       rs(x) = y;                   //右儿子连上上一个Splay的根
       update(x);                   //别忘更新＞﹏＜
    }
}

inline void mkroot(int x)   {       //给原树换根
    access(x);                      //先拉实链，拉好后x一定在Splay的最右（深度最大）
    splay(x);                       //再伸展，伸展后x必定没有右儿子
    spl[x].tag ^= 1;                //翻转拉出来这条实链，使深度顺序翻转
}
inline int findroot(int x)  {       //寻找结点在原树的根
    access(x);                      //先拉实链
    splay(x);                       //再伸展
    while (spl[x].tag && rs(x) || !spl[x].tag && ls(x)) {
        //因为根结点必定深度最小，所以不停往左找就OK了
        pushdw(x);                  //别忘了下传
        x = ls(x);
    }
    splay(x);                       //用来保证时间复杂度，防止卡链
    return x;
}

void modify(int x, int d) {
    splay(x);
    spl[x].val = d;
    update(x);
}

inline void link(int x, int y)  {   //连边，不保证数据合法
    mkroot(x);                      //换根
    if (findroot(y) == x) return;   //如果y所在的树的根结点是x，那说明两者在一棵树上
    fa(x) = y;
}
inline void cut(int x, int y)  {    //断边，不保证数据合法
    mkroot(x);                      //换根
    //如果y跟x不在一棵树上 or x和y之间不是紧紧挨着的，return
    //注意这里findroot后由于保证复杂度的一句伸展，导致刚才被换成根的x成为了Splay的根结点
    //又因为x在原树中是根结点，深度最小，所以在Splay中一定是x为根结点y为其右儿子
    if (findroot(y) != x || fa(y) != x || ls(y)) return;
    fa(y) = rs(x) = 0;              //双向断边
    update(x);                      //别忘更新＞﹏＜
}

inline void split(int x, int y) {   //把x--y的路径拆出来
    mkroot(x);                      //换根
    access(y);                      //拉实链
    splay(y);                       //伸展
    //此时y必定没有右儿子且左儿子是一条到x的实链，所以访问y就可以作任何关于这条链的操作了
}