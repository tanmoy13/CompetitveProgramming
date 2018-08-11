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

ll n,m,z;

ull dp[1002][1002];
int cases[1002][1002];

ull func(int r, int c)
{
    if(c>=m || r>=n) return (ull)0;
    ull &ret=dp[r][c];
    int &cas=cases[r][c];
    if(cas==z) return ret;
    cas=z;
    ret=0;
    ull baki_col=m-c;
    ull baki_row=n-r;
    ull x=gcd((ull)r,(ull)c)-1;
    x*=(baki_row*baki_col);
    ret+=x;
    func(r+1,c);
    func(r,c+1);
    return ret;
}

int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);
    while(sffl(n,m) && (n || m))
    {
        z++;
        n++;
        m++;
        ull point=(n)*(m);
        ull ans=point*(point-1)*(point-2);
        ans/=6;
        ull bad_col=(n*(n-1)*(n-2))/6;
        bad_col*=m;
        ull bad_row=(m*(m-1)*(m-2))/6;
        bad_row*=n;
        ans-=(bad_row+bad_col); // Subtracting co-linear triable of rows and cols
        func(1,1);
        ull temp=0;
//        for(int i=1; i<n; i++,cout<<endl)
//            for(int j=1; j<m; j++)
//                {
//                    cout<<dp[i][j]<<" ";
//                }
        for(int i=1; i<n; i++)
            for(int j=1; j<m; j++)
            {
                temp+=dp[i][j];
            }
        ans-=temp;
        ans-=temp; // This one is for opposite direction
        PRINT_CASE;
        printf("%llu\n",ans);
    }

    return 0;
}
