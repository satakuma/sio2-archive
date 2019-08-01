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

constexpr int maxn = 1000005;

int n, g[maxn], dp[maxn], deg[maxn];
bool vis[maxn];

int dfs(int a=1) {
	vis[a] = true;
	if(vis[g[a]]) return g[a];
	return dfs(g[a]);
}

void prepare() {
	if(dfs() != 1)
		g[1] = 1;
}

pair<int, int> get_max(int a) {
	deg[a] = 0;
	if(deg[g[a]] == 0)
		return {1, dp[a]};
	auto ret = get_max(g[a]);
	ret.st++, ret.nd = max(ret.nd, dp[a]);
	return ret;
}

pair<int, int> get_max_fil(int a=1) {
	deg[a] = 0;
	if(deg[g[a]] == 0) {
		assert(g[a] == 1);
		return {1, dp[a] + (a != 1)};
	}
	auto ret = get_max_fil(g[a]);
	ret.st++;
	ret.nd = max(ret.nd, dp[a] + (a != 1 ? ret.st : 0));
	return ret;
}

void solve() {
	for(int i=1; i<=n; i++)
		deg[g[i]]++;
	queue<int> q;
	for(int i=1; i<=n; i++) 
		if(not deg[i])
			q.push(i);
	
	while(not q.empty()) {
		auto a = q.front();
		q.pop();
		dp[g[a]] = max(dp[g[a]], dp[a] + 1);
		if(--deg[g[a]] == 0)
			q.push(g[a]);
	}
	
	auto ans = 0, cnt = 0;
	auto fil = get_max_fil().nd;
	for(int i=2; i<=n; i++) 
		if(deg[i]) {
			auto tmp = get_max(i);
			ans += tmp.st + tmp.nd;
			cnt++;
		}
	
	cout << cnt << " " << ans + fil << "\n";
}
	

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=1; i<=n; i++)
		cin >> g[i];
		
	prepare();
	solve();
}