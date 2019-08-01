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

int cnt[2][1<<16];

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int d; cin >> d;
	while(d--) {
		int x; cin >> x;
		cnt[1][x & ((1<<16) - 1)]++;
		cnt[0][x >> 16]++;
	}
	
	int res = 0;
	for(int i=0; i<2; i++) {
		res <<= 16;
		for(int j=0; j<(1<<16); j++)
			if(cnt[i][j] & 1) {
				res += j;
				break;
			}
	}
	
	cout << res << '\n';
}