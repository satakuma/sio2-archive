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
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag,
         tree_order_statistics_node_update>;
*/



int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m, k;
	cin >> m >> n >> k;
	vector<pair<int, int>> pkt(k);
	for(auto& p:pkt)
		cin >> p.st >> p.nd;
	
	LL poj = m * n;
	LL pl = m * n * LL(n+1) / 2 + n * m * LL(m+1) / 2 - 2 * poj;
	LL res = ((LL)n*m * n*m - 2 * pl - poj) / 4 + pl + poj;
	
	for(int mask = 1; mask < (1<<k); mask++) {
		pair<int, int> mn(INF, INF), mx(0, 0);
		for(int i=0; i<k; i++) {
			if(mask & (1<<i)) {
				mn.st = min(mn.st, pkt[i].st);
				mn.nd = min(mn.nd, pkt[i].nd);
				mx.st = max(mx.st, pkt[i].st);
				mx.nd = max(mx.nd, pkt[i].nd);
			}
		}
		
		LL tmp = (LL) mn.st * mn.nd * (m - mx.st + 1) * (n - mx.nd + 1);
		res += (__builtin_popcount(mask) & 1 ? -1 : 1) * tmp;
	}
	
	cout << res << "\n";

	return 0;
}