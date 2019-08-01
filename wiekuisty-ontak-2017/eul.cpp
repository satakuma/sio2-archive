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

constexpr int maxn = 20000000 + 5, mod = INF;

int eul[maxn], C;

void preprocess(long long x) {
	C = (x > maxn ? maxn : maxn / 40);
	eul[1] = 1;
	vector<int> primes;
	for(int i=2; i<C; i++) {
		if(eul[i] == 0) {
			primes.push_back(i);
			eul[i] = i-1;
		}
		for(int j=0; j<primes.size() and primes[j]*i < C; j++) {
			if(i % primes[j])
				eul[i * primes[j]] = (LL) eul[i] * (primes[j]-1) % mod;
			else {
				eul[i * primes[j]] = (LL) eul[i] * primes[j] % mod;
				break;
			}
		}
		if((eul[i] += eul[i-1]) >= mod) 
			eul[i] -= mod;
	}
}

map<long long, int> cache;
int f(long long n) {
	if(n < C) return eul[n];
	if(cache.count(n)) return cache[n];
	long long od = 0, naj = 0;
	for(long long i=1; i*i<=n; i++) {
		od += (n / i - 1) % mod * (f(i) - f(i-1) + mod) % mod;
		naj = n / i;
		if(od >= mod) od -= mod;
	}
	
	int cur = f(n / 2);
	for(long long i=2; i < naj; i++) {
		int nxt = f(n / (i+1));
		od += LL(cur - nxt + mod) * (i - 1) % mod;
		if(od >= mod) od -= mod;
		cur = nxt;
	}
	
	n %= mod;
	auto ret = ((n * (n+1) / 2) % mod - od + mod) % mod;
	if(ret < 0) ret += mod;
	return cache[n] = ret;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	long long n; 
	cin >> n;
	preprocess(n);
	cout << f(n) << "\n";
}