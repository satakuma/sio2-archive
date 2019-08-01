#include<bits/stdc++.h>
using namespace std;

const int maxn=1000*1000+5,eps=10;

int n;
int tab[maxn],co[300];
int cnt[3];

inline bool okb()
{
	return (cnt[0]!=cnt[1] && cnt[0]!=cnt[2] && cnt[1]!=cnt[2]);
}

void brut()
{
	for(int i=0;i<n;i++){
		char c;
		cin>>c;
		tab[i]=co[c];
	}
	int res=-1;
	for(int i=0;i<n;i++){
		for(int j=0;j<3;j++)
			cnt[j]=0;
		for(int j=i;j<n;j++){
			cnt[tab[j]]++;
			if(okb())
				res=max(res,j-i+1);
		}
	}
	if(res==-1)
		cout<<"NIE\n";
	else
		cout<<res<<"\n";
	
	exit(0);
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin>>n;
	co['C']=0;
	co['B']=1;
	co['S']=2;
	if(n<=2500)
		brut();
		
		
	for(int i=1;i<=n;i++){
		char c;
		cin>>c;
		tab[i]=co[(int)c];
	}
	
	int res=-1;
	for(int i=1;i<=eps;i++){
		for(int j=0;j<3;j++)
			cnt[j]=0;
		for(int j=i;j<=n;j++){
			cnt[tab[j]]++;
			if(okb())
				res=max(res,j-i+1);
		}
	}
	for(int j=n-eps;j<=n;j++){
		for(int i=0;i<3;i++)
			cnt[i]=0;
		for(int i=j;i>0;i--){
			cnt[tab[i]]++;
			if(okb())
				res=max(res,j-i+1);
		}
	}
	
	if(res==-1)
		cout<<"NIE\n";
	else
		cout<<res<<"\n";
	
	
	return 0;
}
			
	
	
