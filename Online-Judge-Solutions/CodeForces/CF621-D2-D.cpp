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
#define EPS              10E-8
#define ff               first
#define ss               second
#define sqr(x)           (x)*(x)
#define D(x)             cerr<<#x " = "<<(x)<<endl
#define VI               vector <int>
#define DBG              pf("Hi\n")
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

#define pdi pair<double,int>

vector<double>v;
vector<int>dir[15];
double ans=0.0;
vector<int>ansv;
int id=0;
bool flag=0;

double call(vector<int>temp)
{
    if(flag)
    {
        if(temp[3]==0)
        {
            return pow(v[temp[0]],pow(v[temp[1]],v[temp[2]]));
        }
        else
        {
            double aa=pow(v[temp[0]],v[temp[1]]);
            return pow(aa,v[temp[2]]);
        }
    }
    double x=0.0;
    if(temp[3]==0)
    {
        double y=log(v[temp[0]]);
        if(y<0.0)
            return -100000.0;
        x=v[temp[2]]*log(v[temp[1]])+log(log(v[temp[0]]));
    }
    else
    {
        double y=log(v[temp[0]]);
        if(y<0.0)
            return -100000.0;
//        else
        x=log(v[temp[1]])+log(v[temp[2]])+log(log(v[temp[0]]));
    }
    return x;
}

int main()
{
//#ifndef ONLINE_JUDGE
////    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif



    for(int i=0; i<3; i++)
    {
        double a;
        cin>>a;
//        a*=10.0;
        v.pb(a);
    }

    if(v[0]<2.0 && v[1]<2.0 && v[2]<2.0)
        flag=1;

    dir[0]= {0,1,2,0};
    dir[1]= {0,2,1,0};
    dir[2]= {0,1,2,1};
    dir[3]= {0,2,1,1};
    dir[4]= {1,0,2,0};
    dir[5]= {1,2,0,0};
    dir[6]= {1,0,2,1};
    dir[7]= {1,2,0,1};
    dir[8]= {2,0,1,0};
    dir[9]= {2,1,0,0};
    dir[10]= {2,0,1,1};
    dir[11]= {2,1,0,1};

    double ans=-1000000000.0;

    for(int i=0; i<12; i++)
    {
        double x=call(dir[i]);
        if(x-ans>EPS)
        {
            ans=x;
            ansv=dir[i];
        }
    }

    if(ansv[3]==0)
    {
        cout<<char('x'+ansv[0])<<"^"<<char('x'+ansv[1])<<"^"<<char('x'+ansv[2])<<endl;
    }
    else
    {
        cout<<"("<<char('x'+ansv[0])<<"^"<<char('x'+ansv[1])<<")^"<<char('x'+ansv[2])<<endl;
    }

    return 0;
}
