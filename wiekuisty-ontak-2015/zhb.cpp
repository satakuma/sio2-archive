#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 1000005;

int n, m, k, p[22][maxn], no[maxn], rozm[maxn], lvl[maxn], lp, LOG;
vector<int> G[maxn];

void dfs(int a) {
	rozm[a] = 1;
	no[a] = lp++;
	for(auto v:G[a]) {
		if(v == p[0][a])
			continue;
		p[0][v] = a;
		lvl[v] = lvl[a] + 1;
		dfs(v);
		rozm[a] += rozm[v];
	}
}

void init() {
	LOG = __lg(n) + 1;
	dfs(1);
	
	p[0][1] = 1;
	for(int l=1; l<=LOG; l++)
		for(int i=1; i<=n; i++)
			p[l][i] = p[l-1][p[l-1][i]];
}

bool isAnc(int a, int b) {
	return no[a] <= no[b] and no[b] < no[a] + rozm[a];
}
bool go(int a, int d) {
	return lvl[a] <= d;
}
	
int jump(int a, int b, const function<bool(int, int)>& f) {
	auto l = LOG;
	while(l >= 0) {
		if(not f(p[l][a], b))
			a = p[l][a];
		--l;
	}
	return f(a, b) ? a : p[0][a];
}

int query(int a, int t) {
	auto lca = jump(a, m, isAnc);
	auto d = lvl[a] + lvl[m] - 2*lvl[lca];
	if(t >= d)
		return a;
	else if(t <= lvl[m] - lvl[lca])
		return jump(m, lvl[m] - t, go);
	else
		return jump(a, lvl[a] - (d-t), go);
}


int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> k;
	for(int i=0; i<n-1; i++) {
		int a, b; cin >> a >> b;
		G[a].emplace_back(b);
		G[b].emplace_back(a);
	}
	
	init();
	
	while(k--) {
		int v, t;
		cin >> v >> t;
		cout << (m = query(v, t)) << " ";
	}
	cout << "\n";

}
