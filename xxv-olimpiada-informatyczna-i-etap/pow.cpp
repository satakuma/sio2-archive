//Tymoteusz Wiśniewski XIV LO im. Stanislawa Staszica w Warszawie

#include<bits/stdc++.h>
using namespace std;
const int modulo=1000000007;
const int mn_max=500000;

int n,m,H;
struct tama
{
	int a;
	int b;
	int h;
};

vector<tama>tamy;
struct op													//vector z wysokosciami tam, operator do sortowania
{
	bool operator() (const tama a,const tama b)
	{
		return a.h<b.h;
	}
};

long long fu[mn_max+5][3]; 									//tablica Find&Union: 0 - reprezentant, 1 - ostatnia wysokosc, 2 - wynik

void inicjalizuj()
{
	for(int i=1;i<=n*m;i++)
	{
		fu[i][0]=i;
		fu[i][1]=-1;
	}
}

int fin(int a)												//operacja find - wskazywanie reprezentanta i przepisywanie go
{															//na siebie
	if(fu[a][0]==a)
		return a;
	fu[a][0]=fin(fu[a][0]);
	return fu[a][0];
}

void un(tama a)
{
	int va=fin(a.a);
	int vb=fin(a.b);
	if(va!=vb)
	{
		fu[va][2]+=a.h-fu[va][1];							//zaktualizowanie wyniku - liczby mozliwosci na danym obszarze
		fu[vb][2]+=a.h-fu[vb][1];
		fu[va][1]=a.h;										//ostatnia wysokosc, na ktorej wykonano operacje union
		fu[va][2]*=fu[vb][2];								//przemnozenie wynikow-tyle moglo byc mozliwosci
		fu[va][2]%=modulo;
		fu[vb][0]=va;										//aktualizacja reprezentanta
	}
	else
	{
		fu[va][2]+=a.h-fu[va][1];
		fu[va][1]=a.h;
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin>>m>>n>>H;
	if(m==1 && n==1)
	{
		cout<<H+1<<"\n";
		return 0;
	}
	
	for(int i=0;i<m;i++)
		for(int j=1;j<n;j++)
		{
			int temph;
			cin>>temph;
			tamy.push_back({i*n+j,i*n+j+1,temph});
		}
	for(int i=1;i<m;i++)
		for(int j=1;j<=n;j++)
		{
			int temph;
			cin>>temph;
			tamy.push_back({(i-1)*n+j,i*n+j,temph});				//pola sa numerowane od lewej do prawej
		}
	sort(tamy.begin(),tamy.end(),op());								//sortowanie rosnaco wg wysokosci tam
	inicjalizuj();													//inicjalizacja tablicy reprezentantow - kazdy wskazuje na siebie, ostatnia wysokosc
	for(int i=0;i<(int)tamy.size();i++)									//na ktorej byla operacja union wynosi -1
		un(tamy[i]);
	
	int poleWynikowe=fin(1);
	int wynik=fu[poleWynikowe][2];
	wynik+=H-tamy.back().h;
	wynik%=modulo;
	
	cout<<wynik<<"\n";
		
}	
	
	
