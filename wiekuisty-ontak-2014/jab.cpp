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

struct Edge {
	int x, y, v;
};

int n, m, k, dist[100][805];
vector<Edge> G[100][805];

void bellman() {
	deque<pair<int, int>> vert = {{1, 1}}, hor;
	for(int i=1; i<=n; i++)
		fill(dist[i], dist[i]+m+1, INF);
	dist[1][1] = 0;
	while(not vert.empty() or not hor.empty()) {
		int x, y; 
		tie(x, y) = (vert.empty() ? hor.front() : vert.front());
		(vert.empty() ? hor : vert).pop_front();
		for(auto& u:G[x][y]) {
			if(dist[x][y] + u.v < dist[u.x][u.y]) {
				dist[u.x][u.y] = dist[x][y] + u.v;
				auto& dq = (y == u.y ? vert : hor);
				if(dq.empty() or dist[u.x][u.y] <= dist[dq.front().st][dq.front().nd])
					dq.emplace_front(u.x, u.y);
				else
					dq.emplace_back(u.x, u.y);
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> k;
	for(int i=0; i<k; i++) {
		int a, b, d;
		char c;
		cin >> a >> b >> c >> d;
		swap(a, b);
		int x = a, y = b;
		x += (c == 'N');
		x -= (c == 'S');
		y += (c == 'E');
		y -= (c == 'W');
		G[a][b].push_back({x, y, d});
	}
	
	bellman();
	
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			cout << (dist[i][j] == INF ? "N" : to_string(dist[i][j])) << (j == m ? '\n' : ' ');
}