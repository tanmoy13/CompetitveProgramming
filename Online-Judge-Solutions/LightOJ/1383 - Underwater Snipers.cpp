/**
    Author: Tanmoy Datta

    Solution Idea:
    ~~~~~~~~~~~~~~
        - We can binary search over the answer.
        - Most important observation is all the sniper must stand in a straight line parallel to x axis or river bank.
        - Now in check function we can calculate the vertical distance form the sniper line to soldier. Let this distance is ydiff.
          Then A sniper can kill a soldier if euclidean distance between them is at most d. so d=sqrt((xdiff)^2+(ydiff)^2).
          so, d^2= xdiff^2 + ydiff^2. So we can calculate xdiff = sqrt(d^2-ydiff^2). So if a solders position is (x,y) then if a sniper is
          in the range x-xdiff to x+xdiff then the sniper can kill the soldier.
        - Now we can greedily put sniper and make a ask function for binary search.
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

struct data
{
    pll pos;
    ll l,r;
};

vector<data>v;

ll k,n,s,d;


bool ask(ll dis)
{
    for(int i=0; i<SZ(v); i++)
    {
        ll ydiff = v[i].pos.ss-k+dis;
        if(ydiff>d) return false;
        ll xdiff=sqr(d)-sqr(ydiff);
        xdiff=sqrt((double)xdiff);
        v[i].l=v[i].pos.ff-xdiff;
        v[i].r=v[i].pos.ff+xdiff;
    }

    sort(all(v),[](data a, data b)
    {
        if(a.r==b.r) return a.l<b.l;
        return a.r<b.r;
    });

    int cnt=1;
    ll last=v[0].r;
    for(int i=1; i<SZ(v); i++)
    {
        if(v[i].l<=last) continue;
        else
        {
            cnt++;
            last=v[i].r;
        }
    }

    return cnt<=s;
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
        sfffl(k,n,s);
        sfl(d);

        v.clear();

        data temp;
        for(int i=0; i<n; i++)
        {
            sffl(temp.pos.ff,temp.pos.ss);
            v.pb(temp);
        }

        sort(all(v),[](data a, data b)
        {
            return a.pos<b.pos;
        });

        ll ans=-1;

        ll lo=1,hi=1e10;

        while(lo<=hi)
        {
            ll mid=(lo+hi)/2;
            if(ask(mid))
            {
                ans=mid;
                lo=mid+1;
            }
            else
                hi=mid-1;
        }
        PRINT_CASE;
        if(ans==-1)
            printf("impossible\n");
        else
            printf("%lld\n",ans);

    }

    return 0;
}
