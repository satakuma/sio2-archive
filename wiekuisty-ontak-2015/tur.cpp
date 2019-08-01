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

constexpr int maxn = 2005;

int n, k, deg[maxn], cnt[maxn], place[maxn];
bool M[maxn][maxn], mark[maxn];
vector<int> base, spec;

vector<int> solve(int mask) {
	vector<int> ret, cur;
	for(int i=0; i<k; i++) {
		(mask & (1<<i) ? cur : ret).emplace_back(spec[i]);
	}
	
	for(auto x:cur)
		deg[x] = 0;
	for(auto x:cur)
		for(auto y:cur)
			deg[y] += M[x][y];
	queue<int> q;
	for(auto x:cur)
		if(deg[x] == 0)
			q.emplace(x);
	
	vector<int> tmp;
	while(not q.empty()) {
		auto w = q.front();
		q.pop();
		tmp.emplace_back(w);
		for(auto x:cur)
			if(M[w][x] and --deg[x] == 0)
				q.emplace(x);
	}
	
	if(tmp.size() < cur.size())
		return vector<int>(k+1, -1);
	cur = tmp;
	tmp.clear();
	
	for(auto x:base) {
		bool out = false;
		for(int i=0; i<siz(cur)-1; i++) {
			if(M[x][cur[i]] > M[x][cur[i+1]])
				out = true;
		}
		(out ? ret : tmp).emplace_back(x);
	}
	
	vector<vector<pair<int, int>>> A;
	for(auto x:tmp) {
		place[x] = find_if(all(cur), [&](int a) {
			return M[x][a];
		}) - cur.begin();
		
		auto i = upper_bound(all(A), place[x], [&](int val, vector<pair<int, int>>& v) {
			return val < place[v.back().st];
		}) - A.begin();
		if(i == A.size())
			A.emplace_back();
		A[i].emplace_back(x, i > 0 ? A[i-1].size()-1 : -1);
	}
	
	for(int i=A.size()-1, y=A.back().size()-1; i>=0; i--) {
		auto pom = A[i][y].nd;
		A[i][y] = A[i].back();
		A[i].pop_back();
		y = pom;
	}
	
	for(auto& v:A)
		for(auto& x:v)
			ret.emplace_back(x.st);
	
	return ret;
}


int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			cin >> M[i][j];
	
	cin >> k;
	spec.resize(k);
	for(auto& x:spec) {
		cin >> x;
		mark[x] = true;
	}
	//sort(all(spec));
	//spec.erase(unique(all(spec)), spec.end());
	//k = spec.size();
	
	for(int i=1; i<=n; i++)
		if(not mark[i])
			base.emplace_back(i);
	
	sort(all(base), [&](int a, int b) {
		return M[a][b];
	});
	
	auto ret = spec;
	for(int mask=0; mask<(1<<k); mask++) {
		auto&& tmp = solve(mask);
		if(tmp.size() < ret.size())
			ret = tmp;
	}
	
	cout << ret.size() << "\n";
	for(auto x:ret)
		cout << x << " ";
	cout << "\n";
}