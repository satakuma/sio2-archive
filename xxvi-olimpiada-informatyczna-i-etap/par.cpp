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

const int maxn=1e5+5;

int n,m;
bool xs,xt,s[maxn],t[maxn],os[maxn],ot[maxn];
int mp[maxn];

void kmp(bool tab[],int S,bool okr[]){
	int b=-1; mp[0]=b;
	for(int i=1;i<=S;i++){
		while(b>-1 and tab[i-1]!=tab[b]) b=mp[b];
		mp[i]=++b;
		okr[i]=false;
	}
	while(b>-1){
		okr[S-b]=true; b=mp[b];
	}
	assert(okr[S]);
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int T; cin>>T;
	while(T--){
		cin>>n>>m; xs=xt=0;
		for(int a,i=0;i<n;i++){
			cin>>a; s[i]=(a&1); xs^=s[i];
		}
		for(int a,i=0;i<m;i++){
			cin>>a; t[i]=(a&1); xt^=t[i];
		}
		kmp(t,m,ot),kmp(s,n,os); 
		int ans=0;
		for(int l=max(n,m);l>0;l--){
			if(l>m){
				xs^=s[l-1]; continue;
			}
			if(l>n){
				xt^=t[l-1]; continue;
			}
			if(!os[l] or !ot[l] or xs==xt){
				ans=l;
				break;
			}
			xs^=s[l-1],xt^=t[l-1];
		}
		cout<<ans<<"\n";
	}
	
	return 0;
}
