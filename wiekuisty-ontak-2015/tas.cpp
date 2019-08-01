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
template<class L, class R> ostream &operator<<(ostream &os, pair<L,R> P) {
  return os << "(" << P.st << "," << P.nd << ")";
}

constexpr int maxn=2e5+5,p=313,mod=INF;

int n,m,A[maxn],B[maxn],pt[maxn];
int ha[maxn],hb[maxn];

void process(int a[],int N,int tab[]){
	for(int i=1;i<=N;i++)
		tab[i]=((LL)tab[i-1]*p+a[i-1])%mod;
}

int f(int a,int b){
	int l=0,r=min(n-a,m-b)+1;
	while(l<r){
		int s=(l+r)/2+1;
		int h1=ha[a+s-1]-(((LL)ha[a-1]*pt[s])%mod);
		int h2=hb[b+s-1]-(((LL)hb[b-1]*pt[s])%mod);
		if(h1<0) h1+=mod;
		if(h2<0) h2+=mod;
		if(h1==h2)
			l=s;
		else
			r=s-1;
	}
	return l;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin>>n;
	for(int i=0;i<n;i++) cin>>A[i];
	cin>>m;
	for(int i=0;i<m;i++) cin>>B[i];
	pt[0]=1;
	for(int i=1;i<=max(n,m);i++)
		pt[i]=((LL)pt[i-1]*p)%mod;
	process(A,n,ha),process(B,m,hb);
	int i=0,j=0;
	//vector<pair<int,int>>v;
	//vector<int>g;
	while(i<n and j<m){
		//v.pb({i,j});
		int l=f(i+1,j+1);
		//g.pb(l);
		if(i+l==n){
			cout<<B[j++]<<" ";
		}
		else if(j+l==m){
			cout<<A[i++]<<" ";
		}
		else
		{
			if(A[i+l]<B[j+l]){
				cout<<A[i++]<<" ";
			}
			else
			{
				cout<<B[j++]<<" ";
			}
		}		
	}
	while(i<n)
		cout<<A[i++]<<" ";
	while(j<m)
		cout<<B[j++]<<" ";
	//i=0;
	//for(auto p:v)
	//	cerr<<p<<" "<<g[i++]<<endl;
	return 0;
}