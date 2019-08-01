/* 
The Zen of Python, by Tim Peters

Beautiful is better than ugly.
Explicit is better than implicit.
Simple is better than complex.
Complex is better than complicated.
Flat is better than nested.
Sparse is better than dense.
Readability counts.
Special cases aren't special enough to break the rules.
Although practicality beats purity.
Errors should never pass silently.
Unless explicitly silenced.
In the face of ambiguity, refuse the temptation to guess.
There should be one-- and preferably only one --obvious way to do it.
Although that way may not be obvious at first unless you're Dutch.
Now is better than never.
Although never is often better than *right* now.
If the implementation is hard to explain, it's a bad idea.
If the implementation is easy to explain, it may be a good idea.
Namespaces are one honking great idea -- let's do more of those! 
*/

#include<bits/stdc++.h>
using namespace std;
#define st first
#define nd second

constexpr int maxn = 1000005;

int n, m, S[maxn], E[maxn], no[maxn], low[maxn], lp=1;
vector<pair<int, int>> G[maxn];
bool mark[maxn], ans[maxn], vis[maxn];

void mark_bridges(int a, int par=-1) {
	low[a] = no[a] = lp++;
	for(auto& e:G[a]) {
		if(e.nd == par) continue;
		if(no[e.st] == 0) {
			mark_bridges(e.st, e.nd);
			if(low[e.st] >= no[e.st])
				mark[e.nd] = true;
			low[a] = min(low[e.st], low[a]);
		} else {
			low[a] = min(low[a], no[e.st]);
		}
	}
}

void dfs(int a, int par=-1) {
	vis[a] = true;
	no[a] = lp++;
	for(auto& e:G[a]) {
		if(e.nd == par) continue;
		if(vis[e.st] or mark[e.nd]) {
			ans[e.nd] = (S[e.nd] == a) ^ (no[e.st] > no[a]);
		} else {
			ans[e.nd] = (S[e.nd] == a);
			dfs(e.st, e.nd);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	for(int i=0; i<m; i++) {
		cin >> S[i] >> E[i];
		G[S[i]].emplace_back(E[i], i);
		G[E[i]].emplace_back(S[i], i);
	}
	
	for(int i=1; i<=n; i++) {
		if(no[i] == 0)
			mark_bridges(i);
	}
	
	int cnt = 0;
	lp = 1;
	for(int i=1; i<=n; i++) {
		if(not vis[i]) {
			dfs(i);
			cnt++;
		}
	}
	
	cout << cnt << "\n";
	for(int i=0; i<m; i++)
		cout << (ans[i] ? '<' : '>');
	cout << '\n';
	
	return 0;
}