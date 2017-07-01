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
#define Maxn 10004
#define Maxm 10004
using namespace std;

bool vis[Maxn];
int tree[Maxn << 4], l[Maxn], r[Maxn], bin[Maxn << 2], ans;

void update(int rt,int l,int r,int b,int e,int c) 
{
	if (b <= l&&r <= e) 
		tree[rt] = c;
	else
	{
		if (tree[rt] != -1) 
		{
			tree[rt << 1] = tree[rt << 1 | 1] = tree[rt];
			tree[rt] = -1;
		}
		int m = (l + r) >> 1;
		if (b <= m) update(rt << 1, l, m, b, e, c);
		if (m < e)  update(rt << 1 | 1, m + 1, r, b, e, c);
	}
}
void query(int rt, int l, int r)
{
	if (tree[rt] != -1)
	{
		if (!vis[tree[rt]])
		{
			ans++;
			vis[tree[rt]] = 1;
		}
	}
	else
	{
		if (l == r) return;
		int m = (l + r) >> 1;
		query(rt << 1, l, m);
		query(rt << 1 | 1, m + 1, r);
	}
}
int main() 
{
	int n, t, cnt, tmp;
	scanf("%d", &t);
	while (t--) 
	{
		scanf("%d", &n);
		cnt = 0;
		for (int i = 0; i<n; ++i) 
		{
			scanf("%d%d", &l[i], &r[i]);
			bin[cnt++] = l[i], bin[cnt++] = r[i];
		}

		sort(bin, bin + cnt);
		tmp = 1;
		for (int i = 1; i < cnt; ++i)  //数组模拟离散化
			if (bin[i] != bin[i - 1]) bin[tmp++] = bin[i];
		cnt = tmp;
		for (int i = 1; i < tmp; ++i)//本题难点就是在离散化的时候 在差值大于1的两个点中间要再插入一个点 否则会把中间一段长度忽略掉 即用一个点来表示出中间的一段长度
			if (bin[i] != bin[i - 1] + 1) bin[cnt++] = bin[i] - 1;
		sort(bin, bin + cnt);

		mem(tree, -1);//这里不要自作聪明省内存省空间写成memset(tree,-1,4*cnt) 这样反而会直接T掉！
		for (int i = 0; i<n; ++i) 
		{
			int ll = lower_bound(bin, bin + cnt, l[i]) - bin;
			int rr = lower_bound(bin, bin + cnt, r[i]) - bin;
			update(1, 0, cnt, ll, rr, i);
		}

		mem(vis, 0);
		ans = 0;
		query(1, 0, cnt);
		printf("%d\n", ans);
	}
	return 0;
}