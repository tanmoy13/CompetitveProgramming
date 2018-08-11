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

vector<int>g[10005],cost[10005],proposed[10005],cost_prop[10005];

ll dis[11][10005];

struct data
{
    int u,used;
    ll cost;
    data(int a, ll b, int c)
    {
        u=a,cost=b,used=c;
    }

    bool operator< (const data &p) const
    {
        return cost>p.cost;
    }
};


void allclear(int n)
{
    for(int i=0;i<=n+2;i++)
    {
        g[i].clear();
        cost[i].clear();
        proposed[i].clear();
        cost_prop[i].clear();
    }
    for(int i=0;i<10;i++)
        for(int j=0;j<=n;j++)
            dis[i][j]=infinity;
}

int main()
{

//    freopen("in.txt","r",stdin);
    ///freopen("out.txt","w",stdout);

    int t;
    sf(t);
    TEST_CASE(t)
    {
        int n,m,k,d;
        sfff(n,m,k);
        sf(d);

        allclear(n);

        for(int i=0; i<m; i++)
        {
            int a,b,c;
            sfff(a,b,c);
            g[a].pb(b);
            cost[a].pb(c);
        }

        for(int i=0; i<k; i++)
        {
            int a,b,c;Codeblocks error Permission denied in linux mint
            sfff(a,b,c);
            proposed[a].pb(b);
            cost_prop[a].pb(c);
        }

        for(int i=0;i<10;i++)
            dis[i][0]=0;

        priority_queue<data>Q;
        Q.push(data(0,0,0));

        int ans=-1;

        while(!Q.empty())
        {
            data u=Q.top();
            if(u.u==n-1)
                {
                    ans=u.cost;
                    break;
                }
            Q.pop();
            for(int i=0;i<SZ(g[u.u]);i++)
            {
                int v=g[u.u][i];
                if(u.cost+cost[u.u][i]<dis[u.used][v])
                {
                    dis[u.used][v]=u.cost+cost[u.u][i];
                    Q.push(data(v,dis[u.used][v],u.used));
                }
            }

            for(int i=0;i<SZ(proposed[u.u]);i++)
            {
                int v=proposed[u.u][i];
                if(u.cost+cost_prop[u.u][i]<dis[u.used+1][v] && u.used+1<=d)
                {
                    dis[u.used+1][v]=u.cost+cost_prop[u.u][i];
                    Q.push(data(v,dis[u.used+1][v],u.used+1));
                }
            }
        }

        PRINT_CASE;
        if(ans==-1)
            pf("Impossible\n");
        else
            printf("%d\n",ans);

    }
    return 0;
}
