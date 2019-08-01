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

constexpr int maxn = 500005;

int n, m;
LL t[maxn];

void erase(int b) {
	LL pom = ((1LL << 61) - 1) ^ (1LL << b);
	for(int i=0; i<n; i++)
		t[i] &= pom;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	LL X = 0;
	for(int i=0; i<n; i++) {
		cin >> t[i];
		X ^= t[i];
	}
	
	LL ans = 0;
	for(int b=60; b >= 0; b--) {
		if(X & (1LL << b)) {
			erase(b);
			ans ^= (1LL << b);
			continue;
		}
		int free = 0, cnt = 0;
		LL cur = 0, lst = 0, mask = (1LL << 61) - (1LL << b);
		for(int i=0; i<n; i++) {
			cur ^= t[i];
			LL pom = (cur & mask);
			if((pom == 0) != (lst == 0))
				cnt += (pom != 0);
			else
				free += (pom == 0);
			lst = pom;
		}
		if(m - cnt > free) {
			erase(b);
			ans ^= (1LL << b);
		}
	}
	
	cout << ans << '\n';
}