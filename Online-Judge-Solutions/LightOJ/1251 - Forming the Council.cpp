#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

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
#define VI               vector <int>
#define MOD              1000000007
#define fast_cin         ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define SZ(a)            (int)a.size()
#define sf(a)            scanf("%d",&a)
#define sfl(a)           scanf("%lld",&a)
#define sff(a,b)         scanf("%d %d",&a,&b)
#define sffl(a,b)        scanf("%lld %lld",&a,&b)
#define sfff(a,b,c)      scanf("%d %d %d",&a,&b,&c)
#define sfffl(a,b,c)     scanf("%lld %lld %lld",&a,&b,&c)
#define stlloop(v)       for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define UNIQUE(v)        (v).erase(unique((v).begin(),(v).end()),(v).end())
#define POPCOUNT         __builtin_popcountll
#define RIGHTMOST        __builtin_ctzll
#define LEFTMOST(x)      (63-__builtin_clzll((x)))
#define NUMDIGIT(x,y)    (((vlong)(log10((x))/log10((y))))+1)
#define NORM(x)          if(x>=mod) x-=mod;if(x<0) x+=mod;
#define ODD(x)           (((x)&1)==0?(0):(1))
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
#define D(x)        	 cerr << __LINE__ << ": " << #x << " = " << (x) << '\n'
#define DD(x,y)          cerr << __LINE__ << ": " << #x << " = " << x << "   " << #y << " = " << y << '\n'
#define DDD(x,y,z)       cerr << __LINE__ << ": " << #x << " = " << x << "   " << #y << " = " << y << "   " << #z << " = " << z << '\n'
#define DBG              cerr << __LINE__ << ": Hi" << '\n'

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

int getNode(int x) ///Convert a choice to node
{
    int p=abs(x);
    p=(p-1)*2;
    if(x<0)
        p^=1;
    return p;
}

int getVal(int x) ///Convert a node to choice
{
    int p=1;
    if(x&1)
    {
        p=-1;
        x-=1;
    }
    x/=2;
    x++;
    p*=x;
    return p;
}

#define mx 2*8005

vector<int>g[mx];

///SCC variables
int disc[mx],low[mx],Time, scc_count;
int component[mx];
stack<int>scc;
bool vis[mx];

///2-SAT variables
deque<int>sat;
int isSAT[mx];

void allclear()
{
    for(int i=0; i<mx; i++)
    {
        g[i].clear();
        disc[i]=0;
        low[i]=0;
        component[i]=0;
        isSAT[i]=-1;
    }

    scc_count=0;
    Time=0;
    while(!scc.empty())
        scc.pop();
    sat.clear();
}

void tarjan_SCC(int u)
{
    disc[u]=low[u]=++Time;
    scc.push(u);
    for(int i=0; i<SZ(g[u]); i++)
    {
        int v=g[u][i];
        if(disc[v]==0)
            tarjan_SCC(v);
        if(disc[v]!=-1)
            low[u]=min(low[u],low[v]);
    }
    if(low[u]==disc[u])
    {
        scc_count++;
        int v;
        do
        {
            v=scc.top();
            scc.pop();
            sat.push_back(v);
            component[v]=scc_count;
            disc[v]=-1;
        }
        while(v!=u);
    }
}


bool checkSAT(int n)
{
    while(!sat.empty())
    {
        int x=sat.front();
        sat.pop_front();
        if(isSAT[x]==-1)
        {
            isSAT[x]=1;
            x=getNode(-getVal(x)); ///Getting opposite value
            isSAT[x]=0;
        }
    }

    bool check=1;
    for(int i=1; i<=n && check; i++)
    {
        check=(component[getNode(i)]!=component[getNode(-i)]);
    }
    return check;
}

int main()
{
//#ifndef ONLINE_JUDGE
//    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif

//    int n,m;
//    cin>>n>>m;
//    for(int i=0; i<m; i++)
//    {
//        int a,b;
//        cin>>a>>b;
//        g[a].pb(b);
//    }
//
//    for(int i=1; i<=n; i++)
//    {
//        if(disc[i]==0)
//        {
//            tarjan_SCC(i);
//        }
//    }
//
//    D(scc_count);
//
//    for(int i=1; i<=n; i++)
//        DD(i,component[i]);


    int t;
    sf(t);
    TEST_CASE(t)
    {
        allclear();
        int n,m;
        sff(n,m);
        for(int i=0; i<n; i++)
        {
            int a,b;
            sff(a,b);
            g[getNode(-a)].pb(getNode(b));
            g[getNode(-b)].pb(getNode(a));
        }

        for(int i=1; i<=m; i++)
        {
            int x=getNode(i);
            if(disc[x]==0)
                tarjan_SCC(x);
            x=getNode(-i);
            if(disc[x]==0)
                tarjan_SCC(x);
        }


        bool check=checkSAT(m);
        PRINT_CASE;
        if(check)
        {
            printf("Yes\n");
            vector<int>temp;
            for(int i=1; i<=m; i++)
            {
                int x=getNode(i);
                if(isSAT[x])
                    temp.pb(i);
            }
            printf("%d",SZ(temp));
            for(int i=0; i<SZ(temp); i++)
            {
                printf(" %d",temp[i]);
            }
            printf("\n");
        }
        else
            printf("No\n");

    }

    return 0;
}
