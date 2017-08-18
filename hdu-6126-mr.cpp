#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <bitset>
#include <string>
#include <queue>
#include <stack>
#include<iomanip>
#include<ctime>
#define PI 3.1415926535898
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f
#define Dinf 0x434343434343434
#define sqr(a) ((a) * (a))
#define mem(a, b) memset(a, b, sizeof(a))
#define EPS(a, b) (abs(a - b) <= eps ? 1 : 0)
#define mid ((l + r) >> 1)
#define lson rt << 1, l, m
#define rson rt << 1 | 1, m + 1, r
#define maxn 2544
#define maxm 6471936
#define MOD 1000000007
#define eps 1e-6
using namespace std;
using LL = long long;
using Pii = pair<int, int>;
//#pragma comment(linker, "/STACK:1024000000,1024000000")

//inline void read(int &x)
//{
//	bool f = 0; char ch = getchar(); x = 0;
//	while (ch < '0' || ch > '9') ch = getchar(), f = (ch == '-');
//	while (ch >= '0' && ch <= '9')
//		x = (x << 1) + (x << 3) + ch - 48, ch = getchar();
//	if (f) x = -x;
//}
//inline void read(LL &x)
//{
//	bool f = 0; char ch = getchar(); x = 0;
//	while (ch < '0' || ch > '9') ch = getchar(), f = (ch == '-');
//	while (ch >= '0' && ch <= '9')
//		x = (x << 1) + (x << 3) + ch - 48, ch = getchar();
//	if (f) x = -x;
//}


template <int N, int M>
struct Isap
{
	struct Edge {
		int to, next, cap, flow;
	}edge[M];//注意是maxm  
	int tol;
	int head[N];
	int cur[N], d[N];// 当前弧下标   结点到汇点距离下界  
	int p[N], gap[N];//可增广路上的上一条弧   gap优化  //比dinic多的两个数组  
	void init() {
		tol = 0;
		memset(head, -1, sizeof(head));
	}

	void add(int u, int v, int w, int rw = 0) {
		edge[tol].to = v; edge[tol].cap = w; edge[tol].flow = 0;
		edge[tol].next = head[u]; head[u] = tol++;
		edge[tol].to = u; edge[tol].cap = rw; edge[tol].flow = 0;
		edge[tol].next = head[v]; head[v] = tol++;
	}

	int Q[N];
	void bfs(int s, int t) {//逆向进行bfs  
		memset(d, -1, sizeof(d));
		memset(gap, 0, sizeof(gap));
		gap[0] = 1;
		int front = 0, rear = 0;
		d[t] = 0;
		Q[rear++] = t;
		while (front != rear) {
			int u = Q[front++];
			for (int i = head[u]; i != -1; i = edge[i].next) {
				int v = edge[i].to;
				if (d[v] != -1)continue;
				Q[rear++] = v;
				d[v] = d[u] + 1;
				gap[d[v]]++;
			}
		}
	}

	int S[N];
	int sap(int s, int t, int num) {
		bfs(s, t);
		memcpy(cur, head, sizeof(head));
		int top = 0;
		int u = s;
		int ans = 0;
		while (d[s]<num) {
			if (u == t) {
				int Min = 1000000000;
				int inser;
				for (int i = 0; i<top; i++)//找最小残量值  
					if (Min>edge[S[i]].cap - edge[S[i]].flow) {
						Min = edge[S[i]].cap - edge[S[i]].flow;
						inser = i;
					}
				for (int i = 0; i<top; i++) {//增广  
					edge[S[i]].flow += Min;
					edge[S[i] ^ 1].flow -= Min;
				}
				ans += Min;
				top = inser;
				u = edge[S[top] ^ 1].to;
				continue;
			}
			bool ok = false;
			int v;
			for (int i = cur[u]; i != -1; i = edge[i].next) {
				v = edge[i].to;
				if (edge[i].cap - edge[i].flow && d[v] + 1 == d[u]) {////Advance前进  
					ok = true;
					cur[u] = i;
					break;
				}
			}
			if (ok) {
				S[top++] = cur[u];
				u = v;
				continue;
			}
			//Retreat走不动了，撤退  
			int Min = num;
			for (int i = head[u]; i != -1; i = edge[i].next)
				if (edge[i].cap - edge[i].flow && d[edge[i].to]<Min) {
					Min = d[edge[i].to];
					cur[u] = i;
				}
			gap[d[u]]--;
			if (!gap[d[u]])return ans;
			d[u] = Min + 1;
			gap[d[u]]++;
			if (u != s)u = edge[S[--top] ^ 1].to;//退一步，沿父边返回  
		}
		return ans;
	}
};
Isap<maxn, maxm> isap;


int n, m, k, x, y, z, w;
int code(int r, int c) {
	if (c == 1) return 1;
	if (c == m + 1) return n*(m - 1) + 2;
	return (r - 1)*(m - 1) + c;
}
int main()
{
	int T; scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d%d", &n, &m, &k);
		isap.init();
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				scanf("%d", &w), isap.add(code(i, j), code(i, j + 1), 1000 - w);
		while (k--)
		{
			scanf("%d%d%d", &x, &y, &z);
			for (int i = 1; i <= m; ++i) if (i - z > 1)
				isap.add(code(x, i), code(y, min(i - z, m + 1)), 1000000000);
		}
		int ans = isap.sap(1, n*(m - 1) + 2, n*(m - 1) + 2);
		printf("%d\n", ans >= 1000000000 ? -1 : n * 1000 - ans);
	}
	return 0;
}