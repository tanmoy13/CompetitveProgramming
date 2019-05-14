/**
    Author: Tanmoy Datta

    Solution Idea:
    ~~~~~~~~~~~~~~
        - For circle put the point in circle equation as x and y. If the output value is-
            = 0 then point is on the circle.
            > 0 then point is outside the circle
            < 0 then point is inside the circle

        - For rectangle if rectangles upper left coordinate is x1,y1 and lower right coordinate is x2,y2 and input point is x,y then
            the point is inside the rectangle iff (x>x1 && x<x2 && y>y2 && y<y1)
            otherwise the point is  outside the rectangle.

        - For triangle if the three point is a, b, c and given point is p. Then the point p is inside the circle iff
            area_of_triangle(a,b,c) = area_of_triangle(a,b,p)+area_of_triangle(b,c,p)+area_of_triangle(c,a,p)
            and none of the triangle have area 0..

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

// define X, Y as real(), imag()
typedef complex<double> point;
#define X real()
#define Y imag()

double cross_product(point a, point b)
{
    return (conj(a) * b).Y;
}

struct circle
{
    point p;
    double r;
    int id;
    bool inside_circle(point a)
    {
        double temp=sqr(a.X-p.X)+sqr(a.Y-p.Y)-sqr(r);
        return temp<EPS;
    }
};

struct triangle
{
    point a,b,c;
    int id;
    bool inside_triangle(point p)
    {
        double area_triangle = abs(cross_product(b-a,c-a)*0.5);
        double area1=abs(cross_product(p-a,p-b)*0.5);
        double area2=abs(cross_product(p-b,p-c)*0.5);
        double area3=abs(cross_product(p-c,p-a)*0.5);

        if(area1<=EPS || area2<=EPS || area3<=EPS || fabs(area_triangle-area1-area2-area3)>EPS)
            return false;
        return true;
    }
};


struct rectangle
{
    point ul,lr;
    int id;
    bool inside_rectangle(point p)
    {
        if(p.X>ul.X && p.X<lr.X && p.Y>lr.Y && p.Y<ul.Y) return true;
        return false;
    }
};

int main()
{
    vector<circle>c;
    vector<triangle>t;
    vector<rectangle>r;

    char ch;
    int cnt=0;
    while(cin>>ch && ch!='*')
    {
        cnt++;
        if(ch=='r')
        {
            rectangle temp_r;
            double x1,y1,x2,y2;
            cin>>x1>>y1>>x2>>y2;
            temp_r.ul=point(x1,y1);
            temp_r.lr=point(x2,y2);
            temp_r.id=cnt;
            r.pb(temp_r);

        }
        else if(ch=='c')
        {
            circle temp_c;
            double x1,y1,r;
            cin>>x1>>y1>>r;
            temp_c.p=point(x1,y1);
            temp_c.r=r;
            temp_c.id=cnt;
            c.pb(temp_c);
        }
        else
        {
            double x1,y1,x2,y2,x3,y3;
            cin>>x1>>y1>>x2>>y2>>x3>>y3;
            triangle temp_t;
            temp_t.a=point(x1,y1);
            temp_t.b=point(x2,y2);
            temp_t.c=point(x3,y3);
            temp_t.id=cnt;
            t.pb(temp_t);
        }
    }

    double x,y;
    cnt=0;
    while(cin>>x>>y)
    {
        if(x==9999.9 && y==9999.9) break;
        cnt++;
        vector<int>ans;
        for(int i=0; i<SZ(c); i++)
        {
            if(c[i].inside_circle(point(x,y)))
            {
                ans.pb(c[i].id);
            }
        }

        for(int i=0; i<SZ(r); i++)
        {
            if(r[i].inside_rectangle(point(x,y)))
            {
                ans.pb(r[i].id);
            }
        }

        for(int i=0; i<SZ(t); i++)
        {
            if(t[i].inside_triangle(point(x,y)))
            {
                ans.pb(t[i].id);
            }
        }

        sort(all(ans));

        if(ans.empty())
            cout<<"Point "<<cnt<<" is not contained in any figure"<<endl;

        else
        {
            for(int i=0;i<SZ(ans);i++)
            {
                cout<<"Point "<<cnt<<" is contained in figure "<<ans[i]<<endl;
            }
        }
    }

}
