/*
    Author: Tanmoy Datta

    solution idea:
        - At first we need to calculate set of elevators which reach A and which reach B. Let this two sets are st and ed.
        - Now if any elevator from set st  have same stopping point as any elevator from set ed then we can say that
          it is possible to go from A to B.
        - Now for checking this connectivity we can use extended euclidian algorithm and a disjoint set union.
        - Extended euclidian is used to check whether two elevator have same stopping point or not. Light Oj 1306 - Solutions to an Equation
          is the base problem for this idea. You can check my solution for this problem from here-
          https://github.com/tanmoy13/CompetitveProgramming/blob/master/Online-Judge-Solutions/LightOJ/1306%20-%20Solutions%20to%20an%20Equation.cpp
        - Corner case for the problem is two elevator have a same stopping point outside the height of the building.

            1
            10 4 4 5
            9 9
            7 4
            5 0
            9 8

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
#define D(x)             cerr << __LINE__ << ": " << #x << " = " << (x) << '\n'
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

#define mx 205

int par[mx];
vector<pll>lift;
pll lift_ranges[mx];


void init_set()
{
    for(int i=0; i<mx; i++) par[i]=i;
}

int find_par(int u)
{
    return par[u]=(par[u]==u)?u:find_par(par[u]);
}

void union_set(int a, int b)
{
    a=find_par(a);
    b=find_par(b);
    if(a==b) return;
    par[b]=a;
    return;
}

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


bool isConnected(int i, int j)
{
    ll x,y,c;
    ll a=lift[i].ff;
    ll b=lift[j].ff;
    ll g=ext_gcd(a,b,x,y);
    c=lift[j].ss-lift[i].ss;
    if(c%g) return 0;

//    DDD(a,b,c);
//    DDD(x,y,g);
//    D("------------------------------");

    ll min_x=lift_ranges[i].ff;
    ll max_x=lift_ranges[i].ss;
    ll min_y=-lift_ranges[j].ss;
    ll max_y=-lift_ranges[j].ff;

    ll x1=x*(c/g);
    ll y1=y*(c/g);

    ll minT1,minT2,maxT1,maxT2;

    minT1 = ceil((double)(min_x-x1)/((double)b/(double)g));
    maxT1 = floor((double)(y1-min_y)/((double)a/(double)g));
    minT2 = ceil((double)(y1-max_y)/((double)a/(double)g));
    maxT2 = floor((double)(max_x-x1)/((double)b/(double)g));

    ll minT=max(minT1,minT2);
    ll maxT=min(maxT1,maxT2);

    return max(maxT-minT+1,0LL);
}

int main()
{
//#ifndef ONLINE_JUDGE
//    freopen("in.txt","r",stdin);
////      freopen("out.txt","w",stdout);
//#endif

    int t;
    sf(t);
    TEST_CASE(t)
    {
        lift.clear();
        ll F,E,A,B;
        sfffl(F,E,A);
        sfl(B);
        ll x=min(A,B);
        ll y=max(A,B);

        vector<int>st,ed;

        for(int i=0; i<E; i++)
        {
            ll a,b;
            sffl(a,b);
            lift.pb(pll(a,b));

            if(b<=x && (b%a==x%a))
                st.pb(i);
            if(b<=y && (b%a==y%a))
                ed.pb(i);

            lift_ranges[i].ff=0;
            lift_ranges[i].ss=floor(((double)(F-lift[i].ss))/((double)lift[i].ff));
        }

        init_set();

        for(int i=0; i<SZ(lift); i++)
        {
            for(int j=i+1; j<SZ(lift); j++)
            {
                if(isConnected(i,j))
                {
                    union_set(i,j);
                }
            }
        }

        bool ans=0;

        for(int i=0; i<SZ(st) && !ans; i++)
        {
            for(int j=0; j<SZ(ed) && !ans; j++)
            {
                if(find_par(st[i])==find_par(ed[j]))
                {
                    ans=1;
                    break;
                }
            }
        }

        if(ans || x==y)
            printf("It is possible to move the furniture.\n");
        else
            printf("The furniture cannot be moved.\n");

//        cout<<endl;
//        for(int i:st)
//            cout<<i<<" ";
//        cout<<endl;
//
//        for(int i:ed)
//            cout<<i<<" ";
//        cout<<endl;


    }

    return 0;
}
