//2019.06.15
//loj3032 「JOISC 2019 Day1」馕 以每个人的标准,将naan划分为n段,每段的美味度相等
//在naan上从左向右扫,每个段的分割点都使用未被使用的人中的最小的分割点,这样贪心显然是对的
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define li long long
#define fi first
#define se second
#define pll pair<li,li>
#define db double
using namespace std;
int n,m;
int v[2009][2009];
li ed[2009];
pll sp[2009][2009];
pll ans[2009];
int vis[2009],p[2009];
void init(int x)
{
	int sm=0;
	for(int i=1;i<=m;i++)
		sm+=v[x][i],v[x][i]*=n,ed[i]=ed[i-1]+v[x][i];
	int curb=0;
	for(int i=1;i<=n;i++)
	{
		while(curb<m&&ed[curb]<(li)i*sm)
			curb++;
		li res=(li)i*sm-ed[curb-1];
		sp[x][i]=pll(res+(li)v[x][curb]*(curb-1),v[x][curb]);
	}
}
int cmp(pll a,pll b)
{
	return (db)a.fi/a.se<(db)b.fi/b.se;
}
void solve()
{
	for(int i=1;i<=n;i++)
	{
		int t=0;
		for(int j=1;j<=n;j++)
			if(!vis[j])
				t=j;
		for(int j=1;j<=n;j++)
			if(!vis[j]&&cmp(sp[j][i],sp[t][i]))
				t=j;
		vis[t]=1;
		ans[i]=sp[t][i];
		p[i]=t;
	}
	for(int i=1;i<=n-1;i++)
		printf("%lld %lld\n",ans[i].fi,ans[i].se);
	for(int i=1;i<=n;i++)
		printf("%d ",p[i]);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("naan.in","r",stdin);
	freopen("naan.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&v[i][j]);
	for(int i=1;i<=n;i++)
		init(i);
	solve();
	return 0;
}