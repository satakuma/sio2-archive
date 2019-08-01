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

constexpr int maxk = 1000005;

int k, p, q, r, cnt[maxk], t[maxk], ways[maxk];


int fpow(LL a, int b, int mod) {
	LL ret = 1;
	while(b) {
		if(b&1)
			ret = ret * a % mod;
		(a *= a) %= mod;
		b >>= 1;
	}
	return ret;
}


int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> k >> p >> q >> r;
	for(int i=0; i<k; i++) {
		char c; cin >> c;
		t[i] = c - '0';
	}
	
	LL P = 0, Q = 0;
	int oq = fpow(10, q-2, q);
	int od = oq;
	for(int i=0; i<k-1; i++) {
		P = (P * 10 + t[i]) % p;
		Q = (Q * 10 + t[i]) % q;
		ways[i] = cnt[(Q * od) % q];	
		if(i and P == 0 and t[i] == 0)
			ways[i]++;
		if(t[i+1] and P == 0)
			cnt[(Q * od) % q]++;
		od = (LL)od * oq % q;
	}
	
	LL ans = 0, pot = 1, R = 0;
	for(int i=k-1; i>0; i--, pot = pot * 10 % r) {
		R = (R + pot*t[i]) % r;
		if(R == 0 and (t[i] or i == k-1))
			ans += ways[i-1];
	}
	
	
	cout << ans << "\n";
}