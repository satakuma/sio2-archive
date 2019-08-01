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

int mp[5 * 1000 * 1000 + 5];
char **t;

int proceed(int n, int m, bool rev=false) {
	int lcm = 1;
	auto update = [&](int x) {
		if(lcm % x == 0) return;
		lcm = (LL) lcm * x / __gcd(lcm, x);
	};
	
	for(int i=0; i<n; i++) {
		if(lcm == m) break;
		int b = -1;
		mp[0] = b;
		for(int j=1; j<=m; j++) {
			while(b > -1 and (rev ? t[j-1][i] != t[b][i] : t[i][j-1] != t[i][b]))
				b = mp[b];
			mp[j] = ++b;
		}
		
		while(b and m % (m-b))
			b = mp[b];
		update(m-b);
	}
	
	return lcm;
}
		

int main()
{
	int n, m;
	
	scanf("%d%d", &n, &m);
	t = new char* [n];
	for(int i=0; i<n; i++) {
		t[i] = new char [m];
		for(int j=0; j<m; j++) {
			do {
				t[i][j] = getc_unlocked(stdin);
			} while(t[i][j] < 33);
		}
	}
	
	auto b = proceed(n, m);
	auto a = proceed(m, n, true);
	
	printf("%d %d\n", a, b);
	for(int i=0; i<a; i++) {
		for(int j=0; j<b; j++)
			putc_unlocked(t[i][j], stdout);
		puts("");
	}
}