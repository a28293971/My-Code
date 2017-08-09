#include<stdio.h>  
#define N 50010  
struct node
{
	int sum, b;//sum为在范围内的花数，b为判断是否全满或全为空 如果是为1，否则为0  
}tree[4 * N];
void biulde(int l, int r, int k)
{
	int m = (l + r) / 2;
	tree[k].sum = 0; 
	tree[k].b = 1;//开始全为空所以设为1
	if (l == r) return;
	biulde(l, m, k * 2);  
	biulde(m + 1, r, k * 2 + 1);
}
void set_child(int l, int r, int k)
{
	int m = (l + r) / 2;
	tree[k * 2].b = tree[k * 2 + 1].b = 1;//子区间被设为全满或全为空 
	if (tree[k].sum == r - l + 1) //如果父区间全满则 子区间全满 
	{
		tree[k * 2].sum = m - l + 1; 
		tree[k * 2 + 1].sum = r - m;
	}
	else  //否则子区间全设为空
	{
		tree[k * 2].sum = 0;
		tree[k * 2 + 1].sum = 0;
	}
}
int QL, QR, L, R, ans, n;
void putInFlower(int l, int r, int k)
{
	if (ans <= 0) return;//花已经被插完
	int m = (l + r) / 2;
	if (L <= l&&r <= R&&tree[k].b)//如果区间全满或全空
	{
		if (!tree[k].sum) //如果全空
		{
			int tans = ans;
			ans -= (r - l + 1);//插花 花的数量减少
			tree[k].sum = r - l + 1;//区间填满
			if (QL < 0)//如果最左没更新则更新一次
				QL = l;
			QR = r;
		}
		else 
		{//跳动插花范围的右边值，R刚好是插完花的右边范围的最小值，除非超出花瓶数量，则为n  
			R += (r - l + 1); //否则 这个区间全为满 所以R向右偏移
			if (R>n-1) 
				R = n-1;
		}
		return;
	}
	if (tree[k].b)//向下传递
		set_child(l, r, k);
	tree[k].b = 0;//这个区间无法全插花 子区间可能会插花 所以这里先设为0
	if (L <= m) 
		putInFlower(l, m, k * 2);
	if (R>m) 
		putInFlower(m + 1, r, k * 2 + 1);

	tree[k].sum = tree[k * 2].sum + tree[k * 2 + 1].sum;
	if (tree[k].sum == r - l + 1 || !tree[k].sum)//插完花后 判断是否全满或全空
		tree[k].b = 1;
}
void clear(int l, int r, int k)
{
	int m = (l + r) / 2;
	if (L <= l&&r <= R)
	{
		ans += tree[k].sum; //答案增加这区间花的数量
		tree[k].b = 1; //全空
		tree[k].sum = 0;
		return;
	}
	if (tree[k].b)
		set_child(l, r, k);
	tree[k].b = 0;
	if (L <= m) 
		clear(l, m, k * 2);
	if (R>m) 
		clear(m + 1, r, k * 2 + 1);

	tree[k].sum = tree[k * 2].sum + tree[k * 2 + 1].sum;//向上传递
	if (tree[k].sum == r - l + 1 || !tree[k].sum)// 判断全满或全空
		tree[k].b = 1;
}
int main()
{
	int t, m, x;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d%d", &n, &m);
		biulde(0, n, 1);
		while (m--)
		{
			scanf("%d%d", &x, &L);
			if (x == 1) 
			{
				scanf("%d", &ans);
				R = L + ans - 1; //插完花又边的最小可能
				QL = QR = -1;//初始化
				putInFlower(0, n, 1);
				if (QR >= 0)
					printf("%d %d\n", QL, QR);
				else
					printf("Can not put any one.\n");
			}
			else 
			{
				scanf("%d", &R); 
				ans = 0;
				clear(0, n, 1);
				printf("%d\n", ans);
			}
		}
		printf("\n");
	}
	return 0;
}