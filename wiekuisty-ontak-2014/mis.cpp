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
constexpr int INF=1e9+7;
constexpr LL INFL=1e18;

struct point
{
	int x,y;
	point(){}
	point(int xv,int yv)
	{
		x=xv,y=yv;
	}
	void get()
	{
		cin>>x>>y;
	}
};

int n;
vector< pair<point,point> >str;
point lo,hi,start;

inline bool isIn(pair<point,point> p)
{
	point tmp=p.st;
	for(int i=0;i<2;i++){
		if(lo.x<=tmp.x && tmp.x<=hi.x && lo.y<=tmp.y && tmp.y<=hi.y)
			return true;
		tmp=p.nd;
	}
	if( (lo.x<=p.st.x && p.st.x<=hi.x && lo.x<=p.nd.x && p.nd.x<=hi.x && ((p.st.y<=lo.y && p.nd.y>=hi.y) || (p.nd.y<=lo.y && p.st.y>=hi.y)) )
		|| (lo.y<=p.st.y && p.st.y<=hi.y && lo.y<=p.nd.y && p.nd.y<=hi.y && ((p.st.x<=lo.x && p.nd.x>=hi.x) || (p.nd.x<=lo.x && p.st.x>=hi.x))) )
		return true;
	return false;
}

bool check(int d)
{
	lo=point(-d,-d),hi=point(d,d);
	vector<pair<point,point> >tmp=str;
	bool ok=true;
	while(ok)
	{
		ok=false;
		for(int i=0;i<siz(tmp);i++)
			if(isIn(tmp[i])){
				lo.x=min(lo.x,tmp[i].st.x),hi.x=max(hi.x,tmp[i].st.x);
				lo.x=min(lo.x,tmp[i].nd.x),hi.x=max(hi.x,tmp[i].nd.x);
				lo.y=min(lo.y,tmp[i].st.y),hi.y=max(hi.y,tmp[i].st.y);
				lo.y=min(lo.y,tmp[i].nd.y),hi.y=max(hi.y,tmp[i].nd.y);
				ok=true;
				swap(tmp.back(),tmp[i]);
				tmp.pop_back();
				break;
			}
	}
	return isIn({start,start});
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	start.get();
	cin>>n;
	str.resize(n);
	for(auto& p:str)
	{
		p.st.get(),p.nd.get();
	}
	int l=0,r=max(abs(start.x),abs(start.y));
	while(l!=r)
	{
		int s=(l+r)/2;
		if(check(s))
			r=s;
		else
			l=s+1;
	}
	cout<<l<<"\n";

	return 0;
}
