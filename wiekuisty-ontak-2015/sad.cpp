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

#define int LL
#define INF INFL

constexpr int maxn = 500005;

struct Node {
	int mx=-INF, prop=0, mnp=INF, mxp=-INF;
	
	void add(int v) {
		mx += v;
		prop += v;
		mxp += v;
		mnp += v;
	}
	void ctmx(int v) {
		if(v > mnp)
			mnp = v;
		mxp = max(mxp, v);
		mx = max(mx, mxp);
	}
	void ctmn(int v) {
		if(v < mxp)
			mxp = v;
		mnp = min(mnp, v);
		mx = min(mx, mnp);
	}
} przed[maxn*4];

int n, q, rozm, h[maxn];

inline void merge(int a) {
	przed[a].mx = max(przed[2*a].mx, przed[2*a+1].mx);
}

void propagate(int a) {
	auto x = przed[a].prop, mn = przed[a].mnp, mx = przed[a].mxp;
	for(int v:{2*a, 2*a+1}) {
		przed[v].add(x);
		przed[v].ctmx(mx);
		przed[v].ctmn(mn);
	}
	przed[a].prop = 0;
	przed[a].mxp = -INF;
	przed[a].mnp = INF;
}

void build() {
	rozm = 1;
	while(rozm < n)
		rozm <<= 1;
	
	for(int i=1; i<=n; i++)
		przed[i+rozm-1].mx = h[i];
	for(int i=rozm-1; i>0; i--)
		merge(i);
}

void add(int a, int va, int vb, int xa, int xb, int v, bool cut=false) {
	if(xa <= va and vb <= xb) {
		//cerr << "touchuje: " << a << " : " << make_pair(va, vb) << endl;
		if(cut) {
			if(v < 0)
				przed[a].ctmn(-v);
			else
				przed[a].ctmx(v);
		}
		else 
			przed[a].add(v);
		return;
	}
	propagate(a);
	auto s = (va+vb) / 2;
	if(xa <= s)
		add(2*a, va, s, xa, xb, v, cut);
	if(s+1 <= xb)
		add(2*a+1, s+1, vb, xa, xb, v, cut);
	
	merge(a);
}

int query(int a, int va, int vb, int xa, int xb) {
	if(xa <= va and vb <= xb)
		return przed[a].mx;
	
	propagate(a);
	auto s = (va+vb) / 2;
	
	int res = -INF;
	if(xa <= s)
		res = max(res, query(2*a, va, s, xa, xb));
	if(s+1 <= xb)
		res = max(res, query(2*a+1, s+1, vb, xa, xb));
	merge(a);	
	return res;
}

void water() {
	int l, r, c;
	cin >> l >> r >> c;
	add(1, 1, rozm, l, r, c);
}

void cut(bool down=false) {
	int l, r, c;
	cin >> l >> r >> c;
	add(1, 1, rozm, l, r, c * (down ? -1 : 1), true);
}
void cut_down() { cut(true); }
void cut_up() { cut(); }

void ask() {
	int l, r;
	cin >> l >> r;
	cout << query(1, 1, rozm, l, r) << "\n";
}

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> q;
	for(int i=1; i<=n; i++)
		cin >> h[i];

	build();
	
	const function<void(void)> f[] = {water, cut_down, cut_up, ask};
	while(q--) {
		int type; cin >> type;
		f[type-1]();
	}
}