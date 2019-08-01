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
constexpr int mod=INF;

const int maxk=205;
const int maxn=1e6+5;

int n,k;
int sil[maxn],odwr[maxn];
int dp[2*maxk][maxk][maxk],suf[2*maxk][maxk][maxk];

int fastpot(int a,int b)
{
	if(b==0)
		return 1;
	if(b&1)
		return ((LL)a*fastpot(a,b-1))%mod;
	LL w=fastpot(a,b>>1);
	return (w*w)%mod;
}

void init()
{
	sil[0]=1;
	int N=max(n,k);
	for(int i=1;i<=N;i++)
		sil[i]=((LL)sil[i-1]*i)%mod;
	odwr[N]=fastpot(sil[N],mod-2);
	for(int i=N-1;i>=0;i--){
		odwr[i]=((LL)odwr[i+1]*(i+1))%mod;
	}
}

LL war(int n1,int k1)
{
	return ((LL)sil[n1]*odwr[n1-k1])%mod;
}
LL binom(int n1,int k1)
{
	if(k1>n1 || k1<0)
		return 0;
	LL res=((LL)sil[n1]*odwr[k1])%mod;
	return res*odwr[n1-k1]%mod;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin>>n>>k;
	init();
	dp[0][0][0]=1;
	suf[0][0][0]=1;
	LL res=0;
	for(int i=1;i<=2*k-1;i++)
		for(int lp=1;lp<=min(k,i);lp++)
			for(int r=min(k,i);r>0;r--){
				dp[i][lp][r]=(dp[i-1][lp-1][r-1]+suf[i-1][lp][r+1])%mod;
				d(cerr<<"dp["<<i<<"]["<<lp<<"]["<<r<<"] = "<<dp[i][lp][r]<<", ";)
				LL pom=res;
				res=(res+((dp[i][lp][r]*war(k,lp))%mod)*binom(n-1,i-1))%mod;
				d(cerr<<"dRES = "<<res-pom<<endl;)
				suf[i][lp][r]=(suf[i][lp][r+1]+dp[i][lp][r])%mod;
			}
	cout<<res<<"\n";
	
	d(cerr<<war(2,1)<<" "<<binom(0,0)<<endl;)
	return 0;
}
