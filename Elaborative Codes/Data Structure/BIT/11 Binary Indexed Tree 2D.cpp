// Always starts with (1, 1) as top right corner of grid

LL mx = 100, my = 100;
BIT[mx][my];

// Adds val in position (x, y)
void update(LL x, LL y, LL val)
{
    LL y1;
    while (x <= mx)
    {
        y1 = y;
        while (y1 <= my)
        {
            BIT[x][y1] += val;
            y1 += (y1 & -y1);
        }
        x += (x & -x);
    }
}

// returns the sum of all numbers in rectangle with corner (1, 1) and (x, y).
LL query(LL x, LL y)
{
    LL y1, sum = 0;
    while(x)
    {
        y1 = y;
        while(y1)
        {
            sum += BIT[x][y1];
            y1 -= y1&(-y1);
        }
        x -= x&(-x);
    }
    return sum;
}
