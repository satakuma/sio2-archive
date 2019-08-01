#include<bits/stdc++.h>
using namespace std;

int n,rozm=1;
struct node
{
	long long v;
	long long l,p;
};
node przed[1500*1000+5];  //do zmiany;
int tab[300005][2];

inline void merge(int a)
{
	przed[a].v=przed[2*a].v+przed[2*a+1].v;
}

void zepchnij(int a,int va,int vb){
	int s=(va+vb)/2;
	long long a1=(przed[a].p-przed[a].l)/(vb-va);
	przed[2*a].l+=przed[a].l;
	przed[2*a].p+=przed[a].l+(s-va)*a1;
	przed[2*a].v=(przed[2*a].l+przed[2*a].p)*1LL*(s-va+1)/2;
	if(2*a<rozm)
		przed[2*a].v+=przed[4*a].v+przed[2*(2*a)+1].v;
	
	przed[2*a+1].l+=przed[a].p-(vb-s-1)*a1;
	przed[2*a+1].p+=przed[a].p;
	przed[2*a+1].v=(przed[2*a+1].l+przed[2*a+1].p)*1LL*(vb-s)/2;
	if(2*a+1<rozm)
		przed[2*a+1].v+=przed[2*(2*a+1)].v+przed[2*(2*a+1)+1].v;
	
	przed[a].l=przed[a].p=0;
}

void wstaw1(int a, int va, int vb, int xa, int xb, int l, int a1)
{
	//cout<<"wstaw1 -- jestem w: "<<a<<", l: "<<l<<", a1: "<<a1<<endl;
	if(xa<=va && vb<=xb){
		przed[a].l+=l+(1LL*va-xa)*a1;
		przed[a].p+=l+(1LL*vb-xa)*a1;
		przed[a].v=(przed[a].l+przed[a].p)*1LL*(vb-va+1)/2;
		if(a<rozm)
			przed[a].v+=przed[2*a].v+przed[2*a+1].v;
		//cout<<"wstawiam w: "<<a<<", l: "<<przed[a].l<<", p: "<<przed[a].p<<endl;
		//cout<<"suma: "<<przed[a].v<<endl;
		return;
	}
	if(przed[a].l || przed[a].p)
		zepchnij(a,va,vb);
	int s=(va+vb)/2;
	if(xa<=s)
		wstaw1(2*a,va,s,xa,xb,l,a1);
	if(s+1<=xb)
		wstaw1(2*a+1,s+1,vb,xa,xb,l,a1);
	merge(a);
}

void wstaw2(int a, int va, int vb, int xa, int xb, int p, int a1)
{
	//cout<<"wstaw2 -- jestem w: "<<a<<", p: "<<p<<", a1: "<<a1<<endl;
	if(xa<=va && vb<=xb){
		przed[a].l+=p-(1LL*xb-va)*a1;
		przed[a].p+=p-(1LL*xb-vb)*a1;
		przed[a].v=(przed[a].l+przed[a].p)*1LL*(vb-va+1)/2;
		if(a<rozm)
			przed[a].v+=przed[2*a].v+przed[2*a+1].v;
		//cout<<"wstawiam w: "<<a<<", l: "<<przed[a].l<<", p: "<<przed[a].p<<endl;
		//cout<<"suma: "<<przed[a].v<<endl;
		return;
	}
	if(przed[a].l || przed[a].p)
		zepchnij(a,va,vb);
	int s=(va+vb)/2;
	if(xa<=s)
		wstaw2(2*a,va,s,xa,xb,p,a1);
	if(s+1<=xb)
		wstaw2(2*a+1,s+1,vb,xa,xb,p,a1);
	merge(a);
}


long long czytaj(int a,int va,int vb,int xa,int xb)
{
	if(xa<=va && vb<=xb){
		//cout<<"czytam w: "<<a<<", v == "<<przed[a].v<<endl;
		return przed[a].v;
	}
	if(przed[a].l || przed[a].p)
		zepchnij(a,va,vb);
	int s=(va+vb)/2;
	long long res=0;
	if(xa<=s)
		res+=czytaj(2*a,va,s,xa,xb);
	if(s+1<=xb)
		res+=czytaj(2*a+1,s+1,vb,xa,xb);
	merge(a);
	return res;
}

void dodaj(int x,int s,int a)
{
	tab[x][0]=s;
	tab[x][1]=a;
	int d=ceil(1.0*s/a)-1;
	wstaw1(1,1,rozm,x,min(n,x+d),s,-a);
	if(x-1>0)
		wstaw2(1,1,rozm,max(x-d,1),x-1,s-a,a);
}
void usun(int x){
	int s=tab[x][0];
	int a=tab[x][1];
	int d=ceil(1.0*s/a)-1;
	tab[x][0]=tab[x][1]=0;
	wstaw1(1,1,rozm,x,min(n,x+d),-s,a);
	if(x-1>0)
		wstaw2(1,1,rozm,max(1,x-d),x-1,-s+a,-a);
}


int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int m;
	cin>>n>>m;
	while(rozm<n)
		rozm<<=1;
		
	while(m--)
	{
		char co;
		cin>>co;
		if(co=='P')
		{
			int x,s,a;
			cin>>x>>s>>a;
			dodaj(x,s,a);
		}
		else if(co=='U')
		{
			int x;
			cin>>x;
			usun(x);
		}
		else
		{
			int a,b;
			cin>>a>>b;
			long long sum=czytaj(1,1,rozm,a,b);
			cout<<sum/(b-a+1)<<'\n';
		}
	}
	
	return 0;
}


// #####   #####   #####        #####   #####   #   #
// #   #   #   #       #          #     #       ##  #
// #####   #####       #          #     #####   # # #
//     #       #       #          #     #       #  ##
// #####   #####       #          #     #####   #   # 
// 
// #   #   #   #   #   #   #####   ###      #####    ###
// ##  #   #   #   ## ##   #       #  #       #     #   #
// # # #   #   #   # # #   #####   ###        #     #   #
// #  ##   #   #   #   #   #       #  #       #     #   #
// #   #    ###    #   #   #####   #   #      #      ###
//
// #   #   #        ###    ###      ###    #####   #   #
// #  #    # #     #   #   #  #    #   #     #      # #
// # ##    ##      #   #   ###     #   #     #       #
// ##  #   #       #   #   #       #   #     #       #
// #    #  #####    ###    #        ###      #       #
