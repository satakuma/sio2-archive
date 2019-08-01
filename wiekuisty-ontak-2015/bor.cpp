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

struct Plan {
	int a, b, c;
	
	bool operator < (const Plan& d) const {
		return a < d.a;
	}
	friend istream& operator >> (istream& in, Plan& p) {
		in >> p.a >> p.b >> p.c;
		p.b--;
		return in;
	}
};
vector<Plan> plans;

int n, sum;

int st_defeat(set<pair<int, int>> S, int x, int pt, int thr) {
	int cnt = 0;
	for(int i=x; not S.empty() or pt < n; i++) {
		while(pt < n and plans[pt].a == i) {
			if(plans[pt].c > thr)
				S.emplace(plans[pt].b, pt);
			pt++;
		}
		while(not S.empty() and (thr >= plans[S.begin()->nd].c or S.begin()->st < i))
			S.erase(S.begin());
		
		if(not S.empty()) {
			S.erase(S.begin());
			cnt++;
		}
	}
	
	return cnt;
}

bool possible(set<pair<int, int>> S, int x, int pt) {
	auto it = S.begin()->nd;
	S.erase(S.begin());
	
	return st_defeat(S, x, pt, plans[it].c) == st_defeat(S, x+1, pt, plans[it].c);
}


int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	plans.resize(n);
	for(auto& p:plans)
		cin >> p;
	
	sort(plans.begin(), plans.end());
	
	set<pair<int, int>> S;
	for(int i=1, pt=0; i<=5000; i++) {
		while(pt < n and plans[pt].a == i) {
			S.emplace(plans[pt].b, pt);
			pt++;
		}
		while(not S.empty() and (S.begin()->st < i or not possible(S, i, pt)))
			S.erase(S.begin());
		
		if(not S.empty()) {
			sum += plans[S.begin()->nd].c;
			S.erase(S.begin());
		}
	}
		
	cout << sum << "\n";
}