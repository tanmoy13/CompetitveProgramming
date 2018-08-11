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

#define mx 2005
vector<int>g[mx],rg[mx],scc_graph[mx];
vector<pii>edge_2_way;
bool vis[mx];
int scc_num[mx],scc;
stack<int>st;

void allclear(int n)
{
    for(int i=0;i<=n;i++)
    {
        g[i].clear();
        rg[i].clear();
        scc_graph[i].clear();
        vis[i]=scc_num[i]=0;
    }
    edge_2_way.clear();
    scc=0;
    while(!st.empty())
        st.pop();
}

void dfs1(int u)
{
    vis[u]=1;
    for(int i=0;i<SZ(g[u]);i++)
    {
        int v=g[u][i];
        if(vis[v]==0)
            dfs1(v);
    }
    st.push(u);
}

void dfs2(int u)
{
    scc_num[u]=scc;
    for(int i=0;i<SZ(rg[u]);i++)
    {
        int v=rg[u][i];
        if(scc_num[v]==0)
            dfs2(v);
    }
}

int dfs3(int u)
{
    vis[u]=1;
    int child=1;
    for(int i=0;i<SZ(scc_graph[u]);i++)
    {
        int v=scc_graph[u][i];
        if(!vis[v])
            child+=dfs3(v);
    }
    return child;
}

//void dfs4(int u)
//{
//    vis[u]=1;
//    for(int i=0;i<SZ(scc_graph[u]);i++)
//    {
//        int v=scc_graph[u][i];
//        if(!vis[v])
//            dfs4(v);
//    }
//}

int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);
    int n,m;
    while(sff(n,m) && (n||m))
    {
        allclear(n+2);
        for(int i=0;i<m;i++)
        {
            int a,b,c;
            sfff(a,b,c);
            if(c==2)
                edge_2_way.pb(pii(a,b));
            else
               {
                 g[a].pb(b);
                 rg[b].pb(a);
               }
        }

        for(int i=1;i<=n;i++)
        {
            if(vis[i]==0)
                dfs1(i);
        }
        ms(vis,0);
        while(!st.empty())
        {
            int u=st.top();
            st.pop();
            if(scc_num[u]==0)
            {
                scc++;
                dfs2(u);
            }

        }

        for(int i=1;i<=n;i++)
        {
            for(int j=0;j<SZ(g[i]);j++)
            {
                int v=g[i][j];
                if(scc_num[i]!=scc_num[v])
                {
                    int a=scc_num[i];
                    int b=scc_num[v];
                    scc_graph[a].pb(b);
                }
            }
        }

        for(int i=0;i<SZ(edge_2_way);i++)
        {
            int a=edge_2_way[i].ff;
            int b=edge_2_way[i].ss;
            if(scc_num[a]!=scc_num[b])
            {
                a=scc_num[a];
                b=scc_num[b];
                scc_graph[a].pb(b);
                scc_graph[b].pb(a);
            }
        }

        ms(vis,0);
        bool ans=1;
        for(int i=1;i<=scc && ans;i++)
        {
            ms(vis,0);
            int a=dfs3(i);
            ans&=(a==scc);
        }

        if(ans)
            pf("1\n");
        else
            pf("0\n");

    }
    return 0;
}


//Alternate Easy Solution

/*

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

#define mx 2005
vector<int>g[mx],rg[mx];
bool vis[mx];
int scc;
stack<int>st;

void allclear(int n)
{
    for(int i=0; i<=n; i++)
    {
        g[i].clear();
        rg[i].clear();
        vis[i]=0;
    }
    scc=0;
    while(!st.empty())
        st.pop();
}

void dfs1(int u)
{
    vis[u]=1;
    for(int i=0; i<SZ(g[u]); i++)
    {
        int v=g[u][i];
        if(vis[v]==0)
            dfs1(v);
    }
    st.push(u);
}

void dfs2(int u)
{
    vis[u]=1;
    for(int i=0; i<SZ(rg[u]); i++)
    {
        int v=rg[u][i];
        if(vis[v]==0)
            dfs2(v);
    }
}



int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);
    int n,m;
    while(sff(n,m) && (n||m))
    {
        allclear(n+2);
        for(int i=0; i<m; i++)
        {
            int a,b,c;
            sfff(a,b,c);
            if(c==2)
            {
                g[b].pb(a);
                rg[a].pb(b);
            }
            g[a].pb(b);
            rg[b].pb(a);
        }

        for(int i=1; i<=n; i++)
        {
            if(vis[i]==0)
                dfs1(i);
        }
        ms(vis,0);
        while(!st.empty())
        {
            int u=st.top();
            st.pop();
            if(vis[u]==0)
            {
                scc++;
                dfs2(u);
            }

        }

        if(scc==1)
            pf("1\n");
        else
            pf("0\n");

    }
    return 0;
}

*/

