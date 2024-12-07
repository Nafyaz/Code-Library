LL egcd(LL a, LL b, LL& x, LL& y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    LL x1, y1;
    LL d = egcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

LL egcd2(LL a, LL b, LL& x, LL& y)
{
    x = 1, y = 0;
    LL x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1)
    {
        LL q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}

// Linear Diophantine Equation
// a*x + b*y = c
bool LDE(LL a, LL b, LL c, LL &x0, LL &y0, LL &d)
{
    d = egcd(abs(a), abs(b), x0, y0);
    if (c % d)
        return 0;

    x0 *= c / d;
    y0 *= c / d;
    x0 = (a < 0? -1 : 1) * x0;
    y0 = (b < 0? -1 : 1) * y0;
    return 1;
}

bool LDEall(LL a, LL b, LL c, LL t, LL &x, LL &y)
{
    LL d;
    if(LDE(a, b, c, x, y, d))
    {
        x = x + b*t;
        y = y - a*t;
        return 1;
    }

    return 0;
}
