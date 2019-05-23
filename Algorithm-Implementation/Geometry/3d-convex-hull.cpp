
/*
HDU 3662
Find the number of polygons on the convex hull surface
*/

#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<math.h>
#include<stdlib.h>
using namespace std;
const int MAXN=550;
const double eps=1e-8;

struct Point
{
    double x,y,z;
    Point(){}

    Point(double xx,double yy,double zz):x(xx),y(yy),z(zz){}

    //Difference between two vectors
    Point operator -(const Point p1)
    {
        return Point(x-p1.x,y-p1.y,z-p1.z);
    }

    //Sum of two vectors
    Point operator +(const Point p1)
    {
        return Point(x+p1.x,y+p1.y,z+p1.z);
    }

    //Cross product
    Point operator *(const Point p)
    {
        return Point(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);
    }
    //scalar multiplication
    Point operator *(double d)
    {
        return Point(x*d,y*d,z*d);
    }
    //scalar division
    Point operator / (double d)
    {
        return Point(x/d,y/d,z/d);
    }

    //Dot product
    double  operator ^(Point p)
    {
        return (x*p.x+y*p.y+z*p.z);
    }
};

struct CH3D
{
    struct face
    {
        //Indicates the number of three points on one face of the convex hull
        int a,b,c;
        //Indicates whether the face belongs to the face on the final convex hull
        bool ok;
    };
    //Initial vertex number
    int n;
    //Initial vertex
    Point P[MAXN];
    //Convex hull surface triangle number
    int num;
    //Convex surface triangle
    face F[8*MAXN];
    //Convex surface triangle
    int g[MAXN][MAXN];
    //Vector length
    double vlen(Point a)
    {
        return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
    }
    //Crossing or cross product
    Point cross(const Point &a,const Point &b,const Point &c)
    {
        return Point((b.y-a.y)*(c.z-a.z)-(b.z-a.z)*(c.y-a.y),
                     (b.z-a.z)*(c.x-a.x)-(b.x-a.x)*(c.z-a.z),
                     (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x)
                     );
    }
    //Triangle area * 2
    double area(Point a,Point b,Point c)
    {
        return vlen((b-a)*(c-a));
    }
    //Tetrahedral directed volume * 6
    double volume(Point a,Point b,Point c,Point d)
    {
        return (b-a)*(c-a)^(d-a);
    }
    //Positive: point in the same direction
    double dblcmp(Point &p,face &f)
    {
        Point m=P[f.b]-P[f.a];
        Point n=P[f.c]-P[f.a];
        Point t=p-P[f.a];
        return (m*n)^t;
    }
    void deal(int p,int a,int b)
    {
        int f=g[a][b];//Search for another plane adjacent to the edge
        face add;
        if(F[f].ok)
        {
            if(dblcmp(P[p],F[f])>eps)
              dfs(p,f);
            else
            {
                add.a=b;
                add.b=a;
                add.c=p;//Pay attention to the order here, to be right-handed
                add.ok=true;
                g[p][b]=g[a][p]=g[b][a]=num;
                F[num++]=add;
            }
        }
    }
    void dfs(int p,int now)//Recursively search all faces that should be removed from the convex hull
    {
         F[now].ok=0;
         deal(p,F[now].b,F[now].a);
         deal(p,F[now].c,F[now].b);
         deal(p,F[now].a,F[now].c);
    }
    bool same(int s,int t)
    {
        Point &a=P[F[s].a];
        Point &b=P[F[s].b];
        Point &c=P[F[s].c];
        return fabs(volume(a,b,c,P[F[t].a]))<eps &&
               fabs(volume(a,b,c,P[F[t].b]))<eps &&
               fabs(volume(a,b,c,P[F[t].c]))<eps;
    }
    //Building a three-dimensional convex hull
    void create()
    {
        int i,j,tmp;
        face add;

        num=0;
        if(n<4)return;
    //**********************************************
        //This paragraph is to ensure that the first four points are not coplanar
        bool flag=true;
        for(i=1;i<n;i++)
        {
            if(vlen(P[0]-P[i])>eps)
            {
                swap(P[1],P[i]);
                flag=false;
                break;
            }
        }
        if(flag)return;
        flag=true;
        //Make the first three points not collinear
        for(i=2;i<n;i++)
        {
            if(vlen((P[0]-P[1])*(P[1]-P[i]))>eps)
            {
                swap(P[2],P[i]);
                flag=false;
                break;
            }
        }
        if(flag)return;
        flag=true;
        // make the first four points are not coplanar
        for(int i=3;i<n;i++)
        {
            if(fabs((P[0]-P[1])*(P[1]-P[2])^(P[0]-P[i]))>eps)
            {
                swap(P[3],P[i]);
                flag=false;
                break;
            }
        }
        if(flag)return;
    //*****************************************
        for(i=0;i<4;i++)
        {
            add.a=(i+1)%4;
            add.b=(i+2)%4;
            add.c=(i+3)%4;
            add.ok=true;
            if(dblcmp(P[i],add)>0)swap(add.b,add.c);
            g[add.a][add.b]=g[add.b][add.c]=g[add.c][add.a]=num;
            F[num++]=add;
        }
        for(i=4;i<n;i++)
        {
            for(j=0;j<num;j++)
            {
                if(F[j].ok&&dblcmp(P[i],F[j])>eps)
                {
                    dfs(i,j);
                    break;
                }
            }
        }
        tmp=num;
        for(i=num=0;i<tmp;i++)
          if(F[i].ok)
            F[num++]=F[i];

    }
    // surface area 
    double area()
    {
        double res=0;
        if(n==3)
        {
            Point p=cross(P[0],P[1],P[2]);
            res=vlen(p)/2.0;
            return res;
        }
        for(int i=0;i<num;i++)
          res+=area(P[F[i].a],P[F[i].b],P[F[i].c]);
        return res/2.0;
    }
    double volume()
    {
        double res=0;
        Point tmp(0,0,0);
        for(int i=0;i<num;i++)
           res+=volume(tmp,P[F[i].a],P[F[i].b],P[F[i].c]);
        return fabs(res/6.0);
    }
    // The number of triangular surface
    int triangle()
    {
        return num;
    }
    // Surface Polygon number 
    int polygon()
    {
        int i,j,res,flag;
        for(i=res=0;i<num;i++)
        {
            flag=1;
            for(j=0;j<i;j++)
              if(same(i,j))
              {
                  flag=0;
                  break;
              }
            res+=flag;
        }
        return res;
    }
    // three-dimensional convex hull focus
    Point barycenter()
    {
        Point ans(0,0,0),o(0,0,0);
        double all=0;
        for(int i=0;i<num;i++)
        {
            double vol=volume(o,P[F[i].a],P[F[i].b],P[F[i].c]);
            ans=ans+(o+P[F[i].a]+P[F[i].b]+P[F[i].c])/4.0*vol;
            all+=vol;
        }
        ans=ans/all;
        return ans;
    }
    // point to the surface
    double ptoface(Point p,int i)
    {
        return fabs(volume(P[F[i].a],P[F[i].b],P[F[i].c],p)/vlen((P[F[i].b]-P[F[i].a])*(P[F[i].c]-P[F[i].a])));
    }
};
CH3D hull;

int main()
{
   // freopen("in.txt","r",stdin);
   // freopen("out.txt","w",stdout);
    while(scanf("%d",&hull.n)==1)
    {
        for(int i=0;i<hull.n;i++)
        {
            scanf("%lf%lf%lf",&hull.P[i].x,&hull.P[i].y,&hull.P[i].z);
        }
        hull.create();
        printf("%d\n",hull.polygon());
    }
    return 0;
}
