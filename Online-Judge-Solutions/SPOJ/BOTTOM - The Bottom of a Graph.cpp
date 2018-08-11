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

#define mx 5004

vector<int>g[mx],rg[mx],scc_list[mx];
int scc_num[mx],outdegree[mx],scc;
bool vis[mx];
stack<int>st;

void allclear(int n)
{
    for(int i=0; i<=n; i++)
    {
        g[i].clear();
        rg[i].clear();
        scc_list[i].clear();
        scc_num[i]=outdegree[i]=vis[i]=0;
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
        if(!vis[v])
            dfs1(v);
    }
    st.push(u);
}

void dfs2(int u)
{
    vis[u]=1;
    scc_num[u]=scc;
    scc_list[scc].pb(u);
    for(int i=0; i<SZ(rg[u]); i++)
    {
        int v=rg[u][i];
        if(!vis[v])
            dfs2(v);
    }
}


int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);
    int n,m;

    while(sf(n) && n)
    {
        sf(m);

        allclear(n+2);

        for(int i=0; i<m; i++)
        {

            int a,b;
            sff(a,b);
            g[a].pb(b);
            rg[b].pb(a);
        }

        for(int i=1; i<=n; i++)
            if(!vis[i])
                dfs1(i);
        ms(vis,0);

        while(!st.empty())
        {
            int u=st.top();
            st.pop();
            if(!vis[u])
            {
                scc++;
                dfs2(u);
            }
        }


        for(int i=1;i<=n;i++)
        {
            int u=i;
            for(int j=0;j<SZ(g[u]);j++)
            {
                int v=g[u][j];
                if(scc_num[u]!=scc_num[v])
                    outdegree[scc_num[u]]++;
            }
        }

        vector<int>answer;

        for(int i=1;i<=scc;i++)
        {
            if(outdegree[i]==0)
            {
                for(int j=0;j<SZ(scc_list[i]);j++)
                    answer.pb(scc_list[i][j]);
            }
        }

        sort(all(answer));
        for(int i=0; i<SZ(answer); i++)
        {
            printf("%d",answer[i]);
            if(i<SZ(answer)-1)
                printf(" ");
        }
        printf("\n");

    }
    return 0;
}
