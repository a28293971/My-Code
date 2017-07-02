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
	int cover;
	double x, l, r;
}node[Maxn << 2];
bool cmp(Line const &a, Line const &b)
{
	return a.x < b.x;
}

void build(int rt, int l, int r)
{
	node[rt].x = -1, node[rt].l = y[l], node[rt].r = y[r];
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
double query(int rt, double x, double b, double e, int flag)
{
	if (node[rt].l >= e || node[rt].r <= b) return 0;
	if (node[rt].flag)
		if (node[rt].cover > 1)
		{
			double prx = node[rt].x;
			double ans = (x - prx)*(node[rt].r - node[rt].l);
			node[rt].x = x, node[rt].cover += flag;
			return ans;
		}
		else
		{
			node[rt].x = x, node[rt].cover += flag;
			return 0;
		}
	return query(rt << 1, x, b, e, flag) + query(rt << 1 | 1, x, b, e, flag);
}
int main()
{
	int t, n, cnt;
	double x1, x2, y1, y2;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
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
		sort(line, line + cnt, cmp);
		build(1, 0, cnt - 1);
		double ans = 0;
		for (int i = 0; i < cnt; ++i)
			ans += query(1, line[i].x, line[i].ydown, line[i].yup, line[i].flag);
		printf("%.2lf\n", ans);
	}
	return 0;
}
/*
一般是求并的面积 而这道题目要求求交的面积 所以按照原来的思路 将cover>0改为cover>1即可通过
*/