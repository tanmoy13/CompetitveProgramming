#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

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
#define D(x)             cerr<<#x " = "<<(x)<<endl
#define VI               vector <int>
#define DBG              pf("Hi\n")
#define MOD              1000000007
#define CIN              ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define SZ(a)            (int)a.size()
#define sf(a)            scanf("%d",&a)
#define sfl(a)           scanf("%lld",&a)
#define sff(a,b)         scanf("%d %d",&a,&b)
#define sffl(a,b)        scanf("%lld %lld",&a,&b)
#define sfff(a,b,c)      scanf("%d %d %d",&a,&b,&c)
#define sfffl(a,b,c)     scanf("%lld %lld %lld",&a,&b,&c)
#define stlloop(v)       for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
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

#define mx 52

int n,m;
vector<pii>node;
double dp[mx][mx];
bool g[mx][mx];

#define data pair<double,pair<double, pii > >

double dist(int a, int b)
{
    return hypot((node[a].ff-node[b].ff),node[a].ss-node[b].ss);
}

void init()
{
    node.clear();
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
        {
            if(i==j)
            {
                dp[i][j]=0.0;
                g[i][j]=1;
            }
            else
            {
                dp[i][j]=(double)infinity;
                g[i][j]=0;
            }
        }
}

data solve()
{
    loop1(k,n) loop1(i,n) loop1(j,n)
    {
        dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]);
    }

    data ret=data(1000000000000000.0,MP(1000000000000000.0,pii(10000,10000)));

    for(int u=1;u<=n;u++) for(int v=u+1;v<=n;v++)
    {
//        if(g[u][v]) continue;
        double temp=0.0,uv=dist(u-1,v-1);
        loop1(i,n) loop1(j,n)
        {
            temp+=dp[i][j]-min(dp[i][j],min(dp[i][u]+dp[v][j]+uv,dp[i][v]+uv+dp[u][j]));
        }
        ret=min(ret,data(-temp,MP(uv,pii(u,v))));
    }
    return ret;
}

int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);

    while(sff(n,m) && n|m)
    {
        init();
        for(int i=0; i<n; i++)
        {
            int a,b;
            sff(a,b);
            node.pb(pii(a,b));
        }

        for(int i=0; i<m; i++)
        {
            int a,b;
            sff(a,b);
            g[a][b]=g[b][a]=1;
            dp[a][b]=dp[b][a]=dist(a-1,b-1);
        }

        data ans=solve();

//        D(ans.ff);

        if(ans.ff>=1000000000000000.0 || -ans.ff<=1.0)
            printf("No road required\n");
        else
            printf("%d %d\n",ans.ss.ss.ff,ans.ss.ss.ss);
    }


    return 0;
}

