#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 500005;

int n, s, L[maxn], R[maxn], delta[maxn];
bool choice[maxn];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> n >> s;
	for(int i=0; i<n-1; i++) {
		cin >> L[i] >> R[i];
		choice[i] = (L[i] > R[i]);
		delta[i] = abs(L[i] - R[i]);
	}
	
	int pref = choice[0], len = (choice[0] ? n - s : s - 1) + 1;
	choice[n-1] = !choice[0];
	for(int i=0; i<len; i++) {
		pref = ((int)choice[i] == pref ? pref : -1);
	}
	
	if(pref != -1) {
		auto it = min_element(delta, delta + len) - delta;
		choice[it] ^= 1;
	}
	
	long long sum = 0;
	for(int i=0; i<n-1; i++)
		sum += (choice[i] ? R[i] : L[i]);
	
	cout << sum << "\n" << s << " ";
	
	deque<int> dq;
	for(int i=1; i<=n; i++) {
		if(i != s)
			dq.emplace_back(i);
	}
	for(int i=0; i<n-1;) {
		auto j = i;
		while(j < n-1 and choice[i] == choice[j])
			j++;
		stack<int> tmp;
		while(i < j) {
			if(choice[i]) {
				tmp.emplace(dq.back());
				dq.pop_back();
			} else {
				tmp.emplace(dq.front());
				dq.pop_front();
			}
			i++;
		}
		
		while(not tmp.empty()) {
			cout << tmp.top() << " ";
			tmp.pop();
		}
	}
	
	return 0;
}

// 997 <-- ten numer to kłopoty!