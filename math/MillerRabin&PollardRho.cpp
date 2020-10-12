const int test_case_size = 12;
const int test_cases[test_case_size] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

long long multiply_mod(long long x, long long y, long long p) {
    long long t = (x * y - (long long) ((long double) x / p * y + 1e-3) * p) % p;
    return t < 0 ? t + p : t;
}

long long add_mod(long long x, long long y, long long p) {
    return (0ull + x + y) % p;
}

long long power_mod(long long x, long long exp, long long p) {
    long long ans = 1;
    while (exp) {
        if (exp & 1)
            ans = multiply_mod(ans, x, p);
        x = multiply_mod(x, x, p);
        exp >>= 1;
    }
    return ans;
}

bool miller_rabin_check(long long prime, long long base) {
    long long number = prime - 1;
    for (; ~number & 1; number >>= 1)
        continue;
    long long result = power_mod(base, number, prime);
    for (; number != prime - 1 && result != 1 && result != prime - 1; number <<= 1)
        result = multiply_mod(result, result, prime);
    return result == prime - 1 || (number & 1) == 1;
}

bool miller_rabin(long long number) {
    if (number < 2)
        return false;
    if (number < 4)
        return true;
    if (~number & 1)
        return false;
    for (int i = 0; i < test_case_size && test_cases[i] < number; i++)
        if (!miller_rabin_check(number, test_cases[i]))
            return false;
    return true;
}

long long gcd(long long x, long long y) {
    return y == 0 ? x : gcd(y, x % y);
}

long long pollard_rho_test(long long number, long long seed) {
    long long x = rand() % (number - 1) + 1, y = x;
    int head = 1, tail = 2;
    while (true) {
        x = multiply_mod(x, x, number);
        x = add_mod(x, seed, number);
        if (x == y)
            return number;
        long long answer = gcd(std::abs(x - y), number);
        if (answer > 1 && answer < number)
            return answer;
        if (++head == tail) {
            y = x;
            tail <<= 1;
        }
    }
}

void factorize(long long number, std::vector<long long> &divisor) {
    if (number > 1) {
        if (miller_rabin(number)) {
            divisor.push_back(number);
        } else {
            long long factor = number;
            while (factor >= number)
                factor = pollard_rho_test(number, rand() % (number - 1) + 1);
            factorize(number / factor, divisor);
            factorize(factor, divisor);
        }
    }
}
