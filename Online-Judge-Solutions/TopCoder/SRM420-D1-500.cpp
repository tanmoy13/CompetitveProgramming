/*
    Author: Tanmoy Datta

    Solution Idea:
    ~~~~~~~~~~~~~~
        - In every state we have some RED card and some BLUE card.
        - We can chose any card with equal probability.
        - Let we have x RED card and Y BLUE card.
        - Then probability of choosing a RED card is PR = x/(x+y) and a BLUE card is PB = y/(x+y).
        - So if we chose a RED card the transition will be p1 = PR*(1+call(x-1,y)).
        - And if we chose a BLUE card then the transition will be p2 = PB*(call(x,y-1)-1).
        - In each state we can select a RED card or a BLUE card so expected value of state (x,y) is p1+p2.
        - We need to take maximum of 0.0 and p1+p2.
        - Another important thing is memory limit for this problem is 64 mb. So we can't afford a 2D matrix.
          So we have to use row swapping technique.

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

//double dp[5002][5002];
//
//double call(int r, int b)
//{
//    if(r==0 && b==0)
//        return 0;
//    double &ret=dp[r][b];
//    if(ret>-1.0) return ret;
//    double p=0,q=0;
//    if(r>0)
//    {
//        double up=r;
//        double down=r+b;
//        p=(up/down)*(1.0+call(r-1,b));
//    }
//    if(b>0)
//    {
//        double up=b;
//        double down=r+b;
//        q=(up/down)*(-1.0+call(r,b-1));
//    }
//    return ret=max(p+q,0.0);
//}
//
//
//void init(int r, int b)
//{
//    for(int i=0;i<r;i++)
//    {
//        for(int j=0;j<b;j++)
//            dp[i][j]=-5.0;
//    }
//}

double dp[2][5005];

class RedIsGood
{
public:
    double getProfit(int R, int B)
    {
        ms(dp,0.0);
        int cur=1,prev=0;
        for(int i=1; i<=R; i++)
        {
            for(int j=0; j<=B; j++)
            {
                double pr=((double)i)/((double)i+(double)j);
                double pb=((double)j)/((double)i+(double)j);
                double temp=pr*(1+dp[prev][j]);
                if(j)
                    temp+=pb*(dp[cur][j-1]-1);
                dp[cur][j]=max(0.0,temp);
            }
            swap(cur,prev);
        }
        return dp[prev][B];
    }
};
