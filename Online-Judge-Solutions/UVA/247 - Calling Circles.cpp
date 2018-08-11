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

#define mx 50

int n,m;
map<string,int>mp1;
map<int,string>mp2;

vector<int>g[mx],scc;
int h[mx],low[mx],dfsnum;
bool visited[mx];
vector<string>ans;


void allclear()
{
    mp1.clear();
    mp2.clear();
    scc.clear();
    for(int i=0; i<mx; i++)
    {
        g[i].clear();
        h[i]=0;
        low[i]=0;
        visited[i]=0;
    }
    dfsnum=0;
    ans.clear();
}

void dfs(int u)
{
    h[u]=low[u]=++dfsnum;
    visited[u]=1;
    scc.pb(u);

    for(int i=0; i<SZ(g[u]); i++)
    {
        int v=g[u][i];
        if(h[v]==0)
            dfs(v);
        if(visited[v])
            low[u]=min(low[u],low[v]);
    }

    if(low[u]==h[u])
    {
        string str;
        while(1)
        {
            int v=scc.back();
            scc.pop_back();
            str+=mp2[v];
            visited[v]=0;
            if(u==v)
                break;
            else
                str+=", ";
        }
        ans.pb(str);
    }
}

int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);
    CIN;
    int z=0;
    while(cin>>n>>m && (n||m))
    {
        if(z)
            cout<<endl;
        allclear();
        z++;
        int cnt=1;
        while(m--)
        {
            string s1,s2;
            cin>>s1>>s2;
            int a,b;
            if(mp1[s1]==0)
            {
                mp1[s1]=cnt;
                mp2[cnt]=s1;
                cnt++;
            }
            if(mp1[s2]==0)
            {
                mp1[s2]=cnt;
                mp2[cnt]=s2;
                cnt++;
            }
            a=mp1[s1];
            b=mp1[s2];
            g[a].pb(b);
        }

        cout<<"Calling circles for data set "<<z<<":"<<endl;
        for(int i=1; i<=n; i++)
        {
            if(h[i]==0)
                dfs(i);
        }
//        sort(all(ans));
        for(int i=0; i<SZ(ans); i++)
            cout<<ans[i]<<endl;
    }
    return 0;
}
