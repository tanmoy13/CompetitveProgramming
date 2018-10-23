/*
    Author: Tanmoy Datta
    Solution Idea:
    ---------------
        - Make a source.

        - Make a first group of vertices consisting of n vertices, each of them for one city.

        - Connect a source with ith vertex in first group with edge that has capacity ai.

        - Make a sink and second group of vertices in the same way, but use bi except for ai.

        - If there is a road between cities i and j or i = j. Make two edges, first should be connecting ith vertex from first group,
          and jth vertex from second group, and has infinity capacity. Second should be similar, but connect jth from first group and
          ith from second group.

        - Then find a maxflow, in any complexity.

        - If maxflow is equal to sum of ai and is equal to sum of bi, then there exists an answer. How can we get it?
          We just have to check how many units are we pushing through edge connecting two vertices from different groups.
*/


///Using MaxFlow Dinitz

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

///Max Flow Dinitz (Zobayer Vhai)
///clear()
///Build graph by addEdge
///Call findFLOW() to find maximum flow

const int INF = 1<<28; ///INT_MAX
const int MAXN = 4005, MAXE=4005;
///Maximum number of nodes and edges.

int Q[MAXN], fin[MAXN], pro[MAXN], dist[MAXN];
int flow[MAXE], cap[MAXE], nxt[MAXE], to[MAXE];

struct DINITZ
{
    int src, snk, nNode, nEdge;

    ///Parameters: (source, sink, no of nodes)
    void clear(int _src, int _snk, int _n)
    {
        src = _src, snk = _snk;
        nNode = _n, nEdge = 0;
        memset(fin,-1, sizeof fin);
    }

    ///Parameters: (from, to, capacity)
    void addEdge(int u, int v, int _cap)
    {
        to[nEdge] = v, cap[nEdge] = _cap, flow[nEdge] = 0;
        nxt[nEdge] = fin[u];
        fin[u] = nEdge++;
        ///Make this 2nd capacity zero for directed edge
        _cap=0;
        to[nEdge] = u, cap[nEdge] = _cap, flow[nEdge] = 0;
        nxt[nEdge] = fin[v];
        fin[v] = nEdge++;
    }

    bool BFS()
    {
        int st, en;
        memset(dist,-1,sizeof dist);
        dist[src] = st = en = 0;
        Q[en++] = src;
        while(st<en)
        {
            int u = Q[st++];
            for(int i = fin[u]; i>=0; i = nxt[i])
            {
                int v = to[i];
                if(flow[i] < cap[i] && dist[v] == -1)
                {
                    dist[v] = dist[u] + 1;
                    Q[en++] = v;
                }
            }
        }
        return dist[snk] != -1;
    }

    int DFS(int u, int fw)
    {
        if(u == snk) return fw;
        for(int &e = pro[u]; e >= 0; e = nxt[e])
        {
            int v = to[e];
            if(flow[e] < cap[e] && dist[v] == dist[u] + 1)
            {
                int cur_flow = DFS(v, min(cap[e]-flow[e], fw));
                if(cur_flow > 0)
                {
                    flow[e] += cur_flow;
                    flow[e^1]-= cur_flow;
                    return cur_flow;
                }
            }
        }
        return 0;
    }

    long long findFLOW()
    {
        long long fflow = 0;
        while(BFS())
        {
            for(int i = 0; i<= nNode; i++)
            {
                pro[i] = fin[i];
            }
            while(true)
            {
                long long fw=DFS(src,INF);
                if(fw > 0)
                    fflow += fw;
                else
                    break;
            }
        }
        return fflow;
    }
}dinitz;


int A[MAXN],B[MAXN];

int grid[MAXN][MAXN];

int main()
{
//#ifndef ONLINE_JUDGE
////    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif
    int sum1=0,sum2=0;

    int n,m;
    sff(n,m);
    dinitz.clear(0,2*n+1,2*n+2);
    for(int i=1;i<=n;i++)
    {
        sf(A[i]);
        dinitz.addEdge(0,i,A[i]);
        sum1+=A[i];
    }

    for(int i=1;i<=n;i++)
    {
        sf(B[i]);
        dinitz.addEdge(n+i,2*n+1,B[i]);
        sum2+=B[i];
    }

    for(int i=1;i<=n;i++)
    {
        dinitz.addEdge(i,n+i,INF);
    }

    for(int i=0;i<m;i++)
    {
        int u,v;
        sff(u,v);
        dinitz.addEdge(u,n+v,INF);
        dinitz.addEdge(v,n+u,INF);
    }

    int ans=dinitz.findFLOW();

    if(ans!=sum1 || ans!=sum2)
    {
        printf("NO\n");
        return 0;
    }

    for(int u=1;u<=n;u++)
    {
        for(int i=fin[u];i>=0;i=nxt[i])
        {
            int v=to[i];
            if(v>n)
                grid[u][v-n]=flow[i];
        }
    }

    printf("YES\n");

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            printf("%d",grid[i][j]);
            if(j<n)
                printf(" ");
        }
        printf("\n");
    }


    return 0;
}



///Using Maxflow Ford Fulkerson

/*

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


#define mx 105

int n,m;
int a[mx],b[mx];
int g[2*mx][2*mx];
bool vis[2*mx];
int par[2*mx];

bool find_path(int s, int t)
{
    ms(vis,0);
    queue<int>Q;
    Q.push(s);
    vis[s]=1;
    while(!Q.empty())
    {
        int u=Q.front();
        Q.pop();
        if(u==t) return true;
        for(int i=0; i<=2*n+1; i++)
        {
            if(vis[i]==0 && g[u][i]>0)
            {
                vis[i]=1;
                par[i]=u;
                Q.push(i);
//                if(i==t) return true;
            }
        }
    }
    return false;
}

int find_flow(int s, int t)
{
    int ret=0;
    while(find_path(s,t))
    {
        int mini=INT_MAX;
        for(int i=t; i!=s; i=par[i])
        {
            int u=par[i];
            mini=min(g[u][i],mini);
        }

        for(int i=t; i!=s; i=par[i])
        {
            int u=par[i];
            g[u][i]-=mini;
            g[i][u]+=mini;
        }
        ret+=mini;
    }
    return ret;
}

int main()
{
//#ifndef ONLINE_JUDGE
////    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif

    sff(n,m);
    int total=0,total1=0;
    for(int i=1; i<=n; i++)
    {
        sf(a[i]);
        total1+=a[i];
    }
    for(int i=1; i<=n; i++)
    {
        sf(b[i]);
        total+=b[i];
    }

    for(int i=0; i<m; i++)
    {
        int x,y;
        sff(x,y);
        g[x][n+y]=1e5;
//        g[n+y][x]=1e5;
        g[y][n+x]=1e5;
//        g[n+x][y]=1e5;
    }

    for(int i=1;i<=n;i++)
    {
        g[i][n+i]=1e5;
//        g[n+i][i]=1e5;
    }

    for(int i=1; i<=n; i++)
    {
        g[0][i]=a[i];
    }

    for(int i=1; i<=n; i++)
    {
        g[n+i][2*n+1]=b[i];
    }


    int ans=find_flow(0,2*n+1);

    if(ans!=total || ans!=total1)
    {
        printf("NO\n");
        return 0;
    }

    printf("YES\n");

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
//            if(i==j)
//                g[n+j][i]=max(0,g[n+j][i]-100000);
            printf("%d",g[n+j][i]);
            if(j<n)
                printf(" ");
        }
        printf("\n");
    }




    return 0;
}

*/
