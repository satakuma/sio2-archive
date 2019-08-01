#include<bits/stdc++.h>
using namespace std;


constexpr int maxn = 250;

int n, m, k, pos[maxn];
bitset<maxn> pom, M[17][maxn], Mpom[maxn], Mpom2[maxn];

void init() {
	for(int tmp=2, l=0; tmp<=n*n+5; tmp <<= 1, l++) {
		for(int i=0; i<n; i++) {
			M[l+1][i].reset();
			for(int j=0; j<n; j++)
				if(M[l][i][j])
					M[l+1][i] |= M[l][j];
		}
	}
}

bool check(int x) {
	for(int i=0; i<n; i++) {
		Mpom[i].reset();
		Mpom[i][i] = 1;
	}
	
	for(int l=20; l>=0; l--) {
		if(x & (1 << l)) {
			for(int i=0; i<n; i++) {
				Mpom2[i].reset();
				for(int j=0; j<n; j++)
					if(Mpom[i][j])
						Mpom2[i] |= M[l][j];
			}
			for(int i=0; i<n; i++)
				Mpom[i] = Mpom2[i];
		}
	}
	
	pom.set();
	for(int i=0; i<k; i++)
		pom &= Mpom[pos[i]];
	return pom.any();
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> k;
	for(int i=0; i<k; i++) {
		int s; cin >> s; s--;
		bool ex = false;
		for(int j=0; j<i; j++)
			if(pos[j] == s) {
				ex = true;
				break;
			}
		if(ex) {
			k--;
			i--;
			continue;
		}
		pos[i] = s;
	}
	
	for(int a, b, i=0; i<m; i++) {
		cin >> a >> b;
		a--, b--;
		M[0][a][b] = 1;
	}
	
	init();
	int l = 0, r = n*n+5;
	while(l < r) {
		auto s = (l+r) / 2;
		if(check(s))
			r = s;
		else
			l = s+1;
	}
	
	if(l > n*n) {
		cout << "NIE\n";
	} else {
		cout << "TAK\n";
		cout << l << '\n';
	}
}