/**
    Author: Tanmoy Datta

    Solution Idea:
    ~~~~~~~~~~~~~~
        - At first check whether any vertex lie in the given line. If yes then answer is NO. Otherwise we need to do the following.
        - Determine all intersection points with the given y-axis parallel line for given x. and sort them according to y coordinate value.
        - Sum up the distances covers inside the polygon area. Here comes an observation 1st and 2nd point's distance are inside polygon.
          similarly 3rd and 4th point's distance are inside polygon. But 2nd and 3rd point's distance are outside the polygon.
        - If the sum up value is >=d then answer is YES otherwise NO.
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

const double eps=1e-8;
const double pi=acos(-1.0);
const double inf=1e20;
const int maxp=20000;

int dblcmp(double d) ///d=a-b
{
    if (fabs(d)<eps)return 0; ///if equal return 0
    return d>eps?1:-1; ///if a>b return 1 and if a<b return -1
}

/**
point()						- Empty constructor
point(double x, double y)	- constructor
input()						- double input
output()					- .2lf output
operator ==					- compares x and y
operator <					- compares first by x, then by y
len()						- gives length from origin
len2()						- gives square of length from origin
distance(point p)			- gives distance from p
add(point p)				- returns new point after adding corresponding x and y
sub(point p)				- returns new point after subtracting corresponding x and y
mul(double b)				- returns new point after multiplying x and y by b
div(double b)				- returns new point after dividing x and y by b
dot(point p)				- dot product
det(point p)				- cross product of 2d points
rad(point a, point b)		- Probably radius of circumcircle of the triangle
trunc(double r)				- return point that is truncated the distance from center to r
rotleft()					- returns 90 degree ccw rotated point
rotright()					- returns 90 degree cw rotated point
rotate(point p, double angle) - returns point after rotateing the point centering at p by angle radian ccw
*/

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

    double distance(point p) ///gives distance from p
    {
        return hypot(x - p.x, y - p.y);
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


struct line
{
    point a,b;
    line() { }
    line(point _a,point _b) ///line through a and b
    {
        a=_a;
        b=_b;
    }

    int linecrossseg(line v) ///*this is seg and v is line
    {
        int d1=dblcmp(b.sub(a).det(v.a.sub(a)));
        int d2=dblcmp(b.sub(a).det(v.b.sub(a)));
        if ((d1^d2)==-2)return 2;
        return (d1==0||d2==0);
    }

    ///returns intersection point
    point crosspoint(line v)
    {
        double a1=v.b.sub(v.a).det(a.sub(v.a));
        double a2=v.b.sub(v.a).det(b.sub(v.a));
        return point((a.x*a2-b.x*a1)/(a2-a1),(a.y*a2-b.y*a1)/(a2-a1));
    }


};
struct polygon
{
    int n;
    point p[maxp];
    line l[maxp];
    polygon()
    {
        n=0;
    }

    ///adds a point at end of the list
    void add(point q)
    {
        p[n++]=q;
    }

    ///populates line array
    void getline()
    {
        for (int i=0; i<n; i++)
            l[i]=line(p[i],p[(i+1)%n]);
    }
};


polygon pgn;

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
        pgn.n=0;
        vector<pii>v;
        for(int i=0; i<n; i++)
        {
            int a,b;
            sff(a,b);
            pgn.add(point(a,b));
            v.pb(pii(a,b));
        }
//        pgn.add(point(v[0].ff,v[0].ss));

        int d;
        scanf("%d",&d);
        int x;
        sf(x);
        bool ans=1;

        for(int i=0; i<SZ(v) && ans; i++)
        {
            if(v[i].ff==x && v[i].ss%d==0)
                ans=0;
        }

        if(ans==0)
        {
            printf("NO\n");
            continue;
        }


        pgn.getline();

        line l1(point(x,-100000000),point(x,100000000));

        vector<point>vp;

        for(int i=0;i<pgn.n;i++)
        {
            if(l1.linecrossseg(pgn.l[i])==2)
            {
                point cross=pgn.l[i].crosspoint(l1);
                vp.pb(cross);
            }
        }

        sort(all(vp));

        bool check=0;
        double dis=0.0;
        for(int i=1;i<SZ(vp) && !check;i+=2)
        {
            double dis1=vp[i-1].distance(vp[i]);
            dis+=dis1;
        }

        if(dblcmp(dis-d)>=0)
            check=1;

        if(check)
            printf("YES\n");
        else
            printf("NO\n");



    }

    return 0;
}
