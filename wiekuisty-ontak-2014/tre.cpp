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

int M, R;
char t[maxn][maxn];
pair<int, int> jl[maxn][maxn][13], jr[maxn][maxn][13];
int ans[maxn][maxn];


int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> M >> R;
	for(int i=1; i<=R; i++)
		for(int j=1; j<=M; j++)
			cin >> t[i][j];
	
	int LOG = __lg(M + R) + 1;
	for(int l=0; l<=LOG; l++)
		jl[R][M][l] = jr[R][M][l] = {R, M};
	ans[R][M] = 1;
	
	for(int s = R + M - 1; s > 1; s--) {
		for(int a = max(1, s - M); a <= min(R, s-1); a++) {
			auto b = s - a;
			if(t[a][b] == 'R') {
				ans[a][b] = ans[a+1][b];
				jl[a][b][0] = jr[a][b][0] = {a+1, b};
			} else if(t[a][b] == 'M') {
				ans[a][b] = ans[a][b+1];
				jl[a][b][0] = jr[a][b][0] = {a, b+1};
			} else {
				ans[a][b] = ans[a+1][b] + ans[a][b+1];
				jl[a][b][0] = {a+1, b};
				jr[a][b][0] = {a, b+1};
			}
			
			for(int l=1; l<=LOG; l++) {
				auto p = jl[a][b][l-1];
				jl[a][b][l] = jl[p.st][p.nd][l-1];
				p = jr[a][b][l-1];
				jr[a][b][l] = jr[p.st][p.nd][l-1];
			}
			
			if(t[a][b] == 'O') {
				auto u = jr[a][b][0], v = jl[a][b][0];
				int l = LOG;
				while(l >= 0) {
					auto ut = jl[u.st][u.nd][l], vt = jr[v.st][v.nd][l];
					if(ut.nd > vt.nd)
						u = ut, v = vt;
					--l;
				}
				
				u = jl[u.st][u.nd][0];
				ans[a][b] -= ans[u.st][u.nd];
			}
			
			ans[a][b]++;
		}
	}
	
	for(int i=1; i<=R; i++) {
		for(int j=1; j<=M; j++)
			cout << ans[i][j] << " ";
		cout << "\n";
	}
}