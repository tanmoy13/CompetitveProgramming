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
const int fx[]= {+1,-1,+0,+0};
const int fy[]= {+0,+0,+1,-1};
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

vector<pii>ghost,human;

char grid[30][30];

int dis[50][30][30];

bool vis[50][28][28];

int nn;

void bfs(pii src, int id)
{
    vis[id][src.ff][src.ss]=1;
    queue<pii>Q;
    Q.push(src);
    dis[id][src.ff][src.ss]=0;
    while(!Q.empty())
    {
        pii u=Q.front();
        Q.pop();
        for(int i=0; i<4; i++)
        {
            int x=u.ff+fx[i];
            int y=u.ss+fy[i];
            if(!vis[id][x][y] && x>=0 && x<nn && y>=0 && y<nn && grid[x][y]!='#')
            {
                vis[id][x][y]=1;
                dis[id][x][y]=dis[id][u.ff][u.ss]+1;
                Q.push(pii(x,y));
            }
        }
    }
}

///matching part

vector<int>g[102];

void build_bipertite_graph(int mid)
{


    int total_human = SZ(human);
    for(int i=0; i<total_human+SZ(ghost); i++)
        g[i].clear();

    for(int i=0; i<SZ(human); i++)
    {
        for(int j=0; j<SZ(ghost); j++)
        {
            int x=ghost[j].ff,y=ghost[j].ss;
            if(vis[i][x][y])
            {
                int d=2+dis[i][x][y]*2;
                if(d<=mid)
                {
                    g[i].pb(total_human+j);
                    g[total_human+j].pb(i);
                }
            }
        }
    }
}

int match[102];
int visi[102];
int cas;

bool find_match(int u)
{
    if(visi[u]==cas) return false;
    visi[u]=cas;
    for(int i=0; i<SZ(g[u]); i++)
    {
        int v=g[u][i];
        if(match[v]==-1)
        {
            match[u]=v;
            match[v]=u;
            return true;
        }
    }

    for(int i=0; i<SZ(g[u]); i++)
    {
        int v=g[u][i];
        if(find_match(match[v]))
        {
            match[u]=v;
            match[v]=u;
            return true;
        }
    }

    return false;
}

int matching(int n)
{
    ms(match,-1);
    int ret=0;
    for(int i=0; i<n; i++)
    {
        if(match[i]==-1)
        {
            cas++;
            bool ans=find_match(i);
            if(ans)
                ret++;
        }
    }
    return ret;
}

void allclear()
{
    ms(vis,0);
    ghost.clear();
    human.clear();
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
        allclear();
        int n;
        sf(n);
        nn=n;
        for(int i=0; i<n; i++)
        {
            scanf(" %s",grid[i]);
        }

        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(grid[i][j]=='G')
                    ghost.pb(pii(i,j));
                else if(grid[i][j]=='H')
                    human.pb(pii(i,j));
            }
        }

        for(int i=0; i<SZ(human); i++)
        {
            bfs(human[i],i);
        }

        int lo=0,hi=110;
        int ans=-1;
        while(lo<=hi)
        {
            int mid=(lo+hi)/2;
            build_bipertite_graph(mid);
            int x=matching(SZ(human));
            if(x==SZ(human))
            {
                ans=mid;
                hi=mid-1;
            }
            else
                lo=mid+1;
        }

        PRINT_CASE;
        if(ans==-1)
            printf("Vuter Dol Kupokat\n");
        else
            printf("%d\n",ans);


    }

    return 0;
}
