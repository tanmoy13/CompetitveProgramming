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

int n;
int g[102][102];
bool vis[102],vis1[102];
bool dominator[102][102];

void dfs(int u)
{
    vis[u]=1;
    for(int i=0; i<n; i++)
    {
        if(g[u][i]==1)
        {
            if(!vis[i])
                dfs(i);
        }
    }
}

void dfs1(int u, int block)
{
    vis1[u]=1;
    if(u==block) return;
    for(int i=0;i<n;i++)
    {
        if(g[u][i]==1 && !vis1[i])
            dfs1(i,block);
    }
}

int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);

    int t;
    sf(t);
    TEST_CASE(t)
    {
        ms(vis,0);
        ms(dominator,0);
        sf(n);
        for(int i=0; i<n; i++) for(int j=0; j<n; j++) sf(g[i][j]);
        dfs(0);

        for(int i=0;i<n;i++)
            dominator[0][i]=vis[i];

        for(int i=1; i<n; i++)
        {
            ms(vis1,0);
            dfs1(0,i);
            if(vis[i])
                dominator[i][i]=1;
            for(int j=0;j<n;j++)
            {
                if(vis[j]==1 && vis1[j]==0)
                    dominator[i][j]=1;
            }
        }

        LINE_PRINT_CASE;

        string bar="+"+string(2*n-1,'-')+"+";
        printf("%s\n",bar.c_str());
        for(int i=0; i<n; i++)
        {
            printf("|");
            for(int j=0; j<n; j++)
            {
                if(dominator[i][j])
                    printf("Y|");
                else
                    printf("N|");
            }
            printf("\n");
            printf("%s\n",bar.c_str());
        }
    }

    return 0;
}
