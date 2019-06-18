//2019.06.18
//loj3036 「JOISC 2019 Day3」指定城市 点数为1,2时直接树形dp,点数为k,k>=3时,答案一定是在k-1的基础上加了一个贡献最大的叶子
//用线段树去维护dfs序区间最大值和最大值的位置,每次向上暴力修改,在线段树上区间加即可
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define li long long
#define pli pair<li,int>
#define fi first
#define se second
#define inf 0x7F7F7F7F
using namespace std;
int n,m,tot=1,tme;
li sm=0;
int hd[200009],eg[400009],nxt[400009],len[400009];
int deg[200009];
int dfn[200009],ed[200009],id[200009];
li ans[200009];
li ls1[200009];
pli ls2[200009];
pli fl[200009],gl[200009];
int f[200009],vis[200009],pl[200009];
li dis[200009];
li mx[800009],lz[800009];
int mv[800009];
void ins(int a,int b,int c)
{
	eg[++tot]=b;
	len[tot]=c;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void dfs0(int x,int fa)
{
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa)
		{
			ls1[1]+=len[i^1];
			dfs0(eg[i],x);
		}
}
void dfs1(int x,int fa,li l)
{
	ls1[x]=l;
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa)
		{
			li nl=l-len[i^1]+len[i];
			dfs1(eg[i],x,nl);
		}
}
void dfs2(int x,int fa)
{
	fl[x]=pli(0,x),gl[x]=pli(-1,0);
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa)
		{
			dfs2(eg[i],x);
			pli nf=pli(fl[eg[i]].fi+len[i],fl[eg[i]].se);
			gl[x]=max(gl[x],nf);
			if(gl[x]>fl[x])
				swap(fl[x],gl[x]);
		}
}
void dfs3(int x,int fa,pli l)
{
	ls2[x]=max(l,fl[x]);
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa)
		{
			pli nl=l;
			if(fl[x].se==fl[eg[i]].se)
				nl=max(nl,gl[x]);
			else
				nl=max(nl,fl[x]);
			dfs3(eg[i],x,pli(nl.fi+len[i^1],nl.se));
		}
}
void dfs4(int x,int fa,li l)
{
	f[x]=fa;
	dfn[x]=inf;
	dis[x]=l;
	if(deg[x]==1&&fa)
		dfn[x]=ed[x]=++tme,id[tme]=x;
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa)
		{
			pl[eg[i]]=len[i];
			dfs4(eg[i],x,l+len[i]);
			dfn[x]=min(dfn[x],dfn[eg[i]]);
			ed[x]=max(ed[x],ed[eg[i]]);
		}
}
void down(int a)
{
	int la=a<<1,ra=a<<1|1;
	li t=lz[a];
	mx[la]+=t,mx[ra]+=t;
	lz[la]+=t,lz[ra]+=t;
	lz[a]=0;
}
void update(int a)
{
	int la=a<<1,ra=a<<1|1;
	if(mx[la]>mx[ra])
		mx[a]=mx[la],mv[a]=mv[la];
	else
		mx[a]=mx[ra],mv[a]=mv[ra];
}
void build(int a,int l,int r)
{
	if(l==r)
		return mx[a]=dis[id[l]],mv[a]=id[l],void();
	int mid=(l+r)>>1;
	build(a<<1,l,mid);
	build(a<<1|1,mid+1,r);
	update(a);
	mx[a]=max(mx[a<<1],mx[a<<1|1]);
}
void add(int a,int l,int r,int ll,int rr,li val)
{
	if(l>rr||r<ll)
		return;
	if(l>=ll&&r<=rr)
		return mx[a]+=val,lz[a]+=val,void();
	down(a);
	int mid=(l+r)>>1;
	add(a<<1,l,mid,ll,rr,val);
	add(a<<1|1,mid+1,r,ll,rr,val);
	update(a);
}
void modify(int x)
{
	for(;!vis[x];x=f[x])
	{
		vis[x]=1;
		// printf("x:%d pl:%d\n",x,pl[x]);
		add(1,1,tme,dfn[x],ed[x],-pl[x]);
	}
}
void dbg(int a,int l,int r)
{
	if(l==r)
	{
		printf("l:%d id:%d mx:%lld\n",l,id[l],mx[a]);
		return;
	}
	printf("l:%d r:%d mx:%lld mv:%d\n",l,r,mx[a],mv[a]);
	down(a);
	int mid=(l+r)>>1;
	dbg(a<<1,l,mid);
	dbg(a<<1|1,mid+1,r);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("city.in","r",stdin);
	freopen("city.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1,a,b,c,d;i<=n-1;i++)
	{
		scanf("%d%d%d%d",&a,&b,&c,&d);
		sm+=c+d;
		ins(a,b,c),ins(b,a,d);
		deg[a]++,deg[b]++;
	}
	if(n==1)
		ans[1]=0;
	else if(n==2)
	{
		ans[1]=max(len[2],len[3]);
		ans[2]=sm;
	}
	else
	{
		dfs0(1,0);
		dfs1(1,0,ls1[1]);
		dfs2(1,0);
		dfs3(1,0,pli(-1,0));
		int rt=0;
		// for(int i=1;i<=n;i++)
		// 	printf("i:%d ls1:%lld fl:%lld %d gl:%lld %d ls2:%lld %d\n",i,ls1[i],fl[i].fi,fl[i].se,gl[i].fi,gl[i].se,ls2[i].fi,ls2[i].se);
		for(int i=1;i<=n;i++)
		{
			ans[1]=max(ans[1],ls1[i]);
			if(ls1[i]+ls2[i].fi>ans[2])
				ans[2]=ls1[i]+ls2[i].fi,rt=i;
		}
		// printf("rt:%d\n",rt);
		dfs4(rt,0,0);
		vis[rt]=1;
		build(1,1,tme);
		// dbg(1,1,tme);
		modify(ls2[rt].se);
		for(int i=3;i<=tme+1;i++)
		{
			int x=mv[1];
			// printf("mv1:%d mx1:%lld\n",mv[1],mx[1]);
			ans[i]=ans[i-1]+mx[1];
			modify(x);
			// dbg(1,1,tme);
		}
		for(int i=tme+2;i<=n;i++)
			ans[i]=ans[i-1];
	}
	// int eoe=0;
	// for(int i=1;i<=n;i++)
	// 	if(deg[i]==1)
	// 		printf("deg1:%d dfn:%d ed:%d\n",i,dfn[i],ed[i]),eoe++;
	// for(int i=1;i<=tme;i++)
	// 	printf("i:%d id:%d dis:%lld vis:%d\n",i,id[i],dis[id[i]],vis[id[i]]);
	// printf("eoe:%d tme:%d\n",eoe,tme);
	scanf("%d",&m);
	for(int i=1,a;i<=m;i++)
	{
		scanf("%d",&a);
		printf("%lld\n",sm-ans[a]);
	}
	return 0;
}