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

vector<int>g[505],cost[505];
int G[505][505];
int n,m;
int dis[505];

void dijikastra(int src)
{
    fill(dis,dis+505,infinity);
    dis[src]=0;
    priority_queue<pii>Q;
    Q.push(pii(-0,src));
    while(!Q.empty())
    {
        pii u=Q.top();
        Q.pop();
        u.ff=-u.ff;
        for(int i=0; i<SZ(g[u.ss]); i++)
        {
            int v=g[u.ss][i];
            if(dis[v]>u.ff+cost[u.ss][i])
            {
                dis[v]=u.ff+cost[u.ss][i];
                Q.push(pii(-dis[v],v));
            }
        }
    }
}

void allclear()
{
    for(int i=0; i<=n; i++)
    {
        g[i].clear();
        cost[i].clear();
        dis[i]=0;
    }
    ms(G,0);
}

int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);
    int z=0;
    while(sff(n,m) && (n||m))
    {
        allclear();
        for(int i=0; i<m; i++)
        {
            int a,b,c;
            sfff(a,b,c);
            g[a].pb(b);
            g[b].pb(a);
            cost[a].pb(c);
            cost[b].pb(c);
            G[a][b]=G[b][a]=c;
        }

        dijikastra(1);

        double maxi=0.0;

        for(int i=1; i<=n; i++)
            for(int j=i+1; j<=n; j++)
            {
                if(G[i][j])
                {
                    int temp=abs(dis[i]-dis[j]);
                    temp=abs(G[i][j]-temp);
                    maxi=max(maxi,max(dis[i],dis[j])+temp/2.0);
                }
            }

        int a=-1,b=-1,id=-1;

        for(int i=1; i<=n; i++)
        {
            if(maxi==dis[i])
            {
                id=i;
                break;
            }
        }


        for(int i=1; i<=n && id==-1; i++)
            for(int j=i+1; j<=n; j++)
            {
                if(G[i][j])
                {
                    int temp=abs(dis[i]-dis[j]);
                    temp=abs(G[i][j]-temp);
                    if(fabs(maxi-(max(dis[i],dis[j])+temp/2.0))<EPS)
                    {
                        a=i;
                        b=j;
                        break;
                    }
                }
            }

        printf("System #%d\n",++z);
        printf("The last domino falls after %.1lf seconds,",maxi);
        if(id==-1)
            printf(" between key dominoes %d and %d.\n",a,b);
        else
            printf(" at key domino %d.\n",id);
        printf("\n");

    }

    return 0;
}
