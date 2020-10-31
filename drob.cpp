class drob {
public:
	int chisl, znam;

	drob(int a) {
		chisl = a;
		znam = 1;
	}
	drob(int _chisl, int _znam) {
		chisl = _chisl;
		znam = _znam;
	}
};

drob operator- (drob a, drob b) {
	return { a.chisl * b.znam - b.chisl * a.znam, a.znam * b.znam };
}

drob operator+ (drob a, drob b) {
	return { a.chisl * b.znam + b.chisl * a.znam, a.znam * b.znam };
}

drob operator* (drob a, drob b) {
	return { a.chisl * b.chisl, a.znam * b.znam };
}

drob operator/ (drob a, drob b) {
	swap(b.chisl, b.znam);
	return a * b;
}

void operator-= (drob &a, drob b) {
	a = a - b;
}

void operator+= (drob &a, drob b) {
	a = a + b;
}

bool operator== (drob a, drob b) {
	return ((a.chisl == b.chisl) && (a.znam == b.znam));
}

bool operator!= (drob a, drob b) {
	return !(a == b);
}

bool operator< (drob a, drob b) {
	auto res = a - b;
	return (res.chisl * res.znam < 0);
}

bool operator> (drob a, drob b) {
	auto res = a - b;
	return (res.chisl * res.znam > 0);
}
