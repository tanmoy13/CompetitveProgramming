/**
    Author: Tanmoy Datta

    Solution Idea:
    ~~~~~~~~~~~~~~
        - Get 4 rotating calipers at bottom most, right most, top most and left most point.
        - Initially make all calipers axis parallel.
        - Now rotate the calipers in minimum angle and get answer.
        - Repeat this process until total rotation is Pi/2.

*/

#include <bits/stdc++.h>

#define sqr(x)           ((x)*(x))


using namespace std;


const double eps=1e-6;
const double pi=acos(-1.0);
const double inf=1e20;

int dblcmp(long double d) ///d=a-b
{
    if (fabs(d)<eps)return 0; ///if equal return 0
    return d>eps?1:-1; ///if a>b return 1 and if a<b return -1
}

struct point
{
    long double x,y;
    point() { }
    point(long double _x, long double _y)
    {
        x = _x;
        y = _y;
    }

    bool operator<(point a)const
    {
        return dblcmp(a.x - x) == 0 ? dblcmp(y - a.y) < 0 : x < a.x;
    }

    long double abs()  ///gives length from origin
    {
        return hypot(x,y);
    }


    long double distance(point p) ///gives distance from p
    {
        return hypot(x-p.x,y-p.y);
    }

    point add(point p)
    {
        return point(x + p.x, y + p.y);
    }

    point sub(point p)
    {
        return point(x - p.x, y - p.y);
    }

    long double dot(point p) ///dot product
    {
        return x*p.x+y*p.y;
    }

    long double det(point p) ///cross product of 2d points
    {
        return x*p.y-y*p.x;
    }

    point rotate(point p,long double angle) ///returns point after rotateing the point centering at p by angle radian ccw
    {
        point v=this->sub(p);
        long double c=cos(angle),s=sin(angle);
        return point(p.x+v.x*c-v.y*s,p.y+v.x*s+v.y*c);
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

    ///returns intersection point
    point crosspoint(line v)
    {
        long double a1=v.b.sub(v.a).det(a.sub(v.a));
        long double a2=v.b.sub(v.a).det(b.sub(v.a));
        return point((a.x*a2-b.x*a1)/(a2-a1),(a.y*a2-b.y*a1)/(a2-a1));
    }
};

const int maxp=100005;
struct polygon
{
    int n;
    point p[maxp];

    void clear()
    {
        n=0;
    }

    ///adds a point at end of the list
    void add(point q)
    {
        p[n++]=q;
    }

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
};


polygon pgn,ch;

point u,v,w,x;
int top=0,btm=0,lft=0,rgt=0;

int nextP(int p)
{
    p++;
    if(p>=ch.n) return 0;
    return p;
}

long double get_angle(point a, point b)
{
    long double prod=a.dot(b);
    prod/=a.abs();
    prod/=b.abs();
    long double angle=acos(min((long double)1.0,max(prod,(long double)-1.0)));
    return angle;
}

long double temp_perimeter,temp_area;

void get_ans(int btm, int rgt, int top, int lft)
{
    line btmline=line(ch.p[btm],ch.p[btm].add(u));
    line rgtline=line(ch.p[rgt],ch.p[rgt].add(v));
    line topline=line(ch.p[top],ch.p[top].add(w));
    line lftline=line(ch.p[lft],ch.p[lft].add(x));
    point a=btmline.crosspoint(rgtline);
    point b=rgtline.crosspoint(topline);
    point c=topline.crosspoint(lftline);
    point d=lftline.crosspoint(btmline);

    temp_area=a.distance(b)*b.distance(c);
    temp_perimeter=a.distance(b)+b.distance(c)+c.distance(d)+d.distance(a);
}

int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);

    int n;
    while(scanf("%d",&n) && n)
    {
        pgn.clear();
        ch.clear();
        for(int i=0; i<n; i++)
        {
            long double a,b;
            scanf("%Lf %Lf",&a,&b);
            pgn.add(point(a,b));
        }

        pgn.getconvex(ch);

        reverse(ch.p,ch.p+ch.n);

        top=0,btm=0,lft=0,rgt=0;

        for(int i=0; i<ch.n; i++)
        {
            if(ch.p[i].y<ch.p[btm].y) btm=i;
            if(ch.p[i].y>ch.p[top].y) top=i;
            if(ch.p[i].x<ch.p[lft].x) lft=i;
            if(ch.p[i].x>ch.p[rgt].x) rgt=i;
        }

        u=point(+1,0);
        v=point(0,+1);
        w=point(-1,0);
        x=point(0,-1);

        long double area=1e35,perimeter=1e35;

        long double tot=0.0;

        while(tot<=pi/2.0)
        {
            get_ans(btm,rgt,top,lft);

            area=min(area,temp_area);
            perimeter=min(perimeter,temp_perimeter);

            long double anglebtm=get_angle(ch.p[nextP(btm)].sub(ch.p[btm]),u);
            long double anglergt=get_angle(ch.p[nextP(rgt)].sub(ch.p[rgt]),v);
            long double angletop=get_angle(ch.p[nextP(top)].sub(ch.p[top]),w);
            long double anglelft=get_angle(ch.p[nextP(lft)].sub(ch.p[lft]),x);

            long double min_angle = min(min(anglebtm,anglergt),min(angletop,anglelft));

            tot+=min_angle;

            u=u.rotate(point(0,0),min_angle);
            v=v.rotate(point(0,0),min_angle);
            w=w.rotate(point(0,0),min_angle);
            x=x.rotate(point(0,0),min_angle);

            if(dblcmp(anglebtm-min_angle)==0)
            {
                btm=nextP(btm);
            }
            if(dblcmp(anglergt-min_angle)==0)
            {
                rgt=nextP(rgt);
            }
            if(dblcmp(angletop-min_angle)==0)
            {
                top=nextP(top);
            }
            if(dblcmp(anglelft-min_angle)==0)
            {
                lft=nextP(lft);
            }
        }

        printf("%.2Lf %.2Lf\n",area,perimeter);

    }

    return 0;
}
