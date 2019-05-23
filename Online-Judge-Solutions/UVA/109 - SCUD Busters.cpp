/**
    Author: Tanmoy Datta

    Solution Idea:
    ~~~~~~~~~~~~~~
        - Build separate convex hull for all polygon.
        - Check if any given point is inside a convex hull or not. if it's inside then add this convex polygons area to answer.
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
const int maxp=105;

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

    point operator-(point a)const
    {
        return point(x-a.x, y-a.y);
    }

    double len()  ///gives length from origin
    {
        return hypot(x, y);
    }

    double len2() ///gives square of length from origin
    {
        return x * x + y * y;
    }

    double distance(point p) ///gives distance from p
    {
        return hypot(x - p.x, y - p.y);
    }

    point add(point p)
    {
        return point(x + p.x, y + p.y);
    }

    point sub(point p)
    {
        return point(x - p.x, y - p.y);
    }

    point mul(double b)
    {
        return point(x * b, y * b);
    }

    point div(double b)
    {
        return point(x / b, y / b);
    }
    double dot(point p) ///dot product
    {
        return x*p.x+y*p.y;
    }

    double det(point p) ///cross product of 2d points
    {
        return x*p.y-y*p.x;
    }

    double rad(point a,point b) ///probably radius of circumcircle of the triangle
    {
        point p=*this;
        return fabs(atan2(fabs(a.sub(p).det(b.sub(p))),a.sub(p).dot(b.sub(p))));
    }

    point trunc(double r) ///(required in circle) return point that is truncated the distance from center to r
    {
        double l=len();
        if (!dblcmp(l))return *this;
        r/=l;
        return point(x*r,y*r);
    }

    point rotleft() ///returns 90 degree ccw rotated point
    {
        return point(-y,x);
    }

    point rotright() ///returns 90 degree cw rotated point
    {
        return point(y,-x);
    }

    point rotate(point p,double angle) ///returns point after rotateing the point centering at p by angle radian ccw
    {
        point v=this->sub(p);
        double c=cos(angle),s=sin(angle);
        return point(p.x+v.x*c-v.y*s,p.y+v.x*s+v.y*c);
    }
};

/**
Stores two points

line()								- Empty constructor
line(point a, point b)				- line through a and b
operator ==							- checks if two points are same
line(point p, double angle)			- one end p, another end at angle degree
line(double a, double b, double c)	- line of equation ax + by + c = 0
input()								- inputs a and b
adjust()							- orders in such a way that a < b
length()							- distance of ab
angle()								- returns 0 <= angle < 180
relation()							- 3 if collinear
									  1 if ccw
							  		  2 if cw
pointonseg(point p)					- returns 1 if point is on segment
parallel(line v)					- returns 1 if they are parallel
segcrossseg(line v)					- returns 0 if does not intersect
									  returns 1 if non-standard intersection
									  returns 2 if intersects
segcrossseg_inside(line v)			- returns 1 if intersects strictly inside
									  returns 0 if not
linecrossseg(line v)				- v is line
linecrossline(line v)				- 0 if parallel
									  1 if coincides
									  2 if intersects
crosspoint(line v)					- returns intersection point
dispointtoline(point p)				- distance from point p to the line
dispointtoseg(point p)				- distance from p to the segment
lineprog(point p)					- returns projected point p on ab line
symmetrypoint(point p)				- returns reflection point of p over ab
*/
struct line
{
    point a,b;
    line() { }
    line(point _a,point _b) ///line through a and b
    {
        a=_a;
        b=_b;
    }

    bool operator==(line v) ///checks if two points are same
    {
        return (a==v.a)&&(b==v.b);
    }

    bool pointonseg(point p) ///returns 1 if point is on segment otherwise 0
    {
        return dblcmp(p.sub(a).det(b.sub(a)))==0 && dblcmp(p.sub(a).dot(p.sub(b)))<=0;
    }


};


