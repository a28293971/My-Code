#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<vector>
#include<algorithm>
#include<set>
#include<map>
#include<bitset>
#include<string>
#include<queue>
#include<stack>
#include<iomanip>
#include<ctime>
#define PI 3.1415926535898
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f
#define Dinf 0x434343434343434
#define sqr(a) ((a)*(a))
#define mem(a,b) memset(a,b,sizeof(a))
#define EPS(a,b) (abs(a-b)<=eps? 1:0)
#define mid ((l+r)>>1)
#define lson rt<<1,l,m
#define rson rt<<1|1,m+1,r
#define maxn  2504
#define maxm 12520
#define MOD 998244353
#define eps 1e-6
using namespace std;
using LL = long long;
using Pii = pair<int, int>;

inline void read(int &x)
{
	bool f = 0; char ch = getchar(); x = 0;
	while (ch < '0' || ch > '9') ch = getchar(), f = (ch == '-');
	while (ch >= '0' && ch <= '9')
		x = (x << 1) + (x << 3) + ch - 48, ch = getchar();
	if (f) x = -x;
}
inline void read(LL &x)
{
	bool f = 0; char ch = getchar(); x = 0;
	while (ch < '0' || ch > '9') ch = getchar(), f = (ch == '-');
	while (ch >= '0' && ch <= '9')
		x = (x << 1) + (x << 3) + ch - 48, ch = getchar();
	if (f) x = -x;
}

using ull = unsigned long long;
struct mybeiset
{
	ull bit[1600];
	void reset()
	{
		mem(bit, 0);
	}
	void flip(int pos)
	{
		bit[pos >> 6] ^= 1llu << (pos & 63);
	}
	int get(int pos)
	{
		return bit[pos >> 6] >> (pos & 63) & 1llu;
	}
}a, ans;
ull pp[68];
int main()
{
	pp[0] = 1llu;
	for (int i = 1; i < 64; ++i) pp[i] = (ull)1 << i | pp[i - 1];

	int t; read(t);
	int n, m, q, ma = -inf, mi = inf, num;
	while (t--)
	{
		read(n), read(m), read(q);
		a.reset();
		while (n--)
		{
			read(num);
			if (num > ma) ma = num;
			if (num < mi) mi = num;
			a.flip(num);
		}
		ans.reset();
		while (m--)
		{
			read(num);
			for (ull i = mi / num*num; i <= ma; i += num)
			{
				int idx1 = i >> 6, p1 = i & 63;
				int idx2 = (i + num - 1) >> 6, p2 = (i + num - 1) & 63;
				if (idx1 == idx2)
					ans.bit[0] ^= a.bit[idx1] >> p1&pp[p2 - p1];
				else
				{
					int curidx = 0, curpos = 63 - p1;
					ans.bit[0] ^= a.bit[idx1] >> p1&pp[curpos];
					for (idx1 += 1; idx1 < idx2; ++idx1)
					{
						if (curpos == 63)
							ans.bit[++curidx] ^= a.bit[idx1];
						else
							ans.bit[curidx++] ^= a.bit[idx1] << (curpos + 1), ans.bit[curidx] ^= a.bit[idx1] >> p1&pp[curpos];
					}
					if (curpos == 63)
						ans.bit[++curidx] ^= a.bit[idx2] & pp[p2];
					else if (p2 < p1)
						ans.bit[curidx] ^= (a.bit[idx2] & pp[p2]) << (curpos + 1);
					else
						ans.bit[curidx++] ^= a.bit[idx2] << (curpos + 1), ans.bit[curidx] ^= a.bit[idx2] >> p1&pp[p2 - p1];
				}
			}
		}
		while (q--)
		{
			read(num);
			printf("%d\n", ans.get(num));
		}
	}
	return 0;
}
