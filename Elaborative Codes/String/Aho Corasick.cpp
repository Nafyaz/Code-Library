#include <bits/stdc++.h>
using namespace std;

struct AC 
{
    LL id, P;
    const LL sz = 26;
    vector <vector <LL>> trie;
    vector <LL> link, out_link;
    vector <vector <LL>> out;
    
    AC(): id(0), P(0) 
    {
        node();
    }
    
    LL node() 
    {
        trie.emplace_back(sz, 0);
        link.emplace_back(0);
        out_link.emplace_back(0);
        out.emplace_back(0);
        return id++;
    }

    inline LL get (char c) 
    {
        return c - 'a';
    }

    LL add_pattern (string s) 
    {
        LL r = 0;
        for (auto c : s)
        {
            if (!trie[r][get(c)]) 
                trie[r][get(c)] = node();
            r = trie[r][get(c)];
        }
        out[r].push_back(P);
        return P++;
    }

    void bfs() 
    {
        queue <LL> q;
        q.push(0);
        while(!q.empty()) 
        {
            LL r = q.front(); 
            q.pop();
            for (LL c = 0; c < sz; c++) 
            {
                LL r2 = trie[r][c];
                if (!r2) 
                    trie[r][c] = trie[link[r]][c];
                else 
                {
                    link[r2] = r ? trie[link[r]][c] : 0;
                    out_link[r2] = out[link[r2]].empty() ? out_link[link[r2]] : link[r2];
                    q.push(r2);
                }
            }
        }
    }

    LL advance (LL r, char c) 
    {
        while (r && !trie[r][get(c)]) 
            r = link[r];
        r = trie[r][get(c)];
        return r;
    }

    void match (const string S) 
    {
        LL u = 0;
        for (auto c : S) 
        {
            u = advance(u, c);
            for (LL v = u; v; v = out_link[v]) 
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
    LL n; 
    cin >> n;
    while (n--) 
    {
        string s; 
        cin >> s;
        
        aho.add_pattern(s);
    }
    aho.bfs();
    string text; 
    cin >> text;
    aho.match(text);
    return 0;
}