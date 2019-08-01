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
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag,
         tree_order_statistics_node_update>;
*/

void read(int& x) {
	char c = 0;
	while(c < 33)
		c = getc_unlocked(stdin);
	
	x = 0;
	while(c > 32) {
		x = x * 10 + c - 48;
		c = getc_unlocked(stdin);
	}
}

constexpr int maxn = 5000005;

int n, p[maxn], L[maxn], R[maxn];
int lf[maxn], rf[maxn];
int lrep[maxn], rrep[maxn];

int lvl[maxn], cnt_lvl[maxn];
bool occl[maxn], occr[maxn];

int find(int a, int* t) {
	return t[a] < 0 ? a : t[a] = find(t[a], t);
}

void un(int a, int b, int* t, int* rep) {
	rep[a] = rep[b];
	if(t[a] > t[b])
		swap(a, b);
	t[a] += t[b];
	t[b] = a;
}


int main()
{
	read(n);
	for(int i=1; i<=n; i++)
		read(p[i]);
	
	fill_n(lf, n+2, -1);
	fill_n(rf, n+2, -1);
	iota(lrep, lrep+n+2, 0);
	iota(rrep, rrep+n+2, 0);
	
	for(int i=n; i>0; i--) {
		int r = find(p[i]+1, rf);
		int l = find(p[i]-1, lf);
		R[i] = rrep[r], L[i] = lrep[l];
		un(find(p[i], rf), r, rf, rrep);
		un(find(p[i], lf), l, lf, lrep);
	}
	
	cnt_lvl[0]++;
	for(int i=2; i<=n; i++) {
		if(L[i] == 0 or occr[L[i]]) {
			assert(not occl[R[i]]);
			occl[R[i]] = true;
			lvl[p[i]] = lvl[R[i]] + 1;
			cnt_lvl[lvl[p[i]]]++;
		} else {
			occr[L[i]] = true;
			lvl[p[i]] = lvl[L[i]] + 1;
			cnt_lvl[lvl[p[i]]]++;
		}
	}
	
	int y = 0;
	while(cnt_lvl[y]) {
		printf("%d ", cnt_lvl[y++]);
	}
	puts("");
}