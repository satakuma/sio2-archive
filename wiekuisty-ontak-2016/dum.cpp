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

LL K(LL x) { return x * x; }

struct Tree {
	struct Node {
		int cnt, sum;
		LL sum1, sum2;
		vector<LL> adders;
		Node(int n=0): 
		cnt(0), sum(0), sum1(0), sum2(0), adders(n) {}
		
		LL shift(int k) {
			int b = 2 * k;
			LL ret = sum2;
			for(int l=siz(adders) - 1; l>=0; l--) {
				if(b >= (1 << l)) {
					ret += adders[l];
					b -= (1 << l);
				}
			}
			return ret + LL(K(k+1) - 1) * sum;
		}	
	};
	
	int n, base;
	vector<int> A;
	vector<Node> v;
	
	Tree(int n): n(n), A(n) {
		base = 1;
		while(base < n) base <<= 1;
		v.resize(2*base, __lg(n * 8));
	}
	
	void read() {
		for(auto& x:A)
			cin >> x;
	}
	
	
	
	void merge(int a) {
		v[a].sum = v[2*a].sum + v[2*a+1].sum;
		v[a].sum1 = v[2*a].sum1 + v[2*a+1].sum1 + (LL) v[2*a].cnt * v[2*a+1].sum;
		v[a].sum2 = v[2*a].sum2 + v[2*a+1].shift(v[2*a].cnt);
		v[a].adders[0] = v[2*a].adders[0] + v[2*a+1].adders[0] + (LL) v[2*a].cnt * v[2*a+1].sum;
		for(int i=1; i<siz(v[a].adders); i++) {
			v[a].adders[i] = v[a].adders[i-1] * 2;
		}
	}
	
	void build() {
		for(int i=0; i<n; i++) {
			v[i+base].sum = v[i+base].sum1 = v[i+base].sum2 = A[i];
			v[i+base].cnt = 1;
		}
		for(int i=base-1; i>0; i--) {
			v[i].cnt = v[2*i].cnt + v[2*i+1].cnt;
			merge(i);
			d(cerr << i << " " << make_pair(v[i].sum1, v[i].sum2) << endl;)
		}
	}
	
	void insert(int p, int x) {
		A[--p] = x;
		int va = p + base;
		v[va].sum = v[va].sum1 = v[va].sum2 = x;
		while(va > 1) {
			va >>= 1;
			merge(va);
		}
	}
	
	LL get(int a, int va, int vb, int xa, int xb, int type) {
		if(xa <= va and vb <= xb) {
			if(type == 0) return v[a].sum;
			if(type == 1) return v[a].sum1 + LL(va - xa) * v[a].sum;
			if(type == 2) return v[a].shift(va - xa);
			assert(false);
		}
		
		auto s = (va + vb) / 2;
		LL ret = 0;
		if(xa <= s)
			ret += get(2*a, va, s, xa, xb, type);
		if(s+1 <= xb)
			ret += get(2*a+1, s+1, vb, xa, xb, type);
		
		return ret;
	}		
	
	LL query(int s, int l, int r) {
		return get(1, 1, base, l, r, s);
	}
};
		

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	auto T = Tree(n);
	T.read();
	T.build();
	
	int q; cin >> q;
	while(q--) {
		int a; cin >> a;
		if(a >= 0) {
			int l, r;
			cin >> l >> r;
			cout << T.query(a, l, r) << "\n";
			d(cout << flush;)
		} else {
			int x; cin >> x;
			T.insert(-a, x);
		}
	}
}