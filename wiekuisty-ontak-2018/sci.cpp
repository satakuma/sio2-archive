#include<bits/stdc++.h>
using namespace std;
#ifndef d
#define d(...)
#endif
#define st first
#define nd second
#define pb push_back
#define siz(c) (int)(c).size()
#define all(c) (c).begin(), (c).end()
typedef long long LL;
typedef long double LD;
constexpr int INF=1e9+7;
constexpr LL INFL=1e18;

const int maxn=200005;

int n,p,lp=1,LOG=1;
vector<int>graf[maxn];
int no[maxn],rozm[maxn],par[maxn][20],d[maxn];
vector<int>koniec[maxn],start[maxn];

int res=0;
pair<int,int>ans={0,1};

void calc(int a,int oj=-1)
{
	no[a]=lp++;
	rozm[a]=1;
	for(int& v:graf[a]){
		if(v==oj)
			continue;
		d[v]=d[a]+1;
		calc(v,a);
		par[v][0]=a;
		rozm[a]+=rozm[v];
	}
}

inline bool isAnc(int a,int b)
{
	if(no[b]<no[a] || no[a]+rozm[a]<=no[b])
		return false;
	return true;
}

int getLca(int a,int b)
{
	if(isAnc(a,b))
		return a;
	if(isAnc(b,a))
		return b;
	int l=LOG;
	while(l>=0){
		if(!isAnc(par[a][l],b))
			a=par[a][l];
		--l;
	}
	return par[a][0];
}

struct path
{
	int a,b,ind,lca;
	void get(int i)
	{
		cin>>a>>b;
		ind = i;
		lca=getLca(a,b);
		koniec[lca].pb(i);
		if(lca!=a)
			start[a].pb(i);
		if(lca!=b)
			start[b].pb(i);
	}
};
vector<path>sc;

struct op
{
	bool operator() (const pair<int,int>& a,const pair<int,int>& b)
	{
		if(a.st==b.st)
			return a.nd<b.nd;
		return a.st<b.st;
	}
};

set<pair<int,int>,op>secik[maxn];

typedef set<pair<int,int>,op>::iterator IT;

inline IT pop(IT a,int ind)
{
	if(a==secik[ind].begin())
		a=secik[ind].end();
	return --a;
}
inline IT nast(IT a,int ind)
{
	a++;
	if(a==secik[ind].end())
		a=secik[ind].begin();
	return a;
}

void intersect(int a1,int b1)
{
	if(a1==b1)
		return;
	path& a=sc[a1],b=sc[b1];
	int rest=0;
	int tmp=0;
	int lca=getLca(a.a,b.a);
	if(!isAnc(lca,a.lca) && !isAnc(lca,b.lca)){
		if(isAnc(a.lca,b.lca))
			tmp+=d[lca]-d[b.lca];
		else
			tmp+=d[lca]-d[a.lca];
	}
	lca=getLca(a.b,b.b);
	if(!isAnc(lca,b.lca) && !isAnc(lca,b.lca)){
		if(isAnc(a.lca,b.lca))
			tmp+=d[lca]-d[b.lca];
		else
			tmp+=d[lca]-d[a.lca];
	}
	rest=max(rest,tmp);
	tmp=0;
	lca=getLca(a.a,b.b);
	if(!isAnc(lca,a.lca) && !isAnc(lca,b.lca)){
		if(isAnc(a.lca,b.lca))
			tmp+=d[lca]-d[b.lca];
		else
			tmp+=d[lca]-d[a.lca];
	}
	lca=getLca(a.b,b.a);
	if(!isAnc(lca,b.lca) && !isAnc(lca,b.lca)){
		if(isAnc(a.lca,b.lca))
			tmp+=d[lca]-d[b.lca];
		else
			tmp+=d[lca]-d[a.lca];
	}
	rest=max(rest,tmp);
	if(rest>res){
		res=rest;
		ans={a1,b1};
	}
}


inline void add(pair<int,int> x,int ind)
{
	IT it=secik[ind].insert(x).st;
	if(siz(secik[ind])<2)
		return;
	IT it2=pop(it,ind);
	intersect((*it2).nd,(*it).nd);
	it2=nast(it,ind);
	intersect((*it2).nd,(*it).nd);
}

inline void erase(pair<int,int>x,int ind)
{
	IT it=secik[ind].erase(secik[ind].find(x));
	if(siz(secik[ind])<2)
		return;
	if(it==secik[ind].end())
		it=secik[ind].begin();
	IT it2=pop(it,ind);
	intersect((*it2).nd,(*it).nd);
}

void merge(int in,int out)
{
	if(siz(secik[out])>siz(secik[in]))
		swap(secik[in],secik[out]);
	for(auto x:secik[out]){
		add(x,in);
	}
}

void dfs(int a,int oj=-1)
{
	for(int& v:graf[a]){
		if(v==oj)
			continue;
		dfs(v,a);
		merge(a,v);
	}
	for(auto x:start[a]){
		if(sc[x].a==a)
			add({no[sc[x].b],x},a);
		else
			add({no[sc[x].a],x},a);
	}
	for(auto x:koniec[a]){
		if(sc[x].lca!=sc[x].a)
			erase({no[sc[x].b],x},a);
		if(sc[x].lca!=sc[x].b)
			erase({no[sc[x].a],x},a);
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>p;
	for(int i=2;i<=n;i++){
		int a;
		cin>>a;
		graf[a].pb(i);
		graf[i].pb(a);
	}
	calc(1);
	par[1][0]=1;
	while( (1<<LOG) < n ) LOG++;
	for(int l=1;l<=LOG;l++)
		for(int i=1;i<=n;i++)
			par[i][l]=par[par[i][l-1]][l-1];
			
	sc.resize(p);
	for(int i=0;i<p;i++)
		sc[i].get(i);
	
	dfs(1);
	
	cout<<res<<"\n";
	cout<<ans.st+1<<" "<<ans.nd+1<<"\n";
	
	
	return 0;
}
