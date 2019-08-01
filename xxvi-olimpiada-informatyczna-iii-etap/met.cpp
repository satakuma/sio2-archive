#include<bits/stdc++.h>
using namespace std;
#define st first
#define nd second

constexpr int maxn = 3000005;

int n, k, cnt[maxn], dist[maxn], par[maxn];
pair<int, int> mx[maxn];
vector<int> G[maxn], buck[maxn];
int stos[maxn], sz=0;
int nxt[maxn];

void dfs(int start) {
	stos[sz++] = start;
	while(sz > 0) {
		int a = stos[sz-1];
		for(int& i=nxt[a]; i<G[a].size(); i++) {
			int v = G[a][i];
			if(par[v] == a) continue;
			if(v != par[a]) {
				dist[v] = dist[a] + 1;
				par[v] = a;
				stos[sz++] = v;
				break;
			}
		}
		if(nxt[a] == G[a].size())
			--sz;
	}
}

int root;
void go(int start) {
	stos[sz++] = start;
	while(sz > 0) {
		int a = stos[sz-1];
		
		for(int& i=nxt[a]; i<G[a].size(); i++) {
			int v = G[a][i];
			if(v == par[a]) continue;
			if(par[v] == a) {
				if(mx[v] > mx[a]) swap(mx[v], mx[a]);
				if(mx[v].st > 0)
					buck[mx[v].st].push_back(mx[v].nd);
			} else {
				par[v] = a;
				stos[sz++] = v;
				break;
			}
		}
		
		if(nxt[a] != G[a].size()) continue;
		
		if(mx[a].st == 0)
			mx[a] = {1, a};	
		else if(a == root)
			buck[mx[a].st].push_back(mx[a].nd);
		else
			mx[a].st++;
		--sz;
	}
}	

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	scanf("%d%d", &n, &k);
	for(int a, b, i=0; i<n-1; i++) {
		scanf("%d%d", &a, &b);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	
	dfs(1);
	root = max_element(dist+1, dist+n+1) - dist;
	
	fill_n(par+1, n, 0);
	fill_n(nxt+1, n, 0);
	go(root);
	
	int av = k-1, r = n;
	vector<int> ans = {root};
	for(int& i=r; i>0; i--) {
		if(buck[i].empty()) continue;
		if(buck[i].size() > av) break;
		av -= buck[i].size();
		for(auto x:buck[i]) ans.push_back(x);
		buck[i].clear(); buck[i].shrink_to_fit();
	}
	
	r = max(r, 0);
	printf("%d %d\n", r, ans.size());
	for(auto x:ans)
		printf("%d ", x);
	puts("");
}