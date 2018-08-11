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
int Set(int N,int pos){return N=N | (1<<pos);}
int reset(int N,int pos){return N= N & ~(1<<pos);}
bool check(int N,int pos){return (bool)(N & (1<<pos));}
/*------------------------------------------------*/

int n;

int ara[]={2,3,5,7,11,13,17,19,23,29,31,37};
bool vis[100];

bool test,test1;

void func(int idx, int mask, vector<int>v, int last)
{
//    dp[mask]=1;
    if(idx>=n)
    {
        if(vis[last+1]==0) return;
//        for(int i=1;i<n;i++)
//        {
//            if(vis[v[i]+v[i-1]]==0) return;
//        }
//        if(vis[v[0]+v[n-1]]==0) return;
//
        printf("%d",v[0]);
        for(int i=1;i<n;i++)
            printf(" %d",v[i]);
        printf("\n");
        test1=1;
    }

    for(int i=1;i<=n;i++)
    {
        if(check(mask,i)==0 && vis[last+i])
        {
            vector<int>temp=v;
            temp.pb(i);
            func(idx+1,Set(mask,i),temp,i);
        }
    }

}


int main()
{

//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);

    int z=0;
    for(int i=0;i<12;i++)
        vis[ara[i]]=1;
    test=0;
    while(sf(n)==1)
    {
        if(test)
            printf("\n");
        test=1;
        test1=0;
        z++;
        LINE_PRINT_CASE;
        vector<int>v;
        v.pb(1);
        func(1,Set(0,1),v,1);
//        if(test1==0)
//        printf("\n");
    }
    return 0;
}
