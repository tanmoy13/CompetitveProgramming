#include <bits/stdc++.h>

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
#define D(x)             cout<<#x " = "<<(x)<<endl
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

int n,q;
int par[1005],level[1005];
vector<int>g[1005];
int sparse_par[1005][12];


void dfs(int u, int cnt, int from)
{
    par[u]=from;
    level[u]=cnt;

    for(int i=0;i<SZ(g[u]);i++)
    {
        int v=g[u][i];
        if(v!=from)
        {
            dfs(v,cnt+1,u);
        }
    }
}

void build_table()
{
    for(int i=1;i<=n;i++)
    {
        sparse_par[i][0]=par[i];
    }

    for(int j=1;1<<j<=n;j++)
    {
        for(int i=1;i<=n;i++)
        {
            sparse_par[i][j]=sparse_par[sparse_par[i][j-1]][j-1];
//            D(i);
//            D(j);
//            D(sparse_par[i][j]);
        }
    }
}

int query(int p, int q)
{
    if(level[p]<=level[q]) swap(p,q);
    int log=log2(level[p]);

    for(int i=log;i>=0;i--)
    {
        if(level[p]-(1<<i)>=level[q])
            p=sparse_par[p][i];
    }

    if(p==q) return p;

    for(int i=log;i>=0;i--)
    {
        if(sparse_par[p][i]!=sparse_par[q][i])
        {
            p=sparse_par[p][i];
            q=sparse_par[q][i];
        }
    }

    return par[p];

}

int main()
{

//    freopen("in.txt","r",stdin);
    ///freopen("out.txt","w",stdout);

    int t;
    sf(t);
    TEST_CASE(t)
    {
        sf(n);

        for(int i=1;i<=n;i++)
        {
            int m,a;
            sf(m);
            for(int j=0;j<m;j++)
            {
                sf(a);
                g[a].pb(i);
                g[i].pb(a);
            }
        }

        dfs(1,0,1);

        build_table();

        sf(q);
        LINE_PRINT_CASE;
        while(q--)
        {
            int a,b;
            sff(a,b);
            printf("%d\n",query(a,b));
        }

        for(int i=0;i<=n;i++)
            g[i].clear();


    }

    return 0;
}
