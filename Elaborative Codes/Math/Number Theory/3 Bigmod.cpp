LL bigmod(LL a, LL p, LL mod = MOD)
{
    if(p == 0)
        return 1%mod;
    if(p == 1)
        return a%mod;

    LL ret = bigmod(a, p/2, mod);
    ret = (ret*ret)%mod;
    if(p&1)
        return (a*ret)%mod;
    return ret;
}

// ----------------------------------------------------------------------

LL bigmod(LL a, LL p, LL mod = MOD)
{
    LL ret = 1%mod;
    while(p)
    {
        if(p&1)
            ret = (ret*a)%mod;
        a = (a*a)%mod;
        p /= 2;
    }
    return ret;
}