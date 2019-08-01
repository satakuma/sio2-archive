//Tymoteusz Wiśniewski XIV LO im. Stanisława Staszica w Warszawie
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ALL(c) (c).begin(),(c).end()

struct POINT
{
	int x,y;
	double kat;
};
struct op
{
	bool operator() (const POINT a,const POINT b)
	{
		return a.kat<b.kat;
	}
};
vector<POINT>wektory;

double alfa(int x,int y)
{
	if(y>=0)
		return 180/M_PI*atan2(y,x);
	else
		return 360 + 180/M_PI*atan2(y,x);
}

inline long long odl(long long x,long long y)
{
	return x*x+y*y;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin>>n;
	for(int i=0;i<n;++i)
	{
		int x,y;
		cin>>x>>y;
		wektory.pb({x,y,alfa(x,y)});
	}
	sort(ALL(wektory),op());
	int p=0,k=0;
	long long wynikx=0,wyniky=0,wynikw=0;
	while(p<n)
	{
		if(abs(wektory[p].kat-wektory[k].kat)<=180)
		{
			wynikx+=wektory[p].x;
			wyniky+=wektory[p].y;
			wynikw=max(wynikw,odl(wynikx,wyniky));
			p++;
		}
		else
		{
			wynikx-=wektory[k].x;
			wyniky-=wektory[k].y;
			wynikw=max(wynikw,odl(wynikx,wyniky));
			k++;
		}
	}
	p=0;
	while(k<n)
	{
		if(abs(wektory[p].kat-wektory[k].kat)>=180)
		{
			wynikx+=wektory[p].x;
			wyniky+=wektory[p].y;
			wynikw=max(wynikw,odl(wynikx,wyniky));
			p++;
		}
		else
		{
			wynikx-=wektory[k].x;
			wyniky-=wektory[k].y;
			wynikw=max(wynikw,odl(wynikx,wyniky));
			k++;
		}
	}
	cout<<wynikw<<endl;	
}
	
	
