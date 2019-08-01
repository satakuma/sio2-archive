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

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	LL k;
	int n;
	cin >> k >> n;
	string S;
	cin >> S;
	reverse(all(S));
	int lvl = __lg(k), width = 0;
	LL highest = k;
	for(auto c:S) {
		if(c == 'P') {
			lvl++, width++;
		} else {
			if(lvl == 0 or (width == 0 and highest % 2 != (c == 'R')))
				return cout << 0, 0;
			if(width == 0)
				highest /= 2;
			lvl--, width = max(width-1, 0);
		}
	}
	
	int res = 1;
	for(int i=0; i<width; i++)
		res = (res + res) % INF;
	
	cout << res << "\n";
}