//Tymoteusz Wisniewski XIV LO Wwa
#include<bits/stdc++.h>
using namespace std;
#define pb push_back

int n,m;
vector<int>graf[50005];
vector<int>gt[50005];
int visited[50005];
stack<int>stos;

int lp=0;
int ktoraSpojna[50005];
int dp[50005];
vector<vector<int> >gs;
vector<int>deg;

void dfsPost(int a){
	visited[a]=1;
	for(auto v:graf[a]){
		if(!visited[v])	
			dfsPost(v);
	}
	stos.push(a);
}

void dfsSpoj(int a){
	visited[a]=2;
	ktoraSpojna[a]=lp;
	dp[lp]++;
	for(auto v:gt[a]){
		if(visited[v]!=2)
			dfsSpoj(v);
	}
}
	

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin>>n>>m;
	for(int i=0;i<m;i++)
	{
		int a,b;
		cin>>a>>b;
		graf[a].pb(b);
		gt[b].pb(a);
	}
	for(int i=1;i<=n;i++)
		if(!visited[i])
			dfsPost(i);
	while(!stos.empty()){
		int a=stos.top(); stos.pop();
		if(visited[a]==2)
			continue;
		dfsSpoj(a);
		lp++;
	}
	gs.resize(lp+1);
	deg.resize(lp+1);
	for(int i=1;i<=n;i++)
		for(auto a:gt[i])
			if(ktoraSpojna[i]!=ktoraSpojna[a]){
				gs[ktoraSpojna[i]].pb(ktoraSpojna[a]);
				//deg[ktoraSpojna[a]]++;
			}
	for(int i=0;i<lp;i++){
		sort(gs[i].begin(),gs[i].end());
		auto it=unique(gs[i].begin(),gs[i].end());
		gs[i].resize(distance(gs[i].begin(),it));
		for(auto a:gs[i])
			deg[a]++;
	}
	queue<int>q;
	for(int i=0;i<lp;i++){
		if(!deg[i])
			q.push(i);
	}
	while(!q.empty()){
		int w=q.front(); q.pop();
		for(auto a:gs[w]){
			dp[a]+=dp[w];
			if(--deg[a]==0)
				q.push(a);
		}
	}
	for(int i=1;i<=n;i++)
		cout<<dp[ktoraSpojna[i]]-1<<"\n";
	
	
	return 0;
}
		
		
		
		
		
		
