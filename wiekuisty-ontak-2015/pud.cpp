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

constexpr int maxn=1e5+5,mod=1e9+33;

#define int LL

int n,k,sil[maxn],odwr[maxn],dp[maxn];
vector<int>frb;

bool is[maxn];

int fpow(int a,int b) {
	int res=1,pom=a;
	while(b) {
		if(b&1)
			res=((LL)res*pom)%mod;
		pom=((LL)pom*pom)%mod;
		b>>=1;
	}
	return res;
}

void preprocess() {
	for(auto a:frb) is[a]=true;
	sil[0]=1;
	for(int i=1;i<=n;i++) {
		sil[i]=((LL)sil[i-1]*i)%mod;
	}
	odwr[n]=fpow(sil[n],mod-2);
	for(int i=n-1;i>-1;i--) {
		odwr[i]=((LL)odwr[i+1]*(i+1))%mod;
	}
}

int f(int n,int k) {
	if(n-1-k<0) return 0;
	return ((LL)sil[n-1]*odwr[n-1-k])%mod;
}

void check() {
	vector<int>dpom(n+1);
	dpom[0]=1;
	for(int i=1;i<=n;i++) {
		for(int j=0;j<i;j++) {
			if(is[j+1]) continue;
			dpom[i]+=((LL)dpom[i-j-1]*f(i,j))%mod;
			dpom[i]%=mod;
		}
	}
	cerr<<dp[n]<<endl;
	if(dp[n]!=dpom[n]) cerr<<"CHUJ"<<endl,exit(1);
}

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin>>n>>k;
	frb.resize(k);
	for(auto& a:frb) cin>>a;
	preprocess(); sort(all(frb));
	
	dp[0]=1;
	LL sum=1;
	for(int i=1;i<=n;i++) {
		dp[i]=sum;
		for(auto j:frb) {
			if(j>i) break;
			dp[i]-=((LL)dp[i-j]*f(i,j-1))%mod;
			if(dp[i]<0)
				dp[i]+=mod;
			else
				dp[i]%=mod;
		}
		sum=(sum*i)%mod;
		sum=(sum+dp[i])%mod;
	}
	//check();
	cout<<dp[n]<<endl;
	
	return 0;
}