
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

#define mx 200005

vector<int>g[mx];
pii times[mx];
int dfsnum;
int parent[mx],level[mx],node_cnt[2*mx];

void dfs(int u, int p)
{
    times[u].ff=++dfsnum;
    parent[u]=p;
    for(int i=0; i<SZ(g[u]); i++)
    {
        int v=g[u][i];
        if(v==p) continue;
        level[v]=level[u]+1;
        dfs(v,u);
    }
    times[u].ss=++dfsnum;
}

int dp[mx][21];

int func_lca(int idx, int p)
{
    if(p==0)
    {
        return dp[idx][p]=parent[idx];
    }
    int &ret=dp[idx][p];
    if(ret!=-1) return ret;
    int u=func_lca(idx,p-1);
    ret=func_lca(u,p-1);
    return ret;
}


int lca_query(int p, int q)
{
    if(level[q]>level[p]) swap(p,q);
    for(int i=20;i>=0;i--)
    {
        int a=func_lca(p,i);
        if(level[a]>=level[q])
            p=a;
    }

    if(p==q) return p;

    for(int i=20;i>=0;i--)
    {
        int a=func_lca(p,i);
        int b=func_lca(q,i);
        if(a!=b)
        {
            p=a;
            q=b;
        }
    }

    return parent[p];
}


int tree[31][2*mx];

void update(int id, int idx, int val)
{
    for(;idx<=dfsnum && idx;idx+=idx&-idx)
        tree[id][idx]+=val;
}

int query(int id, int idx)
{
    int ret=0;
    for(;idx;idx-=idx&-idx)
        ret+=tree[id][idx];
    return ret;
}




int main()
{
//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);

    int n;
    sf(n);
    for(int i=1; i<n; i++)
    {
        int a,b;
        sff(a,b);
        g[a].pb(b);
        g[b].pb(a);
    }

    dfs(0,0);

    int qq;
    sf(qq);

    for(int i=0;i<n;i++)
    {
        node_cnt[times[i].ff]=1;
        node_cnt[times[i].ss]=-1;
    }

    partial_sum(node_cnt,node_cnt+(2*mx),node_cnt);


    ms(dp,-1);

    while(qq--)
    {
        int a,b,c;
        sfff(a,b,c);
        if(a==1)
        {
            update(c,times[b].ff,1);
            update(c,times[b].ss,-1);
        }
        else
        {
            if(times[b].ff>times[c].ff)
                swap(b,c);

            bool ans=0;

            int lca=lca_query(b,c);

            for(int i=1;i<=30;i++)
            {
                int x=query(i,times[c].ff);
                int y=query(i,times[b].ff);
                int z=query(i,times[lca].ff);
                x=(x+y-(2*z));
                x+=query(i,times[lca].ff)-query(i,times[lca].ff-1);
                y=node_cnt[times[b].ff]+node_cnt[times[c].ff]-(2*node_cnt[times[lca].ff])+(node_cnt[times[lca].ff]-node_cnt[times[lca].ff-1]);
                if(x)
                {
                    if(x==y)
                        ans=1;
                    break;
                }
            }


            if(ans==0)
                printf("NO\n");
            else
                printf("YES\n");

        }
    }
    return 0;
}



