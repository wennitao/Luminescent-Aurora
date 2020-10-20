inline void Mul(long long &c, long long &d, long long a, long long b, long long w) {
	int cc = (a * c + b * d % mod * w) % mod;
	int dd = (a * d + b * c) %mod;
	c = cc;
	d = dd;
}
inline bool Solve(int n, int &x) {
	if(!n)
		return x = 0, 1;
	if(mod == 2)
		return x = 1, 1;
	if(Pow(n, mod - 2, mod) == mod - 1)
		return 0;
	long long c = 1, d = 0, b = 1, a, w;
	// Finding a such that a ^ 2 - n is not a square
	do {
		a = rand() % mod, w = (a * a - n + mod) % mod;
		if(!w)
			return x = a, 1;
	}while(Pow(w, mod - 2, mod) != mod - 1);
	for(int times = (mod + 1) / 2; times; times >>= 1) {
		if(times & 1)
			Mul(c, d, a, b, w);
		Mul(a, b, a, b, w);
	}
	// x = (a + sqrt(w)) ^ ((p + 1) / 2)
	return x = c, 1;
}
