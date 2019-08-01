#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define st first
#define nd second
#define all(c) (c).begin(),(c).end()
#define siz(c) (int)(c).size()
typedef long long LL;
typedef long double LD;
constexpr int INF=1e9+7;
constexpr LL INFL=1e18;

const int maxn=3e5+5,maxt=1e6+6;

int n,t,rozm=1;
set<int>secik[maxt];
int tab[maxn],nxt[maxn];
int przedmn[4*maxn],przednx[4*maxn],przedmx[4*maxn];

void build()
{
	while(rozm<n)
		rozm<<=1;
	for(int i=1;i<=t;i++)
		secik[i].insert(INF);
	
	for(int i=1;i<=n;i++){
		nxt[i]=*secik[tab[i]].upper_bound(i);
	}
	for(int i=rozm;i<rozm+n;i++){
		przedmn[i]=przedmx[i]=tab[i-rozm+1];
		przednx[i]=nxt[i-rozm+1];
	}
	for(int i=rozm+n;i<2*rozm;i++){
		przednx[i]=przedmn[i]=INF;
	}
	for(int i=rozm-1;i>0;i--){
		przedmn[i]=min(przedmn[2*i],przedmn[2*i+1]);
		przednx[i]=min(przednx[2*i],przednx[2*i+1]);
		przedmx[i]=max(przedmx[2*i],przedmx[2*i+1]);
	}
}

void wstawnx(int a,int v)
{
	nxt[a]=v;
	int va=a+rozm-1;
	przednx[va]=v;
	while(va!=1)
	{
		va>>=1;
		przednx[va]=min(przednx[2*va],przednx[2*va+1]);
	}
}
void wstaw(int a,int v)
{
	int va=a+rozm-1;
	przedmn[va]=przedmx[va]=v;
	while(va!=1){
		va>>=1;
		przedmx[va]=max(przedmx[2*va],przedmx[2*va+1]);
		przedmn[va]=min(przedmn[2*va],przedmn[2*va+1]);
	}
}

void insert(int j,int v)
{
	auto it=secik[tab[j]].erase(secik[tab[j]].find(j));
	if(it!=secik[tab[j]].begin()){
		auto it2=it; it2--;
		wstawnx(*it2,*it);
	}
	tab[j]=v;
	it=secik[tab[j]].insert(j).st;
	if(it!=secik[tab[j]].begin()){
		auto it2=it; it2--;
		wstawnx(*it2,*it);
	}
	auto it2=it;
	it2++;
	wstawnx(*it,*it2);
	wstaw(j,v);
}

pair<int,int> query(int a,int b)
{
	int va=a+rozm-1;
	int vb=b+rozm-1;
	int mn=min(przedmn[va],przedmn[vb]);
	int mx=max(przedmx[va],przedmx[vb]);
	while(va/2 != vb/2){
		if(!(va&1))
		{
			mn=min(mn,przedmn[va+1]);
			mx=max(mx,przedmx[va+1]);
		}
		if(vb&1){
			mn=min(mn,przedmn[vb-1]);
			mx=max(mx,przedmx[vb-1]);
		}
		va>>=1;
		vb>>=1;
	}
	return {mn,mx};
}

int querynx(int a,int b)
{
	int va=a+rozm-1;
	int vb=b+rozm-1;
	int mn=min(przednx[va],przednx[vb]);
	while(va/2 != vb/2){
		if(!(va&1))
		{
			mn=min(mn,przednx[va+1]);
		}
		if(vb&1){
			mn=min(mn,przednx[vb-1]);
		}
		va>>=1;
		vb>>=1;
	}
	return mn;
}

void czytaj(int l,int r){
	int mn,mx;
	tie(mn,mx)=query(l,r);
	if(mx-mn!=r-l){
		cout<<"NO\n";
		return;
	}
	int nx=querynx(l,r);
	if(nx<=r)
		cout<<"NO\n";
	else
		cout<<"YES\n";
}
	
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	cin>>n>>t;
	for(int i=1;i<=n;i++){
		cin>>tab[i];
		secik[tab[i]].insert(i);
	}
	build();
	
	int q;
	cin>>q;
	while(q--)
	{
		int co;
		cin>>co;
		if(co==1){
			int a,b;
			cin>>a>>b;
			czytaj(a,b);
		}
		else
		{
			int j,v;
			cin>>j>>v;
			insert(j,v);
		}
	}
	
	return 0;
}