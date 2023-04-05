// Finds all palindrome in O(n)

vector<LL> manacher(string s)
{
    LL i, l, r, k, n = s.size();
    vector<LL> pal(n);

    for(i = 0, l = 0, r = -1; i < n; i++)
    {
        if(i > r)
            k = 1;
        else
            k = min(pal[l + r - i], r - i + 1);

        while(i-k >= 0 && i+k < n && s[i-k] == s[i+k])
            k++;

        pal[i] = k;
        k--;

        if(i+k > r)
        {
            l = i-k;
            r = i+k;
        }
    }

    return pal;
}

int main()
{
    LL i, ans = 0;
    string s, stemp;

    cin >> n >> stemp;

    s = '#';
    for(i = 0; i < stemp.size(); i++)
    {
        s.push_back(stemp[i]);
        s.push_back('#');
    }

    vector<LL> pal = manacher(s);

    for(i = 0; i < n; i++)
        cout << pal[i] << " ";
}
