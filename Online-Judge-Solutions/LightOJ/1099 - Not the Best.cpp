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

vector<int>g[5005],cost[5005];

int best[5005],not_best[5005];

struct node
{
    int u,cost;
    node(int a, int b)
    {
        u=a,cost=b;
    }
    bool operator < (const node &p) const
    {
        return cost>p.cost;
    }
};



void allclear(int n)
{
    for(int i=0; i<=n; i++)
    {
        g[i].clear();
        cost[i].clear();
    }
}

int main()
{

//    freopen("in.txt","r",stdin);
    ///freopen("out.txt","w",stdout);

    int t;
    sf(t);
    TEST_CASE(t)
    {
        int n,r;
        sff(n,r);
        loop(i,r)
        {
            int a,b,c;
            sfff(a,b,c);
            g[a].pb(b);
            g[b].pb(a);
            cost[a].pb(c);
            cost[b].pb(c);
        }

        PRINT_CASE;


        for(int i=0; i<=n; i++)
            best[i]=not_best[i]=infinity;
        best[1]=0;

        priority_queue<node>Q;
        Q.push(node(1,0));
        while(!Q.empty())
        {
            node u=Q.top();
            Q.pop();

            for(int i=0; i<SZ(g[u.u]); i++)
            {
                int v=g[u.u][i];
                if(u.cost+cost[u.u][i]<best[v])
                {
                    not_best[v]=min(not_best[v],best[v]);
                    best[v]=u.cost+cost[u.u][i];
                    Q.push(node(v,best[v]));
                }
                else if(u.cost+cost[u.u][i]<not_best[v] && u.cost+cost[u.u][i]!=best[v])
                {
                    not_best[v]=u.cost+cost[u.u][i];
                    Q.push(node(v,not_best[v]));
                }
            }
        }

        pf("%d\n",not_best[n]);

        allclear(n);

    }


    return 0;
}
