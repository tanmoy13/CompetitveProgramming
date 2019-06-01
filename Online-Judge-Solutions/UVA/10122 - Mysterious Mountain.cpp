/**
    Author: Tanmoy Datta

    Solution Idea:
    ~~~~~~~~~~~~~~
        - Binary search over the answer.
        - Build graph according to binary search mid value.
        - Make sure that the connecting line never goes up to the hill.

*/

#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

#define pii              pair <int,int>
#define pll              pair <long long,long long>

#define pb(a)            push_back(a)
#define MP               make_pair
#define db               double
#define ll               long long

#define ff               first
#define ss               second
#define sqr(x)           ((x)*(x))
#define SZ(a)            (int)a.size()
#define sf(a)            scanf("%d",&a)
#define sfl(a)           scanf("%lld",&a)
#define sff(a,b)         scanf("%d %d",&a,&b)
#define sffl(a,b)        scanf("%lld %lld",&a,&b)
#define sfff(a,b,c)      scanf("%d %d %d",&a,&b,&c)
#define sfffl(a,b,c)     scanf("%lld %lld %lld",&a,&b,&c)

using namespace std;


const double eps=1e-8;


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

    double distance(point p) ///gives distance from p
    {
        return hypot(x - p.x,y - p.y);
    }

    point sub(point p)
    {
        return point(x - p.x, y - p.y);
    }

    double det(point p) ///cross product of 2d points
    {
        return x*p.y-y*p.x;
    }
};


struct line
{
    point a,b;
    line(point _a,point _b) ///line through a and b
    {
        a=_a;
        b=_b;
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

    bool parallel(line v) ///returns 1 if they are parallel otherwise 0
    {
        return dblcmp(b.sub(a).det(v.b.sub(v.a)))==0;
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
};

vector<point>v;
vector<pair<pii,int> > mans;
vector<pair<int,int> > ranges;


#define mx 205

vector<int>g[mx];

int cnt_node=0;
int vis[mx];

int n;

void init_range()
{
    line xaxis(point(0,0),point(10000,0));
    for(int i=0; i<SZ(v); i++)
    {
        int maxi=0;
        int mini=10000;
        for(int j=0; j<i; j++)
        {
            if(v[j].y<v[i].y)
            {
                line l1(v[i],v[j]);
                if(xaxis.linecrossline(l1)==2)
                {
                    point p=xaxis.crosspoint(l1);
                    maxi=max(maxi,int(ceil(p.x)));
                }
            }
        }
        for(int j=i+1; j<SZ(v); j++)
        {
            if(v[j].y<v[i].y)
            {
                line l1(v[i],v[j]);
                if(xaxis.linecrossline(l1))
                {
                    point p=xaxis.crosspoint(l1);
                    mini=min(mini,int(floor(p.x)));
                }
            }
        }
        ranges.pb(MP(maxi,mini));
    }
}

double ask1(int id1, int id2, double pos)
{
    double dis1=point(pos,0).distance(point(mans[id1].ss,0));
    double t1=dis1/mans[id1].ff.ss;
    double dis2=v[id2].distance(point(pos,0));
    double t2=dis2/mans[id1].ff.ff;
    return t1+t2;
}

double get_cost(int id1, int id2)
{
    int lo=ranges[id2].ff-1,hi=ranges[id2].ss;

    double ret=1e9;

    while(hi-lo>1)
    {
        int mid1=(lo+hi)/2;
        int mid2=mid1+1;

        double f1=ask1(id1,id2,mid1);
        double f2=ask1(id1,id2,mid2);

        if(f1<f2)
        {
            hi=mid1;
        }
        else
        {
            lo=mid1;
        }
    }
    return ask1(id1,id2,lo+1);
}

int cc;
int match[mx];
void allclear()
{
    for(int i=0; i<mx; i++)
    {
        g[i].clear();
        match[i]=-1;
        vis[i]=0;
    }
    cc=1;
    cnt_node=0;
}

void build_graph(double mid)
{
    allclear();

    for(int i=0; i<SZ(mans); i++)
    {
        for(int j=1,k=0; j<SZ(v)-1; j++,k++)
        {
            double cost=get_cost(i,j);
            if(dblcmp(mid-cost)>=0)
            {
                g[i].pb(SZ(mans)+j);
                g[SZ(mans)+j].pb(i);
            }
        }
    }
    for(int i=0; i<SZ(mans); i++)
    {
        if(SZ(g[i]))
            cnt_node++;
    }
}

bool khun(int u)
{
    if(vis[u]==cc) return false;
    vis[u]=cc;
    for(int i=0; i<SZ(g[u]); i++)
    {
        int vv=g[u][i];
        if(match[vv]==-1)
        {
            match[vv]=u;
            match[u]=vv;
            return true;
        }
    }

    for(int i=0; i<SZ(g[u]); i++)
    {
        int vv=g[u][i];
        if(khun(match[vv]))
        {
            match[vv]=u;
            match[u]=vv;
            return true;
        }
    }
    return false;
}

bool ask(double mid)
{
    build_graph(mid);
    if(cnt_node<n) return false;
    cnt_node=0;
    for(int i=0; i<SZ(mans); i++)
    {
        if(match[i]==-1)
        {
            cc++;
            int ret=khun(i);
            cnt_node+=ret;
        }
    }
    return cnt_node==n;
}



int main()
{
    int zz=0;
    while(sf(n) && n)
    {
        v.clear();
        mans.clear();
        ranges.clear();
        for(int i=0; i<n+2; i++)
        {
            int a,b;
            sff(a,b);
            v.pb(point(a,b));
        }


        for(int i=0; i<n; i++)
        {
            int a,b,c;
            sfff(a,b,c);
            mans.pb(MP(pii(a,b),c));
        }

        init_range();


        double lo=0.0,hi=1e9;

        for(int i=0; i<100; i++)
        {
            double mid=(lo+hi)/2;
            bool res=ask(mid);
            if(res)
                hi=mid;
            else
                lo=mid;
        }

        printf("%.2lf\n",lo);
    }

    return 0;
}
