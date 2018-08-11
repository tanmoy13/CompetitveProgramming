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

#define mx 10005

bitset<mx/2>vis;
vector<int>prime;
vector<int>g[mx];
bool visited[mx];
int dis[mx];

bool is_adjacent(int n1, int n2)
{
    int cnt=0;
    while(n1)
    {
        cnt+=(n1%10)!=(n2%10);
        n1/=10;
        n2/=10;
    }
    return cnt==1;
}

void sieve()
{
    int x=mx/2,y=sqrt(mx)/2;
    for(int i=1;i<y;i++)
    {
        if(vis[i]==0)
        {
            for(int j=i*(i+1)*2;j<x;j+=(2*i)+1)
                vis[j]=1;
        }
    }
    for(int i=1001;i<=9999;i+=2)
        if(vis[i/2]==0)
        {
            prime.pb(i);
        }
}

void makeGraph()
{
    for(int i=0;i<SZ(prime);i++)
    {
        for(int j=i+1;j<SZ(prime);j++)
        {
            if(is_adjacent(prime[i],prime[j]))
            {
                g[prime[i]].pb(prime[j]);
                g[prime[j]].pb(prime[i]);
            }
        }
    }
}

int BFS(int src, int dst)
{
    queue<int>Q;
    ms(visited,0);
    visited[src]=1;
    dis[src]=0;
    Q.push(src);
    while(!Q.empty())
    {
        int u=Q.front();
        Q.pop();
        if(u==dst) return dis[u];
        for(int i=0;i<SZ(g[u]);i++)
        {
            int v=g[u][i];
            if(!visited[v])
            {
                dis[v]=dis[u]+1;
                visited[v]=1;
                Q.push(v);
            }

        }
    }
    return -1;
}

int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);

    sieve();
    makeGraph();
//    cout<<SZ(prime)<<endl;
//    for(int i=0;i<100;i++)
//        cout<<prime[i]<<" ";

    int t;
    sf(t);
    TEST_CASE(t)
    {
        int a,b;
        sff(a,b);
        int ans=BFS(a,b);
        if(ans==-1)
            pf("Impossible\n");
        else
            pf("%d\n",ans);
    }


    return 0;
}
