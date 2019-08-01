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

constexpr int maxn = 5005, maxd = 205, mod = INF + 402, pr = 5021, pr2 = 313;

int d, n, m, h[maxn], h2[maxn], p[maxn], p2[maxn];
int fu[maxd][maxn];
vector<int> vert[maxd][maxn];

unordered_map<LL, int> M;
int res;

void change(int x, int y, int k) {
	LL v = (LL)h[x] * mod + h2[x];
	res -= 2 * M[v]--;
	
	h[x] -= (LL) fu[k][x] * p[k] % mod;
	h2[x] -= (LL) fu[k][x] * p2[k] % mod;
	fu[k][x] = y;
	h[x] += (LL) y * p[k] % mod;
	h2[x] += (LL) y * p2[k] % mod;
	if(h[x] < 0) h[x] += mod;
	if(h2[x] < 0) h2[x] += mod;
	h[x] %= mod;
	h2[x] %= mod;
	
	res += 2 * ++M[(LL) h[x] * mod + h2[x]];
}

void add(int a, int b, int k) {
	a = fu[k][a], b = fu[k][b];
	if(a == b) return;
	
	if(vert[k][a].size() < vert[k][b].size())
		swap(a, b);
	
	for(auto y:vert[k][b]) {
		change(y, a, k);
		vert[k][a].emplace_back(y);
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> d >> n >> m;
	
	p[0] = p2[0] = 1;
	for(int i=1; i<=d; i++) {
		p[i] = (LL) p[i-1] * pr % mod;
		p2[i] = (LL) p2[i-1] * pr2 % mod;
		for(int j=1; j<=n; j++) {
			fu[i][j] = j;
			vert[i][j].pb(j);
			h[j] = (h[j] + (LL)p[i] * j) % mod;
			h2[j] = (h2[j] + (LL)p2[i] * j) % mod;
		}
	}
	
	for(int i=1; i<=n; i++)
		M[(LL) h[i] * mod + h2[i]]++;
	
	res = n;
	while(m--) {
		int a, b, k;
		cin >> a >> b >> k;
		add(a, b, k);
		
		cout << res << "\n";
	}
}