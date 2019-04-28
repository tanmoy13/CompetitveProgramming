/// Heavy Light Decomposition
/// Given a tree and a value for each node handle 2 operations
/// Update the value of a node
/// Answer sum of node between u and v

/**
    How To Use?
    Call clear() to clear all
    Define root
    Call DFS(root, -1) to process arrays
    Call HLD(root, -1) to build HLD
    Call init(1, 1, Node) to build segment tree
    Call query_ans(u, v) to answer query
    Call update_val(u, val) to update
    Note: everything is 1 based
**/

#define root 1
#define mx 100005 ///Maximum number of nodes
//#define LN 20

int N, Node;
ll cost[mx];
vector<int> Graph[mx];
int treeAry[mx], subSize[mx], parent[mx];
int chainNo, chainInd[mx], chainHead[mx], posInTree[mx], depth[mx];
ll tree[mx * 4]; /// For segment tree

void clear()
{
    for (int i = 0; i <= N; i++)
    {
        treeAry[i] = 0;
        chainInd[i] = 0;
        chainHead[i] = -1;
        posInTree[i] = 0;
        subSize[i] = 0;
        cost[i] = 0;
        Graph[i].clear();
    }
//    ms(tree, 0);
    chainNo = 0;
    Node = 1;
}

/// Section: Segment Tree (Modify according to problem)
void init(int n, int b, int e)
{
    if (b == e)
    {
        tree[n] = treeAry[b];
        return;
    }

    int l = n*2,r = l+1, mid = (b+e)/2;

    init(l, b, mid);
    init(r, mid+1, e);
    tree[n] = tree[l] + tree[r];
}

void update(int n, int b, int e, int i, int j, ll value)
{
    if(b>j || e<i) return;
    if (b>=i && e<=j)
    {
        tree[n] = value;
        return;
    }

    int l = n*2,r = l+1, mid = (b+e)/2;

    update(l, b, mid, i, j, value);
    update(r, mid+1, e, i, j, value);
    tree[n] = tree[l] + tree[r];
}

ll query(int n, int b, int e, int i, int j)
{
    if(b>j || e<i) return 0;
    if(b>=i && e<=j)
    {
        return tree[n];
    }

    int l = n*2,r = l+1, mid = (b+e)/2;

    ll p = query(l, b, mid, i, j);
    ll q = query(r, mid+1, e, i, j);
    ll sum = p + q;
    return sum;
}
/// endSection

/// Section: HLD
ll queryUp(int u, int v) ///Here v is always parent or grand parent or self of u.
{
    if (u == v)
    {
        return query(1, 1, Node, posInTree[u], posInTree[u]);
    }
    int uchain, vchain = chainInd[v];
    ll ans = 0; /// Modify according to problem
    while (1)
    {
        uchain = chainInd[u];
        if (uchain == vchain)
        {
            int st = posInTree[v];
            int ed = posInTree[u];
            ll ret = query(1, 1, Node, st, ed);
            ans += ret; /// Modify according to problem
            break;
        }
        int st = posInTree[chainHead[uchain]];
        int ed = posInTree[u];
        ll ret = query(1, 1, Node, st, ed);
        ans += ret; /// Modify according to problem
        u = chainHead[uchain];
        u = parent[u];
    }
    return ans;
}

void HLD(int cur, int prev)
{
    if (chainHead[chainNo] == -1)
    {
        chainHead[chainNo] = cur;
    }
    chainInd[cur] = chainNo;
    posInTree[cur] = Node;
    treeAry[Node++] = cost[cur]; ///Change the cost according to the problem. Here treeAry contains the cost for segment tree.

    int mxChild = -1;
    for (int i = 0; i < (int) Graph[cur].size(); i++)
    {
        int v = Graph[cur][i];
        if (v != prev)
        {
            if (mxChild == -1 || subSize[mxChild] < subSize[v])
            {
                mxChild = v;
            }
        }
    }

    if (mxChild != -1)
    {
        HLD(mxChild, cur);
    }

    for (int i = 0; i < (int) Graph[cur].size(); i++)
    {
        int v = Graph[cur][i];
        if (v != prev)
        {
            if (v != mxChild)
            {
                chainNo++;
                HLD(v, cur);
            }
        }
    }
}

void DFS(int cur, int prev, int level = 0)
{
    subSize[cur] = 1;
    depth[cur] = level;
    parent[cur] = prev;
    for (int i = 0; i < (int) Graph[cur].size(); i++)
    {
        int v = Graph[cur][i];
        if (v != prev)
        {
            DFS(v, cur, level + 1);
            subSize[cur] += subSize[v];
        }
    }
}

/// endSection

/// Returns LCA of u and v
int LCA(int u, int v)
{
    while (1)
    {
        int pu = chainHead[chainInd[u]], pv = chainHead[chainInd[v]];
        if (pu == pv) return depth[u]<depth[v] ? u : v;
        else
        {
            if (depth[pu] < depth[pv])
            {
                v = parent[pv];
            }
            else
            {
                u = parent[pu];
            }
        }
    }
}

/// Returns the sum of the nodes between the path u to v
/// Modify according to problem
ll query_ans(int u, int v)
{
    int lca = LCA(u, v);
    ll ret1 = queryUp(u, lca);
    ll ret2 = queryUp(v, lca);
    ll merge = queryUp(lca, lca); /// Counted twice
    return (ret1 + ret2 - merge);
}

/// Update the value of u to val
void update_val(int u, ll val)
{
    update(1, 1, Node, posInTree[u], posInTree[u], val);
}
