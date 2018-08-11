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

#define mx 10004

vector<int>g[mx];
int h[mx],low[mx],dfsnum;
bool artpoint[mx];
int pigeon[mx];

void allclear(int n)
{
    for(int i=0;i<n+2;i++)
    {
        g[i].clear();
        h[i]=low[i]=artpoint[i]=pigeon[i]=0;
    }
    dfsnum=0;
}

void dfs(int u, int par)
{
    h[u]=low[u]=++dfsnum;
    int child=0;
    int cnt=0;
    for(int i=0;i<SZ(g[u]);i++)
    {
        int v=g[u][i];
        if(v==par) continue;
        if(h[v])
        {
            low[u]=min(low[u],h[v]);
        }
        else
        {
            child++;
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>=h[u])
            {
                artpoint[u]=1;
                cnt++;
            }
        }
    }
    if(artpoint[u])
        pigeon[u]=cnt+1;
    else
        pigeon[u]=1;
    if(par==-1)
    {
        if(child>1)
        {
            artpoint[u]=1;
            pigeon[u]=child;
        }
        else
        {
            pigeon[u]=1;
            artpoint[u]=0;
        }
    }
}


bool cmp(pii a, pii b)
{
    if(a.ss>b.ss) return 1;
    if(a.ss==b.ss) return a.ff<b.ff;
    return 0;
}


int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);
    int n,m;
    while(sff(n,m) && (n||m))
    {
        allclear(n);
        int a,b;
        while(sff(a,b))
        {
            if(a==-1 && b==-1) break;
            g[a].pb(b);
            g[b].pb(a);
        }
        for(int i=0; i<n; i++)
        {
            if(h[i]==0)
                dfs(i,-1);
        }

//        for(int i=0;i<n;i++)
//        {
//            if(artpoint[i])
//                D(i);
//        }

        vector<pii>v;

        for(int i=0; i<n; i++)
        {
            v.pb(pii(i,pigeon[i]));
        }

        sort(all(v),cmp);
        for(int i=0;i<SZ(v) && m;i++,m--)
        {
            printf("%d %d\n",v[i].ff,v[i].ss);
        }
        printf("\n");

    }





    return 0;
}
