#include <bits/stdc++.h>

using namespace std;

struct AC 
{
    int id, P;
    const int sz = 26;
    vector <vector <int>> trie;
    vector <int> link, out_link;
    vector <vector <int>> out;
    
    AC(): id(0), P(0) 
    {
        node();
    }
    
    int node() 
    {
        trie.emplace_back(sz, 0);
        link.emplace_back(0);
        out_link.emplace_back(0);
        out.emplace_back(0);
        return id++;
    }

    inline int get (char c) 
    {
        return c - 'a';
    }

    int add_pattern (const string T) 
    {
        int r = 0;
        for (auto c : T) 
        {
            if (!trie[r][get(c)]) 
                trie[r][get(c)] = node();
            r = trie[r][get(c)];
        }
        out[r].push_back(P);
        return P++;
    }

    void compute() 
    {
        queue <int> q;
        q.push(0);
        while(!q.empty()) 
        {
            int u = q.front(); 
            q.pop();
            for (int c = 0; c < sz; c++) 
            {
                int v = trie[u][c];
                if (!v) 
                    trie[u][c] = trie[link[u]][c];
                else 
                {
                    link[v] = u ? trie[link[u]][c] : 0;
                    out_link[v] = out[link[v]].empty() ? out_link[link[v]] : link[v];
                    q.push(v);
                }
            }
        }
    }

    int advance (int r, char c) 
    {
        while (r && !trie[r][get(c)]) 
            r = link[r];
        r = trie[r][get(c)];
        return r;
    }

    void match (const string S) 
    {
        int u = 0;
        for (auto c : S) 
        {
            u = advance(u, c);
            for (int v = u; v; v = out_link[v]) 
            {
                for (auto p : out[v]) 
                    cout << "match " << p << endl;
            }
        }
    }
};

int main() 
{
    AC aho; 
    int n; 
    cin >> n;
    while (n--) 
    {
        string s; 
        cin >> s;
        
        aho.add_pattern(s);
    }
    aho.compute();
    string text; 
    cin >> text;
    aho.match(text);
    return 0;
}