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

constexpr int mod = INF, N = 73;

int n, dp[N][N][N];
int pot[N][N], binom[2*N][2*N], fac[N];

void init() {
	for(int i=1; i<=n; i++) {
		pot[i][0] = 1;
		for(int j=1; j<=n; j++)
			pot[i][j] = (LL) pot[i][j-1] * i % mod;
	}
	
	binom[0][0] = 1;
	for(int _n=1; _n<=2*n; _n++) {
		binom[_n][0] = binom[_n][_n] = 1;
		for(int k=1; k<n; k++)
			binom[_n][k] = (binom[_n-1][k] + binom[_n-1][k-1]) % mod;
	}
	
	fac[0] = 1;
	for(int i=1; i<=n; i++)
		fac[i] = (LL) fac[i-1] * i % mod;
}

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	init();
	dp[1][0][1] = 1;
	for(int i=2; i<=n; i++)
		for(int d=1; d<i; d++)
			for(int k=1; k<=i; k++) {
				for(int cnt=1; cnt<=i-k; cnt++)
					dp[i][d][k] = (dp[i][d][k] + (LL) dp[i-k][d-1][cnt] * binom[i][k] % mod * pot[cnt][k]) % mod;
			}
	
	int sum = 0;
	for(int d=1; d<n; d++) {
		for(int k=1; k<=n; k++)
			sum = (sum + dp[n][d][k]) % mod;
		cout << sum << " ";
	}
	cout << "\n";
					
				




	return 0;
}