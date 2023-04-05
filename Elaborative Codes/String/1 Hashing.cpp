LL base = 31;

LL n, p[MAXN];
LL preHash[MAXN];
LL sufHash[MAXN];

void initHash()
{
    LL i;

    p[0] = 1;
    for(i = 1; i < MAXN; i++)
        p[i] = (p[i-1] * base) % MOD;
}

// Creates Positional Hashing
void createHash (string s)
{
    LL i;

    n = s.size();

    for(i = 1; i <= n; i++)
    {
        preHash[i] = (preHash[i-1] * base) % MOD;
        preHash[i] = (preHash[i] + s[i-1] - 'a' + 1) % MOD;
    }

    for(i = n; i > 0; i--)
    {
        sufHash[i] = (sufHash[i+1] * base) % MOD;
        sufHash[i] = (sufHash[i] + s[i-1] - 'a' + 1) % MOD;
    }
}


LL primes[31] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113,127};
LL nonPos[MAXN];
// Creats Nonpositional Hashing
void createHash(string s)
{
    LL i;

    n = s.size();

    nonPos[0] = 1;
    for(i = 1; i <= n; i++)
        nonPos[i] = (nonPos[i-1] * primes[s[i-1] - 'a']) % MOD;
}