/**
    Author: Tanmoy Datta

    Solution Idea:
    ~~~~~~~~~~~~~~
        - Brute force solution. Check for every possible combination of line through two points.

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

typedef complex<int> point;
#define X real()
#define Y imag()

ll cross_product(point a, point b)
{
    return (conj(a) * b).Y;
}

bool cmp(point a, point b)
{
    return (a.X==b.X)?(a.Y<b.Y):(a.X<b.X);
}

int main()
{
//#ifndef ONLINE_JUDGE
////    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif

    int a,b;
    while(sff(a,b)==2)
    {
        if(a==0 && b==0) break;
        vector<point>v;
        v.pb(point(a,b));
        while(sff(a,b))
        {
            if(a==0 && b==0) break;
            v.pb(point(a,b));
        }


        sort(all(v),cmp);

        vector<vector<point> >ans;

        for(int i=0; i<SZ(v); i++)
        {
            for(int j=i+1; j<SZ(v); j++)
            {

                bool check=0;

                for(int k=0; k<SZ(ans) && !check; k++)
                {
                    if(cross_product(ans[k][0]-ans[k][1],ans[k][0]-v[i])==0 && cross_product(ans[k][0]-ans[k][1],ans[k][0]-v[j])==0)
                    {
                        check=1;
                    }
                }

                if(check) continue;

                vector<point>temp;
                temp.pb(v[i]);
                temp.pb(v[j]);


                for(int k=j+1; k<SZ(v); k++)
                {
                    if(cross_product(v[j]-v[i],v[k]-v[i])==0)
                    {
                        temp.pb(v[k]);
                    }
                }

                if(SZ(temp)>2)
                {
                    sort(all(temp),cmp);
                    ans.pb(temp);
                }

            }
        }


        if(SZ(ans)==0)
            printf("No lines were found\n");
        else
        {
            printf("The following lines were found:\n");
            for(int i=0; i<SZ(ans); i++)
            {
                for(int j=0; j<SZ(ans[i]); j++)
                {
                    printf("(%4d,%4d)",ans[i][j].X,ans[i][j].Y);
                }
                printf("\n");
            }
        }

    }



    return 0;
}
