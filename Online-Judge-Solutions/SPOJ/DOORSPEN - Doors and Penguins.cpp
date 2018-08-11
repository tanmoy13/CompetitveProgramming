#include<vector>
#include<list>
#include<map>
#include<set>
#include<deque>
#include<queue>
#include<stack>
#include<bitset>
#include<algorithm>
#include<functional>
#include<numeric>
#include<utility>
#include<iostream>
#include<sstream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<cctype>
#include<string>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<climits>
#include<complex>
#define mp make_pair
#define pb push_back
using namespace std;
const double eps=1e-8;
const double pi=acos(-1.0);
const double inf=1e20;
const int maxp=1111;
int dblcmp(double d)
{
    if (fabs(d)<eps)return 0;
    return d>eps?1:-1;
}
inline double sqr(double x)
{
    return x*x;
}

struct point
{
    double x,y;
    point()             {                                    }
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
    double len()
    {
        return hypot(x, y);
    }
    double len2()
    {
        return x * x + y * y;
    }
    double distance(point p)
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
//    point mul(double b)
//    {
//        return point(x * b, y * b);
//    }
//    point div(double b)
//    {
//        return point(x / b, y / b);
//    }
    double dot(point p)
    {
        return x*p.x+y*p.y;
    }
    double det(point p)
    {
        return x*p.y-y*p.x;
    }
//    double rad(point a,point b)
//    {
//        point p=*this;
//        return fabs(atan2(fabs(a.sub(p).det(b.sub(p))),a.sub(p).dot(b.sub(p))));
//    }
//    point trunc(double r)
//    {
//        double l=len();
//        if (!dblcmp(l))return *this;
//        r/=l;
//        return point(x*r,y*r);
//    }
//    point rotleft()
//    {
//        return point(-y,x);
//    }
//    point rotright()
//    {
//        return point(y,-x);
//    }
//    point rotate(point p,double angle)
//    {
//        point v=this->sub(p);
//        double c=cos(angle),s=sin(angle);
//        return point(p.x+v.x*c-v.y*s,p.y+v.x*s+v.y*c);
//    }
};

