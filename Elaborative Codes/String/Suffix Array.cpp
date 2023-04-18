// Solves Jarvis And LCP https://www.codechef.com/problems/INSQ16F

#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef long long LL;
typedef pair<LL, LL> pLL;
#define ff first
#define ss second
#define show(x) cout << #x << ": " << x << "; "
#define MOD 1000000007
#define MAXN 2000006

string original[MAXN];
int Pow[25], Log[MAXN], rmq[MAXN][25];
int pos[MAXN];
vector<pair<pii, int>> bucket[MAXN];

void radix_sort(vector<pair<pii, int>> &v)
{
    int i, n = v.size();

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

vector<int> get_SA(string &s)
{
    int i, len, cnt, n = s.size();
    vector<int> prev(n), ret(n);
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
        ret[prev[i]] = i;

    return ret;
}

vector<int> get_LCP(string &s, vector<int>&sa)
{
    int i, j, k, n = s.size();

    vector<int> lcp(n-1), rank(n);
    
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

void rmq_init()
{
    int i;
    
    Pow[0] = 1;
    for(i = 1; i < 25; i++)
        Pow[i] = Pow[i-1]*2;
    
    Log[1] = 0;
    for(i = 2; i < MAXN; i++)
        Log[i] = Log[i/2] + 1;
}

int rmq_query(int bg, int ed)
{
    int k = Log[ed-bg+1];
    return min(rmq[bg][k], rmq[ed - Pow[k] + 1][k]);
}

void build_RMQ(vector<int> &lcp)
{
    int i, j, n = lcp.size();

    for(i = 0; i < n; i++)
        rmq[i][0] = lcp[i];

    for(j = 1; j < 25; j++)
    {
        for(i = 0; i + (1LL << j) - 1 < n; i++)
            rmq[i][j] = min(rmq[i][j-1], rmq[i + Pow[j-1]][j-1]);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, i, j, q, l, r, mn, low, high, mid, left, right;
    string total;

    cin >> n;

    total = "";
    for(i = 0; i < n; i++)
    {
        cin >> original[i];
        pos[i] = total.size() + 1;

        total.push_back('#');
        for(j = 0; j < original[i].size(); j++)
            total.push_back(original[i][j]);
    }
    // total.push_back('#');

    vector<int> sa = get_SA(total);
    vector<int> rank(total.size());
    for(i = 0; i < int(total.size()); i++)
        rank[sa[i]] = i;

    vector<int> lcp = get_LCP(total, sa);

    // cout << total << "\n";
    // cout << "SA: ";
    // for(i = 0; i < total.size(); i++)
    //     cout << setw(3) << sa[i];
    // cout << "\n";
    // cout << "Rank: ";
    // for(i = 0; i < total.size(); i++)
    //     cout << setw(3) << rank[i];
    // cout << "\n";
    // cout << "LCP: ";
    // for(i = 0; i < int(lcp.size()); i++)
    //     cout << setw(3) << lcp[i];
    // cout << "\n";

    rmq_init();
    build_RMQ(lcp);

    // for(i = 0; i < rmq.size(); i++)
    // {
    //     for(int j = 0; j < 25; j++)
    //         cout << rmq[i][j] << " ";
    //     cout << "\n";
    // }

    cin >> q;
    while(q--)
    {
        cin >> l >> r;
        
        l--;    
        r--;

        if(rank[pos[l]] > rank[pos[r]])
            swap(l, r);

        if(l == r)
            mn = original[l].size();
        else
            mn = rmq_query(rank[pos[l]], rank[pos[r]]-1);

        if(mn == 0)
        {
            cout << "0\n";
            continue;
        }

        mn = min(mn, int(original[l].size()));
        mn = min(mn, int(original[r].size()));

        l = pos[l];
        r = pos[r];

        // show(l);
        // show(r);
        // show(mn);
        // cout << "\n";

        low = 0;
        high = rank[l]-1;
        left = rank[l];
        while(low <= high)
        {
            mid = (low + high)/2;

            if(rmq_query(mid, rank[l]-1) >= mn)
            {
                left = mid;
                high = mid - 1;
            }
            else
                low = mid + 1;
        }

        low = rank[r];
        high = total.size()-1;
        right = rank[r];
        while(low <= high)
        {
            mid = (low + high)/2;

            if(rmq_query(rank[r], mid) >= mn)
            {
                right = mid + 1;
                low = mid + 1;
            }
            else
                high = mid - 1;
        }

        // show(left);
        // show(right);
        // cout << "\n";

        cout << right - left + 1 << "\n";
    }
}

/*

idx 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19
str #  a  b  a  b  a  #  a  b  a  #  a  b  c  d  #  c  b  a  b
ran 1  9 15  7 12  4  0  8 13  5  2 10 16 18 19  3 17 14  6 11

mrk  idx  lcp  sa 
     0    4    6    #  a  b  a  #  a  b  c  d  #  c  b  a  b
     1    3    0    #  a  b  a  b  a  #  a  b  a  #  a  b  c  d  #  c  b  a  b
     2    1    10   #  a  b  c  d  #  c  b  a  b
     3    0    15   #  c  b  a  b
     4    4    5    a  #  a  b  a  #  a  b  c  d  #  c  b  a  b
     5    1    9    a  #  a  b  c  d  #  c  b  a  b
     6    2    18   a  b
     7    6    3    a  b  a  #  a  b  a  #  a  b  c  d  #  c  b  a  b
*    8    3    7    a  b  a  #  a  b  c  d  #  c  b  a  b
*    9    2    1    a  b  a  b  a  #  a  b  a  #  a  b  c  d  #  c  b  a  b
     10   0    11   a  b  c  d  #  c  b  a  b
     11   1    19   b
     12   5    4    b  a  #  a  b  a  #  a  b  c  d  #  c  b  a  b
     13   2    8    b  a  #  a  b  c  d  #  c  b  a  b
     14   3    17   b  a  b
     15   1    2    b  a  b  a  #  a  b  a  #  a  b  c  d  #  c  b  a  b
     16   0    12   b  c  d  #  c  b  a  b
     17   1    16   c  b  a  b
     18   0    13   c  d  #  c  b  a  b
     19   -    14   d  #  c  b  a  b

*/