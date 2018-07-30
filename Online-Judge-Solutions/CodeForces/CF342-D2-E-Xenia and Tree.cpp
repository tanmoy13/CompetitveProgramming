#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

#define pii              pair <int,int>
#define pll              pair <long long,long long>
#define sc               scanf
#define pf               printf
#define Pi               2*acos(0.0)
#define ms(a,b)          memset(a, b, sizeof(a))
#define pb(a)            push_back(a)
#define MP               make_pair
#define db               double
#define ll               long long
#define EPS              10E-10
#define ff               first
#define ss               second
#define sqr(x)           (x)*(x)
#define VI               vector <int>
#define MOD              1000000007
#define fast_cin         ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define SZ(a)            (int)a.size()
#define sf(a)            scanf("%d",&a)
#define sfl(a)           scanf("%lld",&a)
#define sff(a,b)         scanf("%d %d",&a,&b)
#define sffl(a,b)        scanf("%lld %lld",&a,&b)
#define sfff(a,b,c)      scanf("%d %d %d",&a,&b,&c)
#define sfffl(a,b,c)     scanf("%lld %lld %lld",&a,&b,&c)
#define stlloop(v)       for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define UNIQUE(v)        (v).erase(unique((v).begin(),(v).end()),(v).end())
#define POPCOUNT         __builtin_popcountll
#define RIGHTMOST        __builtin_ctzll
#define LEFTMOST(x)      (63-__builtin_clzll((x)))
#define NUMDIGIT(x,y)    (((vlong)(log10((x))/log10((y))))+1)
#define NORM(x)          if(x>=mod) x-=mod;if(x<0) x+=mod;
#define ODD(x)           (((x)&1)==0?(0):(1))
#define loop(i,n)        for(int i=0;i<n;i++)
#define loop1(i,n)       for(int i=1;i<=n;i++)
#define REP(i,a,b)       for(int i=a;i<b;i++)
#define RREP(i,a,b)      for(int i=a;i>=b;i--)
#define TEST_CASE(t)     for(int z=1;z<=t;z++)
#define PRINT_CASE       printf("Case %d: ",z)
#define LINE_PRINT_CASE  printf("Case %d:\n",z)
#define CASE_PRINT       cout<<"Case "<<z<<": "
#define all(a)           a.begin(),a.end()
#define intlim           2147483648
#define infinity         (1<<28)
#define ull              unsigned long long
#define gcd(a, b)        __gcd(a, b)
#define lcm(a, b)        ((a)*((b)/gcd(a,b)))
#define D(x)        	 cerr << __LINE__ << ": " << #x << " = " << (x) << '\n'
#define DD(x,y)          cerr << __LINE__ << ": " << #x << " = " << x << "   " << #y << " = " << y << '\n'
#define DDD(x,y,z)       cerr << __LINE__ << ": " << #x << " = " << x << "   " << #y << " = " << y << "   " << #z << " = " << z << '\n'
#define DBG              cerr << __LINE__ << ": Hi" << '\n'

using namespace std;

//using namespace __gnu_pbds;
//typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;


/*----------------------Graph Moves----------------*/
//const int fx[]={+1,-1,+0,+0};
//const int fy[]={+0,+0,+1,-1};
//const int fx[]={+0,+0,+1,-1,-1,+1,-1,+1};   // Kings Move
//const int fy[]={-1,+1,+0,+0,+1,+1,-1,-1};  // Kings Move
//const int fx[]={-2, -2, -1, -1,  1,  1,  2,  2};  // Knights Move
//const int fy[]={-1,  1, -2,  2, -2,  2, -1,  1}; // Knights Move
/*------------------------------------------------*/

/*-----------------------Bitmask------------------*/
//int Set(int N,int pos){return N=N | (1<<pos);}
//int reset(int N,int pos){return N= N & ~(1<<pos);}
//bool check(int N,int pos){return (bool)(N & (1<<pos));}
/*------------------------------------------------*/

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



