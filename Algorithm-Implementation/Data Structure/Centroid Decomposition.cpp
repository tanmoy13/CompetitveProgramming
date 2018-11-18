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
    findCentroid(heavy_child,u,total_nodes);
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


///The below segment depends on the problem

int ans[maxnode];

void update(int u)
{
    ans[u]=0;
    int x=centroid_par[u];
    while(x!=-1)
    {
        ans[x]=min(ans[x],ans[u]+mp[x][u]);
        x=centroid_par[x];
    }
}

int query(int u)
{
    int ret=ans[u];
    int x=centroid_par[u];
    while(x!=-1)
    {
        ret=min(ret,ans[x]+mp[x][u]);
        x=centroid_par[x];
    }
    return ret;
}

int main()
{
//#ifndef ONLINE_JUDGE
//    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif

    int n,m;
    sff(n,m);

    for(int i=1; i<n; i++)
    {
        int a,b;
        sff(a,b);
        tree[a].pb(b);
        tree[b].pb(a);
    }

    int root=decomposeTree(1);
    centroid_par[root]=-1;

    for(int i=0; i<n+4; i++) ans[i]=1e7;

    update(1);

    while(m--)
    {
        int a,b;
        sff(a,b);
        if(a==1)
            update(b);
        else
            printf("%d\n",query(b));
    }

    return 0;
}




