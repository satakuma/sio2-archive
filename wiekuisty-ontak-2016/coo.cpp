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

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag,
         tree_order_statistics_node_update>;

struct Triple {
	int x, y, z;
	Triple(int x, int y, int z):
	x(x), y(y), z(z) {}
	
	bool operator < (const Triple& b) const {
		return x < b.x;
	}
};

struct TripleCounter {
	struct Tree {
		int base;
		vector<ordered_set<int>> v;
		Tree(int n) {
			base = 1;
			while(base < n) base <<= 1;
			v.resize(base * 2);
		}
		
		void clear() {
			for(auto& s:v) s.clear();
		}
		
		void insert(int p, int x) {
			int va = p + base - 1;	
			v[va].insert(x);
			while(va > 1) {
				va >>= 1;
				v[va].insert(x);
			}
		}
		
		int query(int p, int x) { // # of smaller than x in p-prefix
			int va = p + base - 1;
			int ret = v[va].order_of_key(x); // assuming keys are pairwise distinct
			while(va > 1) {
				if(va & 1)
					ret += v[va-1].order_of_key(x);
				va >>= 1;
			}
			return ret;
		}
	} T;
	
	TripleCounter(int n): T(n) {}
	long long count(vector<Triple>&& tr) {
		sort(tr.begin(), tr.end());
		T.clear();
		long long ret = 0;
		for(auto& t:tr) {
			ret += T.query(t.y, t.z);
			T.insert(t.y, t.z);
		}
		
		return ret;
	}
};

struct NotOrderedPairCounter {
	long long count(vector<pair<int, int>>& v) {
		int n = v.size();
		vector<int> fen(n+1);
		auto insert = [&](int i) {
			while(i <= n) {
				fen[i]++;
				i += i&(-i);
			}
		};
		auto query = [&](int i) {
			int ret = 0;
			while(i > 0) {
				ret += fen[i];
				i -= i&(-i);
			}
			return ret;
		};
		
		sort(v.begin(), v.end());
		long long ret = 0;
		for(auto& p:v) {
			ret += query(p.nd);
			insert(p.nd);
		}
		
		return (LL) n * (n-1) / 2 - ret;
	}
};

using X = NotOrderedPairCounter;
			

long long solve(const int n, int k, vector<vector<int>>&& marks) {
	if(k == 2) {
		vector<pair<int, int>> V(n);
		for(int i=0; i<n; i++) 
			V[i] = {marks[0][i], marks[1][i]};
		return (LL) n * (n-1) / 2 - X().count(V);
	}
	
	for(int i=k; i<4; i++)
		marks.emplace_back(marks[i-k]);
	k = 4;
	
	long long res = 0;
	/*TripleCounter T(n);
	for(int i=0; i<4; i++) {
		vector<Triple> tr;
		vector<int> ind;
		for(int j=0; j<4; j++)
			if(i != j)
				ind.emplace_back(j);
		int a = ind[0], b = ind[1], c = ind[2];
		for(int j=0; j<n; j++)
			tr.emplace_back(marks[a][j], marks[b][j], marks[c][j]);
		
		res += T.count(move(tr));
	}
	
	vector<pair<int, int>> V(n);
	for(int i=0; i<4; i+=2) {
		for(int j=0; j<n; j++)
			V[j] = {marks[i][j], marks[i+1][j]};
		res += (LL) n * (n-1) / 2 - X().count(V);
	}*/
	
	vector<pair<int, int>> V(n);
	res = (LL) n * (n-1);
	for(int i:{0, 1}) {
		for(int j:{2, 3}) {
			for(int l=0; l<n; l++)
				V[l] = {marks[i][l], marks[j][l]};
			res -= X().count(V);
		}
	}
	
	return res / 2;
}


int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	auto compress = [](vector<int>& v) {
		vector<pair<int, int>> p;
		for(int i=0; i<(int) v.size(); i++)
			p.emplace_back(v[i], i);
		sort(p.begin(), p.end());
		for(int i=0; i<(int) p.size(); i++)
			v[p[i].nd] = i+1;
	};
	
	int n, k;
	cin >> n >> k;
	vector<vector<int>> marks(k, vector<int>(n));
	for(auto& v:marks) {
		for(auto& x:v)
			cin >> x;
		compress(v);
	}
	
	cout << solve(n, k, move(marks)) << "\n";
}