
/// Min Cost Max Flow Zobayer
/// Note: Doesn't work for negative cycle
/// Initialize using clear()
/// Add the edges using addEdge()
/// Call findMCMF() to get both min cost and max flow.

const int INF = 1e8;
const int MAXN = 105, MAXE = 10005;
/// Maximum no of nodes and edges.

int fin[MAXN], pro[MAXN], dist[MAXN];
int cap[MAXE], cost[MAXE], nxt[MAXE], to[MAXE], from[MAXE];

struct MCMF
{
    int src, snk, nNode, nEdge;

    /// Parameters: (source, sink, no of nodes)
    void clear(int _src, int _snk, int nodes)
    {
        nNode = nodes, nEdge = 0;
        src = _src, snk = _snk;
        memset(fin, -1, sizeof fin);
    }

    /// Parameters: (from, to, capacity, cost per flow)
    void addEdge(int u, int v, int _cap, int _cost)
    {
        from[nEdge] = u, to[nEdge] = v, cap[nEdge] = _cap;
        cost[nEdge] = _cost, nxt[nEdge] = fin[u], fin[u] = nEdge++;
        ///2nd capacity zero for directed edge
        from[nEdge] = v, to[nEdge] = u, cap[nEdge] = 0;
        cost[nEdge] = -_cost, nxt[nEdge] = fin[v], fin[v] = nEdge++;
    }

    bool bellmanford()
    {
        bool flag = true;
        for(int i = 0; i<nNode; i++)
        {
            dist[i] = INF;
            pro[i] = -1;
        }
        dist[src] = 0;
        for (int it = 1; it < nNode && flag; it++)
        {
            flag = false;
            for (int u = 0; u < nNode; u++)
            {
                for (int i = fin[u]; i >= 0; i = nxt[i])
                {
                    int v = to[i];
                    if (cap[i] && dist[v] > dist[u] + cost[i])
                    {
                        dist[v] = dist[u] + cost[i];
                        pro[v] = i;
                        flag = true;
                    }
                }
            }
        }
        return (dist[snk] < INF);
    }

    /// Returns pair {flow, cost}
    pii findMCMF()
    {
        int fflow = 0, fcost = 0;
        while (bellmanford())
        {
            int fw = INF;
            for (int u = pro[snk]; u >= 0; u = pro[from[u]])
            {
                fw = min(fw, cap[u]);
            }
            for (int u = pro[snk]; u >= 0; u = pro[from[u]])
            {
                cap[u] -= fw;
                cap[u ^ 1] += fw;
                fcost += fw * cost[u];
            }
            fflow += fw;
        }
        return MP(fflow, fcost);
    }
} mcmf;
