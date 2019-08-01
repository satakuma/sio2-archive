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

constexpr int maxn = 100005;

int n, m, s[maxn], e[maxn], si[maxn], ei[maxn], start[maxn], lp=1;
vector<pair<int, int>> mach[maxn];
pair<int, int> G[maxn*4];
int deg[maxn*4], repr[4*maxn], who[4*maxn];
bool mark[maxn*4];

void dfs(int a, int pt, int ind) {
	mach[a][pt].nd = ind;
	who[ind] = a;
	if(pt+1 == mach[a].size()) return;
	(si[mach[a][pt].st] ? ei : si)[mach[a][pt].st] = ind;
	
	if(not mach[a][pt+1].nd)
		dfs(a, pt+1, lp++);
	G[ind].nd = mach[a][pt+1].nd;
	
	int he = (s[mach[a][pt].st] == a ? e : s)[mach[a][pt].st];
	auto it = upper_bound(all(mach[he]), pair<int, int>(mach[a][pt].st, INF)) - mach[he].begin();
	
	if(not mach[he][it].nd)
		dfs(he, it, lp++);
	G[ind].st = mach[he][it].nd;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	for(int a, b, i=1; i<=m; i++) {
		cin >> a >> b;
		s[i] = a, e[i] = b;
		mach[a].emplace_back(i, 0);
		mach[b].emplace_back(i, 0);
	}
	for(int i=1; i<=n; i++)
		mach[i].emplace_back(m+i, 0);
	
	for(int i=1; i<=n; i++)
		dfs(i, 0, start[i] = lp++);
	
	for(int i=1; i<lp; i++)
		deg[G[i].st]++, deg[G[i].nd]++;
	queue<int> Q;
	for(int i=1; i<lp; i++)
		if(deg[i] == 0)
			Q.emplace(i);
	
	vector<int> top;
	while(not Q.empty()) {
		auto w = Q.front(); Q.pop();
		if(w == 0) continue;
		top.emplace_back(w);
		if(--deg[G[w].st] == 0)
			Q.emplace(G[w].st);
		if(--deg[G[w].nd] == 0)
			Q.emplace(G[w].nd);
	}
	reverse(all(top));
	
	auto build = [&]() {
		iota(repr, repr + lp, 0);
		for(int i=1; i<=n; i++)
			if(not mach[i].empty())
				mark[mach[i].back().nd] = true;
		for(auto a:top)
			if(not mark[a])
				repr[a] = repr[G[a].st];
	};
	
	vector<int> marked;
	auto set_mark = [&](int mi) {
		mark[si[mi]] = mark[ei[mi]] = true;
		marked.push_back(mi);
	};
	auto unmark = [&]() {
		for(auto mi:marked)
			mark[si[mi]] = mark[ei[mi]] = false;
		marked.clear();
	};
	
	auto change = [&](int mi) {
		for(auto a:{si[mi], ei[mi]})
			swap(G[a].st, G[a].nd);
	};
	int d = 0;
	auto query = [&](int a) {
		a = 1 + (a + d) % n;
		int y = start[a];
		if(y == 0) {
			cout << (d = a) << "\n";
			return;
		}
		
		while(repr[G[y].st]) y = repr[G[y].st];
		cout << (d = who[y]) << "\n";
	};
	
	int q; cin >> q;
	int sq = sqrt(q);
	
	while(q) {
		sq = min(sq, q);
		vector<pair<char, int>> queries(sq);
		for(auto& qr:queries) {
			cin >> qr.st >> qr.nd;
			if(qr.st == 'C')
				set_mark(qr.nd);
		}
		
		build();
		
		for(auto& qr:queries) {
			if(qr.st == 'C')
				change(qr.nd);
			else
				query(qr.nd);
		}
		
		unmark();
		q -= sq;
	}
}