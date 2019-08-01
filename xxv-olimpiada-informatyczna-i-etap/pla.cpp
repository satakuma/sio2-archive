//Tymoteusz Wiśniewski XIV LO im. Stanislawa Staszica w Warszawie

#include<bits/stdc++.h>
#define st first
#define nd second
using namespace std;
const int n_max=500000;

struct stacja
{
    int d;
    int l;
    int num;
};

struct op
{
    bool operator() (const stacja a,const stacja b)
    {
        return a.d<b.d;
    }
};

int n;
vector < pair<int , int > > graf[n_max+5];
vector <stacja> stacje;
vector <stacja> naProstej;

int szukaj(int x)
{
    int p=0,k=naProstej.size()-1;
    while(p!=k)
    {
        int s=(p+k)/2;
        if(naProstej[s].d-naProstej[s].l>=x)
            k=s;
        else
            p=s+1;
    }
    return p;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    stacje.resize(n-2);
    for(int i=0;i<n-2;i++)
        {
            cin>>stacje[i].d;
            stacje[i].num=i+2;
        }
    for(int i=0;i<n-2;i++)
        cin>>stacje[i].l;           //wczytywanie danych
    bool mozna=true;
    if(n==2)
    {
		cout<<"TAK"<<"\n";
		cout<<1<<" "<<2<<" "<<3<<"\n";
		return 0;
	}
    int dl=abs(stacje[0].d-stacje[0].l);
    if(dl>0)
        {
            for(int i=1;i<n-2;i++)
                if(abs(stacje[i].d-stacje[i].l)!=dl)    //jezeli roznica odleglosci jest taka sama to mozna ulozyc plan metra
                {                                       //bez zadnej stacji pomiedzy dworcem a lotniskiem
                    mozna=false;
                    break;
                }
        }
    else
        mozna=false;
    if(mozna)
        {
            cout<<"TAK"<<"\n";
            cout<<1<<" "<<n<<" "<<dl<<"\n";
            for(int i=0;i<(int)stacje.size();i++)
                if(stacje[i].d<stacje[i].l)
                    cout<<1<<" "<<stacje[i].num<<" "<<stacje[i].d<<"\n";
                else
                    cout<<n<<" "<<stacje[i].num<<" "<<stacje[i].l<<"\n";
            return 0;
        }
    dl=INT_MAX;
    int indexdl=0;
    for(int i=0;i<n-2;i++)
        if(stacje[i].d+stacje[i].l<dl)      //jesli sa stacje pomiedzy, to odleglosc miedzy dworcem a lotniskiem jest rowna
        {                                   //najmniejszej sumie odleglosci stacji od lotniska i dworca
            dl=stacje[i].d+stacje[i].l;
            indexdl=i;
        }
    swap(stacje[indexdl],stacje[n-3]);      //przenoszenie stacji o najmniejszej sumie do osobnego vectora
    naProstej.push_back(stacje[n-3]);
    stacje.pop_back();
    for(int i=0;i<(int)stacje.size();)
        if(stacje[i].d+stacje[i].l==dl)             //mozliwe ze jest wiecej stacji o dokladnie tej samej sumie, nalezy je takze przeniesc
            {                                       //do vectora naProstej, gdyz stacje te sa wspolliniowe
                swap(stacje[i],stacje.back());
                naProstej.push_back(stacje.back());
                stacje.pop_back();
            }
        else
            i++;
    sort(naProstej.begin(),naProstej.end(),op());
    for(int i=1;i<(int)naProstej.size();i++)
        if(naProstej[i].d==naProstej[i-1].d)        //jezeli podano dwie stacje o takich samych odleglosciach to sa tozsame
            {                                       //a wiec sprzecznosc
                cout<<"NIE"<<"\n";
                return 0;
            }
    graf[1].push_back(make_pair(naProstej.front().num,naProstej.front().d));    //tworzenie krawedzi pomiedzy wspoliniowymi stacjami
    for(int i=0;i<(int)naProstej.size()-1;i++)
        graf[naProstej[i].num].push_back(make_pair(naProstej[i+1].num,naProstej[i+1].d-naProstej[i].d));
    graf[naProstej.back().num].push_back(make_pair(n,dl-naProstej.back().d));
    for(int i=0;i<(int)stacje.size();i++)
    {
        int temp=szukaj(stacje[i].d-stacje[i].l);						//binarka szuka czy jest na prostej stacja o takiej samej roznicy odleglosci
        if(stacje[i].d-stacje[i].l==naProstej[temp].d-naProstej[temp].l)
            graf[naProstej[temp].num].push_back(make_pair(stacje[i].num,(stacje[i].d+stacje[i].l-dl)/2));
        else if(stacje[i].d-stacje[i].l==dl)
            graf[n].push_back(make_pair(stacje[i].num,stacje[i].l));		//lub czy mozna stacje przylaczyc do dworca lub lotniska
        else if(stacje[i].l-stacje[i].d==dl)
            graf[1].push_back(make_pair(stacje[i].num,stacje[i].d));
        else
        {
            cout<<"NIE"<<"\n";
            return 0;
        }
    }
    cout<<"TAK"<<"\n";
    for(int i=1;i<=n;i++)		//wypisanie odpowiedzi
        for(int j=0;j<(int)graf[i].size();j++)
            cout<<i<<" "<<graf[i][j].st<<" "<<graf[i][j].nd<<"\n";
    return 0;
}
