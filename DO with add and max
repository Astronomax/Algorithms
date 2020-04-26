const int INF = 1e9;
struct node {
	int lb, rb, ans = 0, lazy = 0;
	node *l, *r;
 
	node(int lq, int rq) {
		lb = lq; rb = rq;
		if (lb + 1 < rb) {
			int mid = (lb + rb) / 2;
			l = new node(lb, mid);
			r = new node(mid, rb);
		}
	}
 
	void update() {
		if (lb + 1 < rb)
			ans = max(l->ans, r->ans);
	}
	void push() {
		ans += lazy;
		if (lb + 1 < rb) {
			l->lazy += lazy;
			r->lazy += lazy;
		}
		lazy = 0;
	}
 
	void add(int lq, int rq, int x) {
		push();
		if (rb <= lq || rq < lb)
			return;
		if (lq <= lb && rb - 1 <= rq) {
			lazy += x;
			push();
			return;
		}
		else {
			l->add(lq, rq, x);
			r->add(lq, rq, x);
			update();
		}
	}
 
	int maxim(int lq, int rq) {
                push();
		if (rb <= lq || rq < lb)
			return -INF;
		if (lq <= lb && rb - 1 <= rq)
			return ans;
		else return max(l->maxim(lq, rq), r->maxim(lq, rq));
	}
};
