#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 1000005;

int n, rnk[maxn], suf[maxn], ans[maxn];

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=1; i<=n; i++) {
		cin >> rnk[i];
		suf[rnk[i]] = i;
	}
	
	rnk[n+1] = n+1;
	ans[suf[1]] = 1;
	for(int i=2, cur=1; i<=n; i++)
		ans[suf[i]] = (rnk[suf[i-1] + 1] < rnk[suf[i] + 1] ? cur : ++cur);
	
	for(int i=1; i<=n; i++)
		cout << ans[i] << " ";
	cout << "\n";
}