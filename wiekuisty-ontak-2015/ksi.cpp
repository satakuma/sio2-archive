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

constexpr int maxn = 500005, mod = INF, base = 1 << 22;

int n, t[maxn];

struct Node {
	int val=1, prod=1, prop=0;
} przed[base<<1];

inline void mod_add(int& a, int x) {
	a += x;
	if(a >= mod) a -= mod;
}

void propagate(int a) {
	auto x = przed[a].prop;
	if(x == 0) return;
	mod_add(przed[2*a].prop, x);
	mod_add(przed[2*a].val, x);
	x = LL(x) * przed[2*a].prod % mod;
	mod_add(przed[2*a+1].prop, x);
	mod_add(przed[2*a+1].val, x);
	przed[a].prop = 0;
}

void merge(int a) {
	przed[a].prod = LL(przed[2*a].prod) * przed[2*a+1].prod % mod;
}

int getVal(int x, int a=1, int va=1, int vb=base) {
	if(x < va or vb < x) return 0;
	if(va == vb)
		return przed[a].val;
	propagate(a);
	auto s = (va+vb) / 2;
	return x <= s ? getVal(x, 2*a, va, s) :
					getVal(x, 2*a+1, s+1, vb);
}

int add(int x, int v, int a=1, int va=1, int vb=base) {
	if(vb < x) return 1;
	if(x <= va) {
		mod_add(przed[a].prop, v);
		mod_add(przed[a].val, v);
		return przed[a].prod;
	}
	propagate(a);
	auto s = (va+vb) / 2;
	LL prod = add(x, v, 2*a, va, s);
	prod = prod * add(x, v * prod % mod, 2*a+1, s+1, vb) % mod;
	return prod;
}

void addOne(int x, int a=1, int va=1, int vb=base) {
	if(x < va or vb < x) return;
	if(va == vb) {
		przed[a].prod++;
		return;
	}
	propagate(a);
	auto s = (va+vb) / 2;
	addOne(x, 2*a, va, s), addOne(x, 2*a+1, s+1, vb);
	merge(a);
}

void insert(int x, int val) {
	add(x+1, val);
	addOne(x);
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	long long ans = 0;
	for(int mx=0, i=0; i<n; i++) {
		int x; cin >> x;
		auto val = getVal(x);
		//cout << i << " " << val << endl;
		insert(x, val);
		if(mx > x)
			ans += val;
		else
			mx = x;
	}
	
	cout << ans % mod << "\n";
}