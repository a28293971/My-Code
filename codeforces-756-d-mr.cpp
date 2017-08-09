#include<iostream>
#include<cstdio>
#include<map>
#include<cstring>
#include<cmath>
#include<vector>
#include<algorithm>
#include<set>
#include<bitset>
#include<string>
#include<queue>
#include<stack>
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
#define mid ((l+r)>>1)
#define lson rt<<1,l,m
#define rson rt<<1|1,m+1,r
#define Maxn  152
#define Maxm 152
#define MOD 10007
using namespace std;

int n, m;
struct Edge//定义边
{
	int u, v, w;
	bool operator<(Edge const &a)//比大小
	{
		return w < a.w;
	}
}edge[Maxm];
void mul(bitset<Maxn> *a, bitset<Maxn> const *b)
{
	bitset<Maxn> r[Maxn];
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			if (a[i][j])
				r[i] |= b[j];//矩阵乘法
	memcpy(a, r, sizeof r);
}
void poww(bitset<Maxn> *a, int k)
{
	bitset<Maxn> r[Maxn];
	for (int i = 1; i <= n; ++i)
		r[i][i] = 1;
	while (k)//快速幂
	{
		if (k & 1)
			mul(r, a);
		mul(a, a);
		k >>= 1;
	}
	memcpy(a, r, sizeof r);
}
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i)
		scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].w);
	sort(edge + 1, edge + 1 + m);//根据所需的最短飞行次数排序

	bitset<Maxn> tmp[Maxn], g[Maxn], ari[Maxn];//g为目前状态的图，ari为是否可到达的图
	int now = 0, ans = inf, u, v, w, dis[Maxn][Maxn];
	mem(dis, 0x3f);
	for (int i = 0; i <= n; ++i)//初始化
		dis[i][i] = 0, ari[i][i] = 1;
	for (int i = 1; i <= m; ++i)//遍历每一条航线 floyd算法
	{
		u = edge[i].u, v = edge[i].v, w = edge[i].w;
		for (int j = 1; j <= n; ++j)
			for (int k = 1; k <= n; ++k)
				dis[j][k] = Min(dis[j][k], dis[j][u] + dis[v][k] + 1);//添加边后更新最短路
		memcpy(tmp, g, sizeof tmp);
		poww(tmp, w - now);//由定理 有向邻接矩阵的n次幂 如果点非零 说明ij两点n步可达
		mul(ari, tmp);
		for (int j = 1; j <= n; ++j)
			if (ari[1][j] && dis[j][n] != inf)
				ans = Min(ans, dis[j][n] + w);//再次floyd更新答案
		now = w;//更新到当前飞行的次数
		g[u][v] = 1;//u到v有边说明u到v连通
	}

	if (ans == inf)
		puts("Impossible");
	else
		printf("%d\n", ans);
	return 0;
}