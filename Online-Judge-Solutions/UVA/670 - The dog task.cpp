/*
    Author: Tanmoy Datta

    Solution Idea:
    ~~~~~~~~~~~~~~
        - There are some observation in this problem.
        - At first there can be at most only one special place between two bobs place.
        - We must have to visit all the bobs place.
        - Let p1 and p2 is two of bobs place and one interesting place is x. then this condition must be satisfied
          distance(p1,x)+distance(x,p2)<= 2*distance(p1,p2).
        - So we can convert this problem to a maximum bipartite matching problem. Were one set contains all bobs place
          and another set contains all special place.
        - We need to add an edge between point p1 and special node x if for p1, p2 and x the above condition satisfies.
        - Then we need to print every bobs place and their matched special places.
        - Special attention don't print an extra new line after last test case.
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


#define point complex<ll>

#define X real()
#define Y imag()

#define mx 305

vector<int>g[mx];

int vis[mx];
int match[mx];
int cas;

bool matching(int u)
{
    if(vis[u]==cas) return false;
    vis[u]=cas;
    for(int i=0;i<SZ(g[u]);i++)
    {
        int v=g[u][i];
        if(match[v]==-1)
        {
            match[u]=v;
            match[v]=u;
            vis[v]=cas;
            return true;
        }
    }

    for(int i=0;i<SZ(g[u]);i++)
    {
        int v=g[u][i];
        if(matching(match[v]))
        {
            match[u]=v;
            match[v]=u;
            vis[v]=cas;
            return true;
        }
    }
    return false;
}

void allclear(int n)
{
    for(int i=0;i<=n;i++)
    {
        g[i].clear();
        match[i]=-1;
        vis[i]=0;
    }
    cas=0;
}

int main()
{
//#ifndef ONLINE_JUDGE
//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);
//#endif

    int t;
    sf(t);
    TEST_CASE(t)
    {
        int n,m;
        sff(n,m);

        allclear(n+m+2);

        vector<point>must_include,optional;

        for(int i=0;i<n;i++)
        {
            ll a,b;
            sffl(a,b);
            must_include.pb(point(a,b));
        }

        for(int i=0;i<m;i++)
        {
            ll a,b;
            sffl(a,b);
            optional.pb(point(a,b));
        }

        for(int i=0;i<n-1;i++)
        {
            point temp=must_include[i+1]-must_include[i]; // line segment
//            DD(must_include[i+1],must_include[i]);
            double dis=2.0*hypot(temp.X,temp.Y);
//            D(dis1);
            for(int j=0;j<m;j++)
            {
                point temp1=optional[j]-must_include[i]; //line segment
                point temp2=must_include[i+1]-optional[j]; //line segment
                double dis1=hypot(temp1.X,temp1.Y);
                double dis2=hypot(temp2.X,temp2.Y);
                if(dis1+dis2<=dis)
                {
//                    DD(i,j);
                    g[i].pb(n+j);
                    g[n+j].pb(i);
                }
            }
        }

        int ans=0;
        for(int i=0;i<n;i++)
        {
            cas++;
            if(matching(i))
            {
                ans++;
            }
        }

        printf("%d\n",n+ans);
        for(int i=0;i<n;i++)
        {
            printf("%lld %lld",must_include[i].X,must_include[i].Y);
            if(i!=n-1)
                printf(" ");
            if(match[i]!=-1)
            {
                int j=match[i]-n;
                printf("%lld %lld",optional[j].X,optional[j].Y);
                printf(" ");
            }
        }
        printf("\n");

        if(z!=t)
            printf("\n");


    }

    return 0;
}
