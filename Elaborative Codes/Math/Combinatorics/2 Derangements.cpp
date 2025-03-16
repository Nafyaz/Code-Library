// !n = (n-1) (!(n-1) + !(n-2))
LL D[MAXN];
LL getDerange(LL n)
{
    if(n == 0)
        return D[1] = 1;
    if(n == 1)
        return D[2] = 0;
    if(D[n] != 0)
        return D[n];

    return (n-1) * (getDerange(n-1) + getDerange(n-2));
}
