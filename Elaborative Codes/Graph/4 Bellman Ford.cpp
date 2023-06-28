struct edge
{
    int a, b, cost;
};

int n, m, v;
vector<edge> e;

void solve()
{
    vector<int> dist (n, INF);
    vector<int> parent (n, -1);
    dist[v] = 0;
    bool flag = 1;
    while(flag)
    {
        flag = 0;

        for (int j = 0; j < m; j++)
        {
            if (dist[e[j].a] < INF)
            {
                if (dist[e[j].b] > dist[e[j].a] + e[j].cost)
                {
                    dist[e[j].b] = dist[e[j].a] + e[j].cost;
                    parent[e[j].b] = e[j].a;
                    flag = 1;
                }
            }
        }
    }

    if (dist[t] == INF)
        cout << "No path from " << v << " to " << t << ".";
    else
    {
        vector<int> path;
        for (int cur = t; cur != -1; cur = parent[cur])
            path.push_back (cur);
        reverse (path.begin(), path.end());

        cout << "Path from " << v << " to " << t << ": ";
        for (size_t i = 0; i < path.size(); i++)
            cout << path[i] << ' ';
    }
}
