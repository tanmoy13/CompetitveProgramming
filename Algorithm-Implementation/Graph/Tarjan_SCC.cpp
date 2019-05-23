#define mx 100005

int disc[mx],low[mx],dfsnum,scc_cnt;
bool vis[mx];
vector<int>g[mx],scc;

void allclear()
{
    for(int i=0;i<mx;i++)
    {
        disc[i]=low[i]=vis[i]=0;
        g[i].clear();
    }
    scc.clear();
    dfsnum=0;
    scc_cnt=0;
}

void Tarjan_SCC(int u)
{
    disc[u]=low[u]=++dfsnum;
    vis[u]=1;
    scc.pb(u);
    for(int i=0;i<SZ(g[u]);i++)
    {
        int v=g[u][i];
        if(disc[v]==0)
            Tarjan_SCC(v);
        if(vis[v])
            low[u]=min(low[u],low[v]);
    }
    if(low[u]==disc[u])
    {
        scc_cnt++;
        while(1)
        {
            int v=scc.back();
            scc.pop_back();
            vis[v]=0;
            if(v==u)
                break;
        }
    }
}

