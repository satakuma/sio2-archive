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
	
	set<LL> fib;
	LL f1 = 2, f2 = 3;
	fib.emplace(f1);
	while(f2 < INFL) {
		fib.insert(f2);
		auto tmp = f1 + f2;
		f1 = f2; 
		f2 = tmp;
	}
	
	set<LL> tr;
	vector<LL> v = {2, 3, 4, 6, 8};
	for(auto x:v) tr.insert(x);
	while(v.back() < INFL) {
		v.push_back(v.back() + v.rbegin()[3]);
		tr.insert(v.back());
	}
	
	int T; cin >> T;
	while(T--) {
		LL n, k;
		cin >> n >> k;
		if(k == 1) {
			if(n > 1 and __builtin_popcountll(n) == 1)
				cout << "R\n";
			else
				cout << "C\n";
		} else if(k == 2) {
			if(fib.count(n))
				cout << "R\n";
			else
				cout << "C\n";
		} else {
			if(tr.count(n))
				cout << "R\n";
			else
				cout << "C\n";
		}
	}
}