/**
n, p, line l for each side

input(n)						- inputs n size polygon
add(point p)					- adds a point at end of the list
getline()						- populates line array
cmp								- comparison in convex_hull order
norm()							- sorting in convex_hull order
getconvex(polygon &convex)		- returns convex hull in convex (monotone chain)
isconvex()						- checks if convex
relationpoint(point q)			- returns 3 if q is a vertex
										  2 if on a side
										  1 if inside
										  0 if outside
relationline(line u)			- returns 1 if there is some intersection
										  0 if no intersection
										  2 if intersect at corner
convexcut(line u,polygon &po)	- left side of u in po
getcircumference()				- returns side length
getarea()						- returns area
getdir()						- returns 0 for cw, 1 for ccw
getbarycentre()					- returns barycenter / cg
areaintersection(polygon po)	- not implemented
areaunion(polygon po)			- not implemented
areacircle(circle c)			- intersection area of circle and polygon
relationcircle(circle c)		- returns 0 if outside circle
										  1 if tangent
										  2 if inside
mincircle()						- returns minimum enclosing circle
circlecover()					- i think there is mistake. it tries to find minimum enclosing circle
pointinpolygon(point q)			- -1 if not on polygon, non negative number.. side index
inside_polygon(point q, int on_edge=1)
			- returns on_edge if on edge, otherwise 0 for outside 1 for inside
isdiagonal(int a, int b)		- checks if p[a], p[b] is diagonal or not. returns 0/1
*/
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

    ///comparison in convex_hull order
    struct cmp
    {
        point p;
        cmp(const point &p0)
        {
            p=p0;
        }
        bool operator()(const point &aa,const point &bb)
        {
            point a=aa,b=bb;
            int d=dblcmp(a.sub(p).det(b.sub(p)));
            if (d==0)
                return dblcmp(a.distance(p)-b.distance(p))<0;
            return d>0;
        }
    };

    ///sorting in convex_hull order
    void norm()
    {
        point mi=p[0];
        for (int i=1; i<n; i++)mi=min(mi,p[i]);
        sort(p,p+n,cmp(mi));
    }

    ///returns convex hull in convex (monotone chain)
    ///complexity n log n
    ///First build the upper hull then lower hull
    /// points are stored in clockwise order
    void getconvex(polygon &convex)
    {
        int i;
        sort(p,p+n);
        convex.n=n;
        for (i=0; i<min(n,2); i++) convex.p[i]=p[i];
        if (n<=2)return;
        int &top=convex.n;
        top=1;
        for (i=2; i<n; i++)
        {
            while (top&&convex.p[top].sub(p[i]).det(convex.p[top-1].sub(p[i]))<=0)
                top--;
            convex.p[++top]=p[i];
        }
        int temp=top;
        convex.p[++top]=p[n-2];
        for (i=n-3; i>=0; i--)
        {
            while (top!=temp&&convex.p[top].sub(p[i]).det(convex.p[top-1].sub(p[i]))<=0)
                top--;
            convex.p[++top]=p[i];
        }
    }


    ///returns 3 if q is a vertex
    ///2 if on a side
    ///1 if inside
    ///0 if outside
    int relationpoint(point q)
    {
        int i,j;
        for (i=0; i<n; i++)
        {
            if (p[i]==q)return 3;
        }
        getline();
        for (i=0; i<n; i++)
        {
            if (l[i].pointonseg(q))return 2;
        }
        int cnt=0;
        for (i=0; i<n; i++)
        {
            j=(i+1)%n;
            int k=dblcmp(q.sub(p[j]).det(p[i].sub(p[j])));
            int u=dblcmp(p[i].y-q.y);
            int v=dblcmp(p[j].y-q.y);
            if (k>0&&u<0&&v>=0)cnt++;
            if (k<0&&v<0&&u>=0)cnt--;
        }
        return cnt!=0;
    }


    ///returns area
    double getarea()
    {
        double sum=0;
        int i;
        for (i=0; i<n; i++)
            sum+=p[i].det(p[(i+1)%n]);
        return fabs(sum)/2;
    }
};


int main()
{
//#ifndef ONLINE_JUDGE
//    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif

    polygon inp[25],ch[25];

    int n;
    int cnt=-1;
    while(sf(n) && n!=-1)
    {
        cnt++;
        for(int i=0; i<n; i++)
        {
            int a,b;
            sff(a,b);
            inp[cnt].add(point(a,b));
        }
        inp[cnt].getconvex(ch[cnt]);
    }

    double ans=0.0;

    vector<point>v;
    int a,b;
    while(sff(a,b)==2)
    {
        v.pb(point(a,b));
    }

    for(int i=0; i<=cnt; i++)
    {
        bool check=0;
        for(int j=0; j<SZ(v) && !check; j++)
        {
            if(ch[i].relationpoint(v[j])==1)
            {
                check=1;
            }
        }
        if(check)
            ans+=ch[i].getarea();
    }

    printf("%.2lf\n",ans);

    return 0;
}
