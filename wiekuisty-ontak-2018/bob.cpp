#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define st first
#define nd second
#define all(c) (c).begin(),(c).end()
#define siz(c) (int)(c).size()
typedef long long LL;
typedef long double LD;
constexpr int INF=1e9+7;
constexpr LL INFL=1e18;

const int maxn=200005;

int n,m,lpv=0,lp,res=0;
vector<int>graf[maxn],gt[maxn];
stack<int>stos;
int vis[maxn],degi[maxn],dego[maxn],degsIn[maxn],degsOut[maxn];
bool zeroIn[maxn],zeroOut[maxn];
int kt[maxn];
bool marki[maxn],marko[maxn];

void dfs(int a)
{
	vis[a]=lpv;
	for(auto v:graf[a]){
		if(vis[v]!=lpv)
			dfs(v);
	}
	stos.push(a);
}

void dfsSp(int a)
{
	vis[a]=lpv;
	kt[a]=lp;
	for(auto v:gt[a]){
		if(vis[v]!=lpv)
			dfsSp(v);
	}
}

void makeSCC()
{
	lpv++;
	for(int i=1;i<=n;i++)
		if(vis[i]!=lpv)
			dfs(i);
	lpv++;
	lp=1;
	while(!stos.empty()){
		int w=stos.top(); stos.pop();
		if(vis[w]==lpv)
			continue;
		dfsSp(w);
		lp++;
	}
	for(int i=1;i<lp;i++)
		degsIn[i]=degsOut[i]=0;
	for(int i=1;i<=n;i++)
		for(auto v:graf[i]){
			if(kt[v]!=kt[i])
				degsIn[kt[v]]++,degsOut[kt[i]]++;
		}
}

void match()
{
	if(lp==2)
		return;
	for(int i=1;i<lp;i++)
		zeroIn[i]=zeroOut[i]=false;
		
	int cnti=0,cnto=0;
	for(int i=1;i<lp;i++){
		if(degsIn[i]==0)
			zeroIn[i]=true,cnti++;
		if(degsOut[i]==0)
			zeroOut[i]=true,cnto++;
	}
	int mn=min(cnti,cnto);
	res+=mn;
	int in=-1;
	for(int i=1;i<=n;i++)
		if(in==-1 && zeroOut[kt[i]] && degi[i]>dego[i])
			in=i;
	//cerr<<"in: "<<in<<", res = "<<res<<endl;
	cnti=cnto=0;
	for(int i=1;i<lp;i++)
		marki[i]=marko[i]=false;
	for(int i=1;i<=n;i++){
		if(cnti<mn && zeroIn[kt[i]] && !marki[kt[i]] && degi[i]<dego[i]){
			marki[kt[i]]=true;
			graf[in].pb(i);
			gt[i].pb(in);
			degi[i]++,dego[in]++;
			cnti++;
		}
		if(cnto<mn && zeroOut[kt[i]] && !marko[kt[i]] && degi[i]>dego[i]){
			marko[kt[i]]=true;
			graf[i].pb(in);
			gt[in].pb(i);
			degi[in]++,dego[i]++;
			cnto++;
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	cin>>n>>m;
	for(int i=0;i<m;i++)
	{
		int a,b;
		cin>>a>>b;
		graf[a].pb(b);
		gt[b].pb(a);
		degi[b]++,dego[a]++;
	}
	makeSCC();  //git
	match();
	
	/*for(int i=1;i<=n;i++){
		cerr<<"graf["<<i<<"]: ";
		for(auto v:graf[i])
			cerr<<v<<" ";
		cerr<<endl;
	}
	cerr<<res<<endl;*/
	
	
	int cnto=0,cnti=0;
	for(int i=1;i<=n;i++){
		cnti+=max(0,dego[i]-degi[i]);
		cnto+=max(0,degi[i]-dego[i]);
	}
	
	assert(cnti==cnto);
	res+=cnti;
	
	cout<<res<<"\n";
	
	return 0;
}