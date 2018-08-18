/*
    Author: Tanmoy Datta

    Solution Idea:

        - This is a straight forward Aho-Chorasick problem. But challenging part is the update and query part.
          In as usual way in Aho-Chorasick will cost a TLE.

        - For this we need to maintain some additional data structure for efficient update and query.

        - At first we need build aho-chorasic tree from the input patterns.

        - Now we need to build a new tree from the aho-chorasick tree. In this tree for every node u we have
          a directed edge from fail[u] to u. We can see that for every u and v in the new tree where v is in
          subtree of u, a string starting from the root to u in the aho-chorasick tree must be a suffix of the string
          starting from root to v in aho-chorasick tree.

        - After building the new tree we need to calculate start time and end time of every node using euler tour
          on the new tree.

        - Now for every node u such that a pattern ends in u, we need to add 1 to all nodes which are in subtree of u
          in the new tree. We can do it using a binary indexed tree and the start time and end time.

        - Now for every - operation we need to add -1 in the starting_time of u and add +1 to ending_time+1 position in BIT.
          and the reverse for + operation.

        - For every ? operation we need to traverse the aho-chorasick tree and add the value of the current node from BIT.
          answer for a single ? operation is the summation of all traversed aho-chorasick node value in BIT.

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


/*
    - Always remember to execute trie[nodeCnt].clear(); in multiple test case problem
      In insertTrie function
    - Function call order in main function
            insertTrie(str,i);
            calcFailFunction();
            match_text(text);
            push_up();
*/

const int Size = 1000006; /// Maximum Text Length
const int NODE = 1000006; /// Maximum Nodes
const int MXQ = 100005; /// Maximum Patterns
const int MXL = 100005; /// Maximum Length Of Pattern
const int MXCHR = 26; /// Maximum Characters

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

vector<int>g[NODE];

int get_name(char ch)
{
    if(ch>='a' && ch<='z')
        return ch-'a';
    if(ch>='A' && ch<='Z')
        return 26+(ch-'A');
}

int root=0,nodeCnt=0; ///Root node and total node count of the trie tree
int endNode[NODE];


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
            trie[nodeCnt].clear();
            trie[nodeCnt].val=a;
        }
        cur=trie[cur].next[a];
    }
    trie[cur].endmark=1;
    trie[cur].endsList.pb(id);
    endNode[id]=cur;
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
        lvlnode.pb(u);
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
            g[fail[v]].pb(v);
            Q.push(v);
        }
    }
}



pii timing[NODE];

int Time=0;

void dfs(int u)
{
    timing[u].ff=++Time;
    for(int i=0; i<SZ(g[u]); i++)
    {
        int v=g[u][i];
        dfs(v);
    }
    timing[u].ss=Time;
}

ll tree[NODE];

void update(int idx, ll val)
{
    for(int i=idx; i<NODE; i+=(i & -i))
        tree[i]+=val;
}

ll query(int idx)
{
    ll ret=0;
    for(int i=idx; i>0; i-=(i&-i))
        ret+=tree[i];
    return ret;
}



//ll ans[MXQ]; /// How many times i'th pattern matched

ll match_text(string &str) /// Iterate through the whole text and find all the matchings
{
    ll ret=0;
    int cur=root;
    for(int i=0; i<SZ(str); i++)
    {
        int a=get_name(str[i]);
        if(trie[cur].next[a]!=0)
            cur=trie[cur].next[a];
        else
            cur=go_to(fail[cur],a);
        ret+=query(timing[cur].ff);
    }
    return ret;
}

//bool cmp(int a, int b)
//{
//    return level[a]<level[b];
//}
//
//void push_up()
//{
//
//    /// The prefix of my fall back node matches with my suffix
//    /// So every time i match with text, my fall back node also match
//
//    for(int i=SZ(lvlnode)-1; i>=0; i--)
//    {
//        int u=lvlnode[i];
//        if(trie[u].endCnt)
//            trie[fail[u]].endCnt+=trie[u].endCnt;
//        for(int j=0; j<SZ(trie[u].endsList); j++)
//        {
//            int v=trie[u].endsList[j];
//            ans[v]+=trie[u].endCnt;
//        }
//    }
//}

//void allclear()
//{
//    root=0;
//    nodeCnt=0;
//    trie[root].clear();
//    lvlnode.clear();
//    ms(ans,0);
//}

char s1[Size];

bool isPresent[NODE];

int main()
{
//#ifndef ONLINE_JUDGE
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
//#endif

    int n,m;
    sff(n,m);
    string str;
    for(int i=1; i<=m; i++)
    {
        scanf(" %s",s1);
        str=string(s1);
        insertTrie(str,i);
    }

    calcFailFunction();

    dfs(0);

    for(int i=1;i<=m;i++)
    {
        isPresent[i]=1;
        int a=endNode[i];
        update(timing[a].ff,1);
        update(timing[a].ss+1,-1);
    }

    while(n--)
    {
        char ch;
        scanf(" %c",&ch);
        if(ch=='?')
        {
            scanf(" %s",s1);
            str=string(s1);
            ll ans=match_text(str);
            printf("%lld\n",ans);
        }
        else if(ch=='-')
        {
            int a;
            sf(a);
            if(isPresent[a]==1)
            {
                isPresent[a]=0;
                a=endNode[a];
                update(timing[a].ff,-1);
                update(timing[a].ss+1,1);
            }
        }
        else if(ch=='+')
        {
            int a;
            sf(a);
            if(isPresent[a]==0)
            {
                isPresent[a]=1;
                a=endNode[a];
                update(timing[a].ff,1);
                update(timing[a].ss+1,-1);
            }
        }
    }


    return 0;
}
