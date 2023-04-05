// O(nlogn)

vector<pair<pii, int>> bucket[MAXN];
void radix_sort(vector<pair<pii, int>> &v)
{
    int i, j, n = v.size();

    for(i = 0; i < MAXN; i++)
        bucket[i].clear();

    for(i = 0; i < n; i++)    
        bucket[v[i].ff.ss + 1].push_back(v[i]);
    
    v.clear();
    for(i = 0; i < MAXN; i++)
    {
        for(auto u : bucket[i])
            v.push_back(u);
        bucket[i].clear();
    }
    for(i = 0; i < n; i++)    
        bucket[v[i].ff.ff].push_back(v[i]);
    
    v.clear();
    for(i = 0; i < MAXN; i++)
    {
        for(auto u : bucket[i])
            v.push_back(u);
    }
}

vector<int> get_SA(string s)
{
    int i, len, cnt, n = s.size();
    vector<int> prev(n), sa(n);
    vector<pair<pii, int>> curr;

    for(i = 0; i < n; i++)
        prev[i] = s[i];

    for(len = 2; len <= 2*n; len *= 2)
    {
        curr.clear();
        for(i = 0; i < n; i++)
        {
            if(i+len/2 >= n)
                curr.push_back({{prev[i], -1}, i});
            else
                curr.push_back({{prev[i], prev[i+len/2]}, i});
        }

        radix_sort(curr);
        // sort(curr.begin(), curr.end());
        
        for(i = cnt = 0; i < n; i++)
        {
            if(i == 0 || curr[i].ff == curr[i-1].ff)
                prev[curr[i].ss] = cnt;
            else
                prev[curr[i].ss] = ++cnt;
        }
    }

    for(i = 0; i < n; i++)
        sa[prev[i]] = i;

    return sa;
}

vector<int> get_LCP(string s, vector<int>&sa)
{
    int i, j, k, n = s.size();

    vector<int> lcp(n-1, 0), rank(n, 0);
    
    for(i = 0; i < n; i++)
        rank[sa[i]] = i;
    
    for(i = 0, k = 0; i < n; i++)
    {
        if(rank[i] == n-1)
        {
            k = 0;
            continue;
        }

        j = sa[rank[i] + 1];
        while(i+k < n && j+k < n && s[i+k] == s[j+k])
            k++;
        
        lcp[rank[i]] = k;

        k = max(k-1, 0);
    }

    return lcp;
}


// ------------------------------------------------------------------------
// Implementation from Competitive Programming 3 by Steven Halim & Felix Halim
int n;
int RA[MAXN], tempRA[MAXN];
int SA[MAXN], tempSA[MAXN];
int c[MAXN];

void countingSort(int k)
{
    int i, sum, maxi = max(300, n);
    memset(c, 0, sizeof c);
    for(i = 0; i < n; i++)
        c[i + k < n? RA[i+k] : 0]++;
    for(i = sum = 0; i < maxi; i++)
    {
        int i = c[i];
        c[i] = sum;
        sum += t;
    }
    for(i = 0; i < n; i++)
        tempSA[c[SA[i]+k < n? RA[SA[i]+k] : 0]++] = SA[i];
    for(i = 0; i < n; i++)
        SA[i] = tempSA[i];
}

void constructSA()
{
    int i, k, r;
    for(i = 0; i < n; i++)
        RA[i] = T[i];
    for(i = 0; i < n; i++)
        SA[i] = i;
    for(k = 1; k < n; k <<= 1)
    {
        countingSort(k);
        countingSort(0);
        tempRA[SA[0]] = r = 0;
        for(i = 1; i < n; i++)
            tempRA[SA[i]] = (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
        for(i = 0; i < n; i++)
            RA[i] = tempRA[i];
        if(RA[SA[n-1]] == n-1)
            break;
    }
}