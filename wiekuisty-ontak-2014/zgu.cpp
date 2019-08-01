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

constexpr int maxn = 305;

int n;
struct Edge {
	int a, b;
	unsigned int v;
	Edge(int _a, int _b, int _v):
	a(_a), b(_b), v(_v) {}
	
	bool operator < (const Edge& e) const {
		return v < e.v;
	}
	
	friend ostream& operator << (ostream& out, const Edge& e) {
		return out << e.a << " " << e.b << " " << e.v;
	}
};
vector<Edge> edges;


unsigned int dist[maxn][maxn];


int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			int x; cin >> x;
			if(x > 0) 
				edges.emplace_back(i, j, x);
		}
	}
	
	sort(all(edges));
	
	int sq = sqrt(edges.size());
	vector<Edge> tmp, ans;
	for(int i=1; i<=n; i++) {
		fill(dist[i], dist[i]+n+1, INF);
		dist[i][i] = 0;
	}
	
	auto add = [&](Edge& e) {
		for(int i=1; i<=n; i++)
			dist[e.a][e.b] = min(dist[e.a][e.b], dist[e.a][i] + dist[i][e.b]);
		for(auto& q:tmp) 
			dist[e.a][e.b] = min(dist[e.a][e.b], dist[e.a][q.a] + (unsigned int)q.v + dist[q.b][e.b]);
		
		if(dist[e.a][e.b] > e.v) {
			dist[e.a][e.b] = e.v;
			tmp.emplace_back(e);
			ans.emplace_back(e);
		}
	};	
		
	for(int i=0; i<siz(edges);) {
		int j = i;
		while(j < siz(edges) and tmp.size() < sq and 2*edges[i].v > edges[j].v)
			add(edges[j++]);
		tmp.clear();
		i = j;
	}
	
	sort(all(ans), [&](const Edge a, const Edge b) {
		return (a.a == b.a ? a.b < b.b : a.a < b.a);
	});
	
	cout << ans.size() << "\n";
	for(auto& e:ans)
		cout << e << "\n";
}