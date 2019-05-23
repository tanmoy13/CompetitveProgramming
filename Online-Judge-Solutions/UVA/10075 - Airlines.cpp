/**
    Author: Tanmoy Datta

    Solution Idea:
    ~~~~~~~~~~~~~~

*/

#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

#define pii              pair <int,int>
#define pll              pair <long long,long long>
#define sc               scanf
#define pf               printf
#define Pi               (acos(-1.0))
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


/**
	The lattitude and longitude are given with respect to the earth radius.
	Which is R = 6378. radius of earth.
	Find the minimum distance between the two points.
	UVa : 10075
**/

#define pi 3.141592653589793

double gc_distance(double pLat, double pLong, double qLat, double qLong, double r)
{
    /// Angels must be converted into radian.
    pLat *= pi / 180;
    pLong *= pi / 180;
    qLat *= pi / 180;
    qLong *= pi / 180;
    return r * acos(cos(pLat) * cos(qLat) * cos(pLong - qLong) + sin(pLat) * sin(qLat));
}

map<string,int>mp;
pair<double,double>ara[105];
ll dis[102][102];


int main()
{
//#ifndef ONLINE_JUDGE
//    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif

    int n,m,q;
    int cas=0;
    while(sfff(n,m,q))
    {
        mp.clear();
        if(n==0 && m==0 && q==0) break;
        if(cas)
            printf("\n");
        cas++;
        double r=6378;

        char ss[30];
        double Lat,Long;
        for(int i=1; i<=n; i++)
        {
            scanf(" %s %lf %lf\n",ss,&Lat,&Long);
            string str=string(ss);
            mp[str]=i;
            ara[i]=MP(Lat,Long);
        }

        for(int i=0; i<=n; i++)
        {
            for(int j=0; j<=n; j++)
            {
                dis[i][j]=1e15;
                if(i==j)
                    dis[i][j]=0.0;
            }
        }

        for(int i=0; i<m; i++)
        {
            scanf(" %s",ss);
            int id1=mp[string(ss)];
            scanf(" %s",ss);
            int id2=mp[string(ss)];
            double temp=(gc_distance(ara[id1].ff,ara[id1].ss,ara[id2].ff,ara[id2].ss,r)+0.5);
            dis[id1][id2]=temp;
        }

        for(int k=1; k<=n; k++)
        {
            for(int i=1; i<=n; i++)
            {
                for(int j=1; j<=n; j++)
                {
                    dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
                }
            }
        }

        printf("Case #%d\n",cas);

        while(q--)
        {
            scanf(" %s",ss);
            int id1=mp[string(ss)];
            scanf(" %s",ss);
            int id2=mp[string(ss)];
            if(dis[id1][id2]>1e14)
                printf("no route exists\n");
            else
            {
                ll ans=(dis[id1][id2]);
                printf("%lld km\n",ans);
            }

        }


    }

    return 0;
}
