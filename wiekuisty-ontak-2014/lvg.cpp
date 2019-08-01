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

constexpr int maxn = 202, maxk = 5;

int n, k;
int G[maxk][maxn];
vector<pair<int, int>> Q[maxn][maxn];
bool vis[maxn][maxn];

void make_edges(int a, int b) {
	assert(a <= b);
	for(int i=0; i<k; i++) {
		int x = G[i][a], y = G[i][b];
		if(x > y) swap(x, y);
		Q[x][y].emplace_back(a, b);
	}
}

void dfs(int x, int y) {
	vis[x][y] = true;
	for(auto& p:Q[x][y]) {
		if(not vis[p.st][p.nd])
			dfs(p.st, p.nd);
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int T; cin >> T;
	while(T--) {
		cin >> n >> k;
		for(int i=0; i<k; i++)
			for(int j=0; j<n; j++)
				cin >> G[i][j];
		for(int i=0; i<n; i++)
			for(int j=i; j<n; j++)
				Q[i][j].clear(), vis[i][j] = false;
		for(int i=0; i<n; i++)
			for(int j=i; j<n; j++)
				make_edges(i, j);
		
		dfs(0, 0);
		bool ex = false;
		for(int i=0; i<n; i++)
			for(int j=i; j<n; j++)
				if(not vis[i][j]) {
					ex = true;
					break;
				}
		
		cout << (ex ? "NIE\n" : "TAK\n");
	}
}