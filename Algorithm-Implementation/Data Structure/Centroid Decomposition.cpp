/**
    1. Input the tree.
    2. call int root=decomposeTree(1);
    3. Set centroid_par[root]=-1;
**/

const int maxnode = 100005;

vector<int>tree[maxnode],centroid_tree[maxnode];
bool centroid_marked[maxnode];
int child_count[maxnode];
int centroid_par[maxnode];

///This map store distance from a centroid to centroid subtree nodes in original tree
unordered_map<int,int>mp[maxnode];

///Calculate distance from all centroid
void calculate_dis(int u, int par, int dis, int src)
{
    mp[src][u]=dis;
    for(int i=0; i<SZ(tree[u]); i++)
    {
        int v=tree[u][i];
        if(v==par || centroid_marked[v]) continue;
        calculate_dis(v,u,dis+1,src);
    }
}


///calculate number of child in a subtree
int dfs(int u, int par)
{
    child_count[u]=1;
    for(int i=0; i<SZ(tree[u]); i++)
    {
        int v=tree[u][i];
        if(v==par || centroid_marked[v]) continue;
        child_count[u]+=dfs(v,u);
    }
    return child_count[u];
}


///This function get input a tree or subtree of current tree and find it's centroid
int findCentroid(int u, int par, int total_nodes)
{
    bool isCentroid=true;
    int heavy_child=0;  ///heaviest child of current node
    int heavy_cnt=0;    ///number of nodes  in subtree of heavy child
    for(int i=0; i<SZ(tree[u]); i++)
    {
        int v=tree[u][i];
        if(v==par || centroid_marked[v]) continue;

        if(child_count[v]>(total_nodes/2))
            isCentroid=false;

        if(child_count[v]>heavy_cnt)
        {
            heavy_cnt=child_count[v];
            heavy_child=v;
        }

    }

    if(isCentroid && total_nodes-child_count[u]<=(total_nodes/2))
        return u;
    return findCentroid(heavy_child,u,total_nodes);
}

///calculate single centroid and mark it
int getCentroid(int u)
{
    int total=dfs(u,u);
    int centroid=findCentroid(u,u,total);
    calculate_dis(centroid,centroid,0,centroid);
    centroid_marked[centroid]=1;
    return centroid;
}

///Form centroid tree from centroids
int decomposeTree(int u)
{
    int cur_centroid=getCentroid(u);
    D(cur_centroid);
    for(int i=0; i<SZ(tree[cur_centroid]); i++)
    {
        int v=tree[cur_centroid][i];
        if(centroid_marked[v]) continue;
        int sub_centorid=decomposeTree(v);
        centroid_tree[cur_centroid].pb(sub_centorid);
        centroid_tree[sub_centorid].pb(cur_centroid);

        centroid_par[sub_centorid]=cur_centroid; ///marking parent of a centroid in centroid tree
    }
    return cur_centroid;
}
