#include<stdio.h>
#include<string.h>
#define Maxn 604
char ch[8];
int x, y, dp[Maxn][Maxn], root[Maxn], cnt;
struct
{
	bool from;
	int pr, ral, same, dif;
}people[Maxn];

int find(int x)
{
	if (x != people[x].pr)
	{ 
		int pre = people[x].pr;
		people[x].pr = find(people[x].pr);
		people[x].ral = (people[x].ral + people[pre].ral) % 2;
	}
	return people[x].pr;
}

int main()
{
	int n, p1, p2, fx, fy, d, u, pop, num;
	while (~scanf("%d%d%d", &n, &p1, &p2) && n+p1+p2)
	{
		pop = p1 + p2;
		for (int i = 1; i <= pop; ++i)
		{
			people[i].dif = people[i].ral = people[i].from = 0;
			people[i].pr = i, people[i].same = 1;
		}
		for (int i = 0; i < n; ++i)
		{
			scanf("%d%d%s", &x, &y, ch);
			if (x == y) continue;
			if (ch[0] == 'y') d = 0;
			else d = 1;
			fx = find(x), fy = find(y);
			if (fx != fy)
				people[fy].pr = fx, people[fy].ral = (people[x].ral + people[y].ral + d) % 2;
		}

		cnt = 1;
		for (int i = 1; i <= pop; ++i)
		{
			u = find(i);
			if (i == u)
				root[cnt++] = i;
			else if (people[i].ral)
				++people[u].dif;
			else
				++people[u].same;
		}

		memset(dp, 0, sizeof dp);
		dp[1][people[root[1]].dif] = 1;
		dp[1][people[root[1]].same] += 1;
		for (int i = 2; i < cnt; ++i)
		{
			u = root[i];
			for (int j = 0; j <= pop; ++j)
				if (dp[i - 1][j])
				{
					dp[i][j + people[u].dif] += dp[i - 1][j];
					dp[i][j + people[u].same] += dp[i - 1][j];
				}
		}

		if (dp[cnt - 1][p1] != 1)
			printf("no\n");
		else
		{
			for (int i = cnt - 1; i >= 1; --i)
			{
				u = root[i], num = people[u].same;
				if ((i != 1 && dp[i - 1][p1 - num]) || (i == 1 && p1 == num))
					people[u].from = 1, p1 -= num;
				else
					p1 -= people[u].dif;
			}
			for (int i = 1; i <= pop; ++i)
			{
				u = people[i].pr;
				if ((people[u].from && !people[i].ral) || (!people[u].from && people[i].ral))
					printf("%d\n", i);
			}
			printf("end\n");
		}
	}
	return 0;
}