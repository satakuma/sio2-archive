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

const int maxn=1e5+5;

int n,mx,tab[maxn];
vector<bool>dp[22];

int check(int mask)
{
	int cnt=0;
	for(int i=0;i<=mx;i++){
		if(mask&(1<<i))
			continue;
		int tmp=mask&((1<<i)-1);
		if(dp[i][tmp])
			cnt++;
	}
	return cnt;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin>>n;
	mx=0;
	for(int i=0;i<n;i++){
		int a; cin>>a;
		int bit=31-__builtin_clz(a);
		mx=max(mx,bit);
		tab[i]=a;
	}
	for(int i=0;i<=mx;i++){
		dp[i].resize(1<<(i));
	}
	for(int i=0;i<n;i++){
		int bit=31-__builtin_clz(tab[i]);
		dp[bit][tab[i]^(1<<bit)]=true;
	}
	for(int i=1;i<=mx;i++){
		for(int j=0;j<i;j++)
			for(int subs=0;subs<(1<<i);subs++)
				if(subs&(1<<j))
					dp[i][subs]=(dp[i][subs^(1<<j)] || dp[i][subs]);
	}
	int res=0;
	for(int i=0;i<(1<<(mx+1));i++){
		res=max(res,check(i));
	}
	
	cout<<res<<"\n";

	return 0;
}
