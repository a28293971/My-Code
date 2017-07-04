#include <iostream>  
#include<stdio.h>  
#include<string.h>  
using namespace std;  
const int maxn=50010;  
int ml[maxn<<2],mr[maxn<<2],sta[maxn];//sta为栈  
int flag,tail;  
void btree(int L,int R,int k)  
{  
    int ls,rs,mid;  
    ml[k]=mr[k]=R-L+1;  //初始化每个节点的区间，左连续和又连续长度为区间长度
    if(L==R)  //如果节点也更新过了 那么返回
        return;  
    ls=k<<1;  
    rs=ls|1;  
    mid=(L+R)>>1;  
    btree(L,mid,ls);  
    btree(mid+1,R,rs);  
}  
void update(int L,int R,int k,int p,int op)
{  
    int ls,rs,mid;  
    if(L==R)  
    {  
        if(op)  //po=1时为删除，po=0时为恢复
            ml[k]=mr[k]=0;  
        else  
            ml[k]=mr[k]=1;  
        return;  
    }  
    ls=k<<1;  
    rs=ls|1;  
    mid=(L+R)>>1;  
    if(p>mid)  //由于更新的是节点 所以只往对应的区间搜索
        update(mid+1,R,rs,p,op);  
    else  
        update(L,mid,ls,p,op);  
    ml[k]=ml[ls];  //将子区间的连续情况传递上来大的区间
    mr[k]=mr[rs];  
    if(ml[ls]==mid-L+1)  //例如C的子区间A与B 如果A全部为连续的 那么C的左连续数量要加上B区间左连续的部分
        ml[k]+=ml[rs];  
    if(mr[rs]==R-mid)    //同理 如果右边全部连续 那么C的右连续数量要加上A的右连续部分
        mr[k]+=mr[ls];  
}  
int qu(int L,int R,int k,int p)  
{  
    int ls,rs,mid,t;  
    if(mr[k]>=R-p+1)  //p点在区间的右连续区间中
    {  
        flag=1;//加以标记。返回上层时加上扩展值  
        return mr[k];  
    }  
    if(ml[k]>=p-L+1)  //p在区间的左连续区间中
    {  
        flag=1;  
        return ml[k];  
    }  
    if(L==R)  
        return 0;  
    ls=k<<1;  
    rs=ls|1;  
    mid=(L+R)>>1;  
    if(p>mid)  
    {  
        t=qu(mid+1,R,rs,p);  
        if(flag)  
        {  
            flag=0;  
            t+=mr[ls];  //返回时为大区间的左连续区间 所以要加上左区间的右连续值
        }  
    }  
    else  
    {  
        t=qu(L,mid,ls,p);  
        if(flag)  
        {  
            flag=0;  
            t+=ml[rs];  //同理 加上右区间的左连续值
        }  
    }  
    return t;  
}  
int main()  
{  
    int n,m,p,i;  
    char com[10];  
  
    while(~scanf("%d%d",&n,&m))  
    {  
        btree(1,n,1);  
        flag=tail=0;  
        for(i=0;i<m;i++)  
        {  
            scanf("%s",com);  
            switch(com[0])  
            {  
            case 'D':  
                scanf("%d",&p);  
                update(1,n,1,p,1);  
                sta[tail++]=p;  
                break;  
            case 'Q':  
                scanf("%d",&p);  
                flag=0;//注意flag初始化！  
                printf("%d\n",qu(1,n,1,p));  
                break;  
            case 'R':  
                update(1,n,1,sta[--tail],0);  
            }  
        }  
    }  
    return 0;  
}  