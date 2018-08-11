//#include <bits/stdc++.h>
//
//#define pii              pair <int,int>
//#define pll              pair <long long,long long>
//#define sc               scanf
//#define pf               printf
//#define Pi               2*acos(0.0)
//#define ms(a,b)          memset(a, b, sizeof(a))
//#define pb(a)            push_back(a)
//#define MP               make_pair
//#define db               double
//#define ll               long long
//#define EPS              10E-10
//#define ff               first
//#define ss               second
//#define sqr(x)           (x)*(x)
//#define D(x)             cout<<#x " = "<<(x)<<endl
//#define VI               vector <int>
//#define DBG              pf("Hi\n")
//#define MOD              1000000007
//#define CIN              ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
//#define SZ(a)            (int)a.size()
//#define sf(a)            scanf("%d",&a)
//#define sfl(a)           scanf("%lld",&a)
//#define sff(a,b)         scanf("%d %d",&a,&b)
//#define sffl(a,b)        scanf("%lld %lld",&a,&b)
//#define sfff(a,b,c)      scanf("%d %d %d",&a,&b,&c)
//#define sfffl(a,b,c)     scanf("%lld %lld %lld",&a,&b,&c)
//#define stlloop(v)       for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
//#define loop(i,n)        for(int i=0;i<n;i++)
//#define loop1(i,n)       for(int i=1;i<=n;i++)
//#define REP(i,a,b)       for(int i=a;i<b;i++)
//#define RREP(i,a,b)      for(int i=a;i>=b;i--)
//#define TEST_CASE(t)     for(int z=1;z<=t;z++)
//#define PRINT_CASE       printf("Case %d: ",z)
//#define LINE_PRINT_CASE  printf("Case %d:\n",z)
//#define CASE_PRINT       cout<<"Case "<<z<<": "
//#define all(a)           a.begin(),a.end()
//#define intlim           2147483648
//#define infinity         (1<<28)
//#define ull              unsigned long long
//#define gcd(a, b)        __gcd(a, b)
//#define lcm(a, b)        ((a)*((b)/gcd(a,b)))
//
//using namespace std;
//
//
///*----------------------Graph Moves----------------*/
////const int fx[]={+1,-1,+0,+0};
////const int fy[]={+0,+0,+1,-1};
////const int fx[]={+0,+0,+1,-1,-1,+1,-1,+1};   // Kings Move
////const int fy[]={-1,+1,+0,+0,+1,+1,-1,-1};  // Kings Move
////const int fx[]={-2, -2, -1, -1,  1,  1,  2,  2};  // Knights Move
////const int fy[]={-1,  1, -2,  2, -2,  2, -1,  1}; // Knights Move
///*------------------------------------------------*/
//
///*-----------------------Bitmask------------------*/
////int Set(int N,int pos){return N=N | (1<<pos);}
////int reset(int N,int pos){return N= N & ~(1<<pos);}
////bool check(int N,int pos){return (bool)(N & (1<<pos));}
///*------------------------------------------------*/
//
//pii ara[105];
//
//bool dp[105][105][105];
//int cases[105][105][105];
//int zz=0;
//
//int max_work, n;
//
//bool func(int idx, int p1, int p2)
//{
//    if(p1==0 && p2==0) return true;
//    if(idx>=n) return false;
//    bool &ret=dp[idx][p1][p2];
//    int &cas=cases[idx][p1][p2];
//    if(cas==zz) return ret;
//    cas=zz;
//    ret=0;
//    for(int i=0;i<=p1 && i*ara[idx].ff<=max_work;i++)
//    {
//        int remaining_time=(max_work-(i*ara[idx].ff));
//        int project2=remaining_time/ara[idx].ss;
//        project2=min(project2,p2);
//        ret|=func(idx+1,p1-i,p2-project2);
//        if(ret) break;
//    }
//    return ret;
//}
//
//int main()
//{
//
////    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//
//    int t;
//    sf(t);
//    TEST_CASE(t)
//    {
//        int m;
//        sff(n,m);
//        for(int i=0;i<n;i++) sff(ara[i].ff,ara[i].ss);
//
////        int lo=0,hi=ara[0].ff*m+ara[0].ss*m;
//        int lo=0,hi=50000;
//        int ans=0;
//        while(lo<=hi)
//        {
//            zz++;
//            int mid=(lo+hi)/2;
//            max_work=mid;
//            if(func(0,m,m))
//            {
//                ans=mid;
//                hi=mid-1;
//            }
//            else
//                lo=mid+1;
//        }
//
//        PRINT_CASE;
//        printf("%d\n",ans);
//
//    }
//
//    return 0;
//}



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

pii ara[105];

bool dp[101][101][101];
int cases[101][101][101];
int zz=0;

int max_work, n;

bool func(int idx, int p1, int p2)
{
    if(p1==0 && p2==0) return true;
    if(idx>=n) return false;
    bool &ret=dp[idx][p1][p2];
    int &cas=cases[idx][p1][p2];
    if(cas==zz) return ret;
    cas=zz;
    ret=0;
    for(int i=0; i<=p1 && i*ara[idx].ff<=max_work; i++)
    {
        int remaining_time=(max_work-(i*ara[idx].ff));
        int project2=remaining_time/ara[idx].ss;
        project2=min(project2,p2);
        ret|=func(idx+1,p1-i,p2-project2);
        if(ret) break;
    }
    return ret;
}

int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);

    int t;
    sf(t);
    TEST_CASE(t)
    {
        int m;
        sff(n,m);
        for(int i=0; i<n; i++) sff(ara[i].ff,ara[i].ss);

        int lo=0,hi=5000;
        int ans=0;
        while(lo<=hi)
        {
            zz++;
            int mid=(lo+hi)/2;
            max_work=mid;
            if(func(0,m,m))
            {
                ans=mid;
                hi=mid-1;
            }
            else
                lo=mid+1;
        }

        PRINT_CASE;
        printf("%d\n",ans);

    }

    return 0;
}
