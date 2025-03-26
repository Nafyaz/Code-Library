LL bell(LL n)
{
    if (n == 0 || n == 1)
        return 1;

    LL ret = 0;
    for (LL i = 0; i < n; i++)
    {
        ret += nCr(n - 1, i);
    }

    return ret;
}