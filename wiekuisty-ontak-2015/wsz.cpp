#include<bits/stdc++.h>
using namespace std;
#define st first
#define nd second
#define pb push_back

constexpr int maxn = 200005;

int n, m, root, res, in[maxn], t;
vector<pair<int, int>> G[maxn];
vector<int> ans;

int dfs(int a, int from=-1, int par=-1) {
	int cnt = 0;
	in[a] = ++t;
	for(auto e:G[a]) {
		if(e.nd == from) continue;
		if(not in[e.st])
			cnt += dfs(e.st, e.nd, a);
		else if(in[e.st] < in[a])
			cnt++;
	}
	if(cnt > 1 or (cnt == 1 and par == root)) {
		res++;
		ans.pb(a);
		cnt = 0;
	}
	return cnt;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> root;
	for(int i=0; i<m; i++) {
		int a, b; cin >> a >> b;
		G[a].emplace_back(b, i);
		G[b].emplace_back(a, i);
	}
	
	dfs(root);
	
	cout << res << "\n";
	for(auto a:ans)
		cout << a << ' ';
	cout << endl;
}