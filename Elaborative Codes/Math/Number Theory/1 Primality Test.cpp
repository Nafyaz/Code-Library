// Easy BruteForce
// Complexity: O(sqrt(n))
bool isPrime(LL n)
{
    LL i;
    for(i = 2; i*i <= n; i++)
    {
        if(n%i == 0)
            return 0;
    }

    return 1;
}

// ----------------------------------------------------------------------

// Fermat's Primality Test, vulnerable to Charmichael numbers
bool isPrime2(LL n)
{
    vector<LL> checkerPrimes = {2, 3, 5, 7};
    if(binary_search(checkerPrimes.begin(), checkerPrimes.end(), n) == 1)
        return 1;

    vector<LL> carmichael = {561,1105,1729,2465,2821,6601,8911,10585,15841,
					29341,41041,46657,52633,62745,63973,75361,101101,
					115921,126217,162401,172081,188461,252601,278545,
					294409,314821,334153,340561,399001,410041,449065,
					488881,512461};

    if(binary_search(carmichael.begin(), carmichael.end(), n) == 1)
        return 0;

    for(auto cp : checkerPrimes)
    {
        if(bigmod(cp, n, n) != cp%n)
            return 0;
    }

    return 1;
}

// ----------------------------------------------------------------------

//Miller Rabin
bool isPrime3(LL n) {
  if (n < 2 or n % 6 % 4 != 1) return (n | 1) == 3;
  LL a[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
  LL s = __builtin_ctzll(n - 1), d = n >> s;
  for (LL x : a) {
    LL p = bigmod(x % n, d, n), i = s;
    for (; p != 1 and p != n - 1 and x % n and i--; p = mulmod(p, p, n))
      ;
    if (p != n - 1 and i != s) return false;
  }
  return true;
}

// ----------------------------------------------------------------------

//Miller-Rabin (2)
bool witness(LL wit, LL n){
    if(wit >= n) 
        return false;

    int s=0; LL t=n-1;
    while(t%2==0) s++,t/=2;

    wit = bigmod(wit,t,n);
    if(wit==1 || wit==n-1) 
        return false;

    for(int i=1;i<s;i++){
        wit=mulmod(wit,wit,n);
        if(wit == 1) 
            return true;
        if(wit == n - 1) 
            return false;
    }
    return true;
}

//Is n prime?
bool miller(LL n){
    
    //Check if n is a multiple of 2 or 3
    if (n < 2 or n % 6 % 4 != 1) 
        return (n | 1) == 3;

    // For numbers upto 2^64:
    LL bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

    // For numbers upto 2^32:
    // LL bases[] = {2, 7, 61};

    for(LL b : bases)
    {
        if(witness(b, n))
            return false;
    }
    
    return true;
}