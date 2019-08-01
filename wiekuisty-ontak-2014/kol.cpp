#include<bits/stdc++.h>
#include "kol.h"
using namespace std;
#ifndef d
#define d(...)
#endif
#define st first
#define nd second
#define pb push_back
#define siz(c) (int)(c).size()
#define all(c) (c).begin(), (c).end()
typedef long long LL;
typedef long double LD;
constexpr int INF=1e9+7;
constexpr LL INFL=1e18;
template<class L, class R> ostream &operator<<(ostream &os, pair<L,R> P) {
  return os << "(" << P.st << "," << P.nd << ")";
}
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag,
         tree_order_statistics_node_update>;
*/



int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	init();
	
	int sz = 0, my_sz = 0;
	vector<int> my_rooms(10 * 5);
	for(int i=0; i<10; i++) {
		for(int j=0; j<3; j++) {
			vector<int> tmp(i * 5 + j);
			iota(all(tmp), 0);
			int no = create(tmp);
			assert(no == sz);
			sz++;
			my_rooms[i * 5 + j] = my_sz++;
		}
		
		vector<int> tmp(i * 5 + 1);
		iota(all(tmp), 0);
		int no = create(tmp);
		
		if(no > sz - 2) {
			my_rooms[i * 5 + 3] = my_sz - 2;
			my_rooms[i * 5 + 4] = my_sz - 1;
			tmp.push_back(i * 5 + 1);
			tmp.push_back(i * 5 + 3);
			if(no == sz) sz++;
			no = create(tmp);
			if(no == sz) sz++;
		} else {
			my_rooms[i * 5 + 3] = my_sz - 1;
			my_rooms[i * 5 + 4] = my_sz - 2;
			tmp.push_back(i * 5 + 2);
			tmp.push_back(i * 5 + 3);
			if(no == sz) sz++;
			no = create(tmp);
			if(no == sz) sz++;
		}
	}
	
	answer(my_rooms);
}