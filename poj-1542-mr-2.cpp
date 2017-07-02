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
#define Maxn 204
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
    double len;
}node[2000];
bool cmp(Line const &a, Line const &b)
{
    return a.x < b.x;
}

void build(int rt, int l, int r)
{
    node[rt].len = 0, node[rt].l = l, node[rt].r = r;
    node[rt].cover = 0;
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
void update(int rt, int b, int e, int cover)
{
    if (node[rt].l > e || node[rt].r < b)
        return;
    if (b <= node[rt].l&&node[rt].r <= e)
    {
        node[rt].cover += cover;
        if (node[rt].cover)
            node[rt].len = y[node[rt].r] - y[node[rt].l];
        else if (node[rt].flag)
            node[rt].len = 0;
        else
            node[rt].len = node[rt << 1].len + node[rt << 1 | 1].len;
    }
    else
    {
        update(rt << 1, b, e, cover);
        update(rt << 1 | 1, b, e, cover);
        if (node[rt].cover)
            node[rt].len = y[node[rt].r] - y[node[rt].l];
        else if (node[rt].flag)
            node[rt].len = 0;
        else
            node[rt].len = node[rt << 1].len + node[rt << 1 | 1].len;
    }
}
int main()
{
    int n, cnt, cas = 0, tmp;
    double x1, x2, y1, y2;
    while (~scanf("%d", &n)&&n)
    {
        cnt = 0;
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
        for (int i = 0; i < cnt - 1; ++i)
        {
            int l = lower_bound(y, y + tmp, line[i].ydown) - y;
            int r = lower_bound(y, y + tmp, line[i].yup) - y;
            update(1, l, r, line[i].flag);
            ans += node[1].len*(line[i + 1].x - line[i].x);
        }
        printf("Test case #%d\nTotal explored area: %.2lf\n\n", ++cas, ans);
    }
    return 0;
}
/*
这解法使用dp递归的方法 所以求答案时每次求的是node[1]的答案
主要思路是用一个len来记录这个区间y的长度差 毕竟是用来求面积的
然后再根据条件 cover>0的时候可以更新这个叶子的len 然后层层递归上去 把符合条件的区间全加起来
要注意的是当更新到最底部的叶子时 也是就(l+1==r)的时候且又因为cover为0 没有被覆盖到 所以直接len=0
至于比第一个代码快的原因就是 这个只搜索到符合区间的时候就停止了即(b<=l&&r<=e) 而不是找到最后一片叶子
*/