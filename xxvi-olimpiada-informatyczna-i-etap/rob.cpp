#include<bits/stdc++.h>
using namespace std;
#define x real()
#define y imag()
#define sgn(c) ((c)<0?-1:1)
typedef long long LL;
typedef complex<LL> C;

constexpr int maxn=4e5+5;

int n,tab[maxn];
C pos[maxn],tmp(0,1);
LL t,pref[maxn],res,d,X,Y;

inline void swp(C& a){
	a=C(a.y,a.x);
}
inline void msx(C& a){
	a=C(-a.x,a.y);
}
inline LL fl(LL a,LL b){
	if(abs(a)%abs(b)==0) return a/b;
	return a/b-(sgn(a)*sgn(b)==-1);
}
inline LL cl(LL a,LL b){
	if(abs(a)%abs(b)==0) return a/b;
	return a/b+(sgn(a)*sgn(b)==1);
}
inline bool between(C& A,C& B,C& P){
	return ((A.x<P.x and P.x<=B.x) or (A.x>P.x and P.x>=B.x));
}
inline LL f(int i){
	return t/d+(pref[i]+1<t%d);		//jesli zawiera sie tylko w kawalku to zaliczamy
}

void proceed(C P,C& W,C& A,C& B,LL k){
	if(k<0) return;
	if(abs(A.y-P.y)%abs(W.y) or (A.y-P.y)/W.y>k or (A.y-P.y)/W.y<0) return;
	if(A.y!=P.y and abs(1e18/((A.y-P.y)/W.y))<abs(W.x)) return;
	P+=W*((A.y-P.y)/W.y);
	res+=between(A,B,P);
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>t; pref[0]=-1;
	for(int i=1;i<=4*n;i++,tmp*=C(0,-1)){
		if(i<=n) cin>>tab[i];
		else tab[i]=tab[i-n];
		pref[i]=pref[i-1]+1+tab[i];
		pos[i]=pos[i-1]+(tmp*(LL)tab[i]);
	}
	n*=4; d=pref[n]+1;
	cin>>X>>Y; C W(-pos[n]),P(X,Y);
	for(int i=0;i<n;i++){
		C A=pos[i],B=pos[i+1],P1=P,W1=W;
		if(!(i&1)) swp(P1),swp(W1),swp(A),swp(B);
		if(W1.y)
			proceed(P1,W1,A,B,f(i)-1);
		else if(A.y==P1.y){		//collinearity
			if(!W1.x){
				res+=f(i)*between(A,B,P1);
				continue;
			}
			LL a,b;
			if(A.x>B.x) msx(A),msx(B),msx(P1),msx(W1);
			if(W1.x>0) a=fl(A.x-P1.x,W1.x)+1,b=fl(B.x-P1.x,W1.x);
			else a=cl(B.x-P1.x,W1.x),b=cl(A.x-P1.x,W1.x)-1;
			a=max(a,0LL),b=min(b,f(i)-1); //cerr<<a<<" "<<b<<endl;
			res+=max(0LL,b-a+1);
		}	
	}
	C cur=-W*(t/d);
	t%=d; pref[n+1]=1e18; //tmp=C(0,1);
	int k=upper_bound(pref,pref+n+2,t)-pref-1;
	if(t-pref[k]>1){
		C A=cur+pos[k]+(pos[k+1]-pos[k])/(LL)tab[k+1]*(t-pref[k]-1),B=cur+pos[k+1];
		if(A.x == B.x) swp(A),swp(B),swp(P);
		if(A.y == P.y) res-=between(A,B,P);
	}
	cout<<res+(!abs(P))<<'\n';
}


