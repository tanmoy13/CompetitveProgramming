/*
    Author: Tanmoy Datta

    Solution Idea:
    ---------------
        This kind of problem can be solved by Extended Euclidean Algorithm.
           If an equation of straight line is given like Ax + By = C, then
           extended euclidean algorithm can find a solution of it using
           diophantine equation. From this concept, all the solution in a
           certain range can also be counted and be found.
           Let  ax1 + by1 = c
                ax1 + a*b*T/g - a*b*T/g + by1 = c, where g = GCD get using EGCD
                a (x1 + b*T/g) + b (y1 + a*T/g) = c
           Comparing this equation with the previous, we get,
                x = x1+(b*T/g)
                y = y1-(a*T/g)
            Now, x>= min_x
                x1+(b*T/g) >= min_x
                (b*T/g) >= min_x - x1
                T >= (min_x-x1)* g/b
            On the other hand, y >= min_y
                y1-(a*T/g) >= min_y
                y1 - min_y >= (a*T/g)
                T <= (y1-min_y)* g/a
            Combining these two, we get
                (min_x-x1)* g/b <= T <= (y1-min_y)* g/a
            Again, x<= max_x
                x1+(b*T/g) <= max_x
                (b*T/g) <= max_x - x1
                T <= (max_x-x1)* g/b
            On the other hand, y <= max_y
                y1-(a*T/g) <= max_y
                y1 - max_y <= (a*T/g)
                T >= (y1-max_y)* g/a
            Combining these two, we get
                (y1-max_y)* g/a <= T <= (max_x-x1)* g/b
            So, the solution of our problem T would be:
            max((min_x-x1)* g/b,  (y1-max_y)* g/a ) <= T
                                <= min( (y1-min_y)* g/a , (max_x-x1)* g/b)

        * This solution idea is by Enamul Hassan and Special Thanks to: Rumman Mahmud Mahdi Al Masud
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

/*----------------extended euclid--------------------*/

long long ext_gcd(long long A, long long B, long long &X, long long &Y)
{
    long long x2, y2, x1, y1, x, y, r2, r1, q, r;
    x2 = 1, y2 = 0;
    x1 = 0, y1 = 1;
    for (r2 = A, r1 = B; r1 != 0; r2 = r1, r1 = r, x2 = x1, y2 = y1, x1 = x, y1 = y )
    {
        q = r2 / r1;
        r = r2 % r1;
        x = x2 - (q * x1);
        y = y2 - (q * y1);
    }
    X = x2;
    Y = y2;
    return r2;
}



ll solve(ll a, ll b, ll c, ll min_x, ll max_x, ll min_y, ll max_y)
{
    ll x,y;
    ll g=ext_gcd(a,b,x,y);

    if(g && c%g) return 0;

    if(a==0 && b==0)
    {
        if(c==0) return (max_x-min_x+1)*(max_y-min_y+1);
        return 0;
    }
    if(a==0)
    {
        if(c/b>=min_y && c/b<=max_y) return (max_x-min_x+1);
        return 0;
    }

    if(b==0)
    {
        if(c/a>=min_x && c/a<=max_x) return (max_y-min_y+1);
        return 0;
    }
//    DDD(x,y,g);
    ll x1,y1;
    x1=x*(c/g);
    y1=y*(c/g);

    ll minT1, minT2, maxT1, maxT2;

    minT1=ceil((double)(min_x-x1)/(b/g));
    maxT1=floor((double)(y1-min_y)/(a/g));
    maxT2=floor((double)(max_x-x1)/(b/g));
    minT2=ceil((double)(y1-max_y)/(a/g));

    ll minT=max(minT1,minT2);
    ll maxT=min(maxT1,maxT2);
//    DD(x1,y1);
//    DD(minT1,maxT2);
//    DD(maxT1,minT2);
//    DD(minT,maxT);
    return max(maxT-minT+1,0LL);
}


int main()
{
//#ifndef ONLINE_JUDGE
//    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif
    ll a,b,c,x1,x2,y1,y2;
    int t;
    sf(t);
    TEST_CASE(t)
    {
        sfffl(a,b,c);
        sffl(x1,x2);
        sffl(y1,y2);
        c=-c;
        if(a<0)
        {
            a=-a;
            swap(x1,x2);
            x1=-x1;
            x2=-x2;
        }
        if(b<0)
        {
            b=-b;
            swap(y1,y2);
            y1=-y1;
            y2=-y2;
        }
        PRINT_CASE;
        ll ans=solve(a,b,c,x1,x2,y1,y2);
        printf("%lld\n",ans);

    }
    return 0;
}
