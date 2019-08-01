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

constexpr int maxn = 1005;


int n, t[2][maxn];
pair<int, int> pos[2*maxn];

constexpr int base = 1000*1000*1000;
constexpr LL BASE = (LL) base * base;
struct Big {
	int sz;
	LL v[37];
	LL& operator [](int a) {
		return v[a];
	}
	void push(LL x) {
		v[sz++] = x;
	}
	void trim() {
		while(sz and v[sz-1] == 0)
			--sz;
	}
	void clear() {
		sz = 0;
	}
	Big(int x=0):sz(0) {
		if(x) v[sz++] = x;
	}
		
	void operator += (Big& b) {
		LL carry = 0;
		for(int i=0; i<=b.sz; i++) {
			if(i == sz) push(0);
			LL cur = (LL)v[i] + carry + (i < b.sz ? b[i] : 0LL);
			v[i] = cur;
			while(v[i] >= BASE) v[i] -= BASE;
			carry = cur / BASE;
		}
		trim();
	}
	
	friend ostream& operator << (ostream& out, Big& b) {
		b.trim();
		if(b.sz == 0)
			return out << "0";
		for(int i=b.sz - 1; i>=0; i--) {
			auto tmp = to_string(b[i]);
			tmp = (i + 1 == b.sz ? "" : string(18 - tmp.size(), '0')) + tmp;
			out << tmp;
		}
		return out;
	}
} dp[2][maxn];

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0; i<2; i++)
		for(int j=0; j<n; j++) {
			cin >> t[i][j];
			if(t[i][j]) 
				pos[t[i][j]] = {i+1, j+1};
		}
	dp[0][0] = Big(1);
	for(int i=0; i<2*n; i++) {
		int ic = i % 2, i1 = (i+1) % 2;
		for(int j=0; j<=i/2; j++) {
			if(pos[i+1].st == 0) {
				dp[i1][j] += dp[ic][j];
				dp[i1][j+1] += dp[ic][j];
			} else if(pos[i+1] == make_pair(1, i-j+1))
				dp[i1][j] += dp[ic][j];
			else if(pos[i+1] == make_pair(2, j+1))
				dp[i1][j+1] += dp[ic][j];
			dp[ic][j].clear();
		}
		dp[ic][i/2+1].clear();
	}
	
	cout << dp[0][n] << "\n";
}
