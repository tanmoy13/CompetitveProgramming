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


/// Min Cost Max Flow Zobayer
/// Note: Doesn't work for negative cycle
/// Initialize using clear()
/// Add the edges using addEdge()
/// Call findMCMF() to get both min cost and max flow.

const int INF = 1e8;
const int MAXN = 105, MAXE = 10005;
/// Maximum no of nodes and edges.

int fin[MAXN], pro[MAXN], dist[MAXN];
int cap[MAXE], cost[MAXE], nxt[MAXE], to[MAXE], from[MAXE];

struct MCMF
{
    int src, snk, nNode, nEdge;

    /// Parameters: (source, sink, no of nodes)
    void clear(int _src, int _snk, int nodes)
    {
        nNode = nodes, nEdge = 0;
        src = _src, snk = _snk;
        memset(fin, -1, sizeof fin);
    }

    /// Parameters: (from, to, capacity, cost per flow)
    void addEdge(int u, int v, int _cap, int _cost)
    {
        from[nEdge] = u, to[nEdge] = v, cap[nEdge] = _cap;
        cost[nEdge] = _cost, nxt[nEdge] = fin[u], fin[u] = nEdge++;
        from[nEdge] = v, to[nEdge] = u, cap[nEdge] = 0;
        cost[nEdge] = -_cost, nxt[nEdge] = fin[v], fin[v] = nEdge++;
    }

    bool bellmanford()
    {
        bool flag = true;
        for(int i = 0; i<nNode; i++)
        {
            dist[i] = INF;
            pro[i] = -1;
        }
        dist[src] = 0;
        for (int it = 1; it < nNode && flag; it++)
        {
            flag = false;
            for (int u = 0; u < nNode; u++)
            {
                for (int i = fin[u]; i >= 0; i = nxt[i])
                {
                    int v = to[i];
                    if (cap[i] && dist[v] > dist[u] + cost[i])
                    {
                        dist[v] = dist[u] + cost[i];
                        pro[v] = i;
                        flag = true;
                    }
                }
            }
        }
        return (dist[snk] < INF);
    }

    /// Returns pair {flow, cost}
    pii findMCMF()
    {
        int fflow = 0, fcost = 0;
        while (bellmanford())
        {
            int fw = INF;
            for (int u = pro[snk]; u >= 0; u = pro[from[u]])
            {
                fw = min(fw, cap[u]);
            }
            for (int u = pro[snk]; u >= 0; u = pro[from[u]])
            {
                cap[u] -= fw;
                cap[u ^ 1] += fw;
                fcost += fw * cost[u];
            }
            fflow += fw;
        }
        return MP(fflow, fcost);
    }
} mcmf;

int main()
{
//#ifndef ONLINE_JUDGE
////    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif

    int t;
    sf(t);
    TEST_CASE(t)
    {
        int n;
        sf(n);
        mcmf.clear(2*n,2*n+1,2*(n+1));
        for(int i=0; i<n; i++)
        {
            for(int j=n; j<2*n; j++)
            {
                int a;
                sf(a);
                mcmf.addEdge(i,j,1,-a);
            }
        }

        for(int i=0; i<n; i++)
        {
            mcmf.addEdge(2*n,i,1,0);
        }

        for(int i=n; i<2*n; i++)
        {
            mcmf.addEdge(i,2*n+1,1,0);
        }

        pii ans=mcmf.findMCMF();

        PRINT_CASE;
        printf("%d\n",-ans.ss);

    }

    return 0;
}
