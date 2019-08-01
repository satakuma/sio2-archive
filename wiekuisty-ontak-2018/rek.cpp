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

const int maxn=200005;

int n,k;
int tab[maxn],B[maxn],deg[maxn],ans[maxn];
vector<int>graf[maxn];

int inv(vector<int>& p){
	int cnt=0;
	for(int i=0;i<siz(p);i++)
		for(int j=i+1;j<siz(p);j++)
			cnt+=(p[i]>p[j]);
	return cnt;
}

void check(vector<int>& p)
{
	for(int i=1;i<=k;i++)
		tab[i]=p[i-1];
	int in=inv(p);
	for(int od,dod,i=2;i<=n-k+1;i++){
		od=tab[i-1]; in-=od-1;
		if(B[i]-in>k-1 || B[i]<in)
			return;
		dod=k-(B[i]-in);
		for(int j=i;j<i+k-1;j++){
			if(tab[j]>od) tab[j]--;
			if(tab[j]>=dod) tab[j]++;
		}	
		tab[i+k-1]=dod; in=B[i];
	}
	
	for(int i=1;i<=k;i++){
		tab[i]=p[i-1];
		if(i==1) continue;
		if(tab[1]>tab[i])
			graf[i].pb(1),++deg[1];
		else
			graf[1].pb(i),++deg[i];
	}
	in=inv(p);
	for(int od,dod,i=2;i<=n-k+1;i++){
		od=tab[i-1],in-=od-1;
		dod=k-(B[i]-in);
		for(int j=i;j<i+k-1;j++){
			if(tab[j]>od) tab[j]--;
			if(tab[j]>=dod) tab[j]++;
		}
		tab[i+k-1]=dod; in=B[i];
		for(int j=i+1;j<i+k;j++)
			if(tab[i]>tab[j])
				graf[j].pb(i),++deg[i];
			else
				graf[i].pb(j),++deg[j];
		
	}
	for(int i=n-k+2;i<n;i++)
		for(int j=i+1;j<=n;j++)
			if(tab[i]>tab[j])
				graf[j].pb(i),++deg[i];
			else
				graf[i].pb(j),++deg[j];
	
	queue<int>q;
	for(int i=1;i<=n;i++)
		if(!deg[i])
			q.push(i);
	int lp=1;
	while(!q.empty()){
		int a=q.front(); q.pop();
		ans[a]=lp++;
		for(auto v:graf[a]){
			if(--deg[v]==0)
				q.push(v);
		}
	}
	for(int i=1;i<=n;i++)
		cout<<ans[i]<<" ";
	exit(0);
}
	
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin>>n>>k;
	for(int i=1;i<=n-k+1;i++)
		cin>>B[i];
	
	vector<int>perm(k); iota(all(perm),1);
	do{
		if(inv(perm)==B[1])
			check(perm);
	}while(next_permutation(all(perm)));
	
	return 0;
}
