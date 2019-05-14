/**
    Author: Tanmoy Datta

    Solution Idea:
    ~~~~~~~~~~~~~~
        - We need to calculate the center and radius of the circle.
        - For calculating the circle through three points we need to calculate the bisector of two sides and calculate
          the intersection point.
        - This intersection point is the center of the circle and distance from this center to a given point is the radius.
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


const double eps=1e-8;
const double pi=acos(-1.0);
const double inf=1e20;
const int maxp=1111;

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

    line(point p,double angle)///one end p, another end at angle degree
    {
        a=p;
        if (dblcmp(angle-pi/2)==0)
        {
            b=a.add(point(0,1));
        }
        else
        {
            b=a.add(point(1,tan(angle)));
        }
    }
    //ax+by+c=0
    line(double _a,double _b,double _c) ///line of equation ax + by + c = 0
    {
        if (dblcmp(_a)==0)
        {
            a=point(0,-_c/_b);
            b=point(1,-_c/_b);
        }
        else if (dblcmp(_b)==0)
        {
            a=point(-_c/_a,0);
            b=point(-_c/_a,1);
        }
        else
        {
            a=point(0,-_c/_b);
            b=point(1,(-_c-_a)/_b);
        }
    }

    void adjust() ///orders in such a way that a < b
    {
        if(b<a)swap(a,b);
    }

    double length() ///distance of ab
    {
        return a.distance(b);
    }

    double angle() ///returns 0 <= angle < 180
    {
        double k=atan2(b.y-a.y,b.x-a.x);
        if (dblcmp(k)<0)k+=pi;
        if (dblcmp(k-pi)==0)k-=pi;
        return k;
    }

    ///3 if collinear
    ///1 if ccw and
    ///2 if cw
    int relation(point p)
    {
        int c=dblcmp(p.sub(a).det(b.sub(a)));
        if (c<0)return 1;
        if (c>0)return 2;
        return 3;
    }

    bool pointonseg(point p) ///returns 1 if point is on segment otherwise 0
    {
        return dblcmp(p.sub(a).det(b.sub(a)))==0 && dblcmp(p.sub(a).dot(p.sub(b)))<=0;
    }

    bool parallel(line v) ///returns 1 if they are parallel otherwise 0
    {
        return dblcmp(b.sub(a).det(v.b.sub(v.a)))==0;
    }


    ///returns 0 if does not intersect
    ///returns 1 if non-standard intersection
    ///returns 2 if intersects
    int segcrossseg(line v)
    {
        int d1=dblcmp(b.sub(a).det(v.a.sub(a)));
        int d2=dblcmp(b.sub(a).det(v.b.sub(a)));
        int d3=dblcmp(v.b.sub(v.a).det(a.sub(v.a)));
        int d4=dblcmp(v.b.sub(v.a).det(b.sub(v.a)));
        if ((d1^d2)==-2&&(d3^d4)==-2)return 2;
        return (d1==0&&dblcmp(v.a.sub(a).dot(v.a.sub(b)))<=0||
                d2==0&&dblcmp(v.b.sub(a).dot(v.b.sub(b)))<=0||
                d3==0&&dblcmp(a.sub(v.a).dot(a.sub(v.b)))<=0||
                d4==0&&dblcmp(b.sub(v.a).dot(b.sub(v.b)))<=0);
    }

    ///returns 1 if intersects strictly inside
    ///returns 0 if not
    int segcrossseg_inside(line v)
    {
        if(v.pointonseg(a) || v.pointonseg(b) || pointonseg(v.a) || pointonseg(v.b)) return 0;
        int d1=dblcmp(b.sub(a).det(v.a.sub(a)));
        int d2=dblcmp(b.sub(a).det(v.b.sub(a)));
        int d3=dblcmp(v.b.sub(v.a).det(a.sub(v.a)));
        int d4=dblcmp(v.b.sub(v.a).det(b.sub(v.a)));
        if ((d1^d2)==-2&&(d3^d4)==-2)return 1;
        return (d1==0&&dblcmp(v.a.sub(a).dot(v.a.sub(b)))<=0||
                d2==0&&dblcmp(v.b.sub(a).dot(v.b.sub(b)))<=0||
                d3==0&&dblcmp(a.sub(v.a).dot(a.sub(v.b)))<=0||
                d4==0&&dblcmp(b.sub(v.a).dot(b.sub(v.b)))<=0);
    }

    int linecrossseg(line v) ///*this is seg and v is line
    {
        int d1=dblcmp(b.sub(a).det(v.a.sub(a)));
        int d2=dblcmp(b.sub(a).det(v.b.sub(a)));
        if ((d1^d2)==-2)return 2;
        return (d1==0||d2==0);
    }

    ///0 if parallel
    ///1 if coincides
    ///2 if intersects
    int linecrossline(line v)
    {
        if ((*this).parallel(v))
        {
            return v.relation(a)==3;
        }
        return 2;
    }

    ///returns intersection point
    point crosspoint(line v)
    {
        double a1=v.b.sub(v.a).det(a.sub(v.a));
        double a2=v.b.sub(v.a).det(b.sub(v.a));
        return point((a.x*a2-b.x*a1)/(a2-a1),(a.y*a2-b.y*a1)/(a2-a1));
    }

    ///distance from point p to the line
    double dispointtoline(point p)
    {
        return fabs(p.sub(a).det(b.sub(a)))/length();
    }

    ///distance from p to the segment
    double dispointtoseg(point p)
    {
        if (dblcmp(p.sub(b).dot(a.sub(b)))<0||dblcmp(p.sub(a).dot(b.sub(a)))<0)
        {
            return min(p.distance(a),p.distance(b));
        }
        return dispointtoline(p);
    }

    ///returns projected point p on ab line
    point lineprog(point p)
    {
        return a.add(b.sub(a).mul(b.sub(a).dot(p.sub(a))/b.sub(a).len2()));
    }

    ///returns reflection point of p over ab
    point symmetrypoint(point p)
    {
        point q=lineprog(p);
        return point(2*q.x-p.x,2*q.y-p.y);
    }
};


struct circle
{
    point p;
    double r;
    circle() {}
    ///circle of point p and radius r
    circle(point _p,double _r):     p(_p),r(_r) {};

    ///circumcircle of triangle of abc
    circle(point a,point b,point c)
    {
        p=line(a.add(b).div(2),a.add(b).div(2).add(b.sub(a).rotleft())).crosspoint(line(c.add(b).div(2),c.add(b).div(2).add(b.sub(c).rotleft())));
        r=p.distance(a);
    }

    ///incircle of triangle of abc, bool t is nothing
    circle(point a,point b,point c,bool t)
    {
        line u,v;
        double m=atan2(b.y-a.y,b.x-a.x),n=atan2(c.y-a.y,c.x-a.x);
        u.a=a;
        u.b=u.a.add(point(cos((n+m)/2),sin((n+m)/2)));
        v.a=b;
        m=atan2(a.y-b.y,a.x-b.x),n=atan2(c.y-b.y,c.x-b.x);
        v.b=v.a.add(point(cos((n+m)/2),sin((n+m)/2)));
        p=u.crosspoint(v);
        r=line(a,b).dispointtoseg(p);
    }

};


int main()
{

    double x1,y1,x2,y2,x3,y3;
    while(scanf("%lf %lf %lf %lf %lf %lf",&x1,&y1,&x2,&y2,&x3,&y3)==6)
    {
        circle c(point(x1,y1),point(x2,y2),point(x3,y3));
        char sign1,sign2;
        if(dblcmp(c.p.x)>=0)
            sign1='-';
        else
            sign1='+';

        if(dblcmp(c.p.y)>=0)
            sign2='-';
        else
            sign2='+';

        char sign3;

        double cc=sqr(c.p.x)+sqr(c.p.y)-sqr(c.r);
        if(dblcmp(cc)<0)
            sign3='-';
        else
            sign3='+';

        printf("(x %c %.3lf)^2 + (y %c %.3lf)^2 = %.3lf^2\n",sign1,sign2,abs(c.p.x),abs(c.p.y),c.r);
        printf("x^2 + y^2 %c %.3lfx %c %.3lfy %c %.3lf = 0\n",sign1,2.0*abs(c.p.x),sign2,2.0*abs(c.p.y),sign3,abs(cc));
        printf("\n");
    }

    return 0;
}
