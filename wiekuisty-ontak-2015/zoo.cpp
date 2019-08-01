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

constexpr int maxn = 50005;

int n, m, deg[maxn], sortd[maxn], kt[maxn];
vector<int> G[maxn], buck[maxn];

bool mark[maxn];
int e[1005], cnt[maxn];
int s[maxn*4], f[maxn*4];

void init() {
	iota(sortd, sortd+n, 1);
	sort(sortd, sortd+n, [&](int a, int b) {
		return deg[a] < deg[b];
	});
	
	for(int i=0; i<n; i++)
		kt[sortd[i]] = i;
	for(int i=1; i<=m; i++) {
		G[s[i]].emplace_back(f[i]);
		G[f[i]].emplace_back(s[i]);
	}
	
	for(int i=1; i<=n; i++) {
		for(int j=0; j<siz(G[i]); j++) {
			auto& x = G[i][j];
			if(kt[x] < kt[i]) {
				x = G[i].back();
				G[i].pop_back();
				j--;
				continue;
			}
		}
	}
}

int fu[maxn];

int fin(int a) {
	return fu[a] == a ? a : fu[a] = fin(fu[a]);
}

bool un(int a, int b) {
	a = fin(a), b = fin(b);
	fu[a] = b;
	return a != b;
}

void small_query(int c) {
	vector<int> v(c);
	for(auto& x:v) {
		cin >> x;
		mark[x] = true;
		fu[x] = x;
	}
	
	int V = c, E = 0, C = c;
	for(auto& x:v) {
		for(auto& u:G[x]) {
			if(mark[u]) {
				++E;
				C -= un(x, u);
			}
		}
	}
	for(auto x:v)
		mark[x] = false;
	
	cout << C + E - V << "\n";
}

void big_query(int);

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	for(int i=1; i<=n; i++) {
		cin >> deg[i];
		for(int j=0; j<deg[i]; j++) {
			int v; cin >> v;
			(s[v] ? f[v] : s[v]) = i;
		}
	}
	
	init();
	
	int q; cin >> q;
	while(q--) {
		int c;
		cin >> c;
		small_query(c);
		/*if(c < 500)
			small_query(c);
		else
			small_query(c); //big_query(c);*/
	}
}