/**
    Author: Tanmoy Datta

    Solution Idea:
    ~~~~~~~~~~~~~~
        - At first calculate shortest distance from start node to all node in original graph.
        - Then calculate shortest distance from end node to all node in reversed graph.
        - Now an edge (u,v) can be the maximum cost edge if distance from (source to u) + cost of (u,v) + (v to destination) <= p.
        - Check for every edges.
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

#define mx 10005

vector<int>g[2][mx],cost[2][mx];

int n,m,s,t,p;

int dis[2][mx];

int dijikastra(int src, int id)
{

    priority_queue<pii>Q;
    Q.push(MP(0,src));
    dis[id][src]=0;


    while(!Q.empty())
    {
        pii u=Q.top();
        Q.pop();
        u.ff=-u.ff;

        for(int i=0;i<SZ(g[id][u.ss]);i++)
        {
            int v=g[id][u.ss][i];
            int c=cost[id][u.ss][i];

            if(dis[id][v]>dis[id][u.ss]+c)
            {
                dis[id][v]=dis[id][u.ss]+c;
                Q.push(MP(-dis[id][v],v));
            }
        }
    }
}


void allclear(int n)
{
    for(int i=0;i<=n;i++)
    {
        g[0][i].clear();
        g[1][i].clear();
        cost[0][i].clear();
        cost[1][i].clear();
        dis[0][i]=(1<<28);
        dis[1][i]=(1<<28);
    }
}

int main()
{
//#ifndef ONLINE_JUDGE
//    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif

    int tt;
    sf(tt);
    TEST_CASE(tt)
    {

        sff(n,m);
        sfff(s,t,p);

        allclear(n+2);

        vector<pair<pii, int> > v;

        for(int i=0;i<m;i++)
        {
            int a,b,c;
            sfff(a,b,c);
            g[0][a].pb(b);
            cost[0][a].pb(c);
            g[1][b].pb(a);
            cost[1][b].pb(c);
            v.pb(MP(pii(a,b),c));
        }

        dijikastra(s,0);
        dijikastra(t,1);

        int ans=-1;

        for(int i=0;i<SZ(v);i++)
        {
            int c=v[i].ss;
            int d1=dis[0][v[i].ff.ff];
            int d2=dis[1][v[i].ff.ss];
            if(d1+d2+c<=p)
            {
                ans=max(ans,c);
            }
        }


        PRINT_CASE;

        printf("%d\n",ans);


    }

    return 0;
}
