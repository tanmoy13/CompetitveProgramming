/*
3d point
rotate function is not complete. every else is same as 2d
*/
struct point3
{
    double x,y,z;
    point3()            {                                    }
    point3(double _x,double _y,double _z):
        x(_x),y(_y),z(_z)   {                                    };
    void input()
    {
        scanf("%lf%lf%lf",&x,&y,&z);
    }
    void output()
    {
        printf("%.2lf %.2lf %.2lf\n",x,y,z);
    }
    bool operator==(point3 a)
    {
        return dblcmp(a.x-x)==0&&dblcmp(a.y-y)==0&&dblcmp(a.z-z)==0;
    }
    bool operator<(point3 a)const
    {
        return dblcmp(a.x-x)==0?dblcmp(y-a.y)==0?dblcmp(z-a.z)<0:y<a.y:x<a.x;
    }
    double len()
    {
        return sqrt(len2());
    }
    double len2()
    {
        return x*x+y*y+z*z;
    }
    double distance(point3 p)
    {
        return sqrt((p.x-x)*(p.x-x)+(p.y-y)*(p.y-y)+(p.z-z)*(p.z-z));
    }
    point3 add(point3 p)
    {
        return point3(x+p.x,y+p.y,z+p.z);
    }
    point3 sub(point3 p)
    {
        return point3(x-p.x,y-p.y,z-p.z);
    }
    point3 mul(double d)
    {
        return point3(x*d,y*d,z*d);
    }
    point3 div(double d)
    {
        return point3(x/d,y/d,z/d);
    }
    double dot(point3 p)
    {
        return x*p.x+y*p.y+z*p.z;
    }
    point3 det(point3 p)
    {
        return point3(y*p.z-p.y*z,p.x*z-x*p.z,x*p.y-p.x*y);
    }
    double rad(point3 a,point3 b)
    {
        point3 p=(*this);
        return acos(a.sub(p).dot(b.sub(p))/(a.distance(p)*b.distance(p)));
    }
    point3 trunc(double r)
    {
        r/=len();
        return point3(x*r,y*r,z*r);
    }
    point3 rotate(point3 o,double r)
    {
    }
};

/*
3d line

*/
struct line3
{
    point3 a,b;
    line3()             {                                    }
    line3(point3 _a,point3 _b)
    {
        a=_a;
        b=_b;
    }
    bool operator==(line3 v)
    {
        return (a==v.a)&&(b==v.b);
    }
    void input()
    {
        a.input();
        b.input();
    }
    double length()
    {
        return a.distance(b);
    }
    bool pointonseg(point3 p)
    {
        return dblcmp(p.sub(a).det(p.sub(b)).len())==0&&dblcmp(a.sub(p).dot(b.sub(p)))<=0;
    }
    double dispointtoline(point3 p)
    {
        return b.sub(a).det(p.sub(a)).len()/a.distance(b);
    }
    double dispointtoseg(point3 p)
    {
        if (dblcmp(p.sub(b).dot(a.sub(b)))<0||dblcmp(p.sub(a).dot(b.sub(a)))<0)
        {
            return min(p.distance(a),p.distance(b));
        }
        return dispointtoline(p);
    }
    point3 lineprog(point3 p)
    {
        return a.add(b.sub(a).trunc(b.sub(a).dot(p.sub(a))/b.distance(a)));
    }
    point3 rotate(point3 p,double ang) //p around this vector counterclockwise arg angle
    {
        if (dblcmp((p.sub(a).det(p.sub(b)).len()))==0)return p;
        point3 f1=b.sub(a).det(p.sub(a));
        point3 f2=b.sub(a).det(f1);
        double len=fabs(a.sub(p).det(b.sub(p)).len()/a.distance(b));
        f1=f1.trunc(len);
        f2=f2.trunc(len);
        point3 h=p.add(f2);
        point3 pp=h.add(f1);
        return h.add((p.sub(h)).mul(cos(ang*1.0))).add((pp.sub(h)).mul(sin(ang*1.0)));
    }
};
/*
plane
*/
struct plane
{
    point3 a,b,c,o;
    plane()             {                                    }
    plane(point3 _a,point3 _b,point3 _c)
    {
        a=_a;
        b=_b;
        c=_c;
        o=pvec();
    }
    plane(double _a,double _b,double _c,double _d)
    {
        //ax+by+cz+d=0
        o=point3(_a,_b,_c);
        if (dblcmp(_a)!=0)
        {
            a=point3((-_d-_c-_b)/_a,1,1);
        }
        else if (dblcmp(_b)!=0)
        {
            a=point3(1,(-_d-_c-_a)/_b,1);
        }
        else if (dblcmp(_c)!=0)
        {
            a=point3(1,1,(-_d-_a-_b)/_c);
        }
    }
    void input()
    {
        a.input();
        b.input();
        c.input();
        o=pvec();
    }
    point3 pvec()
    {
        return b.sub(a).det(c.sub(a));
    }
    bool pointonplane(point3 p) //Whether the point is on the plane
    {
        return dblcmp(p.sub(a).dot(o))==0;
    }
    //0 is not
    //1 on the border
    //2 inside
    int pointontriangle(point3 p) //Whether the point is on the space triangle abc
    {
        if (!pointonplane(p))return 0;
        double s=a.sub(b).det(c.sub(b)).len();
        double s1=p.sub(a).det(p.sub(b)).len();
        double s2=p.sub(a).det(p.sub(c)).len();
        double s3=p.sub(b).det(p.sub(c)).len();
        if (dblcmp(s-s1-s2-s3))return 0;
        if (dblcmp(s1)&&dblcmp(s2)&&dblcmp(s3))return 2;
        return 1;
    }
    //Determine the two plane relationship
    //0 intersect
    //1 parallel but not coincident
    //2 coincidence
    bool relationplane(plane f)
    {
        if (dblcmp(o.det(f.o).len()))return 0;
        if (pointonplane(f.a))return 2;
        return 1;
    }
    double angleplane(plane f) //Angle between two planes
    {
        return acos(o.dot(f.o)/(o.len()*f.o.len()));
    }
    double dispoint(point3 p) //Point to plane distance
    {
        return fabs(p.sub(a).dot(o)/o.len());
    }
    point3 pttoplane(point3 p) //Point to the nearest point on the plane something like projection
    {
        line3 u=line3(p,p.add(o));
        crossline(u,p);
        return p;
    }
    int crossline(line3 u,point3 &p) //Intersection of plane and line
    {
        double x=o.dot(u.b.sub(a));
        double y=o.dot(u.a.sub(a));
        double d=x-y;
        if (dblcmp(fabs(d))==0)return 0;
        p=u.a.mul(x).sub(u.b.mul(y)).div(d);
        return 1;
    }
    int crossplane(plane f,line3 &u) //Plane and plane intersection
    {
        point3 oo=o.det(f.o);
        point3 v=o.det(oo);
        double d=fabs(f.o.dot(v));
        if (dblcmp(d)==0)return 0;
        point3 q=a.add(v.mul(f.o.dot(f.a.sub(a))/d));
        u=line3(q,q.add(oo));
        return 1;
    }
};

