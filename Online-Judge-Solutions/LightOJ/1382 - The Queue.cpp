/*
I could give u some question to reach the solution of the problem.
Try to represent the problem as a tree.
1. What are the subtree means and their root... ?
2. How to find the root of the tree?
3. if i have a root and with 2 child ( left and right ) then what is the answer ?
4. Can I extend the idea of this for many nodes ?
-> ( May be u have to calculate the combinations))
5. try to find a recursive solution.
*/
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

int dp[1005][1005];

int nCr(int n, int r)
{
    if(r==0) return 1;
    if(n==r) return 1;

    int &ret=dp[n][r];

    if(ret!=-1) return ret;

    ret=(nCr(n-1,r)%MOD+nCr(n-1,r-1)%MOD)%MOD;

    return ret;
}

vector<int>g[1005];
bool root[1005];
int child[1005];


ll dfs(int u)
{
    child[u]=1;
    ll ret=1;
//    vector<int> children;
    int sum=0;
    for(int i=0;i<SZ(g[u]);i++)
    {
        int v=g[u][i];
        ret=(ret*dfs(v))%MOD;
        sum+=child[v];
        child[u]+=child[v];
    }

    for(int i=0;i<SZ(g[u]);i++)
    {
        int v=g[u][i];
        ret=(ret*nCr(sum,child[v]))%MOD;
        sum-=child[v];
    }
    return ret;
}

void allclear(int n)
{
    n+=2;
    for(int i=0;i<n;i++)
    {
        g[i].clear();
        root[i]=true;
        child[i]=0;
    }
}

int main()
{

    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);

    int t;
    sf(t);
    ms(dp,-1);
    TEST_CASE(t)
    {
        int n;
        sf(n);

        allclear(n);

        for(int i=1;i<n;i++)
        {
            int a,b;
            sff(a,b);
            g[a].pb(b);
            root[b]=false;
        }

        ll ans=0;

        for(int i=1;i<=n;i++)
        {
            if(root[i])
            {
                ans=dfs(i);
                break;
            }
        }

        PRINT_CASE;
        printf("%lld\n",ans);



    }

    return 0;
}
