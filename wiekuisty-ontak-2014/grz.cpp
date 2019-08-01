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

int n, m, t[maxn][maxn], cnt[maxn][maxn];
LL add[maxn][maxn];

template<typename T>
using priorq = priority_queue<T, vector<T>, greater<T>>;


int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++) {
			cin >> t[i][j];
			cnt[i][j] = int(i != n) + (j != 1);
		}
	
	priorq<pair<LL, pair<int, int>>> q;
	
	q.push({t[n][1], {n, 1}});
	
	LL res = 0;
	while(not q.empty()) {
		LL v;
		pair<int, int> pos;
		tie(v, pos) = q.top();
		q.pop();
		res += max(0LL, v - res);
		
		if(pos.st > 1 and --cnt[pos.st-1][pos.nd] == 0)
			q.push({t[pos.st-1][pos.nd] + add[pos.st-1][pos.nd], {pos.st-1, pos.nd}});
		if(pos.nd < m and --cnt[pos.st][pos.nd+1] == 0)
			q.push({t[pos.st][pos.nd+1] + add[pos.st][pos.nd+1], {pos.st, pos.nd+1}});
		if(pos.nd < m and pos.st > 1)
			add[pos.st-1][pos.nd+1] += res;
	}
	
	cout << res << "\n";
}