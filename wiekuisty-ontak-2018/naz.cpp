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

int n,k;
string s;
vector<bool>zn;
vector<pair<char,int> >co;
vector<vector<int> >pop;
vector<int>pref;

void calcPref()
{
	pref.resize(n+1);
	int b=0;
	pref[0]=0;
	for(int i=1;i<n;i++)
	{
		pref[i]=0;
		if(i<b+pref[b])
			pref[i]=min(pref[i-b],b+pref[b]-i);
		while(i+pref[i]<n && s[i+pref[i]]==s[pref[i]])
			pref[i]++;
		if(i+pref[i]>b+pref[b])
			b=i;
	}
	for(int i=1;i<n;i++)
		pref[i]=min(pref[i],i);
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin>>s;
	n=siz(s);
	
	cin>>k;
	pop.resize(k+1,vector<int>(n+1,-1));
	zn.resize(k+1,false),co.resize(k+1);
	calcPref();
	pop[0][0]=-INF;
	for(int i=1;i<=k;i++){
		char c;
		cin>>c;
		if(c=='A'){
			zn[i]=true;
			cin>>c;
			co[i]={'A',c};
			for(int j=0;j<n;j++)
				if(pop[i-1][j]!=-1 && s[j]==c)
					pop[i][j+1]=j;
		}
		else if(c=='B')
		{
			zn[i]=true;
			int m; cin>>m;
			co[i]={'B',m};
			for(int j=0;j<n-m+1;j++)
				if(pop[i-1][j]!=-1 && pref[j]>=m)
					pop[i][j+m]=j;
		}
		else
		{
			int lst=-1,r=-1;
			for(int j=0;j<n;j++){
				if(j+pref[j]>r && pop[i-1][j]!=-1){
					r=j+pref[j];
					lst=j;
				}
				if(j+1<=r)
					pop[i][j+1]=lst;
			}
			for(int j=1;j<=n;j++)
				if(pop[i-1][j-1]!=-1)
					pop[i][j]=j-1;
		}
	}
	
	if(pop[k][n]==-1){
		cout<<"-1\n";
		return 0;
	}
	
	cout<<k<<"\n";
	
	int y=n;
	vector<pair<char,int> >ans;
	for(int i=k;i>0;y=pop[i--][y]){
		if(zn[i]){
			ans.pb(co[i]);
		}
		else if(pop[i][y]==y-1){
			ans.pb({'A',s[y-1]});
		}
		else
			ans.pb({'B',y-pop[i][y]});
	}
	assert(siz(ans)==k);
	for(int i=k-1;i>=0;i--)
	{
		auto& p=ans[i];
		cout<<p.st<<" ";
		if(p.st=='A')
			cout<<(char)p.nd<<"\n";
		else
			cout<<p.nd<<"\n";
	}

	return 0;
}
