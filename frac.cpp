class frac {
public:
	int chisl, znam;

	frac(int a) {
		chisl = a;
		znam = 1;
	}
	frac(int _chisl, int _znam) {
		chisl = _chisl;
		znam = _znam;
	}
};

frac operator- (frac a, frac b) {
	return { a.chisl * b.znam - b.chisl * a.znam, a.znam * b.znam };
}

frac operator+ (frac a, frac b) {
	return { a.chisl * b.znam + b.chisl * a.znam, a.znam * b.znam };
}

frac operator* (frac a, frac b) {
	return { a.chisl * b.chisl, a.znam * b.znam };
}

frac operator/ (frac a, frac b) {
	swap(b.chisl, b.znam);
	return a * b;
}

void operator-= (frac &a, frac b) {
	a = a - b;
}

void operator+= (frac &a, frac b) {
	a = a + b;
}

bool operator== (frac a, frac b) {
	return ((a.chisl == b.chisl) && (a.znam == b.znam));
}

bool operator!= (frac a, frac b) {
	return !(a == b);
}

bool operator< (frac a, frac b) {
	auto res = a - b;
	return (res.chisl * res.znam < 0);
}

bool operator> (frac a, frac b) {
	auto res = a - b;
	return (res.chisl * res.znam > 0);
}
