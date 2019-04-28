/**
    Author: Tanmoy Datta

    Solution Idea:
    ~~~~~~~~~~~~~~
        - Make a DAG from shortest paths using a dijkastra.
        - Build Dominator tree from the DAG.
        - Count the child of every node in dominator tree.
        - Now the answer for this problem is LCA and child count of dominator tree.
*/

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

#define mx 100005

vector<int>g[mx],cost[mx],par[mx],dag[mx],topsort,dominator_tree[mx];

int dis[mx];
bool vis[mx];
int parent[mx],level[mx];
int dp[mx][18];
int child[mx];
///This dijkastra convert the undirected graph to a DAG with shortest path

void dijkastra(int src)
{
    priority_queue<pii>Q;
    dis[src]=0;
    Q.push(pii(0,src));

    while(!Q.empty())
    {
        pii u=Q.top();
        Q.pop();
        u.ff=-u.ff;
        for(int i=0; i<SZ(g[u.ss]); i++)
        {
            int v=g[u.ss][i];
            if(dis[v]>cost[u.ss][i]+dis[u.ss])
            {
                dis[v]=cost[u.ss][i]+dis[u.ss];
                par[v].clear();
                par[v].pb(u.ss);
                Q.push(pii(-dis[v],v));
            }
            else if(dis[v]==cost[u.ss][i]+dis[u.ss]) ///Adding extra parent if there is multiple shortest path
            {
                par[v].pb(u.ss);
            }
        }
    }
}

void build_dag(int n)
{
    ///Making the DAG from dijkastra

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<SZ(par[i]); j++)
        {
            int u=par[i][j];
            dag[u].pb(i);
        }
    }
}

///determine the topsort
void dfs(int u)
{
    vis[u]=1;
    for(int i=0; i<SZ(dag[u]); i++)
    {
        int v=dag[u][i];
        if(vis[v]==0)
            dfs(v);
    }
    topsort.pb(u);
}



///LCA part

int call(int u, int p)
{
    if(p==0)
    {
        return parent[u];
    }
    int &ret=dp[u][p];
    if(ret!=-1) return ret;
    ret=call(u,p-1);
    ret=call(ret,p-1);
    return ret;
}

int find_lca(int u, int v)
{
    if(level[u]<level[v])
        swap(u,v);

    for(int i=17;i>=0;i--)
    {
        int x=call(u,i);
        if(level[x]>=level[v])
            u=x;
    }

    if(u==v) return v;

    for(int i=17;i>=0;i--)
    {
        int x=call(u,i);
        int y=call(v,i);
        if(x!=y)
        {
            u=x;
            v=y;
        }
    }

    return parent[u];
}

void build_dominator_tree(int root)
{
    parent[root]=root;
    level[root]=1;

    for(int i=1;i<SZ(topsort);i++)
    {
        int u=topsort[i];
        int lca=par[u][0];
        for(int j=1;j<SZ(par[u]);j++)
        {
            int v=par[u][j];
            lca=find_lca(lca,v);
        }
        dominator_tree[lca].pb(u);
        level[u]=level[lca]+1;
        parent[u]=lca;
    }
}


void child_count(int u)
{
    child[u]=1;
    for(int i=0;i<SZ(dominator_tree[u]);i++)
    {
        int v=dominator_tree[u][i];
        child_count(v);
        child[u]+=child[v];
    }
}

void allclear(int n)
{
    for(int i=0; i<=n; i++)
    {
        g[i].clear();
        cost[i].clear();
        par[i].clear();
        dis[i]=(1<<29);
        dag[i].clear();
        dominator_tree[i].clear();
        vis[i]=0;
        ms(dp[i],-1);

    }
    topsort.clear();
}

int main()
{
//#ifndef ONLINE_JUDGE
//    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif

    int t;
    sf(t);
    TEST_CASE(t)
    {
        int n,m;
        sff(n,m);
        allclear(n);
        for(int i=0; i<m; i++)
        {
            int a,b,c;
            sfff(a,b,c);
            g[a].pb(b);
            g[b].pb(a);
            cost[a].pb(c);
            cost[b].pb(c);
        }

        dijkastra(0);

//        for(int i=0;i<n;i++)
//        {
//            D(i);
//            for(int j=0;j<SZ(par[i]);j++)
//                cout<<par[i][j]<<" ";
//            cout<<endl;
//        }

        build_dag(n);

        dfs(0); ///topsorting

        reverse(all(topsort));

//        for(int i=0;i<SZ(topsort);i++)
//            cout<<topsort[i]<<" ";
//        cout<<endl;


        build_dominator_tree(0);
        child_count(0);
//        for(int i=0;i<n;i++)
//        {
//            D(i);
//            for(int j=0;j<SZ(dominator_tree[i]);j++)
//                cout<<dominator_tree[i][j]<<" ";
//            cout<<endl;
//        }

        LINE_PRINT_CASE;
        int q;
        sf(q);
        while(q--)
        {
            int x,y;
            sf(x);
            int ans=0;
            int lca=-1;
            for(int i=0;i<x;i++)
            {
                sf(y);
                if(dis[y]>=(1<<28))
                {
                    ans++;
                }
                else
                {
                    if(lca==-1)
                        lca=y;
                    else
                        lca=find_lca(lca,y);
                }
            }

            if(lca==-1)
            {
                printf("0\n");
            }
            else
            {
                printf("%d %d\n",level[lca],child[lca]);
            }

        }



    }

    return 0;
}
