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

constexpr int maxn = 100005;

int n, d1, d2, c1, c2, c, A[maxn];
int lst[maxn], _A[maxn];

LL compute(int x) {
	int carry = x;
	LL ret = (LL) x * c;
	
	iota(lst+1, lst+n+1, 1);
	fill(_A, _A+n+1, 0);
	
	function<int(int)> fin = [&](const int a) {
		if(a < 0) return 0;
		return lst[a] == a ? a : lst[a] = fin(lst[a]);
	};
	auto erase = [&](const int a) {
		lst[a] = a-1;
	};
	
	for(int i=1; i<=n; i++) {
		int C = A[i];
		auto fcarry = min(carry, C);
		C -= fcarry;
		carry -= fcarry;
		
		int it;
		while(C and (it = fin(i - d2))) {
			auto pom = min(_A[it], C);
			ret += (LL) pom * c2;
			C -= pom;
			_A[it] -= pom;
			
			if(_A[it] == 0) erase(it);
		}
		
		while(C and (it = fin(i - d1))) {
			auto pom = min(_A[it], C);
			ret += (LL) pom * c1;
			C -= pom;
			_A[it] -= pom;
			
			if(_A[it] == 0) erase(it);
		}
		
		if(C) return INFL;
		_A[i] = A[i];
	}
	
	return ret;
}	

LL solve() {
	int L = 0, R = accumulate(A+1, A+n+1, 0);
	while(L < R) {
		auto S = (L+R) / 2;
		if(compute(S) >= compute(S+1))
			L = S + 1;
		else
			R = S;
	}
	
	return compute(L);
}			

void test() {
	int X; cin >> X;
	cerr << compute(X) << endl;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> d1 >> d2 >> c1 >> c2 >> c;
	for(int i=1; i<=n; i++)
		cin >> A[i];
	
	if(d1 > d2)
		swap(d1, d2), swap(c1, c2);
	
	// assume d1 < d2 and c1 > c2
	if(c1 < c2)
		c2 = c1;

	//test();
	//for(int i=1; i<=24; i++)
	//	cout << make_pair(i, compute(i)) << endl;
	
	cout << solve() << "\n";
}