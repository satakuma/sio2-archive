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
constexpr short INF=31000;
constexpr LL INFL=1e18;

const int maxn=302;

int n,res=0;
vector<LL>tab;
short CI[maxn][maxn]; // CI[v][i]= |{ u : 0 <= u < n and |tab[u]-tab[v]|<=|tab[i]-tab[v]| }| 
short fl[maxn][maxn],fr[maxn][maxn]; //First Greater or eq CI on the Left, First Greater or eq CI on the right
short f[maxn][maxn],fp[maxn][maxn],fs[maxn][maxn];
short f1[maxn][maxn][maxn],f2[maxn][maxn][maxn];
short f1pref[maxn][maxn][maxn],f1suf[maxn][maxn][maxn],f2pref[maxn][maxn][maxn],f2suf[maxn][maxn][maxn];
short dp[maxn][maxn];


void calcCI()
{
	for(int i=0;i<n;i++){
		int l=i,r=i+1,cnt=0;
		LL x=tab[i];
		while(l>=0 && r<n){
			if(x-tab[l]<tab[r]-x)
				CI[i][l]=++cnt,--l;
			else if(x-tab[l]>tab[r]-x)
				CI[i][r]=++cnt,++r;
			else
				CI[i][l]=CI[i][r]=(cnt+=2),--l,++r;
		}
		while(l>=0)
			CI[i][l--]=++cnt;
		while(r<n)
			CI[i][r++]=++cnt;
	}
	
	for(int i=0;i<n;i++)		//.st greater left
		for(int j=i+1;j<n;j++){
			int pt=i-1;
			while(pt>=0 && CI[i][j]>=CI[i][pt])
				pt--;
			fl[i][j]=pt;
		}
	
	for(int i=0;i<n;i++)		//.st greater right
		for(int j=i-1;j>=0;j--){
			int pt=i+1;
			while(pt<n && CI[i][j]>=CI[i][pt])
				pt++;
			fr[i][j]=pt;
		}
			
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string co; cin>>co>>n;
	tab.resize(n);
	if(co!="LOG")
		for(auto& a:tab) cin>>a;
	
	if(co=="LOG"){
		res=1; int act=3,cnt=2;
		for(int i=1;i<n;i++){
			res+=act,cnt--;
			if(cnt==0)
				cnt=act++;
		}
		cout<<res<<"\n";
		exit(0);
	}
	if(co=="NORMAL"){
		vector<pair<LL,int> >v;
		for(int i=0;i<n;i++){
			v.pb({tab[i],0});
			LL r=1;
			if(i!=0) r=tab[i]-tab[i-1];
			if(i!=n-1) r=max(r,tab[i+1]-tab[i]);
			v.pb({tab[i]-r,-1}),v.pb({tab[i]+r,1});
		}
		sort(all(v)); 
		for(int cnt=0,i=0;i<siz(v);i++){
			if(!v[i].nd)
				res+=cnt;
			else
				cnt-=v[i].nd;
		}
		cout<<res<<"\n";
		for(int i=0;i<n-1;i++)
			cout<<tab[i]<<" "<<tab[i+1]<<"\n";
		exit(0);
	}
	
	// HARDA CZESC //

	
	calcCI();
	
	for(int l=1;l<n;l++){ //l - length, s+l == m
		
		for(int s=0;s<n-l;s++){	//calc f[s][s+l]
			if(l<=1){
				f[s][s+l]=0; continue;
			}
			f[s][s+l]=INF;
			for(int i=s;i<s+l;i++)
				f[s][s+l]=min((int)f[s][s+l],fp[s][i]+fs[i+1][s+l]);
		}
		
		for(int s=0;s<n-l;s++){ //calc f1[s][p][s+l] and f2[s][p][s+l]
			
			f1[s][s][s+l]=f[s][s+l];
			for(int p=s+1;p<s+l;p++){
				if(fl[p][s+l]<s)
					f1[s][p][s+l]=f1suf[s][s][p]+CI[p][s+l];
				else if(fl[p][s+l]==p-1)
					f1[s][p][s+l]=f1pref[s][fl[p][s+l]][p];
				else
					f1[s][p][s+l]=min((int)f1pref[s][fl[p][s+l]][p],f1suf[s][fl[p][s+l]+1][p]+CI[p][s+l]);
				
				f1[s][p][s+l]+=f[p][s+l];
			}
			
			f1pref[s][s][s+l]=f1[s][s][s+l]+CI[s+l][s];
			for(int p=s+1;p<s+l;p++)
				f1pref[s][p][s+l]=min((int)f1pref[s][p-1][s+l],f1[s][p][s+l]+CI[s+l][p]);
			f1suf[s][s+l-1][s+l]=f1[s][s+l-1][s+l];
			for(int p=s+l-2;p>=s;p--)
				f1suf[s][p][s+l]=min(f1[s][p][s+l],f1suf[s][p+1][s+l]);
			
			f2[s][s+l][s+l]=f[s][s+l];
			for(int p=s+1;p<s+l;p++){
				if(fr[p][s]>s+l)
					f2[s][p][s+l]=f2pref[p][s+l][s+l]+CI[p][s];
				else if(fr[p][s]==p+1)
					f2[s][p][s+l]=f2suf[p][fr[p][s]][s+l];
				else
					f2[s][p][s+l]=min((int)f2suf[p][fr[p][s]][s+l],f2pref[p][fr[p][s]-1][s+l]+CI[p][s]);
				f2[s][p][s+l]+=f[s][p];
			}
			
			f2suf[s][s+l][s+l]=f2[s][s+l][s+l]+CI[s][s+l];
			for(int p=s+l-1;p>s;p--)
				f2suf[s][p][s+l]=min((int)f2suf[s][p+1][s+l],f2[s][p][s+l]+CI[s][p]);
			f2pref[s][s+1][s+l]=f2[s][s+1][s+l];
			for(int p=s+2;p<=s+l;p++)
				f2pref[s][p][s+l]=min(f2pref[s][p-1][s+l],f2[s][p][s+l]);
			
		}
		
		for(int s=0;s<n-l;s++){ //calc fp[s][s+l] and fs[s][s+l]
			
			fp[s][s+l]=fs[s][s+l]=INF;
			for(int p=s;p<s+l;p++)
				fp[s][s+l]=min((int)fp[s][s+l],f1[s][p][s+l]+CI[s+l][p]);
			for(int p=s+1;p<=s+l;p++)
				fs[s][s+l]=min((int)fs[s][s+l],f2[s][p][s+l]+CI[s][p]);
		}
		
	}
	for(int i=1;i<n;i++){
		dp[0][i]=f[0][i]+CI[0][i];
		for(int p=1;p<i;p++){
			dp[p][i]=INF;
			for(int q=0;q<p;q++)
				dp[p][i]=min((int)dp[p][i],dp[q][p]+max(CI[p][q],CI[p][i]));
			dp[p][i]+=f[p][i];
		}
	}
	
	res=INF;
	for(int p=0;p<n-1;p++)
		res=min(res,dp[p][n-1]+CI[n-1][p]);
	
	cout<<res<<"\n";
	
}
