#define mx 1002

map<string,int>mp;
int h[mx],low[mx],dfsnum,ans;
bool vis[mx];
vector<int>g[mx],scc;

void allclear()
{
    mp.clear();
    for(int i=0;i<mx;i++)
    {
        h[i]=low[i]=vis[i]=0;
        g[i].clear();
    }
    scc.clear();
    dfsnum=0;
    ans=0;
}

void Tarjan_SCC(int u)
{
    h[u]=low[u]=++dfsnum;
    vis[u]=1;
    scc.pb(u);
    for(int i=0;i<SZ(g[u]);i++)
    {
        int v=g[u][i];
        if(h[v]==0)
            Tarjan_SCC(v);
        if(vis[v])
            low[u]=min(low[u],low[v]);
    }
    if(low[u]==h[u])
    {
        ans++;
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
