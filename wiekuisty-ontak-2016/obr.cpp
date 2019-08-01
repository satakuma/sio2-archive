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
    Point(int _x=0, int _y=0):
    x(_x), y(_y) {}
    
    bool is_zero() const {
        return (x == 0 and y == 0);
    }
    bool is_upper() const {
        return (y == 0 ? x : y) > 0;
    }
    
    Point operator + (const Point& b) const {
        return Point(x + b.x, y + b.y);
    }
    Point operator -() const {
        return Point(-x, -y);
    }
    Point rotate() {
        return Point(y, -x);
    }
    
    LL operator * (const Point b) const {
        return (LL)x * b.x + (LL)y * b.y;
    }
    LL operator ^ (const Point b) const {
        return (LL)x * b.y - (LL)y * b.x;
    }
    
    bool operator == (const Point& b) const {
        return (x == b.x and y == b.y);
    }
    
    bool operator < (const Point& b) const {
        if(is_zero() != b.is_zero())
            return is_zero();
        //if(is_upper() != b.is_upper())
        //    return is_upper();
        
        return ((*this) ^ b) > 0;
        //auto t = (*this) ^ b;
        //return (t == 0 ? ((*this) * (*this)) < (b * b) : t > 0);
    }
    
    friend istream& operator >> (istream& in, Point& p) {
        return in >> p.x >> p.y;
    }
    friend ostream& operator << (ostream& out, const Point p) {
        return out << make_pair(p.x, p.y);
    }
};

double distance(const Point& p, const Point& q) {
	auto pom = p + (-q);
	return sqrt(pom * pom);
}

struct Event {
	Point p;
	int a, b;
	
	bool operator < (const Event& he) const {
		return p < he.p;
	}
};


int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, k;
	cin >> n >> k;
	vector<Point> pkt(n);
	for(auto& p:pkt)
		cin >> p;
	
	vector<Event> changes;
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			if(i == j) continue;
			auto p = pkt[j] + (-pkt[i]);
			if(p.is_upper())
				changes.push_back({p, j, i});
		}
	}
	
	sort(all(changes));
	vector<int> pos(n), my_pos(n);
	iota(all(pos), 0);
	sort(all(pos), [&](int a, int b) {
		return make_pair(pkt[a].y, pkt[a].x) < make_pair(pkt[b].y, pkt[b].x);
	});
	
	for(int i=0; i<n; i++)
		my_pos[pos[i]] = i;
		
	auto dist = [](Point p, Point q, Point a) {
		// cerr << "dist: " << p << " " << q << " " << a << endl;
		return abs((p + (-a)) ^ (q + (-a))) / distance(p, q);
	};
		
	auto apply = [&](int a, int b) {
		assert(abs(my_pos[a] - my_pos[b]) == 1);
		swap(my_pos[a], my_pos[b]);
		swap(pos[my_pos[a]], pos[my_pos[b]]);
		double ret = INFL;
		if(my_pos[a] > my_pos[b]) swap(a, b);
		if(my_pos[b] + k - 2 < n)
			ret = min(ret, dist(pkt[a], pkt[b], pkt[pos[my_pos[b] + k - 2]]));
		if(my_pos[a] - k + 2 >= 0)
			ret = min(ret, dist(pkt[a], pkt[b], pkt[pos[my_pos[a] - k + 2]]));
		
		return ret;
	};
	
	double best = INFL;
	for(auto& c:changes) {
		best = min(best, apply(c.a, c.b));
	}
	
	cout << fixed << setprecision(12) << best / 2 << "\n";
}