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

constexpr int maxn = 500005;

int n, cnt[maxn], players[maxn], dp[maxn];

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; i++) {
		int a; cin >> a;
		cnt[a]++;
	}
	
	for(int i=0, j=0; i<n; i++)
		for(int _=0; _<cnt[i]; _++)
			players[++j] = i;
	
	for(int i=1; i<=n; i++) {
		dp[i] = -INF;
		for(int x:{players[i], players[i]+1}) 
			if(i - x > -1 and players[i-x+1] >= x-1)
				dp[i] = max(dp[i], dp[i-x] + 1);
	}
	
	
	cout << (dp[n] < 0 ? -1 : dp[n]) << "\n";
}