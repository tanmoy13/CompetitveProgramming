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

#define mx 100005

int n,q;
vector<int>g[mx],cost[mx];

int par[mx], dis[mx], level[mx];

int sparse_par[mx][20],sparse_max[mx][20], sparse_min[mx][20];

void dfs(int u, int cnt, int from)
{
    par[u]=from;
    level[u]=cnt;

    for(int i=0;i<SZ(g[u]);i++)
    {
        int v=g[u][i];
        if(v!=from)
        {
            dis[v]=cost[u][i];
            dfs(v,cnt+1,u);
        }
    }
}

void build_table()
{
    ms(sparse_par,-1);

    sparse_par[1][0]=par[1];
    sparse_min[1][0]=INT_MAX;
    sparse_max[1][0]=0;

    for(int i=2;i<=n;i++)
    {
        sparse_par[i][0]=par[i];
        sparse_min[i][0]=dis[i];
        sparse_max[i][0]=dis[i];
    }

    for(int j=1;1<<j<n;j++)
    {
        for(int i=1;i<=n;i++)
        {
            if(sparse_par[i][j-1]!=-1)
            {
//                D(i);
//                D(j);

                sparse_par[i][j]=sparse_par[sparse_par[i][j-1]][j-1];
                sparse_max[i][j]=max(sparse_max[i][j-1],sparse_max[sparse_par[i][j-1]][j-1]);
                sparse_min[i][j]=min(sparse_min[i][j-1],sparse_min[sparse_par[i][j-1]][j-1]);
//                D(sparse_par[i][j]);
//                D(sparse_max[i][j]);
//                D(sparse_min[i][j]);
            }
        }
    }

}

pii query(int p, int q)
{
    if(level[p]<level[q]) swap(p,q);

    int log=log2(level[p]);

    int maxi=0,mini=INT_MAX;

    for(int i=log;i>=0;i--)
    {
        if(level[p]-(1<<i)>=level[q])
        {
            maxi=max(maxi,sparse_max[p][i]);
            mini=min(mini,sparse_min[p][i]);

            p=sparse_par[p][i];

        }
    }

    if(p==q)
    {
        return pii(mini,maxi);
    }

    for(int i=log;i>=0;i--)
    {
        if(sparse_par[p][i]!=-1 && sparse_par[p][i]!=sparse_par[q][i])
        {
            maxi=max(maxi,max(sparse_max[p][i],sparse_max[q][i]));
            mini=min(mini,min(sparse_min[p][i],sparse_min[q][i]));
            p=sparse_par[p][i];
            q=sparse_par[q][i];
        }
    }

    maxi=max(maxi,max(dis[p],dis[q]));
    mini=min(mini,min(dis[p],dis[q]));

    return pii(mini,maxi);


}

int main()
{

//    freopen("in.txt","r",stdin);
    ///freopen("out.txt","w",stdout);

    int t;
    sf(t);
    TEST_CASE(t)
    {
        sf(n);

        for(int i=1;i<n;i++)
        {
            int a,b,c;
            sfff(a,b,c);
            g[a].pb(b);
            g[b].pb(a);
            cost[a].pb(c);
            cost[b].pb(c);
        }

        dis[1]=0;
        dfs(1,0,1);

        build_table();

        sf(q);

        PRINT_CASE;

        while(q--)
        {
            int a,b;
            sff(a,b);
            pii ans=query(a,b);
            printf("%d %d\n",ans.ff,ans.ss);

        }

        for(int i=0;i<=n;i++)
        {
            g[i].clear();
            cost[i].clear();
        }


    }

    return 0;
}
