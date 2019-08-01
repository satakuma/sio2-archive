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

constexpr int maxn = 200005;

struct Query {
	int x, y, a;
	
	bool operator < (const Query& he) const {
		if(make_pair(x, y) == make_pair(he.x, he.y)) {
			if((a == 1) != (he.a == 1))
				return a == 1;
			return false;
		}
		return make_pair(x, y) < make_pair(he.x, he.y);
	}
	
	friend istream& operator >> (istream& in, Query& q) {
		return in >> q.a >> q.x >> q.y;
	}
} query[maxn];

struct MaximalPrefix {
	set<pair<int, int>> S;
	
	MaximalPrefix() {
		S.emplace(-INF, -INF);
	}
	
	void add(int i, int x) {
		auto it = S.upper_bound({i, INF});
		--it;
		if(it->nd >= x) return;
		if(it->st < i) ++it;
		while(it != S.end() and it->nd <= x)
			it = S.erase(it);
		S.emplace(i, x);
	}
	
	int get(int i) { // on [-oo, i]
		auto it = S.upper_bound({i, INF});
		it--;
		return it->nd;
	}
};

int ans[maxn];

void f(int l, int r) {
	if(l+1 == r) return;
	
	auto s = (l+r) / 2;
	f(l, s), f(s, r);
	
	vector<pair<Query, int>> ev;
	for(int i=l; i<s; i++)
		if(query[i].a == 1)
			ev.emplace_back(query[i], i);
	for(int i=s; i<r; i++)
		if(query[i].a == 2)
			ev.emplace_back(query[i], i);
	
	sort(all(ev));
	MaximalPrefix T;
	for(auto& p:ev) {
		auto& Q = p.st;
		if(Q.a == 1)
			T.add(Q.y, Q.x + Q.y);
		else
			ans[p.nd] = min(ans[p.nd], Q.x + Q.y - T.get(Q.y));
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int q;
	cin >> q;
	for(int i=0; i<q; i++)
		cin >> query[i];
	
	fill_n(ans, q, INF);
	f(0, q);
	for(int i=0; i<q; i++)
		query[i].y *= -1;
	f(0, q);
	for(int i=0; i<q; i++)
		query[i].x *= -1;
	f(0, q);
	for(int i=0; i<q; i++)
		query[i].y *= -1;
	f(0, q);
	
	for(int i=0; i<q; i++)
		if(query[i].a == 2)
			cout << ans[i] << "\n";
}