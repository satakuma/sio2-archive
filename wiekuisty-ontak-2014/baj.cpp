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

LL solve(int n) {
	LL ret = 0;
	int hi = 1;
	for(int& i=hi; i*i<=n; i++) {
		ret += n % i;
	}
	hi--;
	
	for(int i=1; i*i<n; i++) {
		LL l = n/i, r = n/(i+1) + 1;
		r = max(r, hi+1LL);
		l -= (n % l == 0);
		r += (n % r == 0);
		ret += ((n % l) + (n % r)) * max(0LL, l-r+1) / 2;
	}
	
	return ret;
}



int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int Z; cin >> Z;
	while (Z--) {
		int n; cin >> n;
		cout << solve(n) << "\n";
	}
}