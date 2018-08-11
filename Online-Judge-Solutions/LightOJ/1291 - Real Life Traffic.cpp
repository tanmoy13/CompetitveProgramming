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

vector<int>g[10005];
map<int,map<int,bool> > isbridge;
vector<pii>bridge;
int dis[10005],low[10005];
int cnt[10005];

int found=0;

int par[10005];


void allclear(int n)
{
    n+=2;
    for(int i=0;i<n;i++)
    {
        g[i].clear();
        par[i]=i;
        cnt[i]=0;
        dis[i]=0;
        low[i]=infinity;
    }
    isbridge.clear();
    bridge.clear();

}

void dfs(int u, int parent)
{
    dis[u]=low[u]=++found;
    for(int i=0;i<SZ(g[u]);i++)
    {
        int v=g[u][i];
        if(v==parent) continue;
        if(dis[v]==0)
            dfs(v,u);
        low[u]=min(low[u],low[v]);
    }
    if(low[u]>=dis[u] && u!=parent)
    {
        isbridge[u][parent]=isbridge[parent][u]=1;
        bridge.pb(pii(min(parent,u),max(parent,u)));
    }
}

int find_par(int u)
{
    return par[u]= (par[u]==u)?u:find_par(par[u]);
}


int main()
{

//    freopen("in.txt","r",stdin);
    ///freopen("out.txt","w",stdout);

    int t;
    sf(t);
    TEST_CASE(t)
    {
        int n,m;
        sff(n,m);

        allclear(n);

        loop(i,m)
        {
            int a,b;
            sff(a,b);
            g[a].pb(b);
            g[b].pb(a);
        }

        for(int i=0;i<n;i++)
        {
            if(dis[i]==0)
            {
                found=0;
                dfs(i,i);
            }
        }

        for(int i=0;i<n;i++)
        {
            for(int j=0;j<SZ(g[i]);j++)
            {
                int vv=g[i][j];
                if(isbridge[i][vv]==0)
                {
                    int u=find_par(i);
                    int v=find_par(vv);
                    if(u!=v)
                    {
                        par[v]=u;
                    }
                }
            }
        }

        for(int i=0;i<SZ(bridge);i++)
        {
//            cout<<bridge[i].ff<<" "<<bridge[i].ss<<endl;
            int u=find_par(bridge[i].ff);
            int v=find_par(bridge[i].ss);
//            if(u!=v)
//            {
//                par[u]=v;
                cnt[u]++;
                cnt[v]++;
//            }
        }

        int total=0;
        for(int i=0;i<n;i++)
            if(cnt[i]==1)
                total++;

        int ans=(total/2)+(total%2);

        PRINT_CASE;
        printf("%d\n",ans);


    }

    return 0;
}
