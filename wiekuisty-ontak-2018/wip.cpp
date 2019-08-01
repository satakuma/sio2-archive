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

const int maxn=300005;

int n;
vector<pair<int,int> >graf[maxn];
LL koszt[maxn];
pair<LL,LL>med[maxn];

LL calcCost(vector<pair<LL,LL> >&v,LL m)
{
	LL res=0;
	for(auto& p:v){
		if(p.st>m)
			res+=p.st-m;
		else if(p.nd<m)
			res+=m-p.nd;
	}
	return res;
}

pair<LL,LL> calcMed(vector<pair<LL,LL> >& v)
{
	if(v.empty()){
		return {0,0};
	}
	LL l=INFL,r=-INFL;
	for(auto& p:v){
		l=min(l,p.st);
		r=max(r,p.nd);
	}
	l--,r++;
	LL a=l,b=r;
	while(b-a>3){
		LL eps=(b-a)/3;
		LL lt=a+eps,rt=b-eps;
		if(calcCost(v,lt)>calcCost(v,rt))
			a=lt;
		else
			b=rt;
	}
	//cerr<<"po ternarce"<<endl;
	LL lst=INFL;
	LL S=a;
	assert(a<=b);
	//cerr<<"po assercie"<<endl;
	for(LL i=a;i<=b;i++)
	{
		LL x=calcCost(v,i);
		if(x<lst){
			S=i;
			lst=x;
		}
	}
	a=S,b=r;
	//cerr<<"a: "<<a<<", b: "<<b<<endl;
	while(b-a>1){
		LL s=(a+b)/2;
		if(calcCost(v,s)>lst)
			b=s-1;
		else
			a=s;
	}
	//cerr<<"po binarce1"<<endl;
	if(calcCost(v,b)==lst)
		a=b;
	LL ansR=a;
	a=l,b=S;
	while(b-a>1){
		LL s=(a+b)/2;
		if(calcCost(v,s)>lst)
			a=s+1;
		else
			b=s;
	}
	if(calcCost(v,a)>lst)
		a=b;
	return {a,ansR};
}

LL dfs(int a)
{
	//cerr<<"jestem w: "<<a<<endl;
	LL res=0;
	vector<pair<LL,LL> >v;
	for(auto p:graf[a]){
		res+=dfs(p.st);
		v.pb({med[p.st].st+p.nd,med[p.st].nd+p.nd});
	}
	med[a]=calcMed(v);
	res+=calcCost(v,med[a].st);
	//cerr<<"wychodze z: "<<a<<endl;
	return res;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	cin>>n;
	for(int i=1,p,v;i<=n-1;i++){
		cin>>p>>v;
		graf[p].pb({i,v});
	}
	cout<<dfs(0)<<"\n";
	
	//cout<<med[0].st<<" "<<med[0].nd<<endl;
	
	return 0;
}