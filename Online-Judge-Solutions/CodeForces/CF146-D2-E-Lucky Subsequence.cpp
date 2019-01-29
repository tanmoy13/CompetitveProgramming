/*
    Author: Tanmoy Datta

    Solution Idea:
    ~~~~~~~~~~~~~~
        - As you probably know, the number of lucky numbers in range [1,10^9] is 1022. We use this fact to solve problem.
          Let C[i] - number of occurrences of i-th lucky number in array a. Now we should calculate DP with parameters
          DP[pos][cnt] - what is the number of subsequences that we use lucky numbers up to pos-th and our subsequence
          contains exactly cnt lucky number. If we are on state DP[pos][cnt] we can do two things: do not use pos-th lucky
          number (and do DP[pos+1][cnt] += DP[pos][cnt]) or use pos-th lucky (and do DP[pos+1][cnt+1] += DP[pos][cnt]*C[pos],
          because you have C[pos] of pos-th lucky number).

        - Now we need to find total result. To do that we iterate through the number of lucky numbers in our subsequence i.
          Then you need to multiple that number by C(countunlucky, k - i) (bin. coefficient), where countunlucky - number of
          unlucky numbers of sequence. Sum for all such i will be the total result.

        - This ideas is from problem editorial.
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

vector<ll>lucky;

void gen(ll num)
{
    if(num>1000000000) return;
    if(num)
        lucky.pb(num);
    gen(num*10+4);
    gen(num*10+7);
}

map<ll,ll>mark;

ll cnt[1034];

ll dp[1034][1034];

#define mx 100005

ll fact[mx];

ll call(int idx, int cntt)
{
    if(idx>SZ(lucky))
    {
        if(cntt==0) return 1;
        return 0;
    }
    ll &ret=dp[idx][cntt];

    if(ret!=-1) return ret;

    ll p=0,q=0;

    if(cntt)
    {
        p=(cnt[idx]*(call(idx+1,cntt-1)))%MOD;
    }
    q=call(idx+1,cntt);
    return ret=(p+q)%MOD;
}

ll bigmod(ll n, ll p)
{
    ll ret=1;
    while(p>0)
    {
        if(p%2)
            ret=(ret*n)%MOD;
        n=(n*n)%MOD;
        p/=2;
    }
    return ret;
}

ll nCr(ll n, ll r)
{
    ll up=fact[n];
    ll down=(fact[r]*fact[n-r])%MOD;
    down=bigmod(down,MOD-2);
    ll ret=(up*down)%MOD;
    return ret;
}

int main()
{
//#ifndef ONLINE_JUDGE
////    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif

    gen(0);

    sort(all(lucky));

//    D(SZ(lucky));
//
//    for(int i=0;i<SZ(lucky);i++)
//        D(lucky[i]);

    for(int i=0; i<SZ(lucky); i++)
    {
        mark[lucky[i]]=i+1;
    }

    int n,k;
    sff(n,k);
    ll others = 0;
    int total_lucky=0;
    for(int i=0; i<n; i++)
    {
        ll a;
        sfl(a);
        if(mark[a])
        {
            if(cnt[mark[a]]==0)
                total_lucky++;
            cnt[mark[a]]++;
        }
        else
            others++;
    }

    fact[0]=1;
    for(ll i=1; i<mx; i++)
        fact[i]=(fact[i-1]*i)%MOD;

    if(others+total_lucky<k)
    {
        printf("0\n");
        return 0;
    }

    ll ans=0;
    ms(dp,-1);

//    D(SZ(mark));

    for(int i=0;i<=total_lucky;i++)
    {
        ll x=k-i;
        if(x<=others && x>=0)
        {
            ll temp=nCr(others,x);
            ll temp1=(call(1,i))%MOD;
            temp=(temp*temp1)%MOD;
            ans=(ans+temp)%MOD;
        }
    }


    printf("%lld\n",ans);

        return 0;
}
