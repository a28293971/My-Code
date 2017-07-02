#include<iostream>
#include<cstdio>
#include<map>
#include<cstring>
#include<cmath>
#include<vector>
#include<algorithm>
#include<set>
#include<string>
#include<queue>
#include<iomanip>
#define PI 3.1415926535898
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f
#define DINF 0x4343434343434343
#define Abs(a) ((a)>0? (a):-(a))
#define sqr(a) ((a)*(a))
#define Min(a,b) ((a)<(b)?(a):(b))
#define Max(a,b) ((a)>(b)?(a):(b))
#define mem(a,b) memset(a,b,sizeof(a))
#define LL long long
#define Prii pair<int,int>
#define lson rt<<1,l,m
#define rson rt<<1|1,m+1,r
#define Maxn 2004
#define Maxm 10004
using namespace std;

double y[Maxn];
struct Line
{
    int flag;
    double x, yup, ydown;
}line[Maxn];
struct
{
    bool flag;
    int cover, l, r;
    double once, more;
}node[Maxn << 2];
bool cmp(Line const &a, Line const &b)
{
    return a.x < b.x;
}

void build(int rt, int l, int r)
{
    node[rt].cover = node[rt].once = node[rt].more = 0;
    node[rt].l = l, node[rt].r = r;
    if (l + 1 == r)
        node[rt].flag = 1;
    else
    {
        node[rt].flag = 0;
        int m = (l + r) >> 1;
        build(rt << 1, l, m);
        build(rt << 1 | 1, m, r);
    }
}
void pushup(int rt)
{
    if (node[rt].cover >= 2)
    {
        node[rt].once = 0;
        node[rt].more = y[node[rt].r] - y[node[rt].l];
    }
    else if (node[rt].cover == 1)
    {
        if (node[rt].flag)
            node[rt].more = 0;
        else
            node[rt].more = node[rt << 1].more + node[rt << 1 | 1].more + node[rt << 1].once + node[rt << 1 | 1].once;
        node[rt].once = y[node[rt].r] - y[node[rt].l] - node[rt].more;
    }
    else
    {
        if (node[rt].flag)
            node[rt].more = node[rt].once = 0;
        else
        {
            node[rt].more = node[rt << 1].more + node[rt << 1 | 1].more;
            node[rt].once = node[rt << 1].once + node[rt << 1 | 1].once;
        }
    }
}
void update(int rt, int b, int e, int cover)
{
    if (b <= node[rt].l&&node[rt].r <= e)
    {
        node[rt].cover += cover;
        pushup(rt);
    }
    else
    {
        if (node[rt].flag) return;
        int m = (node[rt].l + node[rt].r) >> 1;
        if (b <= m) update(rt << 1, b, e, cover);//!
        if (m < e) update(rt << 1 | 1, b, e, cover);
        pushup(rt);
    }
}
int main()
{
    int n, cnt, tmp, t;
    double x1, x2, y1, y2;
    scanf("%d", &t);
    while (t--)
    {
        cnt = 0;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
        {
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            y[cnt] = y1;
            line[cnt].x = x1, line[cnt].ydown = y1, line[cnt].yup = y2;
            line[cnt++].flag = 1;
            y[cnt] = y2;
            line[cnt].x = x2, line[cnt].ydown = y1, line[cnt].yup = y2;
            line[cnt++].flag = -1;
        }
        sort(y, y + cnt);
        tmp = unique(y, y + cnt) - y;
        build(1, 0, tmp - 1);
        sort(line, line + cnt, cmp);
        double ans = 0;
        update(1, lower_bound(y, y + tmp, line[0].ydown) - y, lower_bound(y, y + tmp, line[0].yup) - y, line[0].flag);
        for (int i = 1; i < cnt; ++i)
        {
            ans += node[1].more*(line[i].x - line[i - 1].x);
            update(1, lower_bound(y, y + tmp, line[i].ydown) - y, lower_bound(y, y + tmp, line[i].yup) - y, line[i].flag);
        }
        printf("%.2lf\n", ans);
    }
    return 0;
}
/*
这道题目的第二种方法，也是用dp回溯的思想 
而且根据题目的要求 覆盖两次 所以要用一个变量记录被覆盖一次的范围和被覆盖两次的范围 即once和more
然后需要知道一个规律，当这个区间cover>1的时候 即被覆盖了两次 所以这个区间被覆盖的面积就是区间长度了 并且要一次覆盖的面积变为0
当这个区间cover==1的时候 这个区间的more就等于子区间里once和more的长度了 因为如果子区间已经被覆盖过了 即有cover 再加上本区间再覆盖一次 所以肯定是覆盖两次的面积了
当然 如果这个区间是 最后的叶子节点 那么他没有子区间 就不可能被覆盖两次了
然后这个区间被覆盖一次的部分就是总长里没有被覆盖到两次的部分 即node[rt].once = y[node[rt].r] - y[node[rt].l] - node[rt].more
最后当cover==0的时候 如果是最后的叶子节点的话 那没什么好说肯定once和more都是0
但是当它不是最后的叶子节点的话 那他的once和more就被它的子区间决定了 它的子区间有多少它就有多少

*/