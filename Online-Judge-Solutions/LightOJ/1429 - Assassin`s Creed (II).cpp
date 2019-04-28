/**
    Author: Tanmoy Datta

    Solution Idea:
    ~~~~~~~~~~~~~~
        - At first make a DAG using scc graph.
        - Then then answer is minimum general path cover in a graph.
        - According to Dilworth’s theorem we can find this using bipartite matching matching.
*/

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

#define mx 2005

vector<int>g[mx],scc_dag[mx],matching_graph[mx];
int scc[mx],disc[mx],low[mx],dfs_num,scc_cnt, vis[mx], matching[mx];
stack<int>st;

void allclear()
{
    for(int i=0; i<mx; i++)
    {
        g[i].clear();
        scc_dag[i].clear();
        scc[i]=0;
        disc[i]=0;
        low[i]=0;
        vis[i]=0;
        matching[i]=-1;
        matching_graph[i].clear();
    }
//    edges.clear();
    while(!st.empty())
        st.pop();
    scc_cnt=0;
    dfs_num=0;

}

void Tarjan_SCC(int u)
{
    disc[u]=low[u]=++dfs_num;
    vis[u]=1;
    st.push(u);
    for(int i=0; i<SZ(g[u]); i++)
    {
        int v=g[u][i];
        if(disc[v]==0)
        {
            Tarjan_SCC(v);
        }
        if(vis[v])
            low[u]=min(low[u],low[v]);
    }
    if(low[u]==disc[u])
    {
        scc_cnt++;
        while(1)
        {
            int v=st.top();
            st.pop();
            vis[v]=0;
            scc[v]=scc_cnt;
            if(v==u)
                break;
        }
    }
}


int src;
int cas=0;

void dfs(int u) //build matching graph
{
    vis[u]=cas;
    if(u!=src)
    {
        matching_graph[src].pb(scc_cnt+u);
        matching_graph[scc_cnt+u].pb(src);
    }
    for(int i=0; i<SZ(scc_dag[u]); i++)
    {
        if(vis[scc_dag[u][i]]!=cas)
            dfs(scc_dag[u][i]);
    }
}


bool find_match(int u)
{
    if(vis[u]==cas) return false;
    vis[u]=cas;
    for(int i=0; i<SZ(matching_graph[u]); i++)
    {
        int v=matching_graph[u][i];
        if(matching[v]==-1)
        {
            matching[u]=v;
            matching[v]=u;
            return 1;
        }
    }

    for(int i=0; i<SZ(matching_graph[u]); i++)
    {
        int v=matching_graph[u][i];
        if(find_match(matching[v]))
        {
            matching[u]=v;
            matching[v]=u;
            return true;
        }
    }
    return false;
}

int main()
{
//#ifndef ONLINE_JUDGE
////    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif

    int t;
    sf(t);
    TEST_CASE(t)
    {
        int n,m;
        sff(n,m);
        allclear();
        for(int i=0; i<m; i++)
        {
            int a,b;
            sff(a,b);
            g[a].pb(b);
        }

        for(int i=1; i<=n; i++)
        {
            if(scc[i]==0)
                Tarjan_SCC(i);
        }
        for(int j=1; j<=n; j++)
        {
            for(int i=0; i<SZ(g[j]); i++)
            {
                int a=j;
                int b=g[j][i];
                a=scc[a];
                b=scc[b];
                if(a!=b)
                {
                    scc_dag[a].pb(b);
                }
            }
//            g[j].clear();
        }

        cas=0;

        for(int i=1; i<=scc_cnt; i++)
        {
            cas++;
            src=i;
            dfs(i);
        }

        int matching_count=0;

        for(int i=1; i<=scc_cnt; i++)
        {
            cas++;
            if(find_match(i))
                matching_count++;
        }

        int ans=scc_cnt-matching_count;

        PRINT_CASE;
        printf("%d\n",ans);



    }


    return 0;
}
