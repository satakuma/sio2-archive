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

const int maxn=50005,C=800,alf=122-48;

inline bool r(){
	return ((rand()&1)+(rand()&1))&1;
}

int n;
int tab[maxn][5];
bool sign[alf+5][5];

int mask[maxn];

unordered_set<LL>S;
vector<int>cur[(1<<5)+5];

inline LL hasz(int a,int b){
	return (LL)a*1000000+b;
}

inline void unhash(LL x){
	int b=x%1000000; x/=1000000;
	cout<<x+1<<" "<<b+1<<"\n";
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	srand(time(0));
	
	cin>>n;
	for(int i=0;i<n;i++){
		char c;
		for(int j=0;j<5;j++){
			cin>>c;
			tab[i][j]=c-48;
		}
	}
	const int MX=1e5;
	for(int z=0;z<C && siz(S)<MX;z++){
		for(int i=0;i<=alf;i++)
			for(int j=0;j<5;j++)
				sign[i][j]=r();
		for(int i=0;i<(1<<5);i++)
			cur[i].clear();
		for(int i=0;i<n && siz(S)<MX;i++){
			mask[i]=0;
			for(int j=0;j<5;j++){
				mask[i]<<=1;
				mask[i]+=sign[tab[i][j]][j];
			}
			const int poz=mask[i]^((1<<5)-1);
			for(auto a:cur[poz]){
				S.insert(hasz(min(i,a),max(i,a)));
				if(siz(S)==MX) break;
			}
			cur[mask[i]].pb(i);
		}
	}
	cout<<siz(S)<<"\n";
	for(auto it:S)
		unhash(it);
	
	return 0;
}
