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
#define D(x)             cerr<<#x " = "<<(x)<<endl
#define VI               vector <int>
#define DBG              pf("Hi\n")
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

/*-----------Number Theory Template------------*/

#define mx 100005


/*----------------Sieve--------------------*/
vector<int>prime;
bool vis[mx];

void sieve()
{
    int x=sqrt((int)mx);
    for(int i=3; i<=x; i+=2)
    {
        if(vis[i]==0)
        {
            for(int j=i*i; j<mx; j+=2*i)
                vis[j]=1;
        }
    }
    prime.pb(2);
    for(int i=3; i<mx; i+=2)
        if(vis[i]==0)
            prime.pb(i);
}


/*----------------Mobius--------------------*/
//int mu[mx];

//void mobius()
//{
//    for(int i=1; i<mx; i++) mu[i]=1;
//    int root=sqrt((int)mx);
//    for(int i=0; i<SZ(prime) && prime[i]<=root; i++)
//    {
//        int x=prime[i];
//        x=sqr(x);
//        for(int j=x; j<mx; j+=x)
//            mu[j]=0;
//    }
//    for(int i=0; i<SZ(prime); i++)
//    {
//        int x=prime[i];
//        for(int j=x; j<mx; j+=x)
//            mu[j]*=-1;
//    }
//}


/*----------------euler totient 1 to n--------------------*/
//int phi[mx];

//void euler_totient()
//{
//    for(int i=0; i<mx; i++) phi[i]=i;
//    for(int i=2; i<mx; i++)
//    {
//        if(phi[i]==i)
//        {
//            for(int j=i; j<mx; j+=i)
//                phi[j]-=(phi[j]/i);
//        }
//    }
//}

/*----------------euler totient for n--------------------*/
//
//ll euler_totient(ll n)
//{
//    int root=sqrt(n);
//    ll ret=n;
//    for(int i=0; i<SZ(prime) && prime[i]<=root; i++)
//    {
//        if(n%prime[i]==0)
//        {
//            while(n%prime[i]==0)
//                n/=prime[i];
//            root=sqrt(n);
//            ret-=(ret/prime[i]);
//        }
//    }
//    if(n>1)
//    {
//        ret-=(ret/n);
//    }
//    return ret;
//}

/*----------------extended euclid--------------------*/

long long ext_gcd (long long A, long long B, long long &X, long long &Y)
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


/*----------------Mod Inverse--------------------*/

inline long long modInv (long long a, long long m)
{
    long long x, y;
    ext_gcd(a, m, x, y);
    x %= m;
    if (x < 0) x += m;
    return x;
}

/*----------------bigmod--------------------*/

inline long long bigmod (long long a, long long p, long long m)
{
    long long res = 1 % m, x = a % m;
    while ( p )
    {
        if ( p & 1 ) res = ( res * x ) % m;
        x = ( x * x ) % m;
        p >>= 1;
    }
    return res;
}

/*----------------linear Diophantine equation--------------------*/
//
//bool linearDiophantine ( long long A, long long B, long long C, long long &x, long long &y )
//{
//    int g = gcd ( A, B );
//    if ( C % g != 0 ) return false; //No Solution
//
//    int a = A / g, b = B / g, c = C / g;
//    if ( g < 0 )   //Make Sure gcd(a,b) = 1
//    {
//        a *= -1;
//        b *= -1;
//        c *= -1;
//    }
//    ext_gcd( a, b, x, y ); //Solve ax + by = 1
//
//
//    x *= c;
//    y *= c; //ax + by = c
//    return true; //Solution Exists
//    //more solution {x+k*(b/g), y-k*(a/g)}
//}
//
//
//long long CRT_weak(vector<long long>A, vector<long long>B)
//{
//    ll X=0;
//    ll N=1;
//    ll y,z;
//    for(int i=0;i<SZ(B);i++)
//        N*=B[i];
//    for(int i=0;i<SZ(A);i++)
//    {
//        y=N/B[i];
//        z=modInv(y,B[i]);
//        X+=(A[i]*y*z);
//        X%=N;
//    }
//    return (X+N)%N;
//}

/*-----------Number Theory End------------*/


ll factorial_factor(ll a, ll p)
{
    ll ret=0;
    while(a)
    {
        ret+=a/p;
        a/=p;
    }
    return ret;
}

int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);
    sieve();
    ll n,m;
    while(sffl(n,m)==2)
    {
        ll x=n,y=m;
        vector<pll>v;
        int root=sqrt(m);
        for(int i=0;i<SZ(prime);i++)
        {
            if(m%prime[i]==0)
            {
                int cnt=0;
                while(m%prime[i]==0)
                {
                    cnt++;
                    m/=prime[i];
                }
                v.pb(pll(prime[i],cnt));
                root=sqrt(m);
            }
        }

        if(m>1)
        {
            v.pb(pll(m,1));

        }
        bool check=0;
        for(int i=0;i<SZ(v);i++)
        {
            if(factorial_factor(n,v[i].ff)<v[i].ss)
            {
                check=1;
                break;
            }
        }

        if(check)
            printf("%lld does not divide %lld!\n",y,x);
        else
            printf("%lld divides %lld!\n",y,x);



    }
    return 0;
}
