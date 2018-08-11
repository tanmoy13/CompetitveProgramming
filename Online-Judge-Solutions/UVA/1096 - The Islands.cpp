#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

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
#define D(x)             cerr<<#x " = "<<(x)<<endl
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

int n,a,b;
vector<pii>v;
double dp[102][102][3][3];
int cases[102][102][3][3];
int path[102][102][3][3];
int cas;

double dist(int i, int j)
{
    return hypot(v[i].ff-v[j].ff,v[i].ss-v[j].ss);
}

double func(int i, int j, int x, int y)
{
//    if(x==y && x!=0) return 1000000000000.0;
    int v=max(i,j)+1;
    if(v==n-1)
        return dist(i,v)+dist(j,v);
    int &cc=cases[i][j][x][y];
    double &ret=dp[i][j][x][y];
    if(cc==cas) return ret;
    cc=cas;
    double p=1000000000000.0,q=1000000000000.0;
    if(v==a)
    {
        if(y==2 || y==0)
            p=dist(i,v)+func(v,j,1,y);
        if(y==1 || y==0)
            q=dist(j,v)+func(i,v,2,y);
    }
    else if(v==b)
    {
        if(x==2 || x==0)
            p=dist(i,v)+func(v,j,x,1);
        if(x==1 || x==0)
            q=dist(j,v)+func(i,v,x,2);
    }
    else
    {
        p=dist(i,v)+func(v,j,x,y);
        q=dist(j,v)+func(i,v,x,y);
    }
    if(p<=q)
    {
        path[i][j][x][y]=1;
    }
    else
        path[i][j][x][y]=2;
    return ret=min(p,q);
}

void print_path(int i, int j, int x, int y, vector<int>&up, vector<int>&down)
{
    int v=max(i,j)+1;
    if(v==n-1)
    {
        up.pb(i);
        up.pb(n-1);
        down.pb(j);
        return;
    }
    if(path[i][j][x][y]==1)
    {
        up.pb(i);
        if(v==a)
            print_path(v,j,1,y,up,down);
        else if(v==b)
            print_path(v,j,x,1,up,down);
        else
            print_path(v,j,x,y,up,down);
    }
    else if(path[i][j][x][y]==2)
    {
        down.pb(j);
        if(v==a)
            print_path(i,v,2,y,up,down);
        else if(v==b)
            print_path(i,v,x,2,up,down);
        else
            print_path(i,v,x,y,up,down);
    }
}


int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);
//    D(hypot(3,5));
    int z=0;
    while(sfff(n,a,b))
    {
        if(n==0 && a==0 && b==0)
            break;
        v.clear();
        for(int i=0; i<n; i++)
        {
            int p,q;
            sff(p,q);
            v.pb(pii(p,q));
        }

        sort(all(v));
        cas++;
        z++;
        ms(path,0);
        double ans=func(0,0,0,0);
        vector<int> up,down,aaa;
        print_path(0,0,0,0,up,down);
        PRINT_CASE;
        printf("%.2lf\n",ans);
        reverse(all(down));
        printf("%d",up[0]);
        aaa.pb(up[0]);
        for(int i=1; i<SZ(up); i++)
            printf(" %d",up[i]),aaa.pb(up[i]);
        for(int i=0; i<SZ(down); i++)
            printf(" %d",down[i]),aaa.pb(down[i]);
        printf("\n");
//        double test=0;
//        for(int i=1;i<SZ(aaa);i++)
//            test+=dist(aaa[i],aaa[i-1]);
//        printf("%.2lf\n",test);

    }

    return 0;
}

