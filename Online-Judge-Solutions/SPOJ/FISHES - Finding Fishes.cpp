/*
	SPOJ FISHES
	Author: Tanmoy Datta

	Idea:
	- The first simplification is in the summation formula as follows
		  SUM { Xi * (V . Vi) }
		= SUM {V . Xi Vi}
		= V . SUM {Xi Vi}
	- As you can observe, Xi Vi is constant, so we can precalculate this vector by multiplying each vector by its Xi and adding them all,
	  let's name this vector "Combined vector"
	- Now the problem is reduced to the following: we need to find a subrectangle, where the dot product of its V with the combined vector is maximum
	- The second observation is that the dot product is equivalent to the sum of the same subrectangle with transformed values, where each value
	  is replaced with its corresponding value in the combined vector (try this on paper)
	- Now the problem is reduced to a standard max subrectangle sum in 2D grid, than can be solved in O(n ^ 3) using precalculations
	- We can easily find maximum subrectangle sum in 2D grid in o(n^4) but we can use sum optimization to reduce it in O(n^3)
	- First thing is we can calculate maximum sub-array sum in 1D array in O(n) complexity by using cumulative sum and subtract minimum value
      found so far before this current index. The answer is maximum of (cumulative_sum[i]-minimum_value_found_so_far) for every i.
    - Now at first we calculate cumulative sum of every column of 2D array.
    - Then we can fix two row value in this column cumulative sum array in O(n^2) and then we get a 1D array of column sum of between this two row.
    - Now we can calculate maximum sub array sum in this 1D array in O(n). So overall complexity is O(n^3)

    (Some part of this solution idea is taken from this url  https://github.com/yelghareeb/problem_solving/blob/master/SPOJ/SPOJ%20FISHES.cpp)
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

int r,c,h,t,k;

int grid[102][102];
int v[505];
ll csum[102][102];
ll csum1d[102];

int main()
{
//#ifndef ONLINE_JUDGE
//    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif

    int cas;
    sf(cas);
    TEST_CASE(cas)
    {
        scanf("%d %d %d %d %d",&r,&c,&h,&k,&t);

        for(int i=1; i<=r; i++)
        {
            for(int j=1; j<=c; j++)
            {
                sf(grid[i][j]);
            }
        }

        ms(v,0);

        for(int i=0; i<t; i++) ///Taking input vectors and combining them in one vector array v.
        {
            int x,a;
            sf(x);
            for(int j=1; j<=k; j++)
            {
                sf(a);
                a*=x;
                v[j]+=a;
            }
        }


        for(int i=1; i<=r; i++) ///Replacing each cell value of image by it's corresponding vector value
        {
            for(int j=1; j<=c; j++)
            {
                grid[i][j]=v[grid[i][j]];
            }
        }


        for(int j=1; j<=c; j++) ///Calculating cumulative sum for every column
        {
            csum[0][j]=0;
            for(int i=1; i<=r; i++)
            {
                csum[i][j]=csum[i-1][j]+grid[i][j];
            }
        }


        ll ans=LONG_MIN;

        for(int i=1; i<=r; i++)   ///Finding 2D rectangle sum in O(n^3)
        {
            for(int j=i; j<=r; j++)
            {
                ll mini=0;
                for(int k=1; k<=c; k++)
                {
                    csum1d[k]=csum[j][k]-csum[i-1][k];
                    csum1d[k]+=csum1d[k-1];
                    ans=max(ans,csum1d[k]-mini);
                    mini=min(mini,csum1d[k]);
                }
            }
        }

        printf("Case #%d:\n%lld\n",z,ans+h);

    }

    return 0;
}
