#include<bits/stdc++.h>
#include"ofe.h"
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

constexpr int maxn=10005;

static int n;
vector<int>pop[maxn];

int fun(int a,int b){
	if(a==b) return a;
	int s=(a+b)/2;
	int l=fun(a,s),r=fun(s+1,b);
	if(cmp(l,r)){
		pop[l].pb(r);
		return l;
	}
	else
	{
		pop[r].pb(l);
		return r;
	}
}

int getMin(vector<int>& v){
	assert(!v.empty());
	int best=v[0];
	for(int i=1;i<siz(v);i++){
		if(cmp(v[i],best))
			best=v[i];
	}
	return best;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	n=getN();
	
	int mx=fun(1,n);
	int ans=getMin(pop[mx]);
	answer(ans);
	
}