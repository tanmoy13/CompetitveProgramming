#include <bits/stdc++.h>

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
#define D(x)             cout<<#x " = "<<(x)<<endl
#define VI               vector <int>
#define DBG              pf("Hi\n")
#define MOD              1000000007
#define CIN              ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define SZ(a)            (int)a.size()
#define sf(a)            scanf("%d",&a)
#define sfl(a)           scanf("%lld",&a)
#define sff(a,b)         scanf("%d %d",&a,&b)
#define sffl(a,b)        scanf("%lld %lld",&a,&b)
#define sfff(a,b,c)      scanf("%d %d %d",&a,&b,&c)
#define sfffl(a,b,c)     scanf("%lld %lld %lld",&a,&b,&c)
#define stlloop(v)       for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
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

using namespace std;


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

double DEG_to_RAD(double theta)
{
    return theta*(Pi)/180.0;
}

double RAD_to_DEG(double theta)
{
    return theta*180.0/(Pi);
}

struct point_i
{
    int x,y;
    point_i()
    {
        x=y=0;
    }
    point_i(int a, int b) : x(a),y(b) {}
    bool operator < (point_i other) const
    {
        if(abs(x-other.x)>0)
            return x<other.x;
        return y<other.y;
    }
    bool operator == (point_i other) const
    {
        return (x==other.x && y==other.y);
    }

    double dist(point_i p2)
    {
        return hypot((double)x-p2.x,(double)y-p2.y);
    }

    point_i rotate(int theta)
    {
        double rad=DEG_to_RAD(theta);
        return point_i(x*cos(rad)-y*sin(rad),x*sin(rad)+y*cos(rad));
    }

    point_i mirror_to_point(point_i a)
    {
        return point_i(2*a.x-x,2*a.y-y);
    }

};

struct point
{
    double x,y;
    point()
    {
        x=y=0.0;
    }
    point(double a, double b) : x(a),y(b) {}
    bool operator < (point other) const
    {
        if(fabs(x-other.x)>EPS)
            return x<other.x;
        return y<other.y;
    }
    bool operator == (point other) const
    {
        return (fabs(x-other.x)<EPS && (fabs(y-other.y)<EPS));
    }
    double dist(point p2)
    {
        return hypot((double)x-p2.x,(double)y-p2.y);
    }

    point rotate(double theta)
    {
        double rad=DEG_to_RAD(theta);
        return point(x*cos(rad)-y*sin(rad),x*sin(rad)+y*cos(rad));
    }

    point mirror_to_point(point a)
    {
        return point(2*a.x-x,2*a.y-y);
    }
};

struct line
{
    double a,b,c;
    line (double aa, double bb, double cc)
    {
        a=-(aa/bb);
        b=1.0;
        c=-(cc/bb);
    }
    line (point p1, point p2)
    {
        if(fabs(p1.x-p2.x)<EPS)
        {
            a=1.0,b=0.0,c=-p1.x;
        }
        else
        {
            a=(double)(p1.y-p2.y)/(p1.x-p2.x);
            b=1.0;
            c=(double)(a*-p1.x)+p1.y;
        }
    }
    double slope()
    {
        return a;
    }

    bool areParallel(line l2)
    {
        return ((fabs(a-l2.a)<EPS) && (fabs(b-l2.b)<EPS));
    }

    bool areSame(line l2)
    {
        return (areParallel(l2) && (fabs(c-l2.c)<EPS));
    }
    point intersect(line l2)
    {
        point p;
        p.x=(l2.b*c-b*l2.c)/(l2.a*b-a*l2.b);
        if(fabs(b)>EPS)
            p.y=-(a*p.x+c);
        else
            p.y=-(l2.a*p.x+l2.c);
        return p;
    }



};


struct vec
{
    double x,y;
    vec(double a, double b):x(a),y(b) {}
    vec(point a, point b)
    {
        x=b.x-a.x;
        y=b.y-a.y;
    }
    vec scale(double s)
    {
        return vec(x*s,y*s);
    }
    point translate(point p)
    {
        return point(p.x+x,p.y+y);
    }
    double dot(vec b)
    {
        return x*b.x+y*b.y;
    }

