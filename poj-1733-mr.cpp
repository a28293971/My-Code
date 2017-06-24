#include<iostream>
#include<stdio.h>
#include<map>
#include<string.h>
#include<cmath>
#include<vector>
#include<algorithm>
#include<set>
#include<string>
#include<queue>
#define iNF 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f
#define Min(a,b) ((a)<(b)?(a):(b))
#define Max(a,b) ((a)>(b)?(a):(b))
#define mem(a,b) memset(a,b,sizeof(a))
#define LL long long
#define Prii pair<int,int>
#define sqr(a) ((a)*(a))
#define Maxn 5004
#define Maxm 100005
using namespace std;

int pr[Maxn * 2], sum[Maxn * 2] = { 0 }, n, m, a[Maxn * 2];
struct
{
	int l, r, d;
}Data[Maxn];

int find(int x)
{
	if (pr[x] != x)
	{
		int pre = pr[x];
		pr[x] = find(pr[x]);
		sum[x] = sum[x] ^ sum[pre];
	}
	return pr[x];
}

int main()
{
	char ch[8];
	int x, y, fx, fy, cnt = 0, i;
	scanf("%d%d", &n, &m);
	for (i = 0; i < m; ++i)
	{
		scanf("%d%d%s", &Data[i].l, &Data[i].r, ch);
		if (ch[0] == 'e') Data[i].d = 0;
		else Data[i].d = 1;
		a[cnt++] = --Data[i].l, a[cnt++] = Data[i].r;//每个位置放入a中 之后要进行离散化
	}
	sort(a, a + cnt);//排序
	cnt = unique(a, a + cnt) - a;//去重 且顺便把非重复的个数算出来 算是一个骚操作
	for (i = 0; i<cnt; ++i) pr[i] = i;//构建并查集
	for (i = 0; i<m; ++i)
	{
		x = lower_bound(a, a + cnt, Data[i].l) - a, y = lower_bound(a, a + cnt, Data[i].r) - a;//得到相对位置
		fx = find(x), fy = find(y);
		if (fx != fy)
			pr[fy] = fx, sum[fy] = sum[x] ^ sum[y] ^ Data[i].d;//懒得%2了 所以奇偶直接用位运算
		else if ((sum[x] == sum[y] && Data[i].d) || (sum[x] != sum[y] && !Data[i].d))//同为偶，异为奇
			break;
	}
	printf("%d\n", i);
	return 0;
}
/*
本题设了一个坑，由于总序列长度太长，不能用以往的方法来做，所以这次增加了一个概念 “离散化” 也就是说把原本的数据转成相对的位置
由于问题总数才5000个 所以他最多描述5000*2个点 于是最多有10000个相对的位置 处理这些相对位置就和原来的方法一样了
离散化思路：
1.先把数据读入一个数组a[n]
2.去重 这里的做法使用STL的功能 也就是先sort()排序后 再用unique()把相邻重复的数字去掉 注意unique返回的是最后一个非重复数字后边的地址
3.取值 这里可以做一下处理 用另一个数组b[n]来存储 b[i]=lower_bound(a,a+n,a[i])-a 这种样子a[i]的值就被存储到相对位置b的i中了 相对位置的序号是0,1,2,3,...
       如果序号想从1开始就要用upper_bound() 或者lower_bound()后再加个1也行
*/

