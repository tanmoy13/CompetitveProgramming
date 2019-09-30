/**
    Author: Tanmoy Datta

    Solution Idea:
    ~~~~~~~~~~~~~~
        -

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
#define sqr(x)           ((x)*(x))
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

#define mx 1000006

ll ara[mx];

ll sum[mx];


vector<long long>m,b;

bool bad(int f1, int f2, int f3, int id)
{
    ///mi < mi+1, and all queries are for maximum.
    if(id==4)
        return ((b[f3]-b[f1])*(m[f1]-m[f2]))<=((m[f1]-m[f3])*(b[f2]-b[f1]));

}

void add(long long new_m, long long new_b, int id)
{
    m.push_back(new_m);
    b.push_back(new_b);

    int sz=m.size();

    while(sz>=3 && bad(sz-3,sz-2, sz-1, id))
    {
        m.erase(m.end()-2);
        b.erase(b.end()-2);
        sz--;
    }
}

ll f(int i, ll x)
{
    return  m[i]*x+b[i];
}

///(mi > mi+1) or (mi < mi+1) and all queries are for maximum.
ll query2(ll x)
{
    int lo=0,hi=m.size()-1;
    ll ans=-1e18;
    while(lo+3<=hi)
    {
        int mid1=(lo+lo+hi)/3;
        int mid2=(lo+hi+hi)/3;
        ll y1=f(mid1,x);
        ll y2=f(mid2,x);
        if(y1>=y2)
        {
            ans=max(y1,ans);
            hi=mid2-1;
        }
        else
        {
            ans=max(y2,ans);
            lo=mid1+1;
        }
    }
    for(int i=lo; i<=hi; i++)
        ans=max(ans,f(i,x));
    return ans;
}

ll dp[mx];

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


        int n;
        sf(n);
        ll a,bb,c;
        sfffl(a,bb,c);

        for(int i=1;i<=n;sum[i]=ara[i]+sum[i-1],i++)
            sfl(ara[i]);

        m.clear();
        b.clear();

        add(0,0,4); ///here 3 is CHT type id

        for(int i=1;i<=n;i++)
        {
            ll ret=query2(sum[i]);
            dp[i]=ret+a*sum[i]*sum[i]+bb*sum[i]+c;
            ll nm = -2*a*sum[i];
            ll nb = a*sum[i]*sum[i]-bb*sum[i]+dp[i];
            add(nm,nb,4);
        }

        printf("%lld\n",dp[n]);

    }

    return 0;
}
