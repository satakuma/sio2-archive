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

const int maxn=1e5+5;

struct line
{
	LL a,b;
	line(LL va=0,LL vb=INFL){
		a=va,b=vb;
	}
	LD intersect(const line& d) const {
		return ((LD)d.b-b)/(a-d.a);
	}
	LL get(const LL x){
		return a*x+b;
	}
};

struct hull
{
	vector<pair<line,LD> >v;
	
	void add(line l){
		while(siz(v)>1){
			if(l.a==v.back().st.a){
				if(l.b>v.back().st.b)
					return;
			}
			else if(v.back().st.intersect(l)>v.back().nd)
				break;
			v.pop_back();
		}
		v.pb({l,(v.empty()?-INFL:v.back().st.intersect(l))});
	}
	LL query(LL x)
	{
		if(v.empty()) return INFL;
		int l=0,r=siz(v)-1;
		while(l!=r){
			int sr=(l+r)/2+1;
			if(v[sr].nd>x)
				r=sr-1;
			else
				l=sr;
		}
		return v[l].st.get(x);
	}
};

struct node
{
	int v;
	hull h;
	node *par;
	node(int x=0,node *p=NULL){
		v=x,par=p;
	}
} *centr[maxn];

// LCA STUFF //

int n,LOG=1,lp=1;
vector<pair<int,int> >graf[maxn];
int no[maxn],rozmlca[maxn],par[maxn][20],dist[maxn];

void dfsLCA(int a,int oj=-1){
	rozmlca[a]=1;
	no[a]=lp++;
	for(auto e:graf[a]){
		if(e.st==oj)
			continue;
		dist[e.st]=dist[a]+e.nd;
		par[e.st][0]=a;
		dfsLCA(e.st,a);
		rozmlca[a]+=rozmlca[e.st];
	}
}

void makeLCA(){
	lp=1,dist[1]=0;
	dfsLCA(1);
	par[1][0]=1;
	LOG=1;
	while( (1<<LOG) < n ) LOG++;
	for(int l=1;l<=LOG;l++)
		for(int i=1;i<=n;i++)
			par[i][l]=par[par[i][l-1]][l-1];
}

inline bool isAnc(int a,int b){
	if(no[b]<no[a] || no[a]+rozmlca[a]<=no[b])
		return false;
	return true;
}

int getDist(int a,int b){
	if(isAnc(a,b))
		return dist[b]-dist[a];
	if(isAnc(b,a))
		return dist[a]-dist[b];
	int l=LOG,u=a;
	while(l>=0){
		if(!isAnc(par[a][l],b))
			a=par[a][l];
		--l;
	}
	a=par[a][0];
	return dist[b]+dist[u]-2*dist[a];
}

// CENTROID DECOMPOSITION // 

int best[maxn],rozm[maxn];
bool mark[maxn];

void dfsCalc(int a,int oj=-1){
	rozm[a]=1,best[a]=0;
	for(auto& e:graf[a]){
		if(mark[e.st] || e.st==oj)
			continue;
		dfsCalc(e.st,a);
		rozm[a]+=rozm[e.st];
		best[a]=max(best[a],rozm[e.st]);
	}
}

void dfsFind(int a,int size,int& c,int oj=-1){
	if(best[a]<=size/2 && size-rozm[a]<=size/2){
		c=a; return;
	}
	for(auto& e:graf[a])
		if(!mark[e.st] && e.st!=oj)
			dfsFind(e.st,size,c,a);
}

int getCentr(int a){
	dfsCalc(a);
	int ctr; dfsFind(a,rozm[a],ctr);
	return ctr;
}

void decompose(int v=1,node* parent=NULL){
	int c=getCentr(v);
	centr[c]=new node(c,parent);
	mark[c]=true;
	for(auto e:graf[c]){
		if(!mark[e.st])
			decompose(e.st,centr[c]);
	}
}

// QUERIES //

LL cost[maxn],dp[maxn];

void add(int v){
	node *cur=centr[v];
	while(cur!=NULL){
		cur->h.add(line(cost[v],dp[v]+getDist(v,cur->v)*cost[v]));
		cur=cur->par;
	}
}

LL query(int v){
	node *cur=centr[v];
	LL res=INFL;
	while(cur!=NULL){
		res=min(res,cur->h.query(getDist(v,cur->v)));
		cur=cur->par;
	}
	return res;
}
	
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int Z; cin>>Z;
	while(Z--){
		int s,t;
		cin>>n>>s>>t;
		for(int i=1;i<=n;i++)
			cin>>cost[i];
		for(int a,b,d,i=0;i<n-1;i++){
			cin>>a>>b>>d;
			graf[a].pb({b,d});
			graf[b].pb({a,d});
		}
		makeLCA();
		decompose();
		
		vector<int>tab;
		for(int i=1;i<=n;i++)
			if(i!=t && cost[i]<cost[s])
				tab.pb(i);
		sort(all(tab),[](const int& a,const int& b){return cost[a]>cost[b];});
		
		dp[s]=0; add(s);
		for(int a:tab){
			dp[a]=query(a);
			add(a);
		}
		
		cout<<query(t)<<'\n';
		
		for(int i=1;i<=n;i++){
			graf[i].clear(), mark[i]=false;
			delete centr[i];
		}
	}

	return 0;
}
