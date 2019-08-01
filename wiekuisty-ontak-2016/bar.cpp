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

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	vector<int> A(n+1);
	for(int i=1; i<=n; i++)
		cin >> A[i];
	string S;
	cin >> S;
	
	int res = 0, f = 0, b = 0;
	priority_queue<int, vector<int>, greater<int>> Q;
	for(int i=1; i<=n; i++) {
		if(i + f <= n)
			Q.emplace(A[i + f]);
		while(i + b < Q.top()) {
			if(S[res++] == 'F') {
				if(i + (++f) <= n)
					Q.emplace(A[i + f]);
			}	
			else
				++b;
		}
		Q.pop();
	}
	
	cout << res << "\n";
}