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

const int maxn=3e5+5;

int n,q,rozm=1;
int tab[maxn],przed[4*maxn],ans[maxn];
int lft[maxn],rht[maxn];

void wstaw(int a,int b,int x)
{
	int va=a+rozm;
	int vb=b+rozm;
	przed[va]=max(przed[va],x);
	przed[vb]=max(przed[vb],x);
	while(va/2 != vb/2){
		if(!(va&1))
			przed[va+1]=max(przed[va+1],x);
		if(vb&1)
			przed[vb-1]=max(przed[vb-1],x);
		va>>=1,vb>>=1;
	}
}
int czytaj(int va)
{
	va+=rozm;
	int res=przed[va];
	while(va!=1){
		va>>=1;
		res=max(res,przed[va]);
	}
	return res;
}	

void build(){
	for(int i=0;i<n;i++){ //pamietaj
		tab[i]=czytaj(i);
		przed[i+rozm]=tab[i];
	}
	for(int i=rozm+n;i<2*rozm;i++){
		przed[i]=INF;
	}
	for(int i=rozm-1;i>0;i--)
		przed[i]=min(przed[2*i],przed[2*i+1]);
}

void spierpapier()
{
	cout<<"-1\n";
	exit(0);
}

int niuchaj(int va)
{
	while(va<rozm){
		if(przed[2*va]<przed[2*va+1])
			va=2*va;
		else
			va=2*va+1;
	}
	return va-rozm;
}

void wywal(int va)
{
	va+=rozm;
	przed[va]=INF;
	while(va!=1)
	{
		va>>=1;
		przed[va]=min(przed[2*va],przed[2*va+1]);
	}
}

int query(int a,int va,int vb,int xa,int xb,int v)
{
	if(xa<=va && vb<=xb){
		if(przed[a]<=v)	
			return niuchaj(a);
		return -1;
	}
	int s=(va+vb)/2;
	int res=-1;
	if(xa<=s)
		res=query(2*a,va,s,xa,xb,v);
	if(res!=-1)
		return res;
	if(s+1<=xb)
		res=query(2*a+1,s+1,vb,xa,xb,v);
	return res;
}
	
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	cin>>n>>q;
	while(rozm<n)
		rozm<<=1;
	
	for(int i=0;i<n;i++){
		lft[i]=0,rht[i]=n-1;
	}
	for(int i=0;i<q;i++){
		int l,r,a;
		cin>>l>>r>>a;
		lft[a]=max(lft[a],l);
		rht[a]=min(rht[a],r);
		wstaw(l,r,a);
	}
	build();
	for(int i=0;i<n;i++){
		int l=lft[i],r=rht[i];
		if(r<l)
			spierpapier();
		int a=query(1,1,rozm,l+1,r+1,i);
		if(a==-1)
			spierpapier();
		ans[a]=i;
		wywal(a);
	}
		
	for(int i=0;i<n;i++)
		cout<<ans[i]<<" ";
	cout<<"\n";
	
	
	
	
	
	
	
	
	return 0;
}