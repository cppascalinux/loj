//2019.06.14
//loj3033 「JOISC 2019 Day2」两个天线 先将所有的询问离线,按右端点从小到大排序,用线段树去维护每个点作为左端点时的答案
//不妨假设i<j,hi<hj,反转值域再做一遍,ai表示i为左端点时hj-hi的最大值,bi表示当前右端点在i的范围内?hi:inf
//ci表示能通信到i的hj的最大值的标记,标记下传时,用ci和bi的区间最小值去更新ai的区间最大值
//询问时,查询ai的区间最大值,右端点+1时,对于区间的ci取最大值,一个左端点的状态改变时,先将ci全部下传,然后去更新bi,ai O(nlogn)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define pii pair<int,int>
#define fi first
#define se second
#define inf 0x7F7F7F7F
using namespace std;
int n,m;
int h[200009],l1[200009],l2[200009];
int ans[200009];
int va[800009],vb[800009],vc[800009];
vector<int> st[400009],ed[400009];
vector<pii> qry[200009];
void down(int a)
{
	int la=a<<1,ra=a<<1|1;
	vc[la]=max(vc[la],vc[a]);
	vc[ra]=max(vc[ra],vc[a]);
	vc[a]=-1;
	va[la]=max(va[la],vc[la]-vb[la]);
	va[ra]=max(va[ra],vc[ra]-vb[ra]);
}
void update(int a)
{
	int la=a<<1,ra=a<<1|1;
	va[a]=max(va[la],va[ra]);
	vb[a]=min(vb[la],vb[ra]);
}
int ask(int a,int l,int r,int ll,int rr)
{
	if(l>rr||r<ll)
		return -1;
	if(l>=ll&&r<=rr)
		return va[a];
	down(a);
	int mid=(l+r)>>1;
	return max(ask(a<<1,l,mid,ll,rr),ask(a<<1|1,mid+1,r,ll,rr));
}
void add(int a,int l,int r,int ll,int rr,int val)
{
	if(l>rr||r<ll)
		return;
	if(l>=ll&&r<=rr)
	{
		vc[a]=max(vc[a],val);
		va[a]=max(va[a],vc[a]-vb[a]);
		return;
	}
	down(a);
	int mid=(l+r)>>1;
	add(a<<1,l,mid,ll,rr,val);
	add(a<<1|1,mid+1,r,ll,rr,val);
	update(a);
}
void sett(int a,int l,int r,int pos,int val)
{
	if(l==r)
	{
		va[a]=max(va[a],vc[a]-vb[a]);
		vb[a]=val;
		vc[a]=-1;
		return;
	}
	down(a);
	int mid=(l+r)>>1;
	if(pos<=mid)
		sett(a<<1,l,mid,pos,val);
	else
		sett(a<<1|1,mid+1,r,pos,val);
	update(a);
}
void solve()
{
	memset(va,-1,sizeof(va));
	memset(vb,0x7F,sizeof(vb));
	memset(vc,-1,sizeof(vc));
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<(int)ed[i].size();j++)
			sett(1,1,n,ed[i][j],inf);
		for(int j=0;j<(int)st[i].size();j++)
			sett(1,1,n,st[i][j],h[st[i][j]]);
		add(1,1,n,i-l2[i],i-l1[i],h[i]);
		for(int j=0;j<(int)qry[i].size();j++)
			ans[qry[i][j].se]=max(ans[qry[i][j].se],ask(1,1,n,qry[i][j].fi,i));
	}
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("antennas.in","r",stdin);
	freopen("antennas.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d",h+i,l1+i,l2+i);
		st[i+l1[i]].push_back(i),ed[i+l2[i]+1].push_back(i);
	}
	scanf("%d",&m);
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		qry[b].push_back(pii(a,i));
	}
	memset(ans,-1,sizeof(ans));
	solve();
	for(int i=1;i<=n;i++)
		h[i]=1000000001-h[i];
	solve();
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	return 0;
}