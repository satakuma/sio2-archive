//Tymoteusz Wiśniewski XIV LO im. Stanislawa Staszica

#include<bits/stdc++.h>
using namespace std;

const int przed_max=2100000;
const int n_max=1000*1000+5;

struct zdarzenie             //struktura czas zdarzenia, poczatek czy koniec, numer prawnika, analogiczny czas dla danego prawnika
{
    long long czas;
    bool co;
    int numer;
    long long drugiczas;
};

struct op {
  bool operator() (const zdarzenie i,const zdarzenie j) { return (i.czas<j.czas);}
};

int n,k,rozm=1;
int przed[przed_max];
vector <zdarzenie> praw;
long long poczatek=0;
long long wynik=-1;
map <long long,int> liscie;
vector <long long> odp;

void gen()
{
    while(rozm<n)
        rozm*=2;
}
void wstaw(zdarzenie a)
{
    int va=liscie[a.czas]+rozm-1;
    przed[va]++;
    while(va!=1)
    {
        va/=2;
        przed[va]=przed[2*va]+przed[2*va+1];
    }
}
void czytaj(zdarzenie a)                   //dodac co jesli nie ma k prawnikow
{
    int va=1;
    int temp=0;
    if(przed[va]<k)
	{
		va=liscie[a.drugiczas]+rozm-1;
		przed[va]--;
		while(va!=1)
		{
			va/=2;
			przed[va]=przed[2*va]+przed[2*va+1];
		}
		return;
	}
    while(va<rozm)
    {
        if(przed[2*va]+temp<k)
        {
            temp+=przed[2*va];
            va=2*va+1;
        }
        else
            va*=2;
    }
    va-=rozm;
    if(wynik<a.czas-odp[va])
    {
        wynik=a.czas-odp[va];
        poczatek=odp[va];
    }
    va=liscie[a.drugiczas]+rozm-1;
    przed[va]--;
    while(va!=1)
    {
        va/=2;
        przed[va]=przed[2*va]+przed[2*va+1];
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>k;
    gen();
    for(int i=1;i<=n;i++)           //wczytuje dane do tablicy structow i same poczatki bez indeksow do tablicy poczatkow
    {
        zdarzenie tempP,tempK;
        long long p,kon;
        cin>>p>>kon;
        tempP={p,0,i,kon};
        tempK={kon,1,i,p};
        praw.push_back(tempP);
        praw.push_back(tempK);
    }
    sort(praw.begin(),praw.end(),op()); // sortuje po czasie zdarzenia (poczatki i konce)
    for(int i=0,j=1;i<2*n;i++)
        if(praw[i].co==0 && liscie[praw[i].czas]==0)
            {
				liscie[praw[i].czas]=j++;
				odp.push_back(praw[i].czas);
			}								  //wbijam do osobnego vectora posortowane poczatki pracy prawnikow i mapuje je na numery lisci
    for(int i=0;i<2*n;i++)               //jezeli zdarzenie to poczatek wczytuje do drzewa licznikowego
        if(praw[i].co==0)
            wstaw(praw[i]);
        else
            czytaj(praw[i]);           //jezeli zdarzenie to koniec czytam wynik i usuwam poczatek prawnika z drzewa
    long long koniec=poczatek+wynik;
    if(wynik<0)
    {
        cout<<0;
        return 0;
    }
    else
        cout<<wynik<<"\n";
    for(int i=0,j=0;i<2*n && j<k;i++)              //znajduje numery prawnikow ktorzy pracuja w znalezionym zakresie
        if(praw[i].co==0)
            if(praw[i].czas<=poczatek && praw[i].drugiczas>=koniec)
                {
					cout<<praw[i].numer<<" ";
					j++;
				}
    cout<<"\n";
    return 0;
}
