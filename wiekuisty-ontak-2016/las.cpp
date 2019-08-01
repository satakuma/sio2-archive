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
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag,
         tree_order_statistics_node_update>;
*/

constexpr int maxn = 200005;

int n, m;
vector<int> G[maxn];
bool vis[maxn];
int rozm[maxn];
pair<int, int> best[maxn];
LL dp[maxn];

void dfs(int a) {
	vis[a] = true;
	rozm[a] = 1;
	for(auto v:G[a]) {
		if(not vis[v]) {
			dfs(v);
			rozm[a] += rozm[v];
			best[a] = max(best[a], make_pair(rozm[v], v));
			dp[a] += dp[v] + rozm[v];
		}
	}
}

int go(int a, int cnt=0) {
	if(best[a].nd == 0 or 0 <= rozm[a] + cnt - 2 * best[a].st) 
		return a;
	return go(best[a].nd, cnt + rozm[a] - best[a].st);
}

pair<int, int> proceed(int i) {
	dfs(i);
	return {rozm[i], go(i)};
}

LL calc_sum(int a, int par=-1) {
	LL ret = 0;
	rozm[a] = 1;
	for(auto v:G[a]) 
		if(v != par) {
			ret += calc_sum(v, a);
			ret += (LL) rozm[v] * (n - rozm[v]);
			rozm[a] += rozm[v];
		}
	return ret;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	auto add_edge = [&](int a, int b) {
		G[a].push_back(b);
		G[b].push_back(a);
	};

	cin >> n >> m;
	for(int a, b, i=0; i<m; i++) {
		cin >> a >> b;
		add_edge(a, b);
	}
	
	vector<pair<int, int>> parts;
	for(int i=1; i<=n; i++)
		if(not vis[i])
			parts.push_back(proceed(i));
	
	sort(all(parts), greater<pair<int, int>>());
	for(size_t i=1; i<parts.size(); i++) {
		auto a = parts[0].nd, b = parts[i].nd;
		add_edge(a, b);
	}
	
	cout << calc_sum(1) << '\n';
}