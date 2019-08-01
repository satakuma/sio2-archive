#include<bits/stdc++.h>
using namespace std;
using LL = long long;
constexpr int maxn = 1000003;

int m, s, cnt, B;
LL fen[maxn], total, lst;

void insert(int i, LL x) {
	if(i <= B) B = -1;
	while(i <= m) {
		fen[i] += x;
		i += i&(-i);
	}
}
LL query(int i) {
	LL ret = 0;
	while(i > 0) {
		ret += fen[i];
		i -= i&(-i);
	}
	return ret;
}
LL get_val(int i) {
	return query(i) - (i-1 == B ? lst : query(i-1));
}

void inicjuj(int _m) {
	m = _m;
	s = 1;
	cnt = 0;
	B = -1;
}

void dodaj(int k) {
	if(cnt < m) {
		insert(++cnt, k);
		total += k;
	} else {
		LL x = k - get_val(s);
		total += x;
		insert(s++, x);
		if(s > m) s = 1;
	}
}

void koryguj(int i, int k) {
	i = s + cnt - i;
	if(i > m) i -= m;
	insert(i, k);
	total += k;
}

long long suma(int i) {
	int b = s + cnt - 1;
	if(b > m) b -= m;
	int a = b - i;
	
	LL qb;
	if(b == B)
		qb = lst;
	else {
		B = b;
		qb = lst = query(b);
	}
	
	if(a < 0) {
		return total - (query(a+m) - qb);
	} else {
		return qb - query(a);
	}
}
