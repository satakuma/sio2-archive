#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

const int maxn=200005;
const LL mn=1e10;
const LL big180=180*mn;

struct point
{
	int x,y;
	LL kat;
	void get()
	{
		cin>>x>>y;
	}
	bool operator < (const point& b)const 
	{
		return kat<b.kat;
	}
	void alfa(){
		if(x==0){
			if(y>0)
				kat=90*mn;
			else
				kat=-90*mn;
			return;
		}
		double beta=180/M_PI*atan2l(y,x);
		//if(x<0)
		//	beta+=180;
		kat=beta*mn;
	}
	void correct()
	{
		if(kat<0)
			kat+=mn*360;
	}
		
};
vector<point>pkt;
int n;

struct wektor
{
	int x=0,y=0;
	void dodaj(const point& p){
		x+=p.x;
		y+=p.y;
	}
	void usun(const point& p){
		x-=p.x;
		y-=p.y;
	}
	LL get_dist(const wektor& b)
	{
		int x1=x-b.x;
		int y1=y-b.y;
		return (LL)x1*x1+(LL)y1*y1;
	}
};

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin>>n;
	pkt.resize(n);
	for(int i=0;i<n;i++)
		pkt[i].get();
	for(int i=0;i<(int)pkt.size();i++){
		if(pkt[i].x==0 && pkt[i].y==0){
			swap(pkt[i],pkt.back());
			pkt.pop_back();
			i--;
		}
	}
	n=pkt.size();
	for(point& p:pkt){
		p.alfa(); p.correct();
	}
	
	sort(pkt.begin(),pkt.end());
	
	//for(auto& p:pkt)
	//	cout<<p.x<<" "<<p.y<<", kat: "<<p.kat<<endl;
		
	int p=0,k=0;
	wektor a,b;
	while(k<n && pkt[k].kat-pkt[p].kat<=big180)
		a.dodaj(pkt[k++]);
	for(int i=k;i<n;i++)
		b.dodaj(pkt[i]);
	LL res=a.get_dist(b);
	while(k<n)
	{
		while(k<n && pkt[k].kat-pkt[p].kat<=big180){
			a.dodaj(pkt[k]);
			b.usun(pkt[k++]);
			res=max(res,a.get_dist(b));
		}
		while(pkt[k].kat-pkt[p].kat>big180){
			a.usun(pkt[p]);
			b.dodaj(pkt[p++]);
			res=max(res,a.get_dist(b));
		}
	}
	k=0;
	while(p<n)
	{
		while(k<n && k<p && pkt[k].kat+2*big180-pkt[p].kat<=big180){
			a.dodaj(pkt[k]);
			b.usun(pkt[k++]);
			res=max(res,a.get_dist(b));
		}
		while(p<n && pkt[k].kat+2*big180-pkt[p].kat>big180){
			a.usun(pkt[p]);
			b.dodaj(pkt[p++]);
			res=max(res,a.get_dist(b));
		}
	}
	cout<<res<<'\n';
		
	return 0;
}
	
	
	
	
