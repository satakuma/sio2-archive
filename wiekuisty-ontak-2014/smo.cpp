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

struct Point {
	int x, y;
	
	friend istream& operator >> (istream& in, Point& p) {
		return in >> p.x >> p.y;
	}
};
struct Line {
	int a, b, c;
	
	LL operator () (const Point& p) const {
		return (LL) a * p.x + (LL) b * p.y + c;
	}
	bool operator | (const Line& l) const {
		return a * l.b - b * l.a == 0;
	}
	bool operator == (const Line& l) const {
		return ((*this) | l) and c * l.b - l.c * b == 0 and a * l.c - l.a * c == 0;
	}
	
	friend istream& operator >> (istream& in, Line& l) {
		return in >> l.a >> l.b >> l.c;
	}
};


int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int T;
	cin >> T;
	while(T--) {
		int n, m;
		cin >> n >> m;
		vector<Line> lines(n);
		for(auto& l:lines)
			cin >> l;
		vector<Point> points(m);
		for(auto& p:points)
			cin >> p;
		
		for(int i=0; i<n; i++) {
			for(int j=i+1; j<n; j++) {
				if(lines[i] == lines[j]) {
					lines[j] = lines.back();
					lines.pop_back();
					n--, j--;
				}
			}
		}
		
		int cnt = 1;
		for(int i=0; i<n; i++) {
			int cur = 1;
			for(int j=0; j<i; j++)
				if(not (lines[i] | lines[j]))
					cur++;
			cnt += cur;
		}
		
		set<pair<LL, LL>> S;
		for(auto& p:points) {
			pair<LL, LL> P(0, 0);
			for(int i=0; i<min(60, n); i++) {
				P.st <<= 1;
				P.st |= (lines[i](p) > 0);
			}
			for(int i=60; i<n; i++) {
				P.nd <<= 1;
				P.nd |= (lines[i](p) > 0);
			}
			
			S.emplace(P);
		}
		
		if(S.size() < cnt)
			cout << "NIE\n";
		else
			cout << "TAK\n";
	}
}