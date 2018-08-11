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

ll ara[11][101];
ll dp[11][101];
int path[11][101];
int n,m;

int get_idx(int r)
{
    if(r==0) return n;
    if(r==n+1) return 1;
    return r;
}

ll func(int r, int c)
{
    if(r==0) return func(n,c);
    if(r==n+1) return func(1,c);
    if(c>m) return 0;
    ll &ret=dp[r][c];
    if(ret!=-1) return ret;
    ll x,y,z;
    x=y=z=(1LL<<60);
    x=ara[r][c]+func(r,c+1);
    y=ara[r][c]+func(r-1,c+1);
    z=ara[r][c]+func(r+1,c+1);
    ret=min(x,min(y,z));

    int mini=10000;
    if(x==ret)
        mini=min(mini,r);
    if(y==ret)
        mini=min(mini,get_idx(r-1));
    if(z==ret)
        mini=min(mini,get_idx(r+1));
    path[r][c]=mini;
    return ret;
}

void path_print(int x, int y, vector<int>& temp)
{
    if(y>m)
    {
        return;
    }
    temp.pb(x);
    path_print(path[x][y],y+1,temp);
}

int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);

    while(sff(n,m)==2)
    {
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                sfl(ara[i][j]);

        ms(dp,-1);

        int start=0;
        ll ans=(1LL<<60);

        for(int i=1;i<=n;i++)
        {
            if(ans>func(i,1))
            {
                ans=func(i,1);
                start=i;
            }
        }

        vector<int>temp;
        path_print(start,1,temp);
        for(int i=0;i<SZ(temp);i++)
        {
            printf("%d",temp[i]);
            if(i!=SZ(temp)-1)
                printf(" ");
        }

        printf("\n");
        printf("%lld\n",ans);


    }

    return 0;
}
