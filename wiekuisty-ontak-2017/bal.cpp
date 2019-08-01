#include<bits/stdc++.h>
using namespace std;

mt19937 rng;
struct Node {
	int key, pr, sz;
	bool rev;
	Node *l, *r;
	Node(int key, Node *l=nullptr, Node *r=nullptr, int _pr=0, int sz=1, bool rev=false):
	key(key), pr(_pr), sz(sz), rev(rev), l(l), r(r) {
		if(pr == 0) pr = rng();
	}
	
	void touch() {
		if(rev) {
			swap(l, r);
			if(l) l->rev = !l->rev;
			if(r) r->rev = !r->rev;
			rev = false;
		}
	}
	void update() {
		sz = 1;
		if(l) sz += l->sz;
		if(r) sz += r->sz;
	}
};

using pNode = Node*;

struct Treap {
	pNode root;
	Treap(pNode root=nullptr): root(root) {}
	
	int get_sz(pNode p) {
		return p ? p->sz : 0;
	}
	void _split(pNode cur, int x, pNode &l, pNode &r) {
		if(not cur) {
			l = r = nullptr;
			return;
		}
		cur->touch();
		if(x <= get_sz(cur->l))
			_split(cur->l, x, l, cur->l), r = cur;
		else
			_split(cur->r, x - get_sz(cur->l) - 1, cur->r, r), l = cur;
		cur->update();
	}
	pair<Treap, Treap> split(int x) {
		Treap l, r;
		_split(root, x, l.root, r.root);
		return {l, r};
	}
	
	void reverse() {
		if(root) root->rev = !root->rev;
	}
};

void _merge(pNode &cur, pNode l, pNode r) {
	if(not l or not r) {
		cur = (l ? l : r);
		return;
	}
	if(l->pr > r->pr) {
		l->touch();
		_merge(l->r, l->r, r), cur = l;
	} else {
		r->touch();
		_merge(r->l, l, r->l), cur = r;
	}
	cur->update();
}

Treap merge(Treap l, Treap r) {
	Treap ret;
	_merge(ret.root, l.root, r.root);
	return ret;
}

void heapify(pNode cur) {
	auto mx = cur;
	if(cur->l and cur->l->pr > mx->pr)
		mx = cur->l;
	if(cur->r and cur->r->pr > mx->pr)
		mx = cur->r;
	if(mx != cur) {
		swap(mx->pr, cur->pr);
		heapify(mx);
	}
}

void build(int* A, int n, pNode& cur) {
	if(n == 0) return;
	auto mid = n / 2;
	cur = new Node(A[mid]);
	build(A, mid, cur->l);
	build(A + mid + 1, n - mid - 1, cur->r);
	cur->update();
	heapify(cur);
}

int main()
{
	rng = mt19937(time(0));
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, q; cin >> n >> q;
	vector<int> A(n);
	for(auto& x:A)
		cin >> x;
	
	Treap T;
	build(A.data(), n, T.root);
	
	while(q--) {
		char type;
		cin >> type;
		if(type == 'Q') {
			Treap L, x, R;
			int i; cin >> i; i--;
			tie(L, R) = T.split(i);
			tie(x, R) = R.split(1);
			cout << x.root->key << "\n";
			L = merge(L, x);
			T = merge(L, R);
		} else {	
			Treap L, mid, R;
			int a, b; cin >> a >> b; a--;
			tie(L, R) = T.split(b);
			tie(L, mid) = L.split(a);
			mid.reverse();
			L = merge(L, mid);
			T = merge(L, R);
		}	
	}
}