struct line
{
    point a,b;
    line()              {                                    }
    line(point _a,point _b)
    {
        a=_a;
        b=_b;
    }
    bool operator==(line v)
    {
        return (a==v.a)&&(b==v.b);
    }
//    //ax+by+c=0
//    line(double _a,double _b,double _c)
//    {
//        if (dblcmp(_a)==0)
//        {
//            a=point(0,-_c/_b);
//            b=point(1,-_c/_b);
//        }
//        else if (dblcmp(_b)==0)
//        {
//            a=point(-_c/_a,0);
//            b=point(-_c/_a,1);
//        }
//        else
//        {
//            a=point(0,-_c/_b);
//            b=point(1,(-_c-_a)/_b);
//        }
//    }
//    void input()
//    {
//        a.input();
//        b.input();
//    }
    void adjust()
    {
        if(b<a)swap(a,b);
    }
//    double length()
//    {
//        return a.distance(b);
//    }
//    double angle()
//    {
//        double k=atan2(b.y-a.y,b.x-a.x);
//        if (dblcmp(k)<0)k+=pi;
//        if (dblcmp(k-pi)==0)k-=pi;
//        return k;
//    }
//    int relation(point p)
//    {
//        int c=dblcmp(p.sub(a).det(b.sub(a)));
//        if (c<0)return 2;
//        if (c>0)return 1;
//        return 0;
//    }
    bool pointonseg(point p)
    {
        return dblcmp(p.sub(a).det(b.sub(a)))==0&&dblcmp(p.sub(a).dot(p.sub(b)))<=0;
    }
//    bool parallel(line v)
//    {
//        return dblcmp(b.sub(a).det(v.b.sub(v.a)))==0;
//    }
//    int segcrossseg(line v)
//    {
//        int d1=dblcmp(b.sub(a).det(v.a.sub(a)));
//        int d2=dblcmp(b.sub(a).det(v.b.sub(a)));
//        int d3=dblcmp(v.b.sub(v.a).det(a.sub(v.a)));
//        int d4=dblcmp(v.b.sub(v.a).det(b.sub(v.a)));
//        if ((d1^d2)==-2&&(d3^d4)==-2)return 2;
//        return (d1==0&&dblcmp(v.a.sub(a).dot(v.a.sub(b)))<=0||
//                d2==0&&dblcmp(v.b.sub(a).dot(v.b.sub(b)))<=0||
//                d3==0&&dblcmp(a.sub(v.a).dot(a.sub(v.b)))<=0||
//                d4==0&&dblcmp(b.sub(v.a).dot(b.sub(v.b)))<=0);
//    }
//    int segcrossseg_inside(line v)
//    {
//        if(v.pointonseg(a) || v.pointonseg(b) || pointonseg(v.a) || pointonseg(v.b)) return 0;
//        int d1=dblcmp(b.sub(a).det(v.a.sub(a)));
//        int d2=dblcmp(b.sub(a).det(v.b.sub(a)));
//        int d3=dblcmp(v.b.sub(v.a).det(a.sub(v.a)));
//        int d4=dblcmp(v.b.sub(v.a).det(b.sub(v.a)));
//        if ((d1^d2)==-2&&(d3^d4)==-2)return 1;
//        return (d1==0&&dblcmp(v.a.sub(a).dot(v.a.sub(b)))<=0||
//                d2==0&&dblcmp(v.b.sub(a).dot(v.b.sub(b)))<=0||
//                d3==0&&dblcmp(a.sub(v.a).dot(a.sub(v.b)))<=0||
//                d4==0&&dblcmp(b.sub(v.a).dot(b.sub(v.b)))<=0);
//    }
//    int linecrossseg(line v) //*this seg v line
//    {
//        int d1=dblcmp(b.sub(a).det(v.a.sub(a)));
//        int d2=dblcmp(b.sub(a).det(v.b.sub(a)));
//        if ((d1^d2)==-2)return 2;
//        return (d1==0||d2==0);
//    }
//    int linecrossline(line v)
//    {
//        if ((*this).parallel(v))
//        {
//            return v.relation(a)==3;
//        }
//        return 2;
//    }
//    point crosspoint(line v)
//    {
//        double a1=v.b.sub(v.a).det(a.sub(v.a));
//        double a2=v.b.sub(v.a).det(b.sub(v.a));
//        return point((a.x*a2-b.x*a1)/(a2-a1),(a.y*a2-b.y*a1)/(a2-a1));
//    }
//    double dispointtoline(point p)
//    {
//        return fabs(p.sub(a).det(b.sub(a)))/length();
//    }
//    double dispointtoseg(point p)
//    {
//        if (dblcmp(p.sub(b).dot(a.sub(b)))<0||dblcmp(p.sub(a).dot(b.sub(a)))<0)
//        {
//            return min(p.distance(a),p.distance(b));
//        }
//        return dispointtoline(p);
//    }
//    point lineprog(point p)
//    {
//        return a.add(b.sub(a).mul(b.sub(a).dot(p.sub(a))/b.sub(a).len2()));
//    }
//    point symmetrypoint(point p)
//    {
//        point q=lineprog(p);
//        return point(2*q.x-p.x,2*q.y-p.y);
//    }
};

struct polygon
{
    int n;
    point p[maxp];
    line l[maxp];

    void add(point q)
    {
        p[n++]=q;
    }
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
    void norm()
    {
        point mi=p[0];
        for (int i=1; i<n; i++)mi=min(mi,p[i]);
        sort(p,p+n,cmp(mi));
    }
    bool getdir()
    {
        double sum = 0;
        int i;
        for(i = 0; i < n; i++)
        {
            sum += p[i].det(p[(i+1) % n]);
        }
        if(dblcmp(sum) > 0) return 1;
        return 0;
    }
    void getline()
    {
        for(int i = 0; i < n; i++)
        {
            l[i] = line(p[i],p[(i+1) % n]);
        }
    }

