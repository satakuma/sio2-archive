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

const int maxn=100005;

int n,q,pierw;
int tab[maxn];

bool same(LD a,LD b)
{
	LL mn=min(1e18/a,1e18/b);
	LL al=a*mn,bl=b*mn;
	return al==bl;
}

bool bigger(LD a,LD b)
{
	LL mn=min(1e18/a,1e18/b);
	LL al=a*mn,bl=b*mn;
	return al<bl;
}
	
struct point
{
	LD x,y;
	int ind=0;
	point(){}
	point(LD xv,LD yv,int i=0){
		x=xv,y=yv,ind=i;
	}
	bool onLeft(const point& b,const point& base)const
	{
		return (x-base.x)*(b.y-base.y)-(y-base.y)*(b.x-base.x)>0;
	}
};
point base=point(0,0,0);

bool operator <(const point& a,const point& b)
{
	return a.x>b.x;
}
LD operator*(const point& a,const point& b)
{
	return a.x*b.x+a.y*b.y;
}
point operator -(const point& a,const point& b)
{
	return point(a.x-b.x,a.y-b.y);
}

struct prost
{
	point a;
	point l,r;
};

prost turn(point a,point b)
{
	point res=b-a;
	return {point(res.y,-res.x),a,b};
}

struct hull
{
	vector<point>pkt;
	vector<int>ind;
	vector<prost>ar;
	LL sum=0;
	void refresh()
	{
		pkt.clear();
		sum=0;
		for(auto a:ind){
			sum+=tab[a];
			pkt.pb({(LD)1/a,(LD)sum/a,a});
		}
	}
		
	void build()
	{
		if(pkt.empty())
			return;
		sort(all(pkt));
		vector<point>tmp;
		tmp.pb(pkt[0]);
		for(int i=1;i<siz(pkt);i++)
		{
			while(siz(tmp)>1 && pkt[i].onLeft(tmp.back(),tmp[siz(tmp)-2]))
				tmp.pop_back();
			tmp.pb(pkt[i]);
		}
		ar.clear();
		for(int i=0;i<siz(tmp)-1;i++){
			ar.emplace_back(turn(tmp[i],tmp[i+1]));
		}
		if(ar.empty())
		{
			ar.emplace_back(turn(tmp[0],tmp[0]));
		}
	}
	pair<LD,int> query(point x)
	{
		int l=0,r=siz(ar);
		while(l!=r)
		{
			int s=(l+r)/2;
			if(ar[s].a.onLeft(x,base))
				l=s+1;
			else
				r=s;
		}
		l=max(0,l-2);
		r=min(siz(ar)-1,r+1);
		LD res=0;
		int ans=-1;
		for(int i=l;i<=r;i++){
			if(bigger(res,x*ar[i].l)){
				ans=ar[i].l.ind;
				res=x*ar[i].l;
			}
			if(bigger(res,x*ar[i].r)){
				ans=ar[i].r.ind;
				res=x*ar[i].r;
			}
		}
		return {res,ans};
	}
};
hull kub[400];

void init()
{
	for(int i=1;i<=n;i++)
		kub[i/pierw].ind.pb(i);
	for(int i=0;i<=pierw;i++){
		hull& h=kub[i];
		h.refresh();
		h.build();
	}
}	

void insert(int p,int v)
{
	tab[p]=v;
	int j=p/pierw;
	kub[j].refresh();
	kub[j].build();
}	

void query()
{
	LL sum=0;
	LD mx=0;
	int ans=-1;
	for(int i=0,kand;i<=pierw;i++){
		LD tmpMx;
		tie(tmpMx,kand)=kub[i].query(point(sum,1));
		if(bigger(mx,tmpMx)){
			mx=tmpMx;
			ans=kand;
		}
		sum+=kub[i].sum;
	}
	cout<<ans<<"\n";
}
		

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	//point a,b;
	//cin>>a.x>>a.y>>b.x>>b.y;
	//cout<<(a<b)<<endl;

	cin>>n>>q;
	pierw=sqrt(n)+1;
	for(int i=1;i<=n;i++){
		cin>>tab[i];
	}
	init();
	d(cerr<<pierw<<endl;)
	
	while(q--)
	{
		int p,b;
		cin>>p>>b;
		insert(p,b);
		query();
	}
		
	return 0;
}
