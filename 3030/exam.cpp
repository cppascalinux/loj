//2019.06.19
//loj3030 「JOISC 2019 Day1」考试 三位偏序裸题,CDQ分治+树状数组
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define inf 1000000000
using namespace std;
struct node
{
	int x,y,z,typ;
	node(){}
	node(int a,int b,int c,int d){x=a,y=b,z=c,typ=d;}
	bool operator <(const node &p) const
	{
		if(x!=p.x)
			return x<p.x;
		if(y!=p.y)
			return y<p.y;
		if(z!=p.z)
			return z<p.z;
		return typ<p.typ;
	}
};
int n,m,d;
node s[200009];
int ans[100009];
int lsh[600009];
int c[600009];
void init()
{
	int tp=0;
	for(int i=1;i<=n+m;i++)
		lsh[++tp]=s[i].x,lsh[++tp]=s[i].y,lsh[++tp]=s[i].z;
	sort(lsh+1,lsh+tp+1);
	d=unique(lsh+1,lsh+tp+1)-lsh-1;
	for(int i=1;i<=n+m;i++)
	{
		s[i].x=lower_bound(lsh+1,lsh+d+1,s[i].x)-lsh;
		s[i].y=lower_bound(lsh+1,lsh+d+1,s[i].y)-lsh;
		s[i].z=lower_bound(lsh+1,lsh+d+1,s[i].z)-lsh;
	}
}
void add(int x,int val)
{
	for(;x<=d;x+=x&-x)
		c[x]+=val;
}
int ask(int x)
{
	int ans=0;
	for(;x;x-=x&-x)
		ans+=c[x];
	return ans;
}
bool cmp(node a,node b)
{
	if(a.y!=b.y)
		return a.y<b.y;
	if(a.z!=b.z)
		return a.z<b.z;
	return a.typ<b.typ;
}
void solve(int l,int r)
{
	if(l==r)
		return;
	int mid=(l+r)>>1;
	solve(l,mid),solve(mid+1,r);
	vector<node> v;
	for(int i=l;i<=mid;i++)
		if(!s[i].typ)
			v.push_back(s[i]);
	for(int i=mid+1;i<=r;i++)
		if(s[i].typ)
			v.push_back(s[i]);
	sort(v.begin(),v.end(),cmp);
	for(int i=0;i<(int)v.size();i++)
		if(!v[i].typ)
			add(v[i].z,1);
		else
			ans[v[i].typ]+=ask(v[i].z);
	for(int i=0;i<(int)v.size();i++)
		if(!v[i].typ)
			add(v[i].z,-1);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("exam.in","r",stdin);
	freopen("exam.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1,a,b;i<=n;i++)
	{
		scanf("%d%d",&a,&b);
		s[i]=node(inf-a,inf-b,2*inf-a-b,0);
	}
	for(int i=1,a,b,c;i<=m;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		s[i+n]=node(inf-a,inf-b,2*inf-c,i);
	}
	init();
	sort(s+1,s+n+m+1);
	solve(1,n+m);
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	return 0;
}