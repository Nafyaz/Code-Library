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


// ------------------------------------------------------------------------
// Jubayer Nirjhor, O(n), https://github.com/MathIsLife/PrewrittenCodes/blob/master/SuffixArray.cpp

#include <bits/stdc++.h>

using namespace std;

/*
  O(|S| + |alphabet|) Suffix Array
  LIM := max{s[i]} + 2
*/

void inducedSort (const vector <int> &vec, int val_range, vector <int> &SA, const vector <int> &sl, const vector <int> &lms_idx) {
  vector <int> l(val_range, 0), r(val_range, 0);
  for (int c : vec) {
    ++r[c]; if (c + 1 < val_range) ++l[c + 1];
  }
  partial_sum(l.begin(), l.end(), l.begin());
  partial_sum(r.begin(), r.end(), r.begin());
  fill(SA.begin(), SA.end(), -1);
  for (int i = lms_idx.size() - 1; i >= 0; --i) SA[--r[vec[lms_idx[i]]]] = lms_idx[i];
  for (int i : SA) if (i > 0 and sl[i - 1]) SA[l[vec[i - 1]]++] = i - 1;
  fill(r.begin(), r.end(), 0);
  for (int c : vec) ++r[c];
  partial_sum(r.begin(), r.end(), r.begin());
  for (int k = SA.size() - 1, i = SA[k]; k; --k, i = SA[k]) {
    if (i and !sl[i - 1]) SA[--r[vec[i - 1]]] = i - 1;
  }
}

vector <int> suffixArray (const vector <int> &vec, int val_range) {
  const int n = vec.size();
  vector <int> sl(n), SA(n), lms_idx;
  for (int i = n - 2; i >= 0; --i) {
    sl[i] = vec[i] > vec[i + 1] or (vec[i] == vec[i + 1] and sl[i + 1]);
    if (sl[i] and !sl[i + 1]) lms_idx.emplace_back(i + 1);
  }
  reverse(lms_idx.begin(), lms_idx.end());
  inducedSort(vec, val_range, SA, sl, lms_idx);
  vector <int> new_lms_idx(lms_idx.size()), lms_vec(lms_idx.size());
  for (int i = 0, k = 0; i < n; ++i) {
    if (SA[i] > 0 and !sl[SA[i]] and sl[SA[i] - 1]) new_lms_idx[k++] = SA[i];
  }
  int cur = 0; SA[n - 1] = 0;
  for (int k = 1; k < new_lms_idx.size(); ++k) {
    int i = new_lms_idx[k - 1], j = new_lms_idx[k];
    if (vec[i] ^ vec[j]) {
      SA[j] = ++cur; continue;
    }
    bool flag = 0;
    for (int a = i + 1, b = j + 1; ; ++a, ++b) {
      if (vec[a] ^ vec[b]) {
        flag = 1; break;
      }
      if ((!sl[a] and sl[a - 1]) or (!sl[b] and sl[b - 1])) {
        flag = !(!sl[a] and sl[a - 1] and !sl[b] and sl[b - 1]); break;
      }
    }
    SA[j] = flag ? ++cur : cur;
  }
  for (int i = 0; i < lms_idx.size(); ++i) lms_vec[i] = SA[lms_idx[i]];
  if (cur + 1 < lms_idx.size()) {
    auto lms_SA = suffixArray(lms_vec, cur + 1);
    for (int i = 0; i < lms_idx.size(); ++i) new_lms_idx[i] = lms_idx[lms_SA[i]];
  }
  inducedSort(vec, val_range, SA, sl, new_lms_idx); return SA;
}

vector <int> getSuffixArray (const string &s, const int LIM = 128) {
  vector <int> vec(s.size() + 1);
  copy(begin(s), end(s), begin(vec)); vec.back() = '$';
  auto ret = suffixArray(vec, LIM);
  ret.erase(ret.begin()); return ret;
}

// build RMQ on it to get LCP of any two suffix
vector <int> getLCParray (const string &s, const vector <int> &SA) {
  int n = s.size(), k = 0;
  vector <int> lcp(n), rank(n);
  for (int i = 0; i < n; ++i) rank[SA[i]] = i;
  for (int i = 0; i < n; ++i, k ? --k : 0) {
    if (rank[i] == n - 1) {
      k = 0; continue;
    }
    int j = SA[rank[i] + 1];
    while (i + k < n and j + k < n and s[i + k] == s[j + k]) ++k;
    lcp[rank[i]] = k;
  }
  lcp[n - 1] = 0; return lcp;
}

int main() {
  string s; cin >> s;
  for (const int i : getSuffixArray(s)) printf("%d ", i);
  puts("");
  return 0;
}


// ------------------------------------------------------------------------
