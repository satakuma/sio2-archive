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

constexpr int maxn = 303, mod = int(1e9) + 33;

int n, K, A[maxn], L[maxn], R[maxn];
int dp[maxn][maxn][maxn][2], pref[maxn][maxn][maxn];

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> K;
	for(int i=1; i<=n; i++) 
		cin >> A[i];
	
	for(int i=1; i<=n; i++) {
		L[i] = R[i] = i;
		while(L[i] and A[i] <= A[L[i]]) L[i]--;
		while(R[i] <= n and A[i] <= A[R[i]]) R[i]++;
		//cout << make_pair(L[i], R[i]) << endl;
	}
	
	dp[0][0][0][1] = pref[0][0][0] = 1;
	for(int j=0; j<=n; j++) {
		for(int k=0; k<=n; k++) {
			for(int i=1; i<=n; i++) {
				pref[i][j][k] = pref[i-1][j][k];
				if(not (L[i] < j and j < R[i])) continue;
				if(i == j)
					dp[i][j][k][0] = pref[i-1][j-1][k];
				if(k)
					dp[i][j][k][1] = ((LL)dp[i][j-1][k][1] + dp[i][j-1][k-1][0]
									+ (i != j ? pref[i-1][j-1][k-1] : 0)) % mod;
				pref[i][j][k] = ((LL)pref[i][j][k] + dp[i][j][k][1] + dp[i][j][k][0]) % mod;
				//cout << i <<", "<< j <<", " << k <<" == "<<dp[i][j][k][0] <<", "<<dp[i][j][k][1]<<endl;
			}
		}
	}
	long long res = 0;
	for(int k=0; k<=min(n,K); k++) 
		for(int i=1; i<=n; i++) 
			res = res + dp[i][n][k][1] + dp[i][n][k][0];
	cout << res % mod << endl;
}