    int relationpoint(point q)
    {
        int i,j;
        for(i = 0; i < n; i++)
        {
            if(p[i] == q)   return 3;
        }
        getline();
        for(i = 0; i < n; i++)
        {
            if(l[i].pointonseg(q))  return 2;
        }

        int cnt = 0;
        for(i = 0; i < n; i++)
        {
            j = (i + 1) % n;
            int k = dblcmp(q.sub(p[j]).det(p[i].sub(p[j])));
            int u = dblcmp(p[i].y - q.y);
            int v = dblcmp(p[j].y - q.y);

            if(k > 0 && u < 0 && v >= 0)    cnt++;
            if(k <0 && v < 0 && u >= 0) cnt--;

        }
        return cnt != 0;
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
    int pointinpolygon(point q)
    {
        if (getdir())reverse(p,p+n);
        if (dblcmp(q.sub(p[0]).det(p[n-1].sub(p[0])))==0)
        {
            if (line(p[n-1],p[0]).pointonseg(q))return n-1;
            return -1;
        }
        int low=1,high=n-2,mid;
        while (low<=high)
        {
            mid=(low+high)>>1;
            if (dblcmp(q.sub(p[0]).det(p[mid].sub(p[0])))>=0&&dblcmp(q.sub(p[0]).det(p[mid+1].sub(p[0])))<0)
            {
                polygon c;
                c.p[0]=p[mid];
                c.p[1]=p[mid+1];
                c.p[2]=p[0];
                c.n=3;
                if (c.relationpoint(q))return mid;
                return -1;
            }
            if (dblcmp(q.sub(p[0]).det(p[mid].sub(p[0])))>0) low=mid+1;
            else high=mid-1;
        }
        return -1;
    }
    double xmult(point a, point b, point c)
    {
        return (b - a).det(c - a);
    }

    int inside_polygon(point q, int on_edge=1)
    {
        point q2;
        int i=0,count;
        while (i<n)
        {
            for(count = i = 0, q2.x = rand()+10000, q2.y = rand() + 10000; i<n; i++)
                if(dblcmp(xmult(q,p[i],p[(i+1)%n]))==0 && (p[i].x-q.x)*(p[(i+1)%n].x-q.x)<eps && (p[i].y-q.y)*(p[(i+1)%n].y-q.y)<eps)
                    return on_edge;
                else if(dblcmp(xmult(q,q2,p[i]))==0)
                    break;
                else if(xmult(q,p[i],q2)*xmult(q,p[(i+1)%n],q2)<-eps&&xmult(p[i],q,p[(i+1)%n])*xmult(p[i],q2,p[(i+1)%n])<-eps)
                    count++;
        }
        return count&1;
    }

};



int main()
{
    int case_no = 0;
    int p,d;
    while(1)
    {
        scanf("%d %d",&d,&p);
        if(!p && !d)    break;
        polygon a,b;
        a.n = 0;
        b.n = 0;
        for(int i = 0; i < d; i++)
        {
            int a_,b_,c_,d_;
            scanf("%d %d %d %d",&a_,&b_,&c_,&d_);

            a.add(point(a_,b_));
            a.add(point(c_,d_));
            a.add(point(a_,d_));
            a.add(point(c_,b_));

        }

        for(int i = 0; i < p; i++)
        {
            int a_,b_,c_,d_;

            scanf("%d %d %d %d",&a_,&b_,&c_,&d_);

            b.add(point(a_,b_));
            b.add(point(c_,d_));
            b.add(point(a_,d_));
            b.add(point(c_,b_));

        }

        polygon c,d;

        a.getconvex(c);
        b.getconvex(d);


        bool ans = 0;

        for(int i = 0; i < c.n; i++)
        {
            int ret = d.inside_polygon(c.p[i],3);
            if(ret == 3 ||  ret == 1)
            {
                ans = true;
                break;
            }
        }

        for(int i = 0; i < d.n; i++)
        {
            int ret = c.inside_polygon(d.p[i],3);
            if(ret == 3 ||  ret == 1)
            {
                ans = true;
                break;
            }
        }

        if(!ans)
        {
            printf("Case %d: It is possible to separate the two groups of vendors.\n",++case_no);
        }
        else
        {
            printf("Case %d: It is not possible to separate the two groups of vendors.\n",++case_no);
        }
    }
    return 0;
}
