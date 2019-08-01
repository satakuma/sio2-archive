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

constexpr int maxn=1e6+5;

char zn[4]={'A','C','T','G'};
int ind[500];

string S[2];
int nxt[2][4][maxn],N[2];

void read_and_build()
{
	for(int i=0;i<4;i++)
		ind[zn[i]]=i;
	for(int i:{0,1}){
		cin>>S[i]; int n=siz(S[i]); N[i]=n;
		for(int x=0;x<4;x++)
			nxt[i][x][n]=n;
		for(int j=n-1;j>=0;j--){
			for(int x=0;x<4;x++)
				nxt[i][x][j]=nxt[i][x][j+1];
			nxt[i][ind[S[i][j]]][j]=j;
		}
	}
}

void gen(string& s,string& wz,vector<int>& suf){
	int n=siz(wz);
	int pt=n-1;
	suf.resize(n);
	for(int i=siz(s)-1;i>=0;i--){
		if(pt>-1 and s[i]==wz[pt]){
			suf[pt--]=i;
		}
	}
}

void solve()
{
	string ans;
	vector<int>suf[2];
	for(int k=0;k<4;k++){
		string res;
		int pos=0,p[2]={0,0};
		while(p[0]<N[0] and p[1]<N[1]){
			if(pos == siz(suf[0]) or (nxt[0][k][p[0]]<suf[0][pos] and nxt[1][k][p[1]]<suf[1][pos])){
				if(nxt[0][k][p[0]]!=N[0] and nxt[1][k][p[1]]!=N[1])
					res.pb(zn[k]);
				for(int i:{0,1})
					p[i]=nxt[i][k][p[i]]+1;
			}
			else
			{
				res.pb(S[0][suf[0][pos]]);
				for(int i:{0,1})
					p[i]=nxt[i][ind[res.back()]][p[i]]+1;
				pos++;
			}
		}
		ans=res;
		for(int i:{0,1})
			gen(S[i],res,suf[i]);
	}
	cout<<ans<<"\n";
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	read_and_build();
	solve();
	
	return 0;
}