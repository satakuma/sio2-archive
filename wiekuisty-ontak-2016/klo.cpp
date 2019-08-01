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

constexpr int N = 1005, K = 105;

int n, m, k;
int dp[2][N][K], mn[2][N], A[N], B[N], delta[N];


int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> k;
	for(int i=1; i<=n; i++)
		cin >> A[i];
	for(int i=1; i<=n; i++) {
		cin >> B[i];
		delta[i] = (B[i] - A[i] + k) % k;
	}
	m /= 2;
	
	for(int i=0; i<=n; i++) {
		fill_n(dp[0][i], k, INF);
		fill_n(mn[0]+1, n, INF);
	}

	dp[0][0][0] = 0;
	for(int i=1; i<n; i++) {
		int me = (i&1), he = me^1;
		for(int saved=0; saved<=n; saved++) {
			auto& my_min = (mn[me][saved] = INF);
			for(int now=0; now<k; now++) {
				int then = delta[i] - now;
				if(then < 0) then += k;
				dp[me][saved][now] = min(mn[he][saved], (saved > 0 ? dp[he][saved-1][then] : INF)) + min(now, k - now);
				my_min = min(my_min, dp[me][saved][now]);
				// cerr << i << " " << saved << " " << now << " == " << dp[me][saved][now] << endl;
			}
		}
	}
	
	int me = (n&1), he = me^1, res = 0;
	for(int saved=1; saved<=n; saved++) {
		int now = 0;
		int then = delta[n] - now;
		if(then < 0) then += k;
		if(min(mn[he][saved], dp[he][saved-1][then]) <= m)
			res = saved;
	}
	cout << n - res << "\n";
}