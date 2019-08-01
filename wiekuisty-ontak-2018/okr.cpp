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

const int maxn=500005;
const int p1=101,p2=313,mod=INF;

int n;
string s;

int hasz[maxn][2],p1n[maxn],p2n[maxn];

void zahashuj()
{
	n=siz(s);
	//cerr<<n<<"\n";
	p1n[0]=p2n[0]=1;
	for(int i=1;i<=n;i++){
		p1n[i]=((LL)p1n[i-1]*p1)%mod;
		p2n[i]=((LL)p2n[i-1]*p2)%mod;
	}
	for(int i=1;i<=n;i++){
		hasz[i][0]=(s[i-1]+(LL)hasz[i-1][0]*p1)%mod;
		hasz[i][1]=(s[i-1]+(LL)hasz[i-1][1]*p2)%mod;
	}
}

inline int getHash1(int a,int d)
{
	a--;
	int res=hasz[a+d][0]-(((LL)hasz[a][0]*p1n[d])%mod);
	if(res<0)
		res+=mod;
	return res;
}
inline int getHash2(int a,int d)
{
	a--;
	int res=hasz[a+d][1]-(((LL)hasz[a][1]*p2n[d])%mod);
	if(res<0)
		res+=mod;
	return res;
}

bool same(int a,int b,int d)	//czy slowa o poczatkach w a i b o dlugosci d sa takie same
{
	//d(cerr<<"same("<<a<<","<<b<<","<<d<<")"<<endl;)
	a--,b--;
	int hsha=hasz[a+d][0]-(((LL)hasz[a][0]*p1n[d])%mod);
	int hshb=hasz[b+d][0]-(((LL)hasz[b][0]*p1n[d])%mod);
	if(hsha<0)
		hsha+=mod;
	if(hshb<0)
		hshb+=mod;
	if(hsha!=hshb)
		return false;
	hsha=hasz[a+d][1]-(((LL)hasz[a][1]*p2n[d])%mod);
	hshb=hasz[b+d][1]-(((LL)hasz[b][1]*p2n[d])%mod);
	if(hsha<0)
		hsha+=mod;
	if(hshb<0)
		hshb+=mod;
	if(hsha!=hshb)
		return false;
	return true;
}

int firstPos(int a,int b,int d)	//pierwsza pozycja na ktorej sie roznia, indeksowana od zera
{
	//d(cerr<<"firstPos("<<a<<","<<b<<","<<d<<")"<<endl;)
	int l=0,r=d;
	while(l!=r)
	{
		int sr=(l+r)/2;
		//d(cerr<<sr<<" ";)
		if(same(a,b,sr+1))
			l=sr+1;
		else
			r=sr;
	}
	//d(cerr<<"Zwr: "<<l<<endl;)
	return l;
}
	

bool ok(int d)
{
	int pos=firstPos(1,n-d+1,d);
	d(cerr<<"ok("<<d<<")";)
	d(cerr<<" , pos = "<<pos<<endl;)
	if(pos==d)
		return true;
	
	//zmieniamy hash prefiksu na literkę sufiksu
	int hsh11=getHash1(1,d);
	hsh11-=(s[pos]*(LL)p1n[d-pos-1])%mod;
	hsh11+=(s[n-d+pos]*(LL)p1n[d-pos-1])%mod;
	if(hsh11<0)
		hsh11+=mod;
	hsh11%=mod;
	int hsh12=getHash2(1,d);
	hsh12-=(s[pos]*(LL)p2n[d-pos-1])%mod;
	hsh12+=(s[n-d+pos]*(LL)p2n[d-pos-1])%mod;
	if(hsh12<0)
		hsh12+=mod;
	hsh12%=mod;
	if(d>n/2 && pos>=n-d){
		//nothing
	}
	else
	{
		int hsh21=getHash1(n-d+1,d);
		int hsh22=getHash2(n-d+1,d);
		if(hsh11==hsh21 && hsh12==hsh22)
			return true;
	}
	
	
	//teraz zmieniamy literkę na tą z prefiksu
	int hsh21=getHash1(n-d+1,d);
	hsh21-=(s[n-d+pos]*(LL)p1n[d-pos-1])%mod;
	hsh21+=(s[pos]*(LL)p1n[d-pos-1])%mod;
	if(hsh21<0)
		hsh21+=mod;
	hsh21%=mod;
	int hsh22=getHash2(n-d+1,d);
	hsh22-=(s[n-d+pos]*(LL)p2n[d-pos-1])%mod;
	hsh22+=(s[pos]*(LL)p2n[d-pos-1])%mod;
	if(hsh22<0)
		hsh22+=mod;
	hsh22%=mod;
	if(d>n/2 && n-d+pos<d)
	{
		int hsh11=getHash1(1,d);
		hsh11-=(s[n-d+pos]*(LL)p1n[d-(n-d+pos)-1])%mod;
		hsh11+=(s[pos]*(LL)p1n[d-(n-d+pos)-1])%mod;
		if(hsh11<0)
			hsh11+=mod;
		hsh11%=mod;
		int hsh12=getHash2(1,d);
		hsh12-=(s[n-d+pos]*(LL)p2n[d-(n-d+pos)-1])%mod;
		hsh12+=(s[pos]*(LL)p2n[d-(n-d+pos)-1])%mod;
		if(hsh12<0)
			hsh12+=mod;
		hsh12%=mod;
		if(hsh11==hsh21 && hsh12==hsh22)
			return true;
	}
	else
	{
		int hsh11=getHash1(1,d);
		int hsh12=getHash2(1,d);
		if(hsh11==hsh21 && hsh12==hsh22)
			return true;
	}
	return false;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin>>s;
	zahashuj();
	vector<int>ans;
	for(int i=1;i<n;i++){
		if(ok(i))
			ans.pb(n-i);
	}
	cout<<siz(ans)<<"\n";
	for(int i=siz(ans)-1;i>=0;i--)
		cout<<ans[i]<<" ";
	cout<<"\n";

	return 0;
}
