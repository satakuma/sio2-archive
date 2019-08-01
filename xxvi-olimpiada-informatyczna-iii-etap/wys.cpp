#include<bits/stdc++.h>
using namespace std;
using LL = long long;
constexpr int maxn = 300005;

int n, q;
LL A[maxn], B[maxn];

struct Tree {
	struct Node {
		LL mx=0, prop=0;
		void touch(LL x) {
			prop += x;
			mx += x;
		}
	} przed[4*maxn];
	int base;

	void merge(int a) {
		przed[a].mx = max(przed[2*a].mx, przed[2*a+1].mx);
	}

	void propagate(int a) {
		if(przed[a].prop == 0) return;
		auto x = przed[a].prop;
		przed[a].prop = 0;
		for(auto v:{2*a, 2*a+1})
			przed[v].touch(x);
	}
	
	void build(LL t[]) {
		base = 1;
		while(base < n) base <<= 1;
		for(int i=1; i<=n; i++)
			przed[i+base-1].mx = t[i];
		for(int i=base-1; i>0; i--)
			merge(i);
	}

	LL get(int a, int va, int vb, int xa, int xb) {
		if(xa <= va and vb <= xb)
			return przed[a].mx;
		
		propagate(a);
		LL ret = 0;
		auto s = (va + vb) / 2;
		if(xa <= s)
			ret = max(ret, get(2*a, va, s, xa, xb));
		if(s+1 <= xb)
			ret = max(ret, get(2*a+1, s+1, vb, xa, xb));
		merge(a);
		return ret;
	}

	void add(int a, int va, int vb, int xa, int xb, LL x) {
		if(xa <= va and vb <= xb) {
			przed[a].touch(x);
			return;
		}
		
		propagate(a);
		auto s = (va + vb) / 2;
		if(xa <= s)
			add(2*a, va, s, xa, xb, x);
		if(s+1 <= xb)
			add(2*a+1, s+1, vb, xa, xb, x);
		merge(a);
	}
} TB, TA;

template<typename T>
void fst(T *x) {
	(*x) = 0;
	char c = getc_unlocked(stdin);
	while(c < 33)
		c = getc_unlocked(stdin);
	bool sign = false;
	if(c == '-') {
		sign = true;
		c = getc_unlocked(stdin);
	}
	while(c > 32) {
		(*x) = (*x) * 10 + c - 48;
		c = getc_unlocked(stdin);
	}
	
	if(sign) (*x) = (*x) * -1;
}

void cfst(char* x) {
	char c = getc_unlocked(stdin);
	while(c < 33)
		c = getc_unlocked(stdin);
	(*x) = c;
}



int main() {
	//ios_base::sync_with_stdio(0);
	//cin.tie(0);
	
	//scanf("%d%d", &n, &q);
	fst(&n), fst(&q);
	for(int i=1; i<=n; i++) {
		fst(&A[i]);
		//scanf("%d", &A[i]);
	}
	
	sort(A+1, A+n+1);
	for(int i=1; i<=n; i++)
		B[i] = A[i] + n-i+1;
	
	TA.build(A), TB.build(B);
	int thr = 1;
	
	auto query = [&]() {
		printf("%d\n", n - thr + 1);
		//cout << n - thr + 1 << "\n";
	};
	
	auto bs = [&](LL x) { // pierwszy ktory ma conajmniej x
		int l = 1, r = n+1;
		while(l < r) {
			auto s = (l+r) / 2;
			if(TA.get(1, 1, TA.base, 1, s) < x)
				l = s+1;
			else
				r = s;
		}
		
		return l;
	};
	
	auto fix = [&]() {
		while(thr < n and TA.get(1, 1, TA.base, thr, thr) + n < TB.get(1, 1, TB.base, thr+1, n))
			thr++;
	};
	
	auto add_suf = [&]() {
		LL x, y;
		fst(&x), fst(&y);
		//scanf("%lld %lld", &x, &y);
		//cin >> x >> y;
		int h = bs(x);
		if(h == n+1) return;
		TB.add(1, 1, TB.base, h, n, y);
		TA.add(1, 1, TA.base, h, n, y);
		
		fix();
	};

	auto add_pref = [&]() {
		LL x, y;
		fst(&x), fst(&y);
		//scanf("%lld %lld", &x, &y);
		//cin >> x >> y;
		int h = bs(x+1);
		//cerr << "bs zwrocil" << h << endl;
		if(--h == 0) return;
		TB.add(1, 1, TB.base, 1, h, -y);
		TA.add(1, 1, TA.base, 1, h, -y);
		
		//cerr << TA.get(1, 1, TA.base, thr, thr) << " " << TB.get(1, 1, TB.base, thr+1, n) << endl;
		fix();
	};
	
	fix();
	while(q--) {
		char type;
		cfst(&type);
		//cin >> type;
		if(type == 'B') {
			add_suf();
		} else if(type == 'K') {
			add_pref();
		} else
			query();
	}
}