/**
    Author: Tanmoy Datta

    Solution Idea:
    ~~~~~~~~~~~~~~
        - Sort all the points according to their angle with positive x axis. In other words polar angle.
        - If two points are in same angle then break the tie using distance from (0,0). put closer point first in the sorted list.
        - Now start from firs point of the list. if point(0,0) and previous point and next points are collinear then if the height of the current
          point is greater than all previous collinear points height then current point must be visible otherwise put it in the invisible list.
        - If current point is not collinear then this point must be visible so change the maximum variable.
        - After this sort the invisible list and print the answer in appropriate format.

*/

#include <bits/stdc++.h>
 #include <ext/pb_ds/assoc_container.hpp>
 #include <ext/pb_ds/tree_policy.hpp>

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

using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;


//----------------------Graph Moves----------------
//const int fx[]={+1,-1,+0,+0};
//const int fy[]={+0,+0,+1,-1};
//const int fx[]={+0,+0,+1,-1,-1,+1,-1,+1};   // Kings Move
//const int fy[]={-1,+1,+0,+0,+1,+1,-1,-1};  // Kings Move
//const int fx[]={-2, -2, -1, -1,  1,  1,  2,  2};  // Knights Move
//const int fy[]={-1,  1, -2,  2, -2,  2, -1,  1}; // Knights Move
//------------------------------------------------

//-----------------------Bitmask------------------
//int Set(int N,int pos){return N=N | (1<<pos);}
//int reset(int N,int pos){return N= N & ~(1<<pos);}
//bool check(int N,int pos){return (bool)(N & (1<<pos));}
//------------------------------------------------


const double eps=1e-8;
const double pi=acos(-1.0);
const double inf=1e20;
const int maxp=1111;

int dblcmp(double d) ///d=a-b
{
    if (fabs(d)<eps)return 0; ///if equal return 0
    return d>eps?1:-1; ///if a>b return 1 and if a<b return -1
}

struct point
{
    double x,y;
    point() { }
    point(double _x,double _y)
    {
        x = _x;
        y = _y;
    }

    bool operator==(point a)const
    {
        return dblcmp(a.x - x) == 0 && dblcmp(a.y - y) == 0;
    }

    bool operator<(point a)const
    {
        return dblcmp(a.x - x) == 0 ? dblcmp(y - a.y) < 0 : x < a.x;
    }

    point operator-(point a)const
    {
        return point(x-a.x, y-a.y);
    }

    double distance(point a)
    {
        return hypot(x-a.x,y-a.y);
    }

    point add(point p)
    {
        return point(x + p.x, y + p.y);
    }

    point sub(point p)
    {
        return point(x - p.x, y - p.y);
    }

    double dot(point p) ///dot product
    {
        return x*p.x+y*p.y;
    }

    double det(point p) ///cross product of 2d points
    {
        return x*p.y-y*p.x;
    }

};

struct data
{
    point p;
    int h;
};

bool cmp(data a, data b)
{
    double temp=a.p.det(b.p);
    if(dblcmp(temp)==0)
    {
        return dblcmp((a.p.dot(a.p))-(b.p.dot(b.p)))<0;
    }
    else if(dblcmp(temp)>0) return true;
    return false;
}

int main()
{
//    freopen("in.txt","r",stdin);

    int n;
    int cas=0;
    while(sf(n) && n)
    {
        cas++;
        vector<data>v;
        for(int i=0;i<n;i++)
        {
            double x,y,z;
            scanf("%lf %lf %lf",&x,&y,&z);
            data temp;
            temp.p=point(x,y);
            temp.h=z;
            v.pb(temp);
        }

        sort(all(v),cmp);

//        for(int i=0;i<SZ(v);i++)
//        {
//            DDD(v[i].p.x,v[i].p.y,v[i].h);
//        }


        vector<point>ans;

        int maxi=v[0].h;

        for(int i=1;i<SZ(v);i++)
        {
            if(dblcmp(v[i-1].p.det(v[i].p))==0)
            {
                if(v[i].h<=maxi)
                {
                    ans.pb(v[i].p);
                }
                else
                {
                    maxi=v[i].h;
                }
            }
            else
            {
                maxi=v[i].h;
            }
        }

        printf("Data set %d:\n",cas);
        if(SZ(ans)==0)
        {
            printf("All the lights are visible.\n");
        }
        else
        {
            sort(all(ans));
            printf("Some lights are not visible:\n");
            for(int i=0;i<SZ(ans);i++)
            {
                printf("x = %.0lf, y = %.0lf",ans[i].x,ans[i].y);
                if(i+1<SZ(ans))
                    printf(";\n");
            }
            printf(".\n");
        }




    }

    return 0;
}
