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
#define PRINT_CASE       printf("Case %d:\n",z)
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

typedef pair<int,pii > piii;

vector< piii > g1;

vector<int>g[50005],cost[50005];

int n,m;

int par[50004];

int find_par(int u)
{
    return par[u]=(par[u]==u)?u:find_par(par[u]);
}


int dis[50005],level[50005];

void dfs(int u, int cnt, int from)
{
    level[u]=cnt;
    par[u]=from;

    for(int i=0; i<SZ(g[u]); i++)
    {
        int v=g[u][i];

        if(level[v]==-1)
        {
            dis[v]=cost[u][i];
            dfs(v,cnt+1,u);
        }
    }

}

int sparse_par[50005][16];
int sparse_max[50005][16];

void build_table()
{

    ms(sparse_par,-1);

    for(int i=1; i<=n; i++)
        sparse_par[i][0]=par[i],sparse_max[i][0]=dis[i];

    for(int i=1; 1<<i <=n; i++)
    {
        for(int j=1; j<=n; j++)
            if(sparse_par[j][i-1]!=-1)
            {
                sparse_par[j][i]=sparse_par[sparse_par[j][i-1]][i-1];
                sparse_max[j][i]=max(sparse_max[j][i-1],sparse_max[sparse_par[j][i-1]][i-1]);
            }
    }


}

int query(int p, int q)
{
    int a=p,b=q;

    if(level[p]<level[q]) swap(p,q);

    int log=log2(level[p]);

    int ret=0;

    for(int i=log; i>=0; i--)
    {
        if(level[p]-(1<<i) >=level[q])
        {
            ret=max(ret,sparse_max[p][i]);
            p=sparse_par[p][i];
        }
    }

    if(p==q) return ret;

    for(int i=log; i>=0; i--)
        if(sparse_par[p][i]!=-1 && sparse_par[p][i]!=sparse_par[q][i])
        {
            ret=max(ret,max(sparse_max[p][i],sparse_max[q][i]));
            p=sparse_par[p][i],q=sparse_par[q][i];
        }
    ret=max(ret,max(dis[p],dis[q]));
    return ret;

}

int main()
{

    freopen("in.txt","r",stdin);
    ///freopen("out.txt","w",stdout);



    int t;
    sf(t);
    TEST_CASE(t)
    {

        g1.clear();

        sff(n,m);
        for(int i=0; i<m; i++)
        {
            int a,b,c;
            sfff(a,b,c);
            g1.pb(piii(c,pii(a,b)));
        }

        sort(all(g1));

//        reverse(all(g1));

        int cnt=0;

        for(int i=1; i<=n; i++) par[i]=i,g[i].clear(),cost[i].clear();

        for(int i=0; i<SZ(g1) && cnt<n-1; i++)
        {
            int a=g1[i].ss.ff;
            int b=g1[i].ss.ss;
            int c=g1[i].ff;
            int u=find_par(a);
            int v=find_par(b);

            if(u!=v)
            {
                par[v]=u;
                g[a].pb(b);
                g[b].pb(a);
                cost[a].pb(g1[i].ff);
                cost[b].pb(g1[i].ff);
                cnt++;
            }
        }


        ms(level,-1);
        dis[1]=0;

        dfs(1,0,1);

        build_table();

        int q;
        sf(q);
        PRINT_CASE;

        while(q--)
        {
            int a, b;
            sff(a,b);
            printf("%d\n",query(a,b));
        }



    }

    return 0;
}
