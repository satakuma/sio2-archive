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

int n, par[maxn], rozm[maxn], deg[maxn];
LL dp[maxn], best[maxn];
vector<pair<int, LL>> G[maxn];
LL mx, total;

void dfs(int a=1) {
	rozm[a] = 1;
	for(auto& e:G[a]) {
		if(e.st == par[a])
			continue;
		par[e.st] = a;
		dfs(e.st);
		rozm[a] += rozm[e.st];
		e.nd = rozm[e.st] * LL(n - rozm[e.st]);
		total += e.nd;
		dp[a] = max({dp[a], dp[e.st], best[e.st] + e.nd + best[a]});
		best[a] = max(best[a], best[e.st] + e.nd);
	}
}

void go(int a=1, LL dpp=0, LL bestp=0, LL epar=0) {
	if(a != 1)
		mx = max(mx, max({dp[a], dpp, dp[a] + dpp}));
	vector<pair<LL, int>> dp2, best2;
	dp2.emplace_back(dpp, par[a]);
	best2.emplace_back(bestp + epar, par[a]);
	for(auto& e:G[a]) {
		if(e.st == par[a])
			continue;
		dp2.emplace_back(dp[e.st], e.st);
		best2.emplace_back(best[e.st] + e.nd, e.st);
	}
	
	if(siz(dp2) < 10) {
		sort(all(dp2), greater<pair<LL, int>>());
		sort(all(best2), greater<pair<LL, int>>());
	} else {
		nth_element(dp2.begin(), dp2.begin() + 3, dp2.end(), greater<pair<LL, int>>());
		sort(dp2.begin(), dp2.begin() + 4, greater<pair<LL, int>>());
		nth_element(best2.begin(), best2.begin() + 3, best2.end(), greater<pair<LL, int>>());
		sort(best2.begin(), best2.begin() + 4, greater<pair<LL, int>>());
	}
	
	for(auto& e:G[a]) {
		if(e.st == par[a]) continue;
		if(siz(dp2) == 2) {
			go(e.st, max(dpp, bestp + epar), bestp + epar, e.nd);
			continue;
		}
		
		LL dpp2 = (e.st == dp2[0].nd ? dp2[1].st : dp2[0].st);
		int i = 0, j = 1;
		if(e.st == best2[0].nd)
			i = 2;
		else if(e.st == best2[1].nd)
			j = 2;
		
		go(e.st, max(dpp2, best2[i].st + best2[j].st), max(best2[i].st, best2[j].st), e.nd);
	}
}



int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0; i<n-1; i++) {
		int a, b;
		cin >> a >> b;
		G[a].emplace_back(b, 0);
		G[b].emplace_back(a, 0);
		deg[a]++, deg[b]++;
	}
	
	if(all_of(deg+1, deg+n+1, [&](int x) {
		return x <= 2;
	}))
		return cout << "0\n", 0;
	
	par[1] = -1;
	dfs();
	go(1);
	
	cout << total - mx << '\n';
}
