#include<bits/stdc++.h>
using namespace std;

constexpr int INF = 1000 * 1000 * 1000 + 7;
constexpr int maxn = 100005;

int n, m, p;
vector<int> G[maxn];


void p1_solve() {
	int a, b;
	cin >> a >> b;
	vector<int> dist(n+1, INF);
	dist[a] = 0;
	queue<int> Q; Q.push(a);
	while(not Q.empty()) {
		auto w = Q.front();
		Q.pop();
		for(auto v:G[w]) {
			if(dist[v] > dist[w] + 1) {
				dist[v] = dist[w] + 1;
				Q.push(v);
			}
		}
	}
	
	cout << dist[b] << "\n";
	exit(0);
}

void tree_solve() {
	int LOG = __lg(n) + 1;
	vector<vector<int>> par(n+1, vector<int>(LOG+1));
	vector<int> no(n+1), dist(n+1), rozm(n+1);
	int lp = 1;
	function<void(int)> dfs = [&](int a) {
		no[a] = lp++;
		rozm[a] = 1;
		for(auto v:G[a]) {
			if(v != par[a][0]) {
				par[v][0] = a;
				dist[v] = dist[a] + 1;
				dfs(v);
				rozm[a] += rozm[v];
			}
		}
	};
	
	dfs(1);
	par[1][0] = 1;
	for(int l=1; l<=LOG; l++)
		for(int i=1; i<=n; i++)
			par[i][l] = par[par[i][l-1]][l-1];
		
	auto isAnc = [&](int a, int b) {
		return (no[a] <= no[b] and no[b] < no[a] + rozm[a]);
	};
	auto query = [&](int a, int b) {
		int u = a;
		for(int l=LOG; l>=0; l--) 
			if(not isAnc(par[u][l], b))
				u = par[u][l];
		if(not isAnc(u, b)) u = par[u][0];
		return dist[a] + dist[b] - 2 * dist[u];
	};
	
	for(int i=0; i<p; i++) {
		int a, b;
		cin >> a >> b;
		cout << query(a, b) << "\n";
	}
	
	exit(0);
}


int dist[200][maxn];

void bfs(int s, int d[]) {
	fill_n(d+1, n, INF);
	d[s] = 0;
	queue<int> Q;
	Q.push(s);
	while(not Q.empty()) {
		int w = Q.front();
		Q.pop();
		for(auto v:G[w]) {
			if(d[v] > d[w] + 1) {
				d[v] = d[w] + 1;
				Q.push(v);
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> n >> m >> p;
	for(int i=0; i<m; i++) {
		int a, b;
		cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	
	//if(p == 1) p1_solve();
	//if(m == n-1) tree_solve();
	
	vector<int> vertices(n);
	iota(vertices.begin(), vertices.end(), 1);
	shuffle(vertices.begin(), vertices.end(), mt19937(time(0)));
	
	constexpr int C = 150;
	int S = min(n, C);
	for(int i=0; i<S; i++) {
		bfs(vertices[i], dist[i]);
	}
	
	for(int i=0; i<p; i++) {
		int a, b;
		cin >> a >> b;
		int ans = INF;
		for(int j=0; j<S; j++) {
			ans = min(ans, dist[j][a] + dist[j][b]);
		}
		cout << ans << "\n";
	}
}
