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
vector<int> buck[maxn];

struct Balwan {
	int a, b, c;
	void sort() {
		if(a < b) swap(a, b);
		if(b < c) swap(b, c);
		if(a < b) swap(a, b);
	}
};


int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int Z; cin >> Z;
	while(Z--) {
		int n; cin >> n;
		map<int, int> M;
		
		for(int i=0; i<n; i++) {
			int x; cin >> x;
			++M[x];
		}
		
		for(auto it:M)
			buck[it.nd].push_back(it.st);
		
		int i = n;
		vector<pair<int, int>> v;
		vector<Balwan> ans;
		
		while(i > 0) {
			while(i > 0 and v.size() < 3) {
				while(not buck[i].empty() and v.size() < 3) {
					auto x = buck[i].back();
					buck[i].pop_back();
					v.emplace_back(x, i);
				}
				if(v.size() < 3) i--;
			}
			if(v.size() == 3) {		
				ans.push_back({v[0].st, v[1].st, v[2].st});
				vector<pair<int, int>> tmp;
				for(auto& p:v)
					if(p.nd > 1) {
						if(p.nd-1 <= i)
							buck[p.nd-1].push_back(p.st);
						else
							tmp.emplace_back(p.st, p.nd-1);
					}
				v = tmp;
			}
		}
		
		cout << ans.size() << "\n";
		for(auto& b:ans) {
			b.sort();
			cout << b.a << " " << b.b << " " << b.c << "\n";
		}
	}
}