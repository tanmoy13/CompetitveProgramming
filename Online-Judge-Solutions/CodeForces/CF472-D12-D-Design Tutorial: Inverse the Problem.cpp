/*
    Author: Tanmoy Datta
    Solution Idea:
    --------------
        - Build a MST from given input.
        - Run dfs from every node and check whether this cost from this node to every node is same as the input or not.
        - If yes then print YES otherwise NO.
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

#define mx 2005

int grid[mx][mx];
vector< pair<int, pii > >edge;

vector<int>g[mx],cost[mx];

int par[mx];

void init()
{
    for(int i=0; i<mx; i++) par[i]=i;
}

int find_par(int u)
{
    return par[u]=(par[u]==u)?u:find_par(par[u]);
}

int n;

void build_mst()
{
    sort(all(edge));
    int total=0;
    for(int i=0; i<SZ(edge); i++)
    {
        int u=edge[i].ss.ff;
        int v=edge[i].ss.ss;
        int w=edge[i].ff;
        int x=find_par(u);
        int y=find_par(v);
        if(x!=y)
        {
            par[y]=x;
            g[u].pb(v);
            g[v].pb(u);
            cost[u].pb(w);
            cost[v].pb(w);
            total++;
            if(total==n-1)
                break;
        }
    }
}

bool check=0;
int cntt=0;

void dfs(int from, int u, int p, ll c)
{
    cntt++;
    if(check) return;
    if(grid[from][u]!=c)
    {
        check=1;
        return;
    }

    for(int i=0; i<SZ(g[u]) && !check; i++)
    {
        int v=g[u][i];
        if(v==p) continue;
        dfs(from,v,u,c+(ll)cost[u][i]);
    }

}

int main()
{
//#ifndef ONLINE_JUDGE
////    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif

    sf(n);
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            sf(grid[i][j]);
        }
    }


    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            if(grid[i][j]!=grid[j][i])
            {
                printf("NO\n");
                return 0;
            }

            if(grid[i][j])
            {
                edge.pb(MP(grid[i][j],MP(i,j)));
            }
        }
    }


    init();
    build_mst();

    for(int i=1; i<=n && !check; i++)
    {
        cntt=0;
        dfs(i,i,i,0);
        if(cntt!=n)
            check=1;
    }

    if(check)
        printf("NO\n");
    else
        printf("YES\n");


    return 0;
}
