/**
    Author: Tanmoy Datta

    Solution Idea:
    ~~~~~~~~~~~~~~
        - Without the bandwidth condition this is straight forward directed minimum spanning tree problem.
        - So we can binary search over the bandwidths and then consider all the edges whose bandwidth is greater than binary search mid.
        - If we can get a minimum spanning tree using all the edges whose bandwidth is greater than mid then we can increase our range
          otherwise we can decrease it.
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

struct Edge
{
    int u, v, w, bandwidth;

    Edge() {}
    Edge(int a, int b, int c, int d)
    {
        u = a, v = b, w = c, bandwidth=d;
    }
};

/// Directed minimum spanning tree in O(n * m)
/// Constructs a rooted tree of minimum total weight from the root node
/// Returns -1 if no solution from root

int directed_MST(int n, vector <Edge> E, int root, int mini)  /// hash = 547539
{
    const int INF = (1 << 30) - 30;

    int i, j, k, l, x, y, res = 0;
    vector <int> cost(n), parent(n), label(n), comp(n);

    for (;;)
    {
        for (i = 0; i < n; i++) cost[i] = INF;
        for (auto e: E)
        {
            if(e.bandwidth<mini) continue;
            if (e.u != e.v && cost[e.v] > e.w)
            {
                cost[e.v] = e.w;
                parent[e.v] = e.u;
            }
        }

        cost[root] = 0;
        for (i = 0; i < n && cost[i] != INF; i++) {};
        if (i != n) return -1; /// No solution

        for (i = 0, k = 0; i < n; i++) res += cost[i];
        for (i = 0; i < n; i++) label[i] = comp[i] = -1;

        for (i = 0; i < n; i++)
        {
            for (x = i; x != root && comp[x] == -1; x = parent[x]) comp[x] = i;
            if (x != root && comp[x] == i)
            {
                for (k++; label[x] == -1; x = parent[x]) label[x] = k - 1;
            }
        }

        if (k == 0) break;
        for (i = 0; i < n; i++)
        {
            if (label[i] == -1) label[i] = k++;
        }

        for (auto &e: E)
        {
            x = label[e.u], y = label[e.v];
            if (x != y) e.w -= cost[e.v];
            e.u = x, e.v = y;
        }
        root = label[root], n = k;
    }
    return res;
}

int main()
{
//#ifndef ONLINE_JUDGE
//    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif

    int t;
    sf(t);
    TEST_CASE(t)
    {
        int n,m,c;
        sfff(n,m,c);

        vector<Edge> E;

        vector<int>v;


        for(int i=0;i<m;i++)
        {
            int a,b,c,d;
            sff(a,b);
            sff(c,d);
            E.pb(Edge(a,b,d,c));
            v.pb(c);
        }

        sort(all(v));

        UNIQUE(v);


        int lo=0,hi=SZ(v)-1;

        int ans=-1;

        while(lo<=hi)
        {
            int mid=(lo+hi)/2;
            int mini=v[mid];
            int temp=directed_MST(n,E,0,mini);
            if(temp==-1)
                temp=INT_MAX;

            if(temp<=c)
            {
                lo=mid+1;
                ans=v[mid];
            }
            else
                hi=mid-1;

        }

        PRINT_CASE;
        if(ans==-1)
            printf("impossible\n");
        else
            printf("%d kbps\n",ans);

    }

    return 0;
}
