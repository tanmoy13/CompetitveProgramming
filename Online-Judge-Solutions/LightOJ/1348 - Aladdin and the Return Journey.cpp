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
#define LINE_PRINT_CASE  printf("Case %d:\n",z)
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


inline void inp( int &n )
{
    n=0;
    int ch=getchar_unlocked();
    int sign=1;
    while( ch < '0' || ch > '9' )
    {
        if(ch=='-')sign=-1;
        ch=getchar_unlocked();
    }
    while(  ch >= '0' && ch <= '9' )
        n = (n<<3)+(n<<1) + ch-'0', ch=getchar_unlocked();
    n=n*sign;
}


#define mx 30005

vector<int>g[mx];
int gini[mx];
int n;

int par[mx],level[mx], max_subtree[mx];
int sparse_par[mx][17];

int chain_head[mx],chain_indx[mx],chain_size[mx];
int node_serial[mx],serial_node[mx];
int chain_no,indx;

ll tree[mx];

int dfs(int u, int from, int cnt)
{
    sparse_par[u][0]=from;
    level[u]=cnt;
    int node=-1, maxi=0, total=1;
    for(int i=0; i<SZ(g[u]); i++)
    {
        int v=g[u][i];
        if(v!=from)
        {
            int temp=dfs(v,u,cnt+1);
            total+=temp;
            if(temp>maxi)
            {
                maxi=temp;
                node=v;
            }
        }
    }

    max_subtree[u]=node;
    return total;
}


void build_table(int n)
{
    for(int j=1; 1<<j<=n; j++)
    {
        for(int i=0; i<n; i++)
        {
            sparse_par[i][j]=sparse_par[sparse_par[i][j-1]][j-1];
        }
    }
}

int LCA_query(int p, int q)
{
    if(level[p]<=level[q]) swap(p,q);
    int log=log2(level[p]);

    for(int i=log; i>=0; i--)
    {
        if(level[p]-(1<<i)>=level[q])
            p=sparse_par[p][i];
    }
    if(p==q) return p;

    for(int i=log; i>=0; i--)
    {
        if(sparse_par[p][i]!=sparse_par[q][i])
        {
            p=sparse_par[p][i];
            q=sparse_par[q][i];
        }
    }

    return sparse_par[p][0];
}


void HLD(int u, int sz)
{
    if(chain_head[chain_no]==-1)
        chain_head[chain_no]=u;
    chain_indx[u]=chain_no;
    chain_size[chain_no]=sz;

    node_serial[u]=indx;
    serial_node[indx]=u;
    indx++;
    if(max_subtree[u]==-1) return ;

    HLD(max_subtree[u],sz+1);

    for(int i=0; i<SZ(g[u]); i++)
    {
        int v=g[u][i];
        if(v!=sparse_par[u][0] && v!=max_subtree[u])
        {
            chain_no++;
            HLD(v,1);
        }
    }
}


void update(int idx, int val)
{
    while(idx<=indx)
    {
        tree[idx]+=val;
        idx+=(idx&-idx);
    }
}

ll query(int a, int b)
{
    ll ret=0;
    ll ret2=0;
    while(b)
    {
        ret+=tree[b];
        b-=(b & -b);
    }
    a--;
    while(a)
    {
        ret2+=tree[a];
        a-=(a&-a);
    }
    return ret-ret2;
}


ll query_tree(int a, int b)
{
    ll ret=0;
    while(chain_indx[a]!=chain_indx[b])
    {
        ret+=query(node_serial[chain_head[chain_indx[a]]],node_serial[a]);
        a=sparse_par[chain_head[chain_indx[a]]][0];
    }
    ret+=query(node_serial[b],node_serial[a]);
    return ret;
}

void update_tree(int a, int val)
{
    update(node_serial[a],gini[a]*-1);
    update(node_serial[a],val);
    gini[a]=val;
}

inline void allclear(int n)
{
    chain_no=1;
    indx=1;
    for(int i=0; i<=n; i++)
    {
        g[i].clear();
    }

    ms(tree,0);
    ms(chain_head,-1);
}



int main()
{

//    freopen("in.txt","r",stdin);
    ///freopen("out.txt","w",stdout);

    int t;
    scanf("%d",&t);
    TEST_CASE(t)
    {
        scanf("%d",&n);
        for(int i=0; i<n; i++) scanf("%d",&gini[i]);
        allclear(n+2);
        for(int i=1; i<n; i++)
        {
            int a,b;
            scanf("%d %d",&a,&b);
            g[a].pb(b);
            g[b].pb(a);
        }

        dfs(0,0,1);
        build_table(n);
        HLD(0,1);

        for(int i=1; i<indx; i++)
        {
            update(i,gini[serial_node[i]]);
        }


        int m;
        scanf("%d",&m);
        LINE_PRINT_CASE;
        while(m--)
        {
            int a,b;
            scanf("%d",&a);
            if(a==0)
            {
                scanf("%d %d",&a,&b);
                int lca=LCA_query(a,b);
                ll ans=query_tree(a,lca);
                ans+=query_tree(b,lca);
                ans-=gini[lca];
                printf("%lld\n",ans);
            }
            else
            {
                scanf("%d %d",&a,&b);
                update_tree(a,b);
            }
        }
    }


    return 0;
}