    double norm_sq()
    {
        return x*x+y*y;
    }
    double cross(vec b)
    {
        return x*b.y-y*b.x;
    }
};

double distToLine(point p, point a, point b, point &c)
{
    vec ap = vec(a, p), ab = vec(a, b);
    double u=ap.dot(ab)/ab.norm_sq();
    c = ab.scale(u).translate(p);
    return p.dist(c);
}


double distToLineSegment(point p, point a, point b, point &c)
{
    vec ap = vec(a, p), ab = vec(a, b);
    double u=ap.dot(ab)/ab.norm_sq();
    if (u < 0.0)
    {
        c = point(a.x, a.y);
        return p.dist(a);
    }
    if (u > 1.0)
    {
        c = point(b.x, b.y);
        return p.dist(b);
    }
    return distToLine(p, a, b, c);
}


double angle(point a, point o, point b)
{
    vec oa = vec(o, a), ob = vec(o, b);
    return acos(oa.dot(ob) / sqrt(oa.norm_sq() * ob.norm_sq()));
}

bool ccw(point p, point q, point r)
{
    vec pq=vec(p,q),pr=vec(p,r);
    return pq.cross(pr)>0;
}

bool collinear(point p, point q, point r)
{
    vec pq=vec(p,q),pr=vec(p,r);
    return fabs(pq.cross(pr))<EPS;
}

/*-----------------Circle-----------------*/

int insideCircle(point_i p, point_i c, int r)
{
    int dx=p.x-c.x,dy=p.y-c.y;
    int Euc=dx*dx+dy*dy,rSq=r*r;
    return Euc<rSq?0:Euc==rSq?1:2;
}

/*-----------------Triangle----------------*/

double area_triangle(double a, double b, double c)
{
    double s=(a+b+c)/2;
    return sqrt(s*(s-a)*(s-b)*(s-c));
}

double rInCircle(double ab, double bc, double ca)
{
    return area_triangle(ab,bc,ca)/(0.5*(ab+bc+ca));
}

double rInCircle(point a, point b, point c)
{
    return rInCircle(a.dist(b),b.dist(c),c.dist(a));
}

int inCircle(point p1, point p2, point p3, point &ctr, double &r)
{
    r=rInCircle(p1,p2,p3);
    if(fabs(r)<EPS) return 0;


    double ratio = p1.dist(p2)/p1.dist(p3);

    vec v= vec(p2,p3);
    v=v.scale(ratio/(1+ratio));
    point p=v.translate(p2);

    line l1=line(p1,p);

    ratio = p2.dist(p1)/p2.dist(p3);
    v=vec(p1,p3);
    v=v.scale(ratio/(1+ratio));
    p=v.translate(p1);
    line l2=line(p2,p);

    ctr=l1.intersect(l2);
    return 1;
}

double rCircumCircle(double ab, double bc, double ca)
{
    return ab*bc*ca/(4.0*area_triangle(ab,bc,ca));
}

double rCircumCircle(point a, point b, point c)
{
    return rCircumCircle(a.dist(b), b.dist(c), c.dist(a));
}

/*----------------------------------------------------------*/


int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);

    int t;
    sf(t);
    TEST_CASE(t)
    {
        double x1,y1,r1,x2,y2,r2;
        scanf("%lf %lf %lf %lf %lf %lf",&x1,&y1,&r1,&x2,&y2,&r2);
        point c1=point(x1,y1),c2=point(x2,y2);
        double d=c1.dist(c2);
        PRINT_CASE;
        if(r1+r2<=d)
        {
            printf("0.000000000000\n");
            continue;
        }
        else if(d+r1<=r2)
        {
            printf("%.10lf\n",Pi*sqr(r1));
        }
        else if(d+r2<=r1)
        {
            printf("%.10lf\n",Pi*sqr(r2));
        }
        else
        {
            double ans=0;
            double alpha= 2*acos((sqr(r1)+sqr(d)-sqr(r2))/(2*r1*d));
            ans+=.5*sqr(r1)*(alpha-sin(alpha));

            alpha= 2*acos((sqr(r2)+sqr(d)-sqr(r1))/(2*r2*d));
            ans+=.5*sqr(r2)*(alpha-sin(alpha));

            printf("%.10lf\n",ans);
        }
    }

    return 0;
}
