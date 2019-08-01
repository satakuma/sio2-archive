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

struct Segment {
	int v;
	bool rev, one;
	
	Segment(int v, bool rev=false, bool one=true):
	v(v), rev(rev), one(one) {}
	
	int reverse() {
		if(one) return 0;
		rev ^= 1;
		return (rev ? 1 : -1);
	}
};

int n, k;
vector<Segment> S;

int bad, reversed;
pair<int, int> moves[3];
vector<pair<int, int>> ans;

void reverse(int a, int b) {
	for(int i=0; a+i <= b-i; i++) {
		reversed += S[a+i].reverse();
		if(a+i != b-i) {
			reversed += S[b-i].reverse();
			if(S[a+i].v == a+i) bad++;
			else if(S[a+i].v == b-i) bad--;
			if(S[b-i].v == b-i) bad++;
			else if(S[b-i].v == a+i) bad--;
			swap(S[a+i], S[b-i]);
		}
	}
}

bool bt(int cnt) {
	if(bad == 0 and reversed == 0) {
		ans.assign(moves, moves+cnt);
		return true;
	}
	if(cnt == k) return false;
	
	int i = 0;
	while(i < siz(S) and not S[i].rev and S[i].v == i)
		i++;
	int j = siz(S) - 1;
	while(j >= i and not S[j].rev and S[j].v == j)
		j--;
	
	for(int a=i; a<=j; a++)
		for(int b=a; b<=j; b++) {
			// a == b and not rev --> ...
			d(cerr << "reversing ... " << make_pair(a, b) << " (move: " << cnt << ")" << endl;)
			d(cerr << make_pair(bad, reversed) << endl;)
			reverse(a, b);
			d(cerr << "after: " << make_pair(bad, reversed) << endl;)
			moves[cnt] = {a, b};
			if(bt(cnt+1)) {
				reverse(a, b);
				return true;
			}
			reverse(a, b);
		}
	
	return false;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k;
	vector<int> A(n);
	for(auto& a:A)
		cin >> a;
	
	vector<int> rep;
	vector<pair<int, int>> bounds;
	
	auto add = [&](int x, int l, int r, bool rev=false, bool one=true) {
		S.emplace_back(x, rev, one);
		rep.emplace_back(x);
		bounds.emplace_back(l, r);
	};
	
	int num = 0;
	for(int i=0; i<n; num++) {
		int j = i+1;
		if(j == n or abs(A[j] - A[i]) != 1) {
			add(A[i], i, i);
		} else {
			int r = A[j] - A[i];
			while(j < n and A[j] - A[j-1] == r)
				j++;
			j--;
			
			add(A[i], i, i);
			
			if(j - i > 1) {
				add(min(A[i+1], A[j-1]), i+1, j-1, A[i+1] > A[j-1], i+1 == j-1);
			}
			
			add(A[j], j, j);
			j++;
		}
		i = j;
	}
	
	if(num > 2 * k + 2) 
		return cout << "NIE\n", 0;
	
	sort(all(rep));
	vector<int> no(n+1);
	for(int i=0; i<siz(rep); i++)
		no[rep[i]] = i;
	for(int i=0; i<siz(S); i++) {
		auto& s = S[i];
		s.v = no[s.v];
		bad += (i != s.v);
		reversed += s.rev;
		d(cerr << s.v << " " << make_pair(s.rev, s.one) << endl;)
	}
	
	if(bt(0)) {
		cout << "TAK\n";
		for(auto p:ans) {
			auto a = bounds[p.st].st, b = bounds[p.nd].nd;
			cout << a+1 << " " << b+1 << "\n";
			reverse(bounds.begin() + p.st, bounds.begin() + p.nd + 1);
			for(int i=p.st; i<=p.nd; i++) {
				swap(bounds[i].st, bounds[i].nd);
				bounds[i].st = b - (bounds[i].st - a);
				bounds[i].nd = b - (bounds[i].nd - a);
			}
		}
		for(int i=0; i<k-(int)ans.size(); i++)
			cout << "1 1\n";
	} else {
		cout << "NIE\n";
	}
}