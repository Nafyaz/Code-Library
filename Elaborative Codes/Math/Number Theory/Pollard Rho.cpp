// [Pollard rho introduction | Math 361](https://www.youtube.com/watch?v=PYmXv4lqSPY&ab_channel=TommyOcchipinti)
// [Pollard rho factoring | Math 361](https://www.youtube.com/watch?v=6khEMeU8Fck&ab_channel=TommyOcchipinti)
// http://miller-rabin.appspot.com/

/**
Complexity : O(sqrt(Smallest Prime Factor of n)) = O(n^(1/4))

get_factor(n):
    Assumes n is a composite.
    Returns a proper divisor of n
Note: for factorizing large number, do trial division upto
      cubic root and then call pollard rho once.
*/

LL get_factor(LL n) 
{
    auto f = [&](LL x) { return mulmod(x, x, n) + 1; };
    LL slow = 0, fast = 0, st = 2, div;
    while(true)
    {
        if(slow == fast)
        {
            slow = st++;
            fast = f(slow);
        }

        div = gcd(abs(fast - slow), n);

        if(div != 1 && div != n)
            return div;

        slow = f(slow); 
        fast = f(f(fast));
    }
}

map<LL, LL> factorize(LL n) 
{
    map<LL, LL> res;
    if (n < 2) return res;
    LL small_primes[] = {2,  3,  5,  7,  11, 13, 17, 19, 23, 29, 31, 37, 41,
                        43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    for (LL p : small_primes)
        for (; n % p == 0; n /= p, res[p]++);

    auto _factor = [&](LL n, auto &_factor) 
    {
        if (n == 1) 
            return;
        if (isPrime(n))
            res[n]++;
        else
        {
            LL x = get_factor(n);
            _factor(x, _factor);
            _factor(n / x, _factor);
        }
    };
    _factor(n, _factor);
    return res;
}