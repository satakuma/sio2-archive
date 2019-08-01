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

inline void fst(int* x)
{
	(*x)=0;
	register char c=0;
	bool m=false;
	while(c<33)
		c=getc_unlocked(stdin);
	if(c=='-')
		m=true,c=getc_unlocked(stdin);
	while(c>32){
		(*x)=(*x)*10 +c-48;
		c=getc_unlocked(stdin);
	}
	if(m)
		(*x)=-(*x);
}


int n,pierw;//licznik=10;
LL r;

struct point
{
	int x,y;
	point(int xv=0,int yv=0){
		x=xv,y=yv;
	}
	void read(){
		fst(&x),fst(&y);
	}
	bool in_upper() const
	{
		return y==0?x>0:y>0;
	}
	LL getDist()const
	{
		return (LL)x*x+(LL)y*y;
	}
	bool isLeft(const point& b,const point z=point())const
	{
		return ((LL)x-z.x)*((LL)b.y-z.y)-((LL)b.x-z.x)*((LL)y-z.y)>0;
	}
	bool operator <(const point& b)const
	{
		if(!x and !y and (b.x or b.y))
			return true;
		else if(!b.x && !b.y)
			return false;
		if(in_upper()!=b.in_upper())
			return in_upper();
		if(!isLeft(b) and !b.isLeft(*this))
			return getDist()<b.getDist();
		return isLeft(b);
	}
	friend point operator +(const point& a,const point& b)
	{
		return {a.x+b.x,a.y+b.y};
	}
	friend point operator -(const point & a,const point& b)
	{
		return {a.x-b.x,a.y-b.y};
	}
};
vector<point>pkt;
point zero;

void makeHull()
{
	point base={INF,INF};
	for(auto p:pkt){
		if(p.y<base.y)
			base=p;
	}
	for(auto& p:pkt)
		p=p-base;
	sort(all(pkt));
	vector<point>tmp; tmp.pb(pkt[0]);
	for(int i=1;i<n;i++){
		auto p=pkt[i];
		while(siz(tmp)>1 && !tmp.back().isLeft(p,tmp[siz(tmp)-2]))
			tmp.pop_back();
		tmp.pb(p);
	}
	if(siz(tmp)>2 && !tmp.back().isLeft(tmp[0],tmp[siz(tmp)-2]))
		tmp.pop_back();
	pkt=tmp;
	for(auto& p:pkt)
		p=p+base;
	n=siz(pkt);
	pierw=min((int)(9*sqrt(n)+2),n);
	sort(all(pkt));
	d(cerr<<"OTOCZKA:\n";
	for(auto p:pkt)
		cerr<<p.x<<" "<<p.y<<endl;
		cerr<<"pierw: "<<pierw<<endl<<endl;
	)
}

LD calc(point &s,point& d)//d zmiejszyc
{
	LD a=s.x,b=s.y,x=d.x,y=d.y;
	LD x0=(a*x+b*y+sqrtl( (a*x+b*y)*(a*x+b*y)-(x*x+y*y)*(a*a+b*b-r)))/
			(x*x+y*y);
	return x0*sqrtl(d.getDist());
}

inline int fmod(int& a){
	if(a>=n) return a-n;
	return a;
}

void query(point& d)
{
	point d2=point(-d.x,-d.y);
	int l=0,p=n-1;
	while(l!=p)
	{
		int s=(l+p)/2;
		if(pkt[s]<d2)
			l=s+1;
		else
			p=s;
	}
	LD res=INFL;
	for(int i=l;i<l+pierw;i++)
		res=min(res,calc(pkt[fmod(i)],d));
	for(int i=l+n-1;i>l+n-1-pierw;i--)
		res=min(res,calc(pkt[fmod(i)],d));
	//if(licznik>0) for(auto p:pkt)res=min(res,calc(p,d));
	printf("%.8Lf\n",res);	
}

int main()
{
	int rt;
	zero.read(); fst(&rt), r=(LL)rt*rt;
	fst(&n);
	pkt.resize(n);
	for(auto& p:pkt){
		p.read(); p=p-zero;
	}
	makeHull();
	
	int q; fst(&q);
	while(q--){
		//licznik--;
		point k; k.read();
		query(k);
	}
	puts("");
	
	return 0;
}
