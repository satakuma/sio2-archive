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

constexpr int maxn = 1000005;

int n, t[3][maxn], d[3][maxn];
bool mark[3][maxn], col_mark[maxn];

constexpr pair<int, int> mv[] = { {0, 1}, {1, 0}, {-1, 0}, {0, -1} };
inline bool valid(int x, int y) {
	return x > 0 and y > 0 and x <= 2 and y <= n;
}

void dfsMark(int x, int y) {
	mark[x][y] = true;
	for(auto r:mv) {
		auto xt = x + r.st, yt = y + r.nd;
		if(valid(xt, yt) and not mark[xt][yt] and t[xt][yt] == t[x][y])
			dfsMark(xt, yt);
	}
}

int bfs() {
	for(int i:{1, 2})
		fill(d[i], d[i] + n + 2, INF);
	
	d[1][1] = 0;
	deque<pair<int, int>> dq;
	dq.emplace_back(1, 1);
	
	while(not dq.empty()) {
		int x, y;
		tie(x, y) = dq.front();
		dq.pop_front();
		
		if(y == n) continue;
		
		for(auto r:mv) {
			auto xt = x + r.st, yt = y + r.nd;
			if(valid(xt, yt)) {
				int v = (not mark[xt][yt] and t[x][y] != t[xt][yt]);
				if(d[xt][yt] > d[x][y] + v) {
					d[xt][yt] = d[x][y] + v;
					if(v)
						dq.emplace_back(xt, yt);
					else
						dq.emplace_front(xt, yt);
				}
			}
		}
	}
	
	return min(d[1][n], d[2][n]);
}
	



int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=1; i<=2; i++)
		for(int j=1; j<=n; j++)
			cin >> t[i][j];
	
	int res = 0;
	dfsMark(1, 1);
	for(int i=n; i>0; i--)
		for(int j=1; j<=2; j++)
			if(not mark[j][i] and not col_mark[t[j][i]]) { // pierwszy warunek niepotrzebny
				dfsMark(j, i);
				col_mark[t[j][i]] = true;
				res++;
			}
		
	cout << res + bfs() << "\n";
}