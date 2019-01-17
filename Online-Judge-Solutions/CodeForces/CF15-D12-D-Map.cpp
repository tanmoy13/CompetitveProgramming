/*
    Author: Tanmoy Datta

    Solution Idea:
    ~~~~~~~~~~~~~~
        - To solve this problem we need to calculate amount of the ground to remove from every sub rectangle.
        - After calculating this we can greedily chose the optimal rectangles by sorting them.
        - The main challenge is here is calculating the amount of the ground to remove.
        - To do this we need the minimum amount M in every sub-rectangle and summation of all the elements in this sub rectangle S.
        - Then the answer for this sub rectangle is (S-(a*b)*M).
        - We can calculate S using cumulative sum technique over 2D grid.
        - We an calculate M using sliding window over row and column.

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

#define mx 1005

ll grid[mx][mx];
ll minic[mx][mx];
ll mini[mx][mx];
ll sum[mx][mx];
bool vis[mx][mx];
ll n,m,a,b;

bool check(int x, int y)
{
    int p=x+a-1;
    int q=y+b-1;
    if(vis[x][y] || vis[p][q] || vis[x][q] || vis[p][y]) return false;
    return true;
}

void Set(int x, int y)
{
    int p=x+a-1;
    int q=y+b-1;
    for(int i=x; i<=p; i++)
    {
        for(int j=y; j<=q; j++)
        {
            vis[i][j]=1;
        }
    }
}

vector<pair<ll, pair<int,int> > > v,ans;

int main()
{
//#ifndef ONLINE_JUDGE
////    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif

    sffl(n,m);
    sffl(a,b);

    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=m; j++)
        {
            sfl(grid[i][j]);
            sum[i][j]=grid[i][j]+sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
        }
    }

//    for(int i=1;i<=n;i++)
//    {
//        for(int j=1;j<=m;j++)
//        {
//            printf("%5d",sum[i][j]);
//        }
//        printf("\n");
//    }


    deque<int>Q;

    for(int i=1; i<=n; i++)
    {
        Q.clear();
        for(int j=1; j<=m; j++)
        {
            while(!Q.empty() && grid[i][Q.back()]>grid[i][j])
                Q.pop_back();
            Q.push_back(j);
            while(Q.back()-Q.front()+1>b)
                Q.pop_front();
            int x=Q.front();
            if(j-b+1>0)
                minic[i][j-b+1]=grid[i][x];
        }
    }


//    for(int i=1; i<=n; i++)
//    {
//        for(int j=1; j<=m; j++)
//        {
//            printf("%5d",minic[i][j]);
//        }
//        printf("\n");
//    }
//
//    printf("\n\n");

    for(int j=1; j<=m; j++)
    {
        Q.clear();
        for(int i=1; i<=n; i++)
        {
            while(!Q.empty() && minic[Q.back()][j]>minic[i][j])
                Q.pop_back();
            Q.push_back(i);
            while(Q.back()-Q.front()+1>a)
                Q.pop_front();
            int x=Q.front();
            if(i-a+1>0)
                mini[i-a+1][j]=minic[x][j];
        }
    }


//    for(int i=1; i<=n; i++)
//    {
//        for(int j=1; j<=m; j++)
//        {
//            printf("%5d",mini[i][j]);
//        }
//        printf("\n");
//    }



    for(int i=1; i<=n-a+1; i++)
    {
        for(int j=1; j<=m-b+1; j++)
        {
            int x=i,y=j;
            int p=i+a-1,q=j+b-1;
            ll val=sum[p][q]-sum[x-1][q]-sum[p][y-1]+sum[x-1][y-1];
            ll total=(a*b)*mini[x][y];
            val=val-total;

            v.pb(MP(val,MP(x,y)));

        }
    }

    sort(all(v));



    for(int i=0;i<SZ(v);i++)
    {
        if(check(v[i].ss.ff,v[i].ss.ss))
        {
            ans.pb(v[i]);
            Set(v[i].ss.ff,v[i].ss.ss);
        }
    }

    printf("%d\n",SZ(ans));
    for(int i=0;i<SZ(ans);i++)
    {
        printf("%d %d %lld\n",ans[i].ss.ff,ans[i].ss.ss,ans[i].ff);
    }



    return 0;
}
