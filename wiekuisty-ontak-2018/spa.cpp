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

const int maxn=505;

int n,m,lp=1;
map<LL,int>pkt[maxn];
LL len[maxn];
int fu[maxn*4];
vector< pair<int,LL> >graf[maxn*4];
LL d[maxn*4][maxn*4];
vector<int>act; vector<pair<pair<int,int>,LL>>kraw;
LD res=0;

int fin(int a){
	return fu[a]==a?a:fu[a]=fin(fu[a]);
}

void build()
{
	for(LL lst=0,lstv=-1,i=1;i<=n;i++,lst=0)
		for(auto it:pkt[i]){
			if(it.st==0){
				lstv=fin(it.nd);
				continue;
			}
			graf[fin(it.nd)].pb({fin(lstv),it.st-lst});
			graf[fin(lstv)].pb({fin(it.nd),it.st-lst});
			kraw.pb({{fin(it.nd),fin(lstv)},it.st-lst});
			tie(lst,lstv)=it;
		}
}

void dijkstra()
{
	priority_queue<pair<LL,int>,vector<pair<LL,int>>,greater<pair<LL,int>>>q;
	for(int i=1;i<lp;i++)
		if(fu[i]==i)
			act.pb(i);
	for(int& s:act){
		for(auto a:act)
			d[s][a]=INFL;
		d[s][s]=0;
		q.push({0,s});
		while(!q.empty()){
			LL u; int w;
			tie(u,w)=q.top(); q.pop();
			if(u>d[s][w])
				continue;
			res=max(res,(LD)u);
			for(auto& e:graf[w]){
				if(d[s][e.st]>u+e.nd){
					d[s][e.st]=u+e.nd;
					q.push({d[s][e.st],e.st});
				}
			}
		}
	}
}

void edge_node()
{
	for(auto& e:kraw){
		int a,b; tie(a,b)=e.st;
		for(auto& v:act)
			res=max(res,max(d[v][a],d[v][b])+((LD)e.nd-abs(d[v][a]-d[v][b]))/2);
	}
}

void edge_edge()
{
	for(int i=0;i<siz(kraw);i++)
		for(int j=i+1;j<siz(kraw);j++){
			int u,w,t,v; LL l1,l2;
			tie(u,w)=kraw[i].st,tie(t,v)=kraw[j].st;
			l1=kraw[i].nd,l2=kraw[j].nd;
			LL best=INFL; int a,b;
			for(int x:{u,w})
				for(int y:{t,v})
					if(d[x][y]<best){
						best=d[x][y];
						a=x,b=y;
					}
			if(a!=u) swap(u,w);
			if(b!=t) swap(t,v);
			LD y=((LD)d[u][v]+l2-best)/2;
			LD x=min(((LD)d[w][v]+l1+l2-best-2*y),((LD)l1+d[w][t]-best))/2;
			res=max(res,best+x+y);
		}
}				

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>len[i];
		pkt[i][0]=lp; fu[lp]=lp; lp++;
		pkt[i][len[i]]=lp; fu[lp]=lp; lp++;
	}
	while(m--){
		int s1,s2; LL l1,l2;
		cin>>s1>>l1>>s2>>l2;
		if(pkt[s1][l1]==0){
			pkt[s1][l1]=lp; fu[lp]=lp; lp++;
		}
		if(pkt[s2][l2]==0){
			pkt[s2][l2]=lp; fu[lp]=lp; lp++;
		}
		if(fin(pkt[s2][l2])!=fin(pkt[s1][l1]))
			fu[fin(pkt[s2][l2])]=fin(pkt[s1][l1]);
	}
	build();
	dijkstra();
	edge_node();
	edge_edge();
	
	LL ans=res;
	cout<<ans<<(ans==res?"\n":".5\n");
	
	return 0;
}
