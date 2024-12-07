// Tested on https://cses.fi/problemset/task/1700/

#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef long long LL;
typedef pair<LL, LL> pLL;
#define ff first
#define ss second
#define show(x) cout << #x << ": " << x << "; "
#define INF 1000000000000015
#define MOD 1000000007
#define MAXN 100005

LL key[MAXN], height[2][MAXN];
vector<LL> adj[2][MAXN];

void dfs(LL type, LL node, LL p)
{
    height[type][node] = 0;

    for(auto nxt : adj[type][node])
    {
        if(nxt == p)
            continue;
        dfs(type, nxt, node);
        height[type][node] = max(height[type][node], height[type][nxt]+1);
    }
}

LL getHash(LL type, LL node, LL p)
{
    LL ret = 1;
    for(auto nxt : adj[type][node])
    {
        if(nxt == p)
            continue;
        ret = (ret * (key[height[type][node]] + getHash(type, nxt, node))) % MOD;
    }

    return ret;
}

void solve(int caseno)
{
    LL n, i, a, b;

    cin >> n;

    for(i = 1; i <= n; i++)
    {
        adj[0][i].clear();
        adj[1][i].clear();
    }

    for(i = 1; i < n; i++)
    {
        cin >> a >> b;
        adj[0][a].push_back(b);
        adj[0][b].push_back(a);
    }

    for(i = 1; i < n; i++)
    {
        cin >> a >> b;
        adj[1][a].push_back(b);
        adj[1][b].push_back(a);
    }

    dfs(0, 1, 1);
    dfs(1, 1, 1);

    cout << (getHash(0, 1, 1) == getHash(1, 1, 1)? "YES\n" : "NO\n");
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1, caseno = 0, i;

    key[0] = 1;
    for(i = 1; i < MAXN; i++)
        key[i] = (key[i-1] * 31) % MOD;

    cin >> T;

    while(T--)
    {
        solve(++caseno);
    }
}