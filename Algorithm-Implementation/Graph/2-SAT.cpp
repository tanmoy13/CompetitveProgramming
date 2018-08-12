///Always remember to call allclear() function before execution

const int NODE = 205; /// Maximum no of node (0 based indexing)

vector<int>g[NODE];

int getNode(int x) ///Convert a choice to node
{
    int p=abs(x);
    p=(p-1)*2;
    if(x<0) p^=1;
    return p;
}

int getNodeVal(int x) ///Convert a node to choice
{
    int p=1;
    if(x&1)
    {
        p=-1;
        x-=1;
    }
    x/=2;
    x++;
    p*=x;
    return p;
}


///Always pass getNode() value to the folloing function
///For example if we want to mustTrue 5 then the call will be mustTrue(getNode(5))

void mustTrue (int a)   /// A is True
{
    g[a^1].pb(a);
}

void xorClause(int a, int b)   /// A ^ B clause
{
    //!a->b !b->a a->!b b->!a
    g[a^1].pb(b);
    g[a].pb(b^1);
    g[b^1].pb (a);
    g[b].pb (a^1);
}

void orClause (int a, int b)   /// A || B clause
{
    //!a->b !b->a
    g[a^1].pb ( b );
    g[b^1].pb ( a );
}

void andClause (int a, int b)   /// A ^ B clause
{
    mustTrue(a);
    mustTrue(b);
}

/// Out of all possible option, at most one is true
void atMostOneClause ( int a[], int n, int flag)
{
    if ( flag == 0 )   /// At most one can be false
    {
        for(int i = 0; i<n; i++)
        {
            a[i] = a[i] ^ 1;
        }
    }
    for(int i = 0; i<n; i++)
    {
        for(int j = i+1; j<n; j++)
        {
            orClause( a[i] ^ 1, a[j] ^ 1 ); /// !a || !b both being true not allowed
        }
    }
}


///SCC variables
int disc[NODE],low[NODE],Time, scc_count;
int component[NODE];
stack<int>scc;
bool vis[NODE];

///2-SAT variables
deque<int>sat;
int isSAT[NODE];

void allclear()
{
    for(int i=0; i<NODE; i++)
    {
        g[i].clear();
        disc[i]=0;
        low[i]=0;
        component[i]=0;
        isSAT[i]=-1;
    }

    scc_count=0;
    Time=0;
    while(!scc.empty())
        scc.pop();
    sat.clear();
}

void tarjan_SCC(int u)
{
    disc[u]=low[u]=++Time;
    scc.push(u);
//    vis[u]=1;
    for(int i=0; i<SZ(g[u]); i++)
    {
        int v=g[u][i];
        if(disc[v]==0)
            tarjan_SCC(v);
        if(disc[v]!=-1)
            low[u]=min(low[u],low[v]);
    }
    if(low[u]==disc[u])
    {
        scc_count++;
        int v;
        do
        {
            v=scc.top();
            scc.pop();
            sat.push_back(v);
            component[v]=scc_count;
            disc[v]=-1;
        }
        while(v!=u);
    }
}


bool checkSAT(int n)
{
    while(!sat.empty()) ///Assigning valid values to candidates
    {
        int x=sat.front();
        sat.pop_front();
        if(isSAT[x]==-1)
        {
            isSAT[x]=1;
            x=getNode(-getNodeVal(x)); ///Getting opposite value
            isSAT[x]=0;
        }
    }

    ///Checking whether satisfiability is possible or not
    bool check=1;
    for(int i=1; i<=n && check; i++)
    {
        check=(component[getNode(i)]!=component[getNode(-i)]);
    }
    return check;
}
