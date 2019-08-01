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

constexpr int maxn = 3005;

int n, m, k, A[maxn], B[maxn], C[maxn], AC[maxn], BC[maxn], AB[maxn][maxn], ABo[maxn][maxn];
int pom[maxn][maxn];

void dp(int t[], int n, int d[]) {
	for(int i=0; i<=n; i++)
		pom[i][0] = pom[0][i] = -1;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=k; j++) {
			if(t[i] == C[j])
				pom[i][j] = (j > 1 ? pom[i-1][j-1] : i);
			else
				pom[i][j] = pom[i-1][j];
		}
		d[i] = pom[i][k];
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=1; i<=n; i++)
		cin >> A[i];
	cin >> m;
	for(int i=1; i<=m; i++)
		cin >> B[i];
	cin >> k;
	for(int i=1; i<=k; i++)
		cin >> C[i];
	
	dp(A, n, AC), dp(B, m, BC);
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++) {
			if(A[i] == B[j])
				AB[i][j] = AB[i-1][j-1] + 1;
			else
				AB[i][j] = max(AB[i-1][j], AB[i][j-1]);
		}
	for(int i=n; i>0; i--)
		for(int j=m; j>0; j--) {
			if(A[i] == B[j])
				ABo[i][j] = ABo[i+1][j+1] + 1;
			else
				ABo[i][j] = max(ABo[i+1][j], ABo[i][j+1]);
		}
	
	/*for(int i=1; i<=n; i++)
		cerr << AC[i] << " ";
	cerr << endl;
	for(int j=1; j<=m; j++)
		cerr << BC[j] << " ";
	cerr << endl;*/
	
	int res = -1;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			if(AC[i] != -1 and BC[j] != -1) {
				res = max(res, AB[AC[i]-1][BC[j]-1] + ABo[i+1][j+1] + k);
			}
	
	cout << (k ? res : AB[n][m]) << "\n";

}