/*
    Author : Tanmoy Datta

    Solution Idea:
    ~~~~~~~~~~~~~~
        - This problem can be solved using 2 SAT but the hard part is formulate the problem in 2 SAT.
        - Let we want to apply 2-SAT on the bench where the groom seated. In other words it's the opposite bench for the answer.
        - Relationship between every couple on this bench is XOR Clause because either husband or wife can sit here not both.
        - Relationship between the pair with adult relationship is NAND Clause. Because only the both can't be seated on this bench.
          But No one of a adult pair and single one of pair is allowed. So we can perform NAND clause on pair a,b using OR Clause.
          NAND_Clause(a,b) = OR_Clause(-a,-b)
        - The is groom must true for this bench. As he must seat here. So we need to apply must true on him.
        - Finally if we take the opposite of this satisfied set then we will get our answer.
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

const int NODE = 205; /// Maximum no of node (0 based indexing)

vector<int>g[NODE];

int getNode(int x) ///Convert a choice to node
{
    int p=abs(x);
    p=(p-1)*2;
    if(x<0) p^=1;
    return p;
}

int getNodeVal(int x) ///Convert a node to choice
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


///Always pass getNode() value to the folloing function
///For example if we want to mustTrue 5 then the call will be mustTrue(getNode(5))

void mustTrue (int a)   /// A is True
{
    g[a^1].pb(a);
}

void xorClause(int a, int b)   /// A ^ B clause
{
    //!a->b !b->a a->!b b->!a
    g[a^1].pb(b);
    g[a].pb(b^1);
    g[b^1].pb (a);
    g[b].pb (a^1);
}

void orClause (int a, int b)   /// A || B clause
{
    //!a->b !b->a
    g[a^1].pb ( b );
    g[b^1].pb ( a );
}

void andClause (int a, int b)   /// A ^ B clause
{
    mustTrue(a);
    mustTrue(b);
}

/// Out of all possible option, at most one is true
void atMostOneClause ( int a[], int n, int flag)
{
    if ( flag == 0 )   /// At most one can be false
    {
        for(int i = 0; i<n; i++)
        {
            a[i] = a[i] ^ 1;
        }
    }
    for(int i = 0; i<n; i++)
    {
        for(int j = i+1; j<n; j++)
        {
            orClause( a[i] ^ 1, a[j] ^ 1 ); /// !a || !b both being true not allowed
        }
    }
}


///SCC variables
int disc[NODE],low[NODE],Time, scc_count;
int component[NODE];
stack<int>scc;
bool vis[NODE];

///2-SAT variables
deque<int>sat;
int isSAT[NODE];

void allclear()
{
    for(int i=0; i<NODE; i++)
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
//    vis[u]=1;
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
    while(!sat.empty()) ///Assigning valid values to candidates
    {
        int x=sat.front();
        sat.pop_front();
        if(isSAT[x]==-1)
        {
            isSAT[x]=1;
            x=getNode(-getNodeVal(x)); ///Getting opposite value
            isSAT[x]=0;
        }
    }

    ///Checking whether satisfiability is possible or not
    bool check=1;
    for(int i=1; i<=n && check; i++)
    {
        check=(component[getNode(i)]!=component[getNode(-i)]);
    }
    return check;
}

int toInt(string &str)
{
    stringstream ss;
    ss<<str;
    int ret;
    ss>>ret;
    return ret;
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


    int n,m;
    while(cin>>n>>m)
    {
        if(n==0 && m==0) break;
        allclear();
        for(int i=0; i<m; i++)
        {
            string s1,s2;
            cin>>s1>>s2;
            char ch1,ch2;
            int a,b;
            ch1=s1.back();
            s1.pop_back();
            ch2=s2.back();
            s2.pop_back();
            a=toInt(s1);
            b=toInt(s2);
            a++;
            b++;
            if(ch1=='w')
                a+=n;
            if(ch2=='w')
                b+=n;
            orClause(getNode(-a),getNode(-b));
        }

        mustTrue(getNode(1));

        for(int i=1; i<=n; i++)
            xorClause(getNode(i),getNode(n+i));

        for(int i=1; i<=2*n; i++)
        {
            int x=getNode(i);
            if(disc[x]==0)
                tarjan_SCC(x);
            x=getNode(-i);
            if(disc[x]==0)
                tarjan_SCC(x);
        }

//        D(scc_count);
//        for(int i=1; i<=2*n; i++)
//            {
//                int x=getNode(i);
//                DD(x,component[x]);
//                x=getNode(-i);
//                DD(x,component[x]);
//            }

        bool check=checkSAT(2*n);
        vector<int>v;
        for(int i=1; i<=2*n; i++)
        {
            int x=getNode(i);
            if(isSAT[x]==0)
                v.pb(i);
        }

        if(check)
        {
            for(int i=0; i<SZ(v); i++)
            {
                int a=v[i];
                if(a<=n)
                {
                    a--;
                    printf("%dh",a);
                }
                else
                {
                    a-=n;
                    a--;
                    if(a==0) continue;
                    printf("%dw",a);
                }
                if(i!=SZ(v)-1)
                    printf(" ");
            }
            printf("\n");
        }
        else
            printf("bad luck\n");

    }

    return 0;
}
