/**
 This code convert a tree to a binary tree by adding some dummy nodes.
 Where distance between any two node will be same after conversion.

    1. Take input tree in g[] and gcost[].
    2. Set nnode = n; where n=number of node.
    3. call make_binary(1,1).
    4. for every node > n is a dummy node.

*/

#define mx 200005

vector<int>g[mx],btree[2*mx];
vector<ll>gcost[mx],btcost[2*mx];


int nnode;
int n,m;

void make_binary(int u, int p)
{
    int cur=u;
    for(int i=0; i<SZ(g[u]); i++)
    {
        int v=g[u][i];
        int c=gcost[u][i];
        if(v==p) continue;
        if(SZ(btree[cur])==1)
        {
            if(i+1==SZ(g[u]))
            {
                btree[cur].pb(v);
                btree[v].pb(cur);
                btcost[cur].pb(c);
                btcost[v].pb(c);
            }
            else
            {
                nnode++;
                btree[cur].pb(nnode);
                btcost[cur].pb(0);
                cur=nnode;
                btree[cur].pb(v);
                btcost[cur].pb(c);
            }
        }
        else
        {
            btree[cur].pb(v);
            btree[v].pb(cur);
            btcost[cur].pb(c);
            btcost[v].pb(c);
        }
        make_binary(v,u);
    }
}

