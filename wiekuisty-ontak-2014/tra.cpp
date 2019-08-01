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

struct Trapez {
	int a, b, c, d, ind, res=0;
	
	bool operator < (const Trapez& he) const {
		return make_pair(a, c) < make_pair(he.a, he.c);
	}
	static bool comp(const Trapez& a, const Trapez& b) {
		return make_pair(a.b, a.d) > make_pair(b.b, b.d);
	}
	
	friend istream& operator >> (istream& in, Trapez& t) {
		return in >> t.a >> t.b >> t.c >> t.d;
	}
};

constexpr int maxn = 500005;
int fen[maxn], base = 1;

void insert(int y, int val) {
	while(y < base) {
		fen[y] = max(fen[y], val);
		y += y&(-y);
	}
}
int query(int y) {
	int ret = 0;
	while(y > 0) {
		ret = max(ret, fen[y]);
		y -= y&(-y);
	}
	return ret;
}

struct cmp {
	bool operator () (const Trapez& a, const Trapez& b) {
		return make_pair(a.b, a.d) > make_pair(b.b, b.d);
	}
};
		


int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	vector<Trapez> T(n);
	map<int, int> M;
	for(int i=0; i<n; i++) {
		cin >> T[i];
		M[T[i].c], M[T[i].d];
		// M[T[i].c-1], M[T[i].d-1];
	}
	
	sort(T.begin(), T.end());
	for(int i=0; i<n; i++) T[i].ind = i;
	for(auto& it:M)
		it.nd = base++;
	
	int ans = 0;
	priority_queue<Trapez, vector<Trapez>, cmp> Q;
	for(auto& t:T) {
		while(not Q.empty() and Q.top().b <= t.a) {
			insert(M[Q.top().d], Q.top().res);
			Q.pop();
		}
		t.res = query(M[t.c]) + 1;
		ans = max(ans, t.res);
		Q.push(t);
	}
	
	cout << ans << "\n";
}