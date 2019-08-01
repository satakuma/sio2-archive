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

constexpr int maxn = 100005;
constexpr int MOD[2] = {998244353, INF + 402};

int n, k, col[maxn], rozm[maxn], tmppar[maxn];
int pr[2][maxn];
pair<int, int> best[maxn];
bool mark[maxn], posbl[maxn];
vector<int> G[maxn];

void dfs_calc(int a, int par=-1) {
	rozm[a] = 1;
	best[a] = {0, 0};
	for(auto v:G[a]) {
		if(v == par or mark[v])	
			continue;
		dfs_calc(v, a);
		best[a] = max(best[a], make_pair(rozm[v], v));
		rozm[a] += rozm[v];
	}
}

int sz;
int dfs_find(int a) {
	if(best[a].st <= sz and sz <= rozm[a])
		return a;
	return dfs_find(best[a].nd);
}

int get_centr(int a) {
	dfs_calc(a);
	sz = rozm[a] / 2;
	return dfs_find(a);
}

int H[2];
bool cnt[maxn];
vector<vector<pair<LL, int>>> V;

inline LL get_hash() {
	return H[0] + (LL) H[1] * MOD[1];
}  
inline pair<int, int> unpack(LL x) {
	return {x % MOD[1], x / MOD[1]};
}

void add(int x, int val=1) {
	assert(cnt[x] == (val == -1));
	cnt[x] ^= 1;
	for(int i:{0, 1}) {
		H[i] += val * pr[i][x];
		if(H[i] >= MOD[i])
			H[i] -= MOD[i];
		else if(H[i] < 0)
			H[i] += MOD[i];
	}
}

void dfs_go(int a) {
	if(cnt[col[a]]) return;
	add(col[a]);
	V.back().emplace_back(get_hash(), a);
	for(auto v:G[a]) {
		if(mark[v] or v == tmppar[a])
			continue;
		tmppar[v] = a;
		dfs_go(v);
	}
	add(col[a], -1);
}

int vis[maxn], vislp;

void go(int a) {
	add(col[a]);
	H[0] = H[1] = 0;
	map<LL, int> M;
	for(auto v:G[a]) {
		if(mark[v]) continue;
		tmppar[v] = a;
		V.emplace_back();
		dfs_go(v);
		for(auto p:V.back()) {
			M[p.st]++;
			// cerr << "cen: " << a << " z w: " << v << " para; " << p << endl;
		}
	}
	
	vislp++;
	vector<int> good;
	M[0]++;
	for(auto& v:V) {
		for(auto& p:v)
			M[p.st]--;
		for(auto& p:v) {
			int x, y;
			tie(x, y) = unpack(p.st);
			x += pr[0][col[a]];
			y += pr[1][col[a]];
			x %= MOD[0], y %= MOD[1];
			x = (MOD[0] - x) % MOD[0], y = (MOD[1] - y) % MOD[1];
			if(M[x + (LL)y * MOD[1]]) {
				good.push_back(p.nd);
				vis[p.nd] = vislp;
			}
		}
		for(auto& p:v)
			M[p.st]++;
	}
	
	for(int i=0; i<(int)good.size(); i++) {
		int x = good[i];
		posbl[x] = true;
		if(x != a and vis[tmppar[x]] != vislp) {
			vis[tmppar[x]] = vislp;
			good.push_back(tmppar[x]);
		}
	}
			
	add(col[a], -1);
	H[0] = H[1] = 0;
	V.clear();
}

void decompose(int v) {
	auto c = get_centr(v);
	go(c);
	mark[c] = true;
	for(auto u:G[c])
		if(not mark[u])
			decompose(u);
}

struct RandomPrimeGenerator {
	constexpr static int MX = 1500005;
	int mod, pt;
	vector<int> primes;
	RandomPrimeGenerator(int mod):mod(mod), pt(0) {
		vector<bool> f(MX);
		for(int i=2; i<MX; i++) {
			if(f[i] == 0)
				primes.push_back(i);
			for(int j=0; j<primes.size() and i * primes[j] < MX; j++) {
				f[i * primes[j]] = true;
				if(i % primes[j] == 0)
					break;
			}
		}
		for(auto& x:primes) {
			x = ((LL)x * x % mod * x + 1) % mod;
		}
		shuffle(all(primes), mt19937(time(0)));
		d(cerr << primes.size() << endl;)
	}
	
	int operator() () {
		if(pt == primes.size()) pt = 0;
		return primes[pt++];
	}
};

using RPG = RandomPrimeGenerator;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int q;
	cin >> n >> k >> q;
	for(int i=1; i<=n; i++)
		cin >> col[i];
	
	RPG rng[2] = {RPG(MOD[0]), RPG(MOD[1])};
	int sum[2] = {0, 0};
	for(int i=1; i<k; i++) {
		for(int j:{0, 1}) {
			(sum[j] += (pr[j][i] = rng[j]())) %= MOD[j];
		}
	}
	for(int j:{0, 1})
		pr[j][k] = (MOD[j] - sum[j]) % MOD[j];
	
	for(int a, b, i=0; i<n-1; i++) {
		cin >> a >> b;
		G[a].pb(b);
		G[b].pb(a);
	}
	
	decompose(1);

	while(q--) {
		int a; cin >> a;
		cout << (posbl[a] or k == 1 ? "YES" : "NO") << "\n";
	}
}
