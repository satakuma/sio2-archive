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

constexpr int maxn = 200005;

int n, A[maxn];

struct Node {
	LL mn = INFL, prop = 0;
	void operator += (LL x) {
		mn += x, prop += x;
	}
} przed[maxn << 2];

int base = 1;

void merge(int a) {
	przed[a].mn = min(przed[2*a].mn, przed[2*a+1].mn);
}

void propagate(int a) {
	for(auto v:{2*a, 2*a+1})
		przed[v] += przed[a].prop;
	przed[a].prop = 0;
}

void build() {
	while(base <= n) base <<= 1;
	for(int i=0; i<=n; i++)
		przed[i+base].mn = A[i];
	for(int i=base-1; i>0; i--)
		merge(i);
}

void add(int a, int va, int vb, int xa, int xb, int v) {
	if(xa <= va and vb <= xb) {
		przed[a] += v;
		return;
	}
	propagate(a);
	
	auto s = (va+vb) / 2;
	if(xa <= s)
		add(2*a, va, s, xa, xb, v);
	if(s+1 <= xb)
		add(2*a+1, s+1, vb, xa, xb, v);
	
	merge(a);
}
void add(int l, int r, int x) {
	add(1, 0, base-1, l, r, x);
}

LL get_min(int a, int va, int vb, int xa, int xb) {
	if(xa <= va and vb <= xb)
		return przed[a].mn;
	propagate(a);
	auto s = (va+vb) / 2;
	LL ret = INFL;
	if(xa <= s)
		ret = min(ret, get_min(2*a, va, s, xa, xb));
	if(s+1 <= xb)
		ret = min(ret, get_min(2*a+1, s+1, vb, xa, xb));
	
	merge(a);
	return ret;
}
LL get_min(int l, int r) {
	return get_min(1, 0, base-1, l, r);
}

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	vector<pair<int, int>> bargains;
	for(int i=1; i<=n; i++) {
		int t, x;
		cin >> t >> x;
		A[i] = A[i-1];
		if(t == 1)
			bargains.emplace_back(x, -i);
		else {
			A[i] += x;
		}
	}
	
	build();
	sort(all(bargains));
	
	int cnt = 0;
	for(auto b:bargains) {
		b.nd = -b.nd;
		if(b.st <= 0 or get_min(b.nd, n) >= b.st) {
			cnt++;
			add(b.nd, n, -b.st);
		}
	}
	
	cout << (get_min(1, n) >= 0 ? cnt : -1) << '\n';
}