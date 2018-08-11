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

#define mx 102

int g1[mx][mx],g2[mx][mx];
int n,r,bh,of,yh,m;
bool vis[mx];

void init()
{
    for(int i=0; i<=n; vis[i]=0,i++)
        for(int j=0; j<=n; j++)
        {
            if(i==j)
                g1[i][j]=g2[i][j]=0;
            else
                g1[i][j]=g1[j][i]=g2[i][j]=g2[j][i]=infinity;
        }
}

void floyd_warshal()
{
    loop1(k,n) loop1(i,n) loop1(j,n) g1[i][j]=min(g1[i][j],g1[i][k]+g1[k][j]);
    loop1(k,n)
    {
        if(g1[bh][of]==g1[bh][k]+g1[k][of])
            vis[k]=1;
    }
    for(int k=1; k<=n; k++)
        for(int i=1; i<=n && !vis[k]; i++)
            for(int j=1; j<=n && !vis[i]; j++)
            {
                if(vis[j]) continue;
                g2[i][j]=min(g2[i][j],g2[i][k]+g2[k][j]);
            }

}

int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);


    while(sfff(n,r,bh)==3 && sfff(of,yh,m)==3)
    {
        init();
        for(int i=0; i<r; i++)
        {
            int a,b,c;
            sfff(a,b,c);
            g1[a][b]=g1[b][a]=c;
            g2[a][b]=g2[b][a]=c;
        }

        floyd_warshal();

        if(g2[yh][m]>=infinity || vis[yh] || vis[m])
            printf("MISSION IMPOSSIBLE.\n");
        else
            printf("%d\n",g2[yh][m]);

    }

    return 0;
}
