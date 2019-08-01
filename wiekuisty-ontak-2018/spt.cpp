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

const int maxn=1505,maxm=1e6+5;

struct edge
{
	int a,b,v,id;
	bool q;
	void get(int i)
	{
		cin>>a>>b>>v;
		id=i;
	}
	bool operator <(const edge& b)const
	{
		if(v==b.v)
			return !q;
		return v>b.v;
	}
};

int n,m,q,lp;
vector<edge>kraw;
int fu[maxn];
vector<pair<int,int> >graf[maxn];
bool ciekaw[maxm];
int ans[maxm];
vector<pair<int,int> >zm[maxm];
int vis[maxn];

int fin(int a)
{
	return fu[a]==a?a:fu[a]=fin(fu[a]);
}

bool bfs(int s,int dest,int j,int v)
{
	lp++;
	queue<int>q;
	q.push(s);
	vis[s]=lp;
	while(!q.empty())
	{
		int w=q.front(); q.pop();
		if(w==dest)
			return true;
		for(auto& e:graf[w]){
			e.st=fin(e.st);
			if(vis[e.st]==lp)
				continue;
			int cur=0;
			while(cur+1<siz(zm[e.nd]) && zm[e.nd][cur+1].st<j)
				cur++;
			if(zm[e.nd][cur].nd>=v){
				vis[e.st]=lp;
				q.push(e.st);
			}
		}
	}
	return false;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin>>n>>m>>q;
	kraw.resize(m);
	for(int i=0;i<m;i++){
		kraw[i].get(i+1);
	}
	for(int i=0;i<q;i++){
		int co;
		cin>>co;
		if(co==1)
		{
			edge tmp;
			tmp.get(i);
			tmp.q=true;
			kraw.pb(tmp);
		}
		else
		{
			ans[i]=-1;
			int j,x;
			cin>>j>>x;
			if(!ciekaw[j]){
				zm[j].pb({-1,kraw[j-1].v});
				graf[kraw[j-1].a].pb({kraw[j-1].b,j});
				graf[kraw[j-1].b].pb({kraw[j-1].a,j});
			}
			ciekaw[j]=true;
			zm[j].pb({i,x});
		}
	}
	iota(fu,fu+n+1,0);
	sort(all(kraw));
	for(auto& e:kraw)
	{
		if(!e.q){
			if(ciekaw[e.id])
				continue;
			int va=fin(e.a),vb=fin(e.b);
			if(va!=vb){
				fu[vb]=va;
				for(auto f:graf[vb]){
					if(fin(f.st)!=va)
						graf[va].pb(f);
				}
			}
		}
		else
		{
			int va=fin(e.a),vb=fin(e.b);
			if(va==vb || bfs(va,vb,e.id,e.v))
				ans[e.id]=true;
		}
	}
	for(int i=0;i<q;i++){
		if(ans[i]==-1)
			continue;
		cout<<(ans[i]?"YES\n":"NO\n");
	}

	return 0;
}
