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

const int Size = 1000005; /// Maximum Text Length
const int NODE = 250005; /// Maximum Nodes
const int MXQ = 505; /// Maximum Patterns
const int MXL = 505; /// Maximum Length Of Pattern
const int MXCHR = 53; /// Maximum Characters

struct node
{
    int val;
    bool endmark;
    int next[MXCHR];
    int endCnt; /// Number of times the prefix match with text
    vector<int>endsList; /// List of patterns ends here
    void clear()
    {
        endmark=0;
        endCnt=0;
        ms(next,0);
        endsList.clear();
    }
} trie[NODE];

int get_name(char ch)
{
    if(ch>='A' && ch<='Z')
        return 26+(ch-'A');
    return ch-'a';
}

int root=0,nodeCnt=0; ///Root node and total node count of the trie tree

void insertTrie(string &str, int id)
{
    /// Add string str to the trie in general way
    int cur=root;
    for(int i=0; i<SZ(str); i++)
    {
        int a=get_name(str[i]);
        if(trie[cur].next[a]==0)
        {
            nodeCnt++;
            trie[cur].next[a]=nodeCnt;
//            trie[nodeCnt].val=a;
//            trie[nodeCnt].clear();
        }
        cur=trie[cur].next[a];
    }
//    trie[cur].endmark=1;
    trie[cur].endsList.pb(id);
}

vector<int>lvlnode; /// List of nodes sorted by level


char ss[Size];
int fail[NODE],par[NODE],level[NODE];


int go_to(int u, int name) ///Return the appropriate position for the char name
{
    while(u!=0 && trie[u].next[name]==0)
        u=fail[u];
    return trie[u].next[name];
}

void calcFailFunction() ///This bfs calculates failure function on trie tree
{
    queue<int>Q;
    Q.push(root);
    par[root]=root;
    level[root]=0;
    fail[root]=root;
    while(!Q.empty())
    {
        int u=Q.front();
        Q.pop();
        /// Add all the child to the queue:
        for(int i=0; i<MXCHR; i++)
        {
            int v=trie[u].next[i];
            if(v==0) continue;
            par[v]=u;
            level[v]=level[u]+1;

            /// Find fall back of s:
            fail[v]=go_to(fail[u],i);
            if(fail[v]==v) /// Self fall back not allowed
                fail[v]=0;
            if(level[v]==1) /// fail of first level nodes is always root
                fail[v]=0;
            Q.push(v);
        }

    }
}

ll ans[1005]; /// How many times i'th pattern matched

void match_text(string &str) /// Iterate through the whole text and find all the matchings
{
    int cur=root;
    for(int i=0; i<SZ(str); i++)
    {
        int a=get_name(str[i]);
        if(trie[cur].next[a]!=0)
            cur=trie[cur].next[a];
        else
            cur=go_to(fail[cur],a);
        if(trie[cur].endsList.size())
            lvlnode.pb(cur);
        trie[cur].endmark=1;
    }
}

void push_up()
{
    sort(all(lvlnode));
    UNIQUE(lvlnode);
    sort(all(lvlnode),[](int a, int b)
    {
        return level[a]<level[b];
    });

    /// The prefix of my fall back node matches with my suffix
    /// So every time i match with text, my fall back node also match

    for(int i=SZ(lvlnode)-1; i>=0; i--)
    {
        int u=lvlnode[i];
        if(trie[u].endmark)
            trie[fail[u]].endmark=1;
        for(int j=0; j<SZ(trie[u].endsList); j++)
        {
            int v=trie[u].endsList[j];
            ans[v]=trie[u].endmark;
        }
    }
}

void allclear()
{
    root=0;
    nodeCnt=0;
    trie[root].clear();
    lvlnode.clear();
    ms(ans,0);
}

int main()
{
//#ifndef ONLINE_JUDGE
////    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif

    scanf(" %s",ss);
    string text=string(ss);
    int q;
    sf(q);
    for(int i=0; i<q; i++)
    {
        scanf(" %s",ss);
        string str=string(ss);
        insertTrie(str,i);
    }

    calcFailFunction();
    match_text(text);
    push_up();
    for(int i=0; i<q; i++)
    {
        if(ans[i])
            printf("Y\n");
        else
            printf("N\n");
    }

    return 0;
}

