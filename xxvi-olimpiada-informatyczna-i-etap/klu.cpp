#include<bits/stdc++.h>
using namespace std;
#define st first
#define nd second
typedef long long LL;

const int maxm=2e6+2,maxn=31;

int n,m,mx,tab[2*maxm];
int lst[maxn][2],nxt[maxm];

inline bool Bit(int& x,int& i){
	return (x&(1<<i))!=0;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin>>n>>m;
	for(int i=0;i<m;i++)
		cin>>tab[i];
	
	for(int i=0;i<n;i++)
		for(int j:{0,1})
			lst[i][j]=2*m;
	for(int i=2*m-1;i>=m;i--)
		for(int j=0;j<n;j++)
			lst[j][Bit(tab[i-m],j)]=i;
	
	for(int i=m-1;i>=0;i--){
		for(int j=0;j<n;j++){
			nxt[i]=max(nxt[i],lst[j][Bit(tab[i],j)]);
			lst[j][Bit(tab[i],j)]=i;
		}
		if(nxt[i]>m)
			mx=max(mx,nxt[i]-m);
	}
	queue<pair<int,int>>q; LL res=0;
	for(int i=0;i<m;i++){
		while(!q.empty() and q.front().st<i) q.pop();
		if(!q.empty())
			res+=min(mx,q.front().nd)-i;
		else
			res+=mx-i;
		q.push({mx,i+m-1});
		mx=max(mx,nxt[i]);
	}
	
	cout<< (LL)m*(m-1)/2 - res <<"\n";

	return 0;
}