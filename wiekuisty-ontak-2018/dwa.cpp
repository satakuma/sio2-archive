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

const int maxn=2005;
const int C=12;

int n,m;
vector<pair<int,int> >graf[maxn];
int par[maxn],lvl[maxn];
int dp[maxn][(1<<C)+5];
bool vis[maxn];

void wypisz(int a,int b)
{
	cout<<"BEZSENSOWNE\n";
	cout<<lvl[a]-lvl[b]+1<<"\n";
	int y=a;
	cout<<a<<" ";
	while(y!=b){
		y=par[y];
		cout<<y<<" ";
	}
	cout<<"\n";
	exit(0);
}

string conv(int a)
{
	string res="";
	while(a){
		if(a&1)
			res+="1";
		else
			res+="0";
		a>>=1;
	}
	if(res=="")
		res="0";
	return res;
}

void dfs(int a,int oj=-1)
{
	vis[a]=true;
	vector<pair<int,int> >ret,son;
	for(auto e:graf[a]){
		if(e.st==oj)
			continue;
		if(vis[e.st]){
			if(lvl[a]>lvl[e.st]){
				if(lvl[a]-lvl[e.st]>=C)
					wypisz(a,e.st);
				ret.pb(e);
			}
		}
		else
		{
			par[e.st]=a;
			lvl[e.st]=lvl[a]+1;
			dfs(e.st,a);
			son.pb(e);
		}
	}
	for(int mask=0;mask<(1<<C);mask++){
		for(auto e:ret)
			dp[a][mask]+=e.nd*( ((mask&1)!=0) == ( ((mask&(1<<(lvl[a]-lvl[e.st])))!=0) ) );
		for(auto e:son)
			dp[a][mask]+=min( dp[e.st][(mask<<1)&((1<<C)-1)]+e.nd*((mask&1)==0),dp[e.st][((mask<<1)&((1<<C)-1))+1] + e.nd*(mask&1) );
		//d(cerr<<a<<", mask: "<<conv(mask)<<" dp = "<<dp[a][mask]<<endl;)
	}
}
		
		

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>m;
	for(int i=0;i<m;i++){
		int a,b,w;
		cin>>a>>b>>w;
		graf[a].pb({b,w});
		graf[b].pb({a,w});
	}
	int res=0;
	for(int i=1;i<=n;i++){
		if(!vis[i])
		{
			dfs(i);
			res+=min(dp[i][0],dp[i][1]);
		}
	}
	
	cout<<"GRAMY\n";
	cout<<res<<"\n";	
	
	return 0;
}
