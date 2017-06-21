#include<algorithm>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<queue>
using namespace std;

const int maxn = 605;

struct people
{
	int father, relation;
	int same, other;//同类数目，和异类数目
	int True;//是说谎者还是诚实者
}p[maxn];

int dp[maxn][maxn];

int Find(int x)
{
	int k = p[x].father;
	if (p[x].father != x)
	{
		p[x].father = Find(k);
		p[x].relation = (p[x].relation + p[k].relation) % 2;
	}

	return p[x].father;
}

int main()
{
	int M, T, L;

	while (scanf("%d%d%d", &M, &T, &L), M + T + L)
	{
		int i, j, u, v, ru, rv, d, N = T + L, k = 1;
		char s[10]; int f[maxn];//f记录最后小集体的头结点

		for (i = 0; i <= N; i++)
		{
			p[i].father = i;
			p[i].other = 0;
			p[i].same = 1;//自己和自己是同类，所以最少也有一个
			p[i].relation = 0;
			p[i].True = 0;
		}

		while (M--)
		{
			scanf("%d%d%s", &u, &v, s);

			ru = Find(u), rv = Find(v);

			if (s[0] == 'y')
				d = 0;//0表示同类，1表示异类
			else d = 1;

			if (ru != rv)
			{
				p[ru].father = rv;
				p[ru].relation = (p[u].relation + p[v].relation + d) % 2;
			}
		}

		for (i = 1; i <= N; i++)
		{
			u = Find(i);
			if (u == i)
				f[k++] = i;//如果为根节点，则将它添加进大集合中
			else
			{
				//计算root的同类和异类
				p[u].other += p[i].relation;
				p[u].same += 1 - p[i].relation;
			}
		}

		memset(dp, 0, sizeof(dp));//初始化dp,dp[i][j]表示前i个大集合中坏人数为[j]的情况有多少种

		dp[1][p[f[1]].same] += 1;//第一个节点的初始化，不知道那个集合是坏人所以都设为有这种情况
		dp[1][p[f[1]].other] += 1;

		for (i = 2; i<k; i++)//遍历所有集合
		{
			u = f[i];
			for (j = 0; j <= N; j++)
			{
				if (dp[i - 1][j])// 如果前(i-1)个集合坏人数量为j有方案时
				{
					dp[i][p[u].same + j] += dp[i - 1][j];//同理不知道同类是好人或者是坏人 
					dp[i][p[u].other + j] += dp[i - 1][j];//使得坏人数量为（j+同类or异类）的方案数量增加
				}
			}
		}
		

		if (dp[k - 1][L] != 1 )//如果坏人数量为L的方案不止一个，则无法判断
			printf("no\n");
		else
		{
			for (i = k - 1; i>0; i--)
			{
				u = f[i];
				v = p[u].same;
				if ((i != 1 && dp[i - 1][T - v] != 0) || (i == 1 && T == v))//递归的方式 dp[i-1][T-v]!=0说明根和它的同类的小集合在好人的集合中
				{
					p[u].True = 1;
					T -= v;
				}
				else//否则说明另外一个小集合在好人的集合中
					T -= p[u].other;
			}

			for (i = 1; i <= N; i++)//从序号小到大遍历所有人
			{
				u = p[i].father;
				if (p[u].True && !p[i].relation || p[u].True == 0 && p[i].relation)//如果父节点是好人且与父节点是同类，
					printf("%d\n", i);											   //或者，父节点是坏人，与父节点是异类
			}
			printf("end\n");
		}
	}

	return 0;
}
/*
1 1
2 yes
